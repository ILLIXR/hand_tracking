#include "mediapipe/calculators/util/illixr_output_calculator.h"
#include "mediapipe/framework/formats/image.h"
#include <map>

#include "mediapipe/framework/deps/ret_check.h"
#include "mediapipe/framework/calculator_framework.h"
#include "mediapipe/framework/formats/image_opencv.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"

#include "mediapipe/framework/formats/classification.pb.h"
#include "mediapipe/calculators/util/illixr_data.h"

namespace mediapipe {

    namespace {
        constexpr char kNormRectTag[] = "NORM_RECT";
        constexpr char kRectTag[] = "RECT";
        constexpr char kNormRectsTag[] = "NORM_RECTS";
        constexpr char kRectsTag[] = "RECTS";

        constexpr char kImageFrameTag[] = "IMAGE";
        constexpr char kImageTag[] = "UIMAGE";
        constexpr char kGpuBufferTag[] = "IMAGE_GPU";
        constexpr char kPointOfViewTag[] = "POINT_OF_VIEW";

        const std::map<input_image_type, const std::string> image_map {{input_image_type::IMAGE, kImageFrameTag},
                                                                       {input_image_type::UIMAGE, kImageTag},
                                                                       {input_image_type::IMAGE_GPU, kGpuBufferTag}};
        constexpr char kHandPointsTag[] = "HAND_POINTS";
        constexpr char kHandedness[] = "HANDEDNESS";


        constexpr char kNormPalmRectTag[] = "NORM_RECT_PALM";
        constexpr char kRectPalmTag[] = "RECT_PALM";
        constexpr char kNormPalmRectsTag[] = "NORM_RECTS_PALM";
        constexpr char kRectsPalmTag[] = "RECTS_PALM";

        const std::map<palm_input_type, const std::string> palm_map {{palm_input_type::NORM_RECT, kNormPalmRectTag},
                                                                     {palm_input_type::RECT, kRectPalmTag},
                                                                     {palm_input_type::NORM_RECTS, kNormPalmRectsTag},
                                                                     {palm_input_type::RECTS, kRectsPalmTag}};
        constexpr char kNormHandRectTag[] = "NORM_RECT_HAND";
        constexpr char kRectHandTag[] = "RECT_HAND";
        constexpr char kNormHandRectsTag[] = "NORM_RECTS_HAND";
        constexpr char kRectsHandTag[] = "RECTS_HAND";

        const std::map<hand_input_type, const std::string> hand_map {{hand_input_type::NORM_RECT, kNormHandRectTag},
                                                                     {hand_input_type::RECT, kRectHandTag},
                                                                     {hand_input_type::NORM_RECTS, kNormHandRectsTag},
                                                                     {hand_input_type::RECTS, kRectsHandTag}};

        constexpr char kIllixrData[] = "ILLIXR_DATA";

        inline bool HasImageTag(mediapipe::CalculatorContext* cc) {
            return cc->Inputs().HasTag(kImageTag);
        }
    }
absl::Status ILLIXROutputCalculator::GetContract(CalculatorContract* cc) {
    RET_CHECK_GE(cc->Inputs().NumEntries(), 1);


    RET_CHECK(cc->Inputs().HasTag(kImageFrameTag) +
#if !MEDIAPIPE_DISABLE_GPU
              cc->Inputs().HasTag(kGpuBufferTag) +
#endif
              cc->Inputs().HasTag(kImageTag) <=
              1);

#if !MEDIAPIPE_DISABLE_GPU
    if (cc->Inputs().HasTag(kGpuBufferTag)) {
        cc->Inputs().Tag(kGpuBufferTag).Set<mediapipe::GpuBuffer>();
    }
#endif  // !MEDIAPIPE_DISABLE_GPU

    if (cc->Inputs().HasTag(kImageFrameTag)) {
        cc->Inputs().Tag(kImageFrameTag).Set<ImageFrame>();
    } else if (cc->Inputs().HasTag(kImageTag)) {
        cc->Inputs().Tag(kImageTag).Set<mediapipe::Image>();
    }

    if (cc->Inputs().HasTag(kHandPointsTag)) {
        cc->Inputs().Tag(kHandPointsTag).Set<std::vector<Points> >();
    }

    if (cc->Inputs().HasTag(kHandedness)) {
        cc->Inputs().Tag(kHandedness).Set<std::vector<mediapipe::ClassificationList>>();
    }

    RET_CHECK(cc->Inputs().HasTag(kNormPalmRectTag) +
              cc->Inputs().HasTag(kRectPalmTag) +
              cc->Inputs().HasTag(kNormPalmRectsTag) +
              cc->Inputs().HasTag(kRectsPalmTag) <=
              1);

    if (cc->Inputs().HasTag(kNormPalmRectTag)) {
        cc->Inputs().Tag(kNormPalmRectTag).Set<NormalizedRect>();
    } else if (cc->Inputs().HasTag(kRectPalmTag)) {
        cc->Inputs().Tag(kRectPalmTag).Set<Rect>();
    } else if (cc->Inputs().HasTag(kNormPalmRectsTag)) {
        cc->Inputs().Tag(kNormPalmRectsTag).Set<std::vector<NormalizedRect>>();
    } else if (cc->Inputs().HasTag(kRectsPalmTag)) {
        cc->Inputs().Tag(kRectsPalmTag).Set<std::vector<Rect>>();
    }

    RET_CHECK(cc->Inputs().HasTag(kNormHandRectTag) +
              cc->Inputs().HasTag(kRectHandTag) +
              cc->Inputs().HasTag(kNormHandRectsTag) +
              cc->Inputs().HasTag(kRectsHandTag) <=
              1);

    if (cc->Inputs().HasTag(kNormHandRectTag)) {
        cc->Inputs().Tag(kNormHandRectTag).Set<NormalizedRect>();
    } else if (cc->Inputs().HasTag(kRectHandTag)) {
        cc->Inputs().Tag(kRectHandTag).Set<Rect>();
    } else if (cc->Inputs().HasTag(kNormHandRectsTag)) {
        cc->Inputs().Tag(kNormHandRectsTag).Set<std::vector<NormalizedRect>>();
    } else if (cc->Inputs().HasTag(kRectsHandTag)) {
        cc->Inputs().Tag(kRectsHandTag).Set<std::vector<Rect>>();
    }

    RET_CHECK(cc->Inputs().HasTag(kPointOfViewTag) == 1);
    cc->Inputs().Tag(kPointOfViewTag).Set<bool>();

    RET_CHECK(cc->Outputs().HasTag(kIllixrData));
    cc->Outputs().Tag(kIllixrData).Set<ILLIXR::illixr_ht_frame>();


    return absl::OkStatus();
}

absl::Status ILLIXROutputCalculator::Open(CalculatorContext* cc) {
    cc->SetOffset(TimestampDiff(0));

    options_ = cc->Options<ILLIXROutputCalculatorOptions>();

    if (cc->Inputs().HasTag(kImageFrameTag)) {
        image_type = input_image_type::IMAGE;
    } else if (cc->Inputs().HasTag(kImageTag)) {
        image_type = input_image_type::UIMAGE;
    }
#if !MEDIAPIPE_DISABLE_GPU
    else if (cc->Inputs().HasTag(kGpuBufferTag)) {
        img_type = IMAGE_GPU;
    }
#endif  // !MEDIAPIPE_DISABLE_GPU
    else {
        image_type = input_image_type::NONE;
    }

    if (cc->Inputs().HasTag(kNormPalmRectTag)) {
        palm_input = palm_input_type::NORM_RECT;
    } else if (cc->Inputs().HasTag(kRectPalmTag)) {
        palm_input = palm_input_type::RECT;
    } else if (cc->Inputs().HasTag(kNormPalmRectsTag)) {
        palm_input = palm_input_type::NORM_RECTS;
    } else if (cc->Inputs().HasTag(kRectsPalmTag)) {
        palm_input = palm_input_type::RECTS;
    } else {
        palm_input = palm_input_type::NONE;
    }

    if (cc->Inputs().HasTag(kNormHandRectTag)) {
        hand_input = hand_input_type::NORM_RECT;
    } else if (cc->Inputs().HasTag(kRectHandTag)) {
        hand_input = hand_input_type::RECT;
    } else if (cc->Inputs().HasTag(kNormHandRectsTag)) {
        hand_input = hand_input_type::NORM_RECTS;
    } else if (cc->Inputs().HasTag(kRectsHandTag)) {
        hand_input = hand_input_type::RECTS;
    } else {
        hand_input = hand_input_type::NONE;
    }

#if !MEDIAPIPE_DISABLE_GPU
    if (use_gpu_) {
        MP_RETURN_IF_ERROR(gpu_helper_.Open(cc));
    }
#endif  // !MEDIAPIPE_DISABLE_GPU

    return absl::OkStatus();
}

absl::Status ILLIXROutputCalculator::Process(CalculatorContext* cc) {
    int component_count = 0;
    int left_idx = -1;
    int right_idx = -1;
    if (cc->Inputs().HasTag(kPointOfViewTag) &&
        !cc->Inputs().Tag(kPointOfViewTag).IsEmpty()) {
        first_person_ = cc->Inputs().Tag(kPointOfViewTag).Get<bool>();
    }
    auto frame_data = absl::make_unique<ILLIXR::illixr_ht_frame>();
    if (cc->Inputs().HasTag(image_map.at(image_type)) &&
        !cc->Inputs().Tag(image_map.at(image_type)).IsEmpty()) {
        auto img = absl::make_unique<cv::Mat>();
        if (use_gpu_) {
#if !MEDIAPIPE_DISABLE_GPU
            if (!gpu_initialized_) {
                MP_RETURN_IF_ERROR(
          gpu_helper_.RunInGlContext([this, cc]() -> absl::Status {
            if (HasImageTag(cc)) {
              return GlSetup<mediapipe::Image, kImageTag>(cc);
            }
            return GlSetup<mediapipe::GpuBuffer, kGpuBufferTag>(cc);
          }));
      gpu_initialized_ = true;
    }
    if (HasImageTag(cc)) {
      MP_RETURN_IF_ERROR(
          (CreateRenderTargetGpu<mediapipe::Image, kImageTag>(cc, image_mat)));
    }
    if (cc->Inputs().HasTag(kGpuBufferTag)) {
      MP_RETURN_IF_ERROR(
          (CreateRenderTargetGpu<mediapipe::GpuBuffer, kGpuBufferTag>(
              cc, image_mat)));
    }
#endif  // !MEDIAPIPE_DISABLE_GPU
        } else if (image_type == input_image_type::UIMAGE) {
            const auto& input =
                    cc->Inputs().Tag(kImageTag).Get<mediapipe::Image>();
            auto input_mat = formats::MatView(&input);
            input_mat->copyTo(*img);
        } else if (image_type == input_image_type::IMAGE) {
            const auto& input_frame =
                    cc->Inputs().Tag(kImageFrameTag).Get<ImageFrame>();
            auto input_mat = formats::MatView(&input_frame);
            input_mat.copyTo(*img);
            frame_data->image_id = input_frame.id();
            frame_data->type = input_frame.type();
        }
        frame_data->image = img.release();
        component_count++;
    } else {
        frame_data->image = nullptr;
    }

    if (cc->Inputs().HasTag(kHandedness) &&
        !cc->Inputs().Tag(kHandedness).IsEmpty()) {
        const auto &hands = cc->Inputs().Tag(kHandedness).Get<std::vector<ClassificationList> >();
        for(int i = 0; i < hands.size(); i++) {
            if (hands[i].classification(0).label() == "Left") {
                if (first_person_) {
                    right_idx = i;
                    frame_data->right_confidence = hands[i].classification(0).score();
                } else {
                    left_idx = i;
                    frame_data->left_confidence = hands[i].classification(0).score();
                }
            } else if (hands[i].classification(0).label() == "Right") {
                if (first_person_) {
                    left_idx = i;
                    frame_data->left_confidence = hands[i].classification(0).score();
                } else {
                    right_idx = i;
                    frame_data->right_confidence = hands[i].classification(0).score();
                }
            } else {
                // something is wrong
            }
            component_count++;
        }
    }
    if (cc->Inputs().HasTag(kHandPointsTag) &&
        !cc->Inputs().Tag(kHandPointsTag).IsEmpty()) {
        const auto &hp = cc->Inputs().Tag(kHandPointsTag).Get<std::vector<Points> >();
        for (auto i = 0; i < hp.size(); i++) {
            auto hand_points = absl::make_unique<::ILLIXR::hand_points>(21, ::ILLIXR::point());
            for (auto j = 0; j < hp[i].points_size(); j++) {
                auto pnt = hp[i].points(j);
                hand_points->at(j).set(pnt.x(), pnt.y(), pnt.z(), pnt.normalized());
            }
            if (i == left_idx)
                frame_data->left_hand_points = hand_points.release();
            else if (i == right_idx)
                frame_data->right_hand_points = hand_points.release();
        }
        component_count++;
    }

    if (cc->Inputs().HasTag(palm_map.at(palm_input)) &&
        !cc->Inputs().Tag(palm_map.at(palm_input)).IsEmpty()) {
        ::ILLIXR::rect* p_rect;
        if (palm_input == palm_input_type::NORM_RECT || palm_input == palm_input_type::RECT) {
            if (palm_input == palm_input_type::NORM_RECT) {
                const auto &rect = cc->Inputs().Tag(kNormPalmRectTag).Get<NormalizedRect>();
                p_rect = make_rect(rect, true);
            } else {
                const auto &rect = cc->Inputs().Tag(kRectPalmTag).Get<Rect>();
                p_rect = make_rect(rect, false);
            }
            if (left_idx == 0)
                frame_data->left_palm = p_rect;
            else if (right_idx == 0)
                frame_data->right_palm = p_rect;
            else
                delete p_rect;
        } else if (palm_input == palm_input_type::NORM_RECTS) {
            const auto& nrects = cc->Inputs().Tag(kNormPalmRectsTag).Get<std::vector<NormalizedRect> >();
            if (nrects.size() > 2) {
                    // ERROR
            }
            for (auto i = 0; i < nrects.size(); i++) {
                p_rect = make_rect(nrects[i], true);
                if (i == left_idx)
                    frame_data->left_palm = p_rect;
                else if (i == right_idx)
                    frame_data->right_palm = p_rect;
                else
                    delete p_rect;
            }
        }
        else if(palm_input == palm_input_type::RECTS) {
            const auto& rects = cc->Inputs().Tag(kRectsPalmTag).Get<std::vector<NormalizedRect> >();
            if (rects.size() > 2) {
                // ERROR
            }
            for (auto i = 0; i < rects.size(); i++) {
                p_rect = make_rect(rects[i], false);
                if (i == left_idx)
                    frame_data->left_palm = p_rect;
                else if (i == right_idx)
                    frame_data->right_palm = p_rect;
                else
                    delete p_rect;
            }
        }
        component_count++;
    }
    if (cc->Inputs().HasTag(hand_map.at(hand_input)) &&
        !cc->Inputs().Tag(hand_map.at(hand_input)).IsEmpty()) {
        ::ILLIXR::rect* h_rect;
        if (hand_input == hand_input_type::NORM_RECT || hand_input == hand_input_type::RECT) {
            if (hand_input == hand_input_type::NORM_RECT) {
                const auto &rect = cc->Inputs().Tag(kNormHandRectTag).Get<NormalizedRect>();
                h_rect = make_rect(rect, true);

            } else {
                const auto &rect = cc->Inputs().Tag(kRectHandTag).Get<Rect>();
                h_rect = make_rect(rect, false);
            }
            if (left_idx == 0)
                frame_data->left_hand = h_rect;
            else if (right_idx == 0)
                frame_data->right_hand = h_rect;
            else
                delete h_rect;

        } else if (hand_input == hand_input_type::NORM_RECTS) {
            const auto &nrects = cc->Inputs().Tag(kNormHandRectsTag).Get<std::vector<NormalizedRect> >();
            if (nrects.size() > 2) {
                // ERROR

            }
            for (auto i = 0; i < nrects.size(); i++) {
                h_rect = make_rect(nrects[i], true);
                if (i == left_idx)
                    frame_data->left_hand = h_rect;
                else if (i == right_idx)
                    frame_data->right_hand = h_rect;
                else
                    delete h_rect;
            }
        } else if (hand_input == hand_input_type::RECTS) {
            const auto& rects = cc->Inputs().Tag(kRectsHandTag).Get<std::vector<NormalizedRect> >();
            if (rects.size() > 2) {
                // ERROR
            }
            for (auto i = 0; i < rects.size(); i++) {
                h_rect = make_rect(rects[i], false);
                if (i == left_idx)
                    frame_data->left_hand = h_rect;
                else if (i == right_idx)
                    frame_data->right_hand = h_rect;
                else
                    delete h_rect;
            }
        }
        component_count++;
    }

    if (component_count == 0) {
        return absl::OkStatus();
    }
    //if (HasImageTag(cc)) {
    //    use_gpu_ = cc->Inputs().Tag(kImageTag).Get<mediapipe::Image>().UsesGpu();
    //}

    cc->Outputs().Tag(kIllixrData).Add(frame_data.release(), cc->InputTimestamp());



    return absl::OkStatus();

}

REGISTER_CALCULATOR(ILLIXROutputCalculator);
} // mediapipe