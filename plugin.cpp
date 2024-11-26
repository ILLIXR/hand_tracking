#include <cmath>
#include "absl/flags/parse.h"

#include "plugin.hpp"

#include "mediapipe/framework/deps/file_helpers.h"
#include "mediapipe/calculators/util/image_data.pb.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"

#ifdef USE_ZED
#include "plugins/zed/plugin.hpp"
#endif

#if !MEDIAPIPE_DISABLE_GPU
#include "mediapipe/gpu/gpu_buffer.h"
#include "mediapipe/gpu/gpu_shared_data_internal.h"
#endif
using namespace ILLIXR;
using namespace ILLIXR::HandTracking;

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "illixr_data";
constexpr char kImageDataTag[] = "image_data";


void img_convert(cv::Mat& img, bool flip=false) {
    switch (img.type()) {
        case CV_8UC1:
            cv::cvtColor(img, img, cv::COLOR_GRAY2RGB);
            break;
        case CV_8UC3:
            break;
        case CV_8UC4:
            if (flip) {
                cv::cvtColor(img, img, cv::COLOR_BGRA2RGB);
            } else {
                cv::cvtColor(img, img, cv::COLOR_RGBA2RGB);
            }
            break;
    }
}

ht::cam_type get_cam_type(const std::shared_ptr<switchboard>& sb) {
    std::string in_src = sb->get_env("HT_INPUT");
    if (ILLIXR::compare(in_src, "zed")) {
        return ht::ZED;
    } else if (ILLIXR::compare(in_src, "cam")) {
        return ht::CAM;
    } else if (ILLIXR::compare(in_src, "webcam")) {
        return  ht::WEBCAM;
    } else {
        throw std::runtime_error("HT_INPUT did not have a valid type");
    }
}

[[maybe_unused]] hand_tracking::hand_tracking(const std::string& name_, phonebook* pb_)
        : plugin{name_, pb_}
        , _graph{{::ILLIXR::image::LEFT_EYE, nullptr},
                 {::ILLIXR::image::RIGHT_EYE, nullptr},
                 {::ILLIXR::image::RGB, nullptr}}
        , _switchboard{pb_->lookup_impl<switchboard>()}
        , _cam_type{get_cam_type(_switchboard)}
        , _publisher{"hand_tracking_publisher", pb_, _cam_type} {
    if (_cam_type == ht::WEBCAM) {
        _input_type = ht::RGB;
        _first_person = false;
    } else if (const char *in_type = _switchboard->get_env_char("HT_INPUT_TYPE")) {
        if (strcmp(in_type, "LEFT") == 0 || strcmp(in_type, "SINGLE") == 0) {
            _input_type = ht::LEFT;
        } else if (strcmp(in_type, "RIGHT") == 0) {
            _input_type = ht::RIGHT;
        } else if (strcmp(in_type, "MULTI") == 0 || strcmp(in_type, "BOTH") == 0) {
            _input_type = ht::BOTH;
        } else if (strcmp(in_type, "RGB") == 0) {
            _input_type = ht::RGB;
        }
    } else {
        _input_type = ht::BOTH;
    }


    if (_input_type == ht::RGB) {
        _graph.at(::ILLIXR::image::RGB) = new mediapipe::CalculatorGraph();
    } else {
        if (_input_type != ht::RIGHT)
            _graph.at(::ILLIXR::image::LEFT_EYE) = new mediapipe::CalculatorGraph();
        if (_input_type == ht::RIGHT || _input_type == ht::BOTH)
            _graph.at(::ILLIXR::image::RIGHT_EYE) = new mediapipe::CalculatorGraph();
    }
    _publisher.set_framecount(_input_type);
}

void hand_tracking::start() {
    plugin::start();
    std::string calculator_graph_config_contents;
    const char* cfile = _switchboard->get_env_char("CALCULATOR_CONFIG_FILE");

    auto status = mediapipe::file::GetContents(cfile, &calculator_graph_config_contents);
    if (!status.ok())
        throw std::runtime_error("Failed to get config contents");
    auto config = mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(calculator_graph_config_contents);

    if (_input_type == ht::RGB) {
        status = _graph[::ILLIXR::image::RGB]->Initialize(config);
        if (!status.ok())
            throw std::runtime_error(std::string(status.message()));
    } else {
        if (_input_type != ht::RIGHT) {
            status = _graph[::ILLIXR::image::LEFT_EYE]->Initialize(config);
            if (!status.ok())
                throw std::runtime_error(std::string(status.message()));
        }
        if (_input_type == ht::RIGHT || _input_type == ht::BOTH) {
            status = _graph[::ILLIXR::image::RIGHT_EYE]->Initialize(config);
            if (!status.ok())
                throw std::runtime_error(std::string(status.message()));
        }
    }

#if !MEDIAPIPE_DISABLE_GPU
    ABSL_LOG(INFO) << "Initialize the GPU.";
#endif
    for (auto& item : _graph) {
        if (item.second != nullptr) {
#if !MEDIAPIPE_DISABLE_GPU
            auto gpu_resources = mediapipe::GpuResources::Create();
            if(!gpu_resources.ok())
                throw std::runtime_error("");

            status = _graph.at(item.first)->SetGpuResources(std::move(gpu_resources).value());
            if (!status.ok())
                throw std::runtime_error(std::string(status.message()));
            _gpu_helper[item.first].InitializeForTest(
                    _graph.at(item.first)->GetGpuResources().get());
#endif
            if (_graph.at(item.first) != nullptr) {
                auto status_or_poller = _graph.at(item.first)->AddOutputStreamPoller(kOutputStream);
                if (!status_or_poller.ok())
                    throw std::runtime_error("Error with output poller");
                _publisher.set_poller(item.first, new mediapipe::OutputStreamPoller(std::move(status_or_poller).value()));
            }

        }
    }
    for (auto& item : _graph) {
        if (item.second != nullptr) {
            status = _graph.at(item.first)->StartRun({});
            if (!status.ok())
                throw std::runtime_error("Error starting graph");
        }
    }
    // subscribe to the expected type
    switch (_cam_type) {
        case ht::WEBCAM:
            _switchboard->schedule<monocular_cam_type>(id, "webcam",
                                                       [this](const switchboard::ptr<const monocular_cam_type> &frame,
                                                              std::size_t) {
                                                           this->process(frame);
                                                       });
            break;
        case ht::CAM:
            _switchboard->schedule<binocular_cam_type>(id, "cam",
                                                       [this](const switchboard::ptr<const binocular_cam_type> &img,
                                                              std::size_t) {
                                                           this->process(img);
                                                       });
            break;
        case ht::ZED:
            _switchboard->schedule<cam_type_zed>(id, "cam_zed",
                                                 [this](const switchboard::ptr<const cam_type_zed> &img, std::size_t) {
                                                     this->process(img);
                                                 });
            break;
    }
    _publisher.start();
}

void hand_tracking::stop() {
    _publisher.stop();
    plugin::stop();
}

hand_tracking::~hand_tracking() {
    for (auto& i : _graph)
        delete i.second;
}

void hand_tracking::process(const switchboard::ptr<const cam_base_type>& frame) {
    _current_images.clear();
    pose_image pose_img;
    switch (frame->type) {
        case ::ILLIXR::camera::BINOCULAR:
            switch (_input_type) {
                case ht::BOTH:
                    _current_images = {{::ILLIXR::image::LEFT_EYE,  frame->at(::ILLIXR::image::LEFT_EYE).clone()},
                                       {::ILLIXR::image::RIGHT_EYE, frame->at(::ILLIXR::image::RIGHT_EYE).clone()}};
                    pose_img.eye_count = 2;
                    break;
                case ht::LEFT:
                    _current_images = {{::ILLIXR::image::LEFT_EYE, frame->at(::ILLIXR::image::LEFT_EYE).clone()}};
                    pose_img.eye_count = 1;
                    pose_img.primary = ::ILLIXR::units::LEFT_EYE;
                    break;
                case ht::RIGHT:
                    _current_images = {{::ILLIXR::image::RIGHT_EYE, frame->at(::ILLIXR::image::RIGHT_EYE).clone()}};
                    pose_img.eye_count = 1;
                    pose_img.primary = ::ILLIXR::units::RIGHT_EYE;
                    break;
                case ht::RGB:
                    std::cout << "RGB not provided by binocular view";
                    break;
            }
            break;
        case ::ILLIXR::camera::MONOCULAR: {
            cv::Mat temp_img(frame->at(::ILLIXR::image::RGB).clone());
            cv::flip(temp_img, temp_img, 1);
            img_convert(temp_img);
            _current_images = {{::ILLIXR::image::LEFT_EYE, temp_img}};
            pose_img.eye_count = 1;
            pose_img.primary = ::ILLIXR::units::LEFT_EYE;
            break;
        }
        case ::ILLIXR::camera::RGB_DEPTH: {
            _current_images = {{::ILLIXR::image::LEFT_EYE, frame->at(::ILLIXR::image::RGB).clone()}};
            pose_img.eye_count = 1;
            pose_img.primary = ::ILLIXR::units::LEFT_EYE;
            break;
        }
        case ::ILLIXR::camera::ZED: {
            switch (_input_type) {
                case ht::BOTH: {
                    cv::Mat tempL(frame->at(::ILLIXR::image::LEFT_EYE).clone());
                    cv::Mat tempR(frame->at(::ILLIXR::image::RIGHT_EYE).clone());
                    img_convert(tempL, true);
                    img_convert(tempR, true);
                    _current_images = {{::ILLIXR::image::LEFT_EYE, tempL},
                                       {::ILLIXR::image::RIGHT_EYE, tempR}};
                    pose_img.eye_count = 2;
                    pose_img.primary = ::ILLIXR::units::LEFT_EYE;
                    break;
                }
                case ht::LEFT: {
                    cv::Mat temp(frame->at(::ILLIXR::image::LEFT_EYE).clone());
                    img_convert(temp, true);
                    _current_images = {{::ILLIXR::image::LEFT_EYE, temp}};
                    pose_img.eye_count = 1;
                    pose_img.primary = ::ILLIXR::units::LEFT_EYE;
                    break;
                }
                case ht::RIGHT: {
                    cv::Mat temp(frame->at(::ILLIXR::image::RIGHT_EYE).clone());
                    img_convert(temp, true);
                    _current_images = {{::ILLIXR::image::RIGHT_EYE, temp}};
                    pose_img.eye_count = 1;
                    pose_img.primary = ::ILLIXR::units::RIGHT_EYE;
                    break;
                }
                case ht::RGB: {
                    cv::Mat temp(frame->at(::ILLIXR::image::RGB).clone());
                    img_convert(temp, true);
                    _current_images = {{::ILLIXR::image::LEFT_EYE, temp}};
                    pose_img.eye_count = 1;
                    pose_img.primary = ::ILLIXR::units::LEFT_EYE;
                    break;
                }
            }
            if (frame->find(::ILLIXR::image::DEPTH) != frame->end()) {
                pose_img.images[::ILLIXR::image::DEPTH] = frame->at(::ILLIXR::image::DEPTH).clone();
                pose_img.depth_valid = true;
            }
            if (frame->find(::ILLIXR::image::CONFIDENCE) != frame->end()) {
                pose_img.images[::ILLIXR::image::CONFIDENCE] = frame->at(::ILLIXR::image::CONFIDENCE).clone();
                pose_img.confidence_valid_ = true;
            }
            pose_img.poses = dynamic_cast<const cam_type_zed*>(frame.get())->poses;
            pose_img.insert(_current_images.begin(), _current_images.end());
            pose_img.pose_valid = true;
            break;
        }
        case ::ILLIXR::camera::DEPTH: {
            /// TODO Error
        }
    }

    size_t frame_id = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    for (const auto &input: _current_images) {
        auto input_frame = absl::make_unique<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGB,
                                                                    input.second.cols,
                                                                    input.second.rows,
#if !MEDIAPIPE_DISABLE_GPU
                                                                    mediapipe::ImageFrame::kGlDefaultAlignmentBoundary
#else
                mediapipe::ImageFrame::kDefaultAlignmentBoundary
#endif
        );

        cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());
        input.second.copyTo(input_frame_mat);

        // Send image _packet into the graph.
        int64_t frame_timestamp_us = std::chrono::high_resolution_clock::now().time_since_epoch().count() / 1000;

        // make sure image data makes it into stream first
        mediapipe::ImageData image_data;
        image_data.set_width(input_frame.get()->Width());
        image_data.set_height(input_frame.get()->Height());
        image_data.set_frame_id(frame_id);
        image_data.set_image_type(input.first);
        image_data.set_first_person(_first_person);

        auto img_ptr = absl::make_unique<mediapipe::ImageData>(image_data);
        auto img_status = _graph.at(input.first)->AddPacketToInputStream(kImageDataTag,
                                                        mediapipe::Adopt(img_ptr.release()).At(
                                                                mediapipe::Timestamp(frame_timestamp_us)));

        if (!img_status.ok())
            throw std::runtime_error(std::string(img_status.message()));

#if !MEDIAPIPE_DISABLE_GPU
        auto gl_status = _gpu_helper.at(input.first).RunInGlContext([&input_frame, &frame_timestamp_us,
                                                            &graph=_graph.at(input.first),
                                                            &gpu_helper=_gpu_helper.at(input.first)]()
                                                            -> absl::Status {
            // Convert ImageFrame to GpuBuffer.
            auto texture = gpu_helper.CreateSourceTexture(*input_frame.get());
            auto gpu_frame = texture.GetFrame<mediapipe::GpuBuffer>();
            glFlush();
            texture.Release();
            // Send GPU image packet into the graph.
            auto submit_status = graph->AddPacketToInputStream(
                    kInputStream, mediapipe::Adopt(gpu_frame.release())
                            .At(mediapipe::Timestamp(frame_timestamp_us)));
            if (!submit_status.ok())
                throw std::runtime_error(std::string(submit_status.message()));
            return absl::OkStatus();
        });
        if (!gl_status.ok())
            throw std::runtime_error(std::string(gl_status.message()));
#else
        auto submit_status = _graph.at(input.first)->AddPacketToInputStream(kInputStream,
                                              mediapipe::Adopt(input_frame.release()).At(
                                                      mediapipe::Timestamp(frame_timestamp_us)));
        if (!submit_status.ok())
            throw std::runtime_error(std::string(submit_status.message()));
#endif
    }
    _publisher.add_raw(frame_id, pose_img);
}

//###############################################################################################


PLUGIN_MAIN(hand_tracking)
