// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "absl/log/absl_log.h"
#include "absl/strings/str_cat.h"
#include "mediapipe/calculators/util/annotation_overlay_calculator.pb.h"
#include "mediapipe/calculators/util/render_and_points.pb.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/calculator_options.pb.h"
#include "mediapipe/framework/formats/image.h"
#include "mediapipe/framework/formats/image_format.pb.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/formats/image_opencv.h"
#include "mediapipe/framework/formats/video_stream_header.h"
#include "mediapipe/framework/port/opencv_core_inc.h"
#include "mediapipe/framework/port/opencv_imgproc_inc.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/port/vector.h"
#include "mediapipe/util/annotation_renderer.h"
#include "mediapipe/util/color.pb.h"

#include <memory>

#if !MEDIAPIPE_DISABLE_GPU
    #include "mediapipe/calculators/util/image_data.pb.h"
    #include "mediapipe/gpu/gl_calculator_helper.h"
    #include "mediapipe/gpu/gl_simple_shaders.h"
    #include "mediapipe/gpu/gpu_buffer.h"
    #include "mediapipe/gpu/gpu_buffer_format.h"
    #include "mediapipe/gpu/shader_util.h"
#endif // !MEDIAPIPE_DISABLE_GPU

namespace mediapipe {

namespace {

    constexpr char kVectorTag[]     = "VECTOR";
    constexpr char kGpuBufferTag[]  = "IMAGE_GPU";
    constexpr char kImageFrameTag[] = "IMAGE";
    constexpr char kImageTag[]      = "UIMAGE"; // Universal Image
    constexpr char kHandPointsTag[] = "HAND_POINTS";
#if !MEDIAPIPE_DISABLE_GPU
    constexpr char kImageDataTag[] = "IMAGE_DATA";
#endif
    enum { ATTRIB_VERTEX, ATTRIB_TEXTURE_POSITION, NUM_ATTRIBUTES };

    // Round up n to next multiple of m.
    size_t RoundUp(size_t n, size_t m) {
        return ((n + m - 1) / m) * m;
    } // NOLINT

    // When using GPU, this color will become transparent when the calculator
    // merges the annotation overlay with the image frame. As a result, drawing in
    // this color is not supported and it should be set to something unlikely used.
    constexpr uchar kAnnotationBackgroundColor = 2; // Grayscale value.

    // Future Image type.
    inline bool HasImageTag(mediapipe::CalculatorContext* cc) {
        return cc->Inputs().HasTag(kImageTag);
    }
} // namespace

// A calculator for rendering data on images.
//
// Inputs:
//  1. IMAGE or IMAGE_GPU (optional): An ImageFrame (or GpuBuffer),
//     or UIMAGE (an Image).
//     containing the input image.
//     If output is CPU, and input isn't provided, the renderer creates a
//     blank canvas with the width, height and color provided in the options.
//  2. RenderData proto on variable number of input streams. All the RenderData
//     at a particular timestamp is drawn on the image in the order of their
//     input streams. No tags required.
//  3. std::vector<RenderData> on variable number of input streams. RenderData
//     objects at a particular timestamp are drawn on the image in order of the
//     input vector items. These input streams are tagged with "VECTOR".
//
// Output:
//  1. IMAGE or IMAGE_GPU: A rendered ImageFrame (or GpuBuffer),
//     or UIMAGE (an Image).
//  Note: Output types should match their corresponding input stream type.
//
// For CPU input frames, only SRGBA, SRGB and GRAY8 format are supported. The
// output format is the same as input except for GRAY8 where the output is in
// SRGB to support annotations in color.
//
// For GPU input frames, only 4-channel images are supported.
//
// Note: When using GPU, drawing with color kAnnotationBackgroundColor (defined
// above) is not supported.
//
// Example config (CPU):
// node {
//   calculator: "AnnotationOverlayCalculator"
//   input_stream: "IMAGE:image_frames"
//   input_stream: "render_data_1"
//   input_stream: "render_data_2"
//   input_stream: "render_data_3"
//   input_stream: "VECTOR:0:render_data_vec_0"
//   input_stream: "VECTOR:1:render_data_vec_1"
//   output_stream: "IMAGE:decorated_frames"
//   options {
//     [mediapipe.AnnotationOverlayCalculatorOptions.ext] {
//     }
//   }
// }
//
// Example config (GPU):
// node {
//   calculator: "AnnotationOverlayCalculator"
//   input_stream: "IMAGE_GPU:image_frames"
//   input_stream: "render_data_1"
//   input_stream: "render_data_2"
//   input_stream: "render_data_3"
//   input_stream: "VECTOR:0:render_data_vec_0"
//   input_stream: "VECTOR:1:render_data_vec_1"
//   output_stream: "IMAGE_GPU:decorated_frames"
//   options {
//     [mediapipe.AnnotationOverlayCalculatorOptions.ext] {
//     }
//   }
// }
//
class AnnotationOverlayCalculator : public CalculatorBase {
public:
    AnnotationOverlayCalculator()           = default;
    ~AnnotationOverlayCalculator() override = default;

    static absl::Status GetContract(CalculatorContract* cc);

    // From Calculator.
    absl::Status Open(CalculatorContext* cc) override;
    absl::Status Process(CalculatorContext* cc) override;
    absl::Status Close(CalculatorContext* cc) override;

private:
    template<typename Type, const char* Tag>
    absl::Status CreateRenderTargetCpu(CalculatorContext* cc, std::unique_ptr<cv::Mat>& image_mat,
                                       ImageFormat::Format* target_format);

    template<typename Type, const char* Tag>
    absl::Status CreateRenderTargetCpuFromGpu(CalculatorContext* cc, std::unique_ptr<cv::Mat>& image_mat,
                                              ImageFormat::Format* target_format);

    absl::Status RenderToCpu(CalculatorContext* cc, const ImageFormat::Format& target_format, uchar* data_image);

    absl::Status GlRender(CalculatorContext* cc);
    template<typename Type, const char* Tag>
    absl::Status GlSetup(CalculatorContext* cc);

    // Options for the calculator.
    AnnotationOverlayCalculatorOptions options_;

    // Underlying helper renderer library.
    std::unique_ptr<AnnotationRenderer> renderer_;

    // Indicates if image frame is available as input.
    bool image_frame_available_ = false;

    bool use_gpu_         = false;
    bool gpu_initialized_ = false;
#if !MEDIAPIPE_DISABLE_GPU
    mediapipe::GlCalculatorHelper gpu_helper_;
    GLuint                        program_       = 0;
    GLuint                        image_mat_tex_ = 0; // Overlay drawing image for GPU.
    int                           width_         = 0;
    int                           height_        = 0;
    int                           width_canvas_  = 0; // Size of overlay drawing texture canvas.
    int                           height_canvas_ = 0;
#endif // MEDIAPIPE_DISABLE_GPU
};

REGISTER_CALCULATOR(AnnotationOverlayCalculator);

absl::Status AnnotationOverlayCalculator::GetContract(CalculatorContract* cc) {
    RET_CHECK_GE(cc->Inputs().NumEntries(), 1);

    bool use_gpu = false;

    RET_CHECK(cc->Inputs().HasTag(kImageFrameTag) + cc->Inputs().HasTag(kGpuBufferTag) + cc->Inputs().HasTag(kImageTag) <= 1);
    RET_CHECK(cc->Outputs().HasTag(kImageFrameTag) + cc->Outputs().HasTag(kImageTag) == 1);

    // Input image to render onto copy of. Should be same type as output.
#if !MEDIAPIPE_DISABLE_GPU
    if (cc->Inputs().HasTag(kGpuBufferTag)) {
        cc->Inputs().Tag(kGpuBufferTag).Set<mediapipe::GpuBuffer>();
        RET_CHECK(cc->Outputs().HasTag(kImageFrameTag));
        use_gpu = true;
    }
#endif
    if (cc->Inputs().HasTag(kImageFrameTag)) {
        cc->Inputs().Tag(kImageFrameTag).Set<ImageFrame>();
        RET_CHECK(cc->Outputs().HasTag(kImageFrameTag));
    }

    if (cc->Inputs().HasTag(kImageTag)) {
        cc->Inputs().Tag(kImageTag).Set<mediapipe::Image>();
        RET_CHECK(cc->Outputs().HasTag(kImageTag));
#if !MEDIAPIPE_DISABLE_GPU
        use_gpu = true; // Prepare GPU resources because images can come in on GPU.
#endif
    }

    // Data streams to render.
    for (CollectionItemId id = cc->Inputs().BeginId(); id < cc->Inputs().EndId(); ++id) {
        auto        tag_and_index = cc->Inputs().TagAndIndexFromId(id);
        std::string tag           = tag_and_index.first;
        if (tag == kVectorTag) {
            cc->Inputs().Get(id).Set<std::vector<RenderPointData>>();
        } else if (tag.empty()) {
            // Empty tag defaults to accepting a single object of RenderData type.
            cc->Inputs().Get(id).Set<RenderData>();
        }
    }

    // Rendered image. Should be same type as input.
#if !MEDIAPIPE_DISABLE_GPU
    RET_CHECK(cc->Inputs().HasTag(kImageDataTag));
    cc->Inputs().Tag(kImageDataTag).Set<mediapipe::ImageData>();
#endif // !MEDIAPIPE_DISABLE_GPU
    if (cc->Outputs().HasTag(kImageFrameTag)) {
        cc->Outputs().Tag(kImageFrameTag).Set<ImageFrame>();
    }
    if (cc->Outputs().HasTag(kImageTag)) {
        cc->Outputs().Tag(kImageTag).Set<mediapipe::Image>();
    }
    cc->Outputs().Tag(kHandPointsTag).Set<std::vector<Points>>();
    if (use_gpu) {
#if !MEDIAPIPE_DISABLE_GPU
        MP_RETURN_IF_ERROR(mediapipe::GlCalculatorHelper::UpdateContract(cc));
#endif // !MEDIAPIPE_DISABLE_GPU
    }

    return absl::OkStatus();
}

absl::Status AnnotationOverlayCalculator::Open(CalculatorContext* cc) {
    cc->SetOffset(TimestampDiff(0));

    options_ = cc->Options<AnnotationOverlayCalculatorOptions>();
    if (cc->Inputs().HasTag(kGpuBufferTag) || HasImageTag(cc)) {
#if !MEDIAPIPE_DISABLE_GPU
        use_gpu_ = true;
#endif // !MEDIAPIPE_DISABLE_GPU
    }

    if (cc->Inputs().HasTag(kGpuBufferTag) || cc->Inputs().HasTag(kImageFrameTag) || HasImageTag(cc)) {
        image_frame_available_ = true;
    } else {
        RET_CHECK(options_.has_canvas_width_px());
        RET_CHECK(options_.has_canvas_height_px());
    }

    // Initialize the helper renderer library.
    renderer_ = absl::make_unique<AnnotationRenderer>();
    renderer_->SetFlipTextVertically(options_.flip_text_vertically());
    if (use_gpu_)
        renderer_->SetScaleFactor(options_.gpu_scale_factor());
    if (renderer_->GetScaleFactor() < 1.0 && HasImageTag(cc))
        ABSL_LOG(WARNING) << "Annotation scale factor only supports GPU backed Image.";

    // Set the output header based on the input header (if present).
    const char* tag = HasImageTag(cc) ? kImageTag : use_gpu_ ? kGpuBufferTag : kImageFrameTag;
    if (image_frame_available_ && !cc->Inputs().Tag(tag).Header().IsEmpty()) {
        const auto& input_header        = cc->Inputs().Tag(tag).Header().Get<VideoHeader>();
        auto*       output_video_header = new VideoHeader(input_header);
        cc->Outputs().Tag(tag).SetHeader(Adopt(output_video_header));
    }

    if (use_gpu_) {
#if !MEDIAPIPE_DISABLE_GPU
        MP_RETURN_IF_ERROR(gpu_helper_.Open(cc));
#endif // !MEDIAPIPE_DISABLE_GPU
    }

    return absl::OkStatus();
}

absl::Status AnnotationOverlayCalculator::Process(CalculatorContext* cc) {
    if (cc->Inputs().HasTag(kGpuBufferTag) && cc->Inputs().Tag(kGpuBufferTag).IsEmpty()) {
        return absl::OkStatus();
    }
    if (cc->Inputs().HasTag(kImageFrameTag) && cc->Inputs().Tag(kImageFrameTag).IsEmpty()) {
        return absl::OkStatus();
    }
    if (cc->Inputs().HasTag(kImageTag) && cc->Inputs().Tag(kImageTag).IsEmpty()) {
        return absl::OkStatus();
    }
    if (HasImageTag(cc)) {
        use_gpu_ = cc->Inputs().Tag(kImageTag).Get<mediapipe::Image>().UsesGpu();
    }
    // Initialize render target, drawn with OpenCV.
    std::unique_ptr<cv::Mat> image_mat;
    ImageFormat::Format      target_format;
    if (use_gpu_) {
#if !MEDIAPIPE_DISABLE_GPU
        mediapipe::ImageData im_data = cc->Inputs().Tag(kImageDataTag).Get<mediapipe::ImageData>();
        width_                       = im_data.width();
        height_                      = im_data.height();
        if (!gpu_initialized_) {
            MP_RETURN_IF_ERROR(gpu_helper_.RunInGlContext([this, cc]() -> absl::Status {
                if (HasImageTag(cc)) {
                    return GlSetup<mediapipe::Image, kImageTag>(cc);
                }
                return GlSetup<mediapipe::GpuBuffer, kGpuBufferTag>(cc);
            }));
            gpu_initialized_ = true;
        }
        if (HasImageTag(cc) || cc->Inputs().HasTag(kGpuBufferTag)) {
            MP_RETURN_IF_ERROR((CreateRenderTargetCpuFromGpu<mediapipe::Image, kImageTag>(cc, image_mat, &target_format)));
        }
        if (cc->Inputs().HasTag(kGpuBufferTag)) {
            MP_RETURN_IF_ERROR(
                (CreateRenderTargetCpuFromGpu<mediapipe::GpuBuffer, kGpuBufferTag>(cc, image_mat, &target_format)));
        }
#endif // !MEDIAPIPE_DISABLE_GPU
    } else {
        if (cc->Outputs().HasTag(kImageFrameTag)) {
            MP_RETURN_IF_ERROR((CreateRenderTargetCpu<mediapipe::ImageFrame, kImageFrameTag>(cc, image_mat, &target_format)));
        }
    }

    // Reset the renderer with the image_mat. No copy here.
    renderer_->AdoptImage(image_mat.get());
    auto hand_points = absl::make_unique<std::vector<Points>>();
    // Render streams onto render target.
    for (CollectionItemId id = cc->Inputs().BeginId(); id < cc->Inputs().EndId(); ++id) {
        auto        tag_and_index = cc->Inputs().TagAndIndexFromId(id);
        std::string tag           = tag_and_index.first;
        if (!tag.empty() && tag != kVectorTag) {
            continue;
        }
        if (cc->Inputs().Get(id).IsEmpty()) {
            continue;
        }
        if (tag.empty()) {
            // Empty tag defaults to accepting a single object of RenderData type.
            const RenderData& render_data = cc->Inputs().Get(id).Get<RenderData>();
            renderer_->RenderDataOnImage(render_data);
        } else {
            RET_CHECK_EQ(kVectorTag, tag);
            const auto& render_data_vec = cc->Inputs().Get(id).Get<std::vector<RenderPointData>>();
            for (const RenderPointData& rp_data : render_data_vec) {
                hand_points->push_back(rp_data.points());
                renderer_->RenderDataOnImage(rp_data.render_data());
            }
        }
    }
    cc->Outputs().Tag(kHandPointsTag).Add(hand_points.release(), cc->InputTimestamp());
    // Copy the rendered image to output.
    uchar* image_mat_ptr = image_mat->data;
    MP_RETURN_IF_ERROR(RenderToCpu(cc, target_format, image_mat_ptr));

    return absl::OkStatus();
}

absl::Status AnnotationOverlayCalculator::Close(CalculatorContext* cc) {
    UNUSED(cc);
#if !MEDIAPIPE_DISABLE_GPU
    gpu_helper_.RunInGlContext([this] {
        if (program_)
            glDeleteProgram(program_);
        program_ = 0;
        if (image_mat_tex_)
            glDeleteTextures(1, &image_mat_tex_);
        image_mat_tex_ = 0;
    });
#endif // !MEDIAPIPE_DISABLE_GPU

    return absl::OkStatus();
}

absl::Status AnnotationOverlayCalculator::RenderToCpu(CalculatorContext* cc, const ImageFormat::Format& target_format,
                                                      uchar* data_image) {
    auto output_frame = absl::make_unique<ImageFrame>(target_format, renderer_->GetImageWidth(), renderer_->GetImageHeight());

#if !MEDIAPIPE_DISABLE_GPU
    output_frame->CopyPixelData(target_format, renderer_->GetImageWidth(), renderer_->GetImageHeight(), data_image,
                                ImageFrame::kGlDefaultAlignmentBoundary);
#else
    output_frame->CopyPixelData(target_format, renderer_->GetImageWidth(), renderer_->GetImageHeight(), data_image,
                                ImageFrame::kDefaultAlignmentBoundary);

#endif // !MEDIAPIPE_DISABLE_GPU

    if (HasImageTag(cc)) {
        auto out = std::make_unique<mediapipe::Image>(std::move(output_frame));
        cc->Outputs().Tag(kImageTag).Add(out.release(), cc->InputTimestamp());
    }
    if (cc->Outputs().HasTag(kImageFrameTag)) {
        cc->Outputs().Tag(kImageFrameTag).Add(output_frame.release(), cc->InputTimestamp());
    }

    return absl::OkStatus();
}

template<typename Type, const char* Tag>
absl::Status AnnotationOverlayCalculator::CreateRenderTargetCpu(CalculatorContext* cc, std::unique_ptr<cv::Mat>& image_mat,
                                                                ImageFormat::Format* target_format) {
    if (image_frame_available_) {
        const auto& input_frame = cc->Inputs().Tag(Tag).Get<Type>();

        image_mat = absl::make_unique<cv::Mat>(input_frame.Height(), input_frame.Width(), CV_8UC4, cv::Scalar(0, 0, 0, 0));

    } else {
        image_mat = absl::make_unique<cv::Mat>(options_.canvas_height_px(), options_.canvas_width_px(), CV_8UC4,
                                               cv::Scalar(0, 0, 0, 0));
    }
    *target_format = ImageFormat::SRGBA;

    return absl::OkStatus();
}

template<typename Type, const char* Tag>
absl::Status AnnotationOverlayCalculator::CreateRenderTargetCpuFromGpu(CalculatorContext*        cc,
                                                                       std::unique_ptr<cv::Mat>& image_mat,
                                                                       ImageFormat::Format*      target_format) {
#if !MEDIAPIPE_DISABLE_GPU
    if (image_frame_available_) {
        const auto&                          input_frame = cc->Inputs().Tag(Tag).Get<Type>();
        const mediapipe::ImageFormat::Format format      = mediapipe::ImageFormatForGpuBufferFormat(input_frame.format());
        if (format != mediapipe::ImageFormat::SRGBA && format != mediapipe::ImageFormat::SRGB)
            RET_CHECK_FAIL() << "Unsupported GPU input format: " << format;
    }
    image_mat = absl::make_unique<cv::Mat>(height_canvas_, width_canvas_, CV_8UC4, cv::Scalar(0, 0, 0, 0));
#else
    UNUSED(cc);
    UNUSED(image_mat);
#endif // !MEDIAPIPE_DISABLE_GPU

    *target_format = ImageFormat::SRGBA;

    return absl::OkStatus();
}

absl::Status AnnotationOverlayCalculator::GlRender(CalculatorContext* cc) {
    UNUSED(cc);
#if !MEDIAPIPE_DISABLE_GPU
    static const GLfloat square_vertices[] = {
        -1.0f, -1.0f, // bottom left
        1.0f,  -1.0f, // bottom right
        -1.0f, 1.0f,  // top left
        1.0f,  1.0f,  // top right
    };
    static const GLfloat texture_vertices[] = {
        0.0f, 0.0f, // bottom left
        1.0f, 0.0f, // bottom right
        0.0f, 1.0f, // top left
        1.0f, 1.0f, // top right
    };

    // program
    glUseProgram(program_);

    // vertex storage
    GLuint vbo[2];
    glGenBuffers(2, vbo);
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vbo 0
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), square_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glVertexAttribPointer(ATTRIB_VERTEX, 2, GL_FLOAT, 0, 0, nullptr);

    // vbo 1
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(GLfloat), texture_vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(ATTRIB_TEXTURE_POSITION);
    glVertexAttribPointer(ATTRIB_TEXTURE_POSITION, 2, GL_FLOAT, 0, 0, nullptr);

    // draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // cleanup
    glDisableVertexAttribArray(ATTRIB_VERTEX);
    glDisableVertexAttribArray(ATTRIB_TEXTURE_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, vbo);
#endif // !MEDIAPIPE_DISABLE_GPU

    return absl::OkStatus();
}

template<typename Type, const char* Tag>
absl::Status AnnotationOverlayCalculator::GlSetup(CalculatorContext* cc) {
    UNUSED(cc);
#if !MEDIAPIPE_DISABLE_GPU
    const GLint attr_location[NUM_ATTRIBUTES] = {
        ATTRIB_VERTEX,
        ATTRIB_TEXTURE_POSITION,
    };
    const GLchar* attr_name[NUM_ATTRIBUTES] = {
        "position",
        "texture_coordinate",
    };

    // Shader to overlay a texture onto another when overlay is non-zero.
    constexpr char kFragSrcBody[] = R"(
  DEFAULT_PRECISION(mediump, float)
  #ifdef GL_ES
    #define fragColor gl_FragColor
  #else
    out vec4 fragColor;
  #endif  // GL_ES

    in vec2 sample_coordinate;
    uniform sampler2D input_frame;
    // "overlay" texture has top-left origin (OpenCV mat with annotations has
    // been uploaded to GPU without vertical flip)
    uniform sampler2D overlay;
    uniform vec3 transparent_color;

    void main() {
      vec3 image_pix = texture2D(input_frame, sample_coordinate).rgb;
  #ifdef INPUT_FRAME_HAS_TOP_LEFT_ORIGIN
      // "input_frame" has top-left origin same as "overlay", hence overlaying
      // as is.
      vec3 overlay_pix = texture2D(overlay, sample_coordinate).rgb;
  #else
      // "input_frame" has bottom-left origin, hence flipping "overlay" texture
      // coordinates.
      vec3 overlay_pix = texture2D(overlay, vec2(sample_coordinate.x, 1.0 - sample_coordinate.y)).rgb;
  #endif  // INPUT_FRAME_HAS_TOP_LEFT_ORIGIN

      vec3 out_pix = image_pix;
      float dist = distance(overlay_pix.rgb, transparent_color);
      if (dist > 0.001) out_pix = overlay_pix;
      fragColor.rgb = out_pix;
      fragColor.a = 1.0;
    }
  )";

    std::string defines;
    if (options_.gpu_uses_top_left_origin()) {
        defines = R"(
      #define INPUT_FRAME_HAS_TOP_LEFT_ORIGIN;
    )";
    }

    const std::string frag_src = absl::StrCat(mediapipe::kMediaPipeFragmentShaderPreamble, defines, kFragSrcBody);

    // Create shader program and set parameters
    mediapipe::GlhCreateProgram(mediapipe::kBasicVertexShader, frag_src.c_str(), NUM_ATTRIBUTES, (const GLchar**) &attr_name[0],
                                attr_location, &program_);
    RET_CHECK(program_) << "Problem initializing the program.";
    glUseProgram(program_);
    glUniform1i(glGetUniformLocation(program_, "input_frame"), 1);
    glUniform1i(glGetUniformLocation(program_, "overlay"), 2);
    glUniform3f(glGetUniformLocation(program_, "transparent_color"), kAnnotationBackgroundColor / 255.0,
                kAnnotationBackgroundColor / 255.0, kAnnotationBackgroundColor / 255.0);

    // Ensure GPU texture is divisible by 4. See b/138751944 for more info.
    const float alignment    = ImageFrame::kGlDefaultAlignmentBoundary;
    const float scale_factor = options_.gpu_scale_factor();
    width_canvas_            = RoundUp(width_ * scale_factor, alignment);
    height_canvas_           = RoundUp(height_ * scale_factor, alignment);

    // Init texture for opencv rendered frame.
    {
        glGenTextures(1, &image_mat_tex_);
        glBindTexture(GL_TEXTURE_2D, image_mat_tex_);
        // TODO
        // OpenCV only renders to RGB images, not RGBA. Ideally this should be RGBA.
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_canvas_, height_canvas_, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
#endif // !MEDIAPIPE_DISABLE_GPU

    return absl::OkStatus();
}

} // namespace mediapipe
