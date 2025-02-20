#include "plugin.hpp"

#include "absl/flags/parse.h"
#include "illixr/data_format/misc.hpp"
#include "illixr/data_format/zed_cam.hpp"
#include "mediapipe/calculators/util/image_data.pb.h"
#include "mediapipe/framework/deps/file_helpers.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/framework/port/parse_text_proto.h"

#include <cmath>

#if !MEDIAPIPE_DISABLE_GPU
    #include "mediapipe/gpu/gpu_buffer.h"
    #include "mediapipe/gpu/gpu_shared_data_internal.h"
#endif
using namespace ILLIXR;
namespace idf = ILLIXR::data_format;
namespace iht = ILLIXR::data_format::ht;

constexpr char kInputStream[]  = "input_video";
constexpr char kOutputStream[] = "illixr_data";
constexpr char kImageDataTag[] = "image_data";

void img_convert(cv::Mat& img, bool flip = false) {
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

ht::cam_type hand_tracking::get_cam_type() {
    const char* input_t = std::getenv("HT_INPUT");
    if (!input_t)
        throw std::runtime_error("HT_INPUT did not have a valid type");
    std::string input_src{input_t};
    // std::string input_src = switchboard_->get_env("HT_INPUT");
    if (ILLIXR::data_format::compare(input_src, "zed")) {
        return ht::ZED;
    } else if (ILLIXR::data_format::compare(input_src, "cam")) {
        return ht::CAM;
    } else if (ILLIXR::data_format::compare(input_src, "webcam")) {
        return ht::WEBCAM;
    } else {
        throw std::runtime_error("HT_INPUT did not have a valid type");
    }
}

[[maybe_unused]] hand_tracking::hand_tracking(const std::string& name_, phonebook* pb_)
    : plugin{name_, pb_}
    , switchboard_{pb_->lookup_impl<switchboard>()}
    , graph_{{idf::image::LEFT_EYE, nullptr}, {idf::image::RIGHT_EYE, nullptr}, {idf::image::RGB, nullptr}}
    , cam_type_{get_cam_type()}
    , publisher_{"hand_tracking_publisher", pb_} {
    if (cam_type_ == ht::WEBCAM) {
        input_type_   = ht::RGB;
        first_person_ = false;
        //} else if (const char *in_type = switchboard_->get_env_char("HT_INPUT_TYPE")) {
    } else if (const char* in_type = std::getenv("HT_INPUT_TYPE")) {
        if (strcmp(in_type, "LEFT") == 0 || strcmp(in_type, "SINGLE") == 0) {
            input_type_ = ht::LEFT;
        } else if (strcmp(in_type, "RIGHT") == 0) {
            input_type_ = ht::RIGHT;
        } else if (strcmp(in_type, "MULTI") == 0 || strcmp(in_type, "BOTH") == 0) {
            input_type_ = ht::BOTH;
        } else if (strcmp(in_type, "RGB") == 0) {
            input_type_ = ht::RGB;
        }
    } else {
        input_type_ = ht::BOTH;
    }

    if (input_type_ == ht::RGB) {
        graph_.at(idf::image::RGB) = new mediapipe::CalculatorGraph();
    } else {
        if (input_type_ != ht::RIGHT)
            graph_.at(idf::image::LEFT_EYE) = new mediapipe::CalculatorGraph();
        if (input_type_ == ht::RIGHT || input_type_ == ht::BOTH)
            graph_.at(idf::image::RIGHT_EYE) = new mediapipe::CalculatorGraph();
    }
    publisher_.set_frame_count(input_type_);
}

void hand_tracking::start() {
    plugin::start();
    const std::string calculator_graph_config_contents =
#if !MEDIAPIPE_DISABLE_GPU
    #include "mediapipe/hand_tracking_desktop_live_gpu.pbtxt"
#else
    #include "mediapipe/hand_tracking_desktop_live.pbtxt"
#endif
        ; // NOLINT(whitespace/semicolon)
    auto         config = mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(calculator_graph_config_contents);
    absl::Status status;
    if (input_type_ == ht::RGB) {
        status = graph_[idf::image::RGB]->Initialize(config);
        if (!status.ok())
            throw std::runtime_error(std::string(status.message()));
    } else {
        if (input_type_ != ht::RIGHT) {
            status = graph_[idf::image::LEFT_EYE]->Initialize(config);
            if (!status.ok())
                throw std::runtime_error(std::string(status.message()));
        }
        if (input_type_ == ht::RIGHT || input_type_ == ht::BOTH) {
            status = graph_[idf::image::RIGHT_EYE]->Initialize(config);
            if (!status.ok())
                throw std::runtime_error(std::string(status.message()));
        }
    }

#if !MEDIAPIPE_DISABLE_GPU
    ABSL_LOG(INFO) << "Initialize the GPU.";
#endif
    for (auto& item : graph_) {
        if (item.second != nullptr) {
#if !MEDIAPIPE_DISABLE_GPU
            auto gpu_resources = mediapipe::GpuResources::Create();
            if (!gpu_resources.ok())
                throw std::runtime_error("");

            status = graph_.at(item.first)->SetGpuResources(std::move(gpu_resources).value());
            if (!status.ok())
                throw std::runtime_error(std::string(status.message()));
            gpu_helper_[item.first].InitializeForTest(graph_.at(item.first)->GetGpuResources().get());
#endif
            if (graph_.at(item.first) != nullptr) {
                auto status_or_poller = graph_.at(item.first)->AddOutputStreamPoller(kOutputStream);
                if (!status_or_poller.ok())
                    throw std::runtime_error("Error with output poller");
                publisher_.set_poller(item.first, new mediapipe::OutputStreamPoller(std::move(status_or_poller).value()));
            }
        }
    }
    for (auto& item : graph_) {
        if (item.second != nullptr) {
            status = graph_.at(item.first)->StartRun({});
            if (!status.ok())
                throw std::runtime_error("Error starting graph");
        }
    }
    // subscribe to the expected type
    switch (cam_type_) {
    case ht::WEBCAM:
        switchboard_->schedule<idf::monocular_cam_type>(
            id_, "webcam", [this](const switchboard::ptr<const idf::monocular_cam_type>& frame, std::size_t) {
                this->process(frame);
            });
        break;
    case ht::CAM:
        switchboard_->schedule<idf::binocular_cam_type>(
            id_, "cam", [this](const switchboard::ptr<const idf::binocular_cam_type>& img, std::size_t) {
                this->process(img);
            });
        break;
    case ht::ZED:
#ifdef HAVE_ZED
        switchboard_->schedule<idf::cam_type_zed>(id_, "cam_zed",
                                                  [this](const switchboard::ptr<const idf::cam_type_zed>& img, std::size_t) {
                                                      this->process(img);
                                                  });
#else
        throw std::runtime_error("No support for zed camera");
#endif
        break;
    default:
        throw std::runtime_error("Unexpected HT_INPUT entry. It must be one of webcam, cam, or zed (if supported).");
    }
    publisher_.start();
}

void hand_tracking::stop() {
    for (auto& item : graph_) {
        if (item.second != nullptr) {
            item.second->Cancel();
            auto status = item.second->CloseAllPacketSources();
            delete item.second;
            item.second = nullptr;
        }
    }
    publisher_.stop();
    plugin::stop();
}

hand_tracking::~hand_tracking() {
    for (auto& i : graph_)
        delete i.second;
}

void hand_tracking::process(const switchboard::ptr<const idf::cam_base_type>& frame) {
    current_images_.clear();
    pose_image pose_img;
    switch (frame->type) {
    case idf::camera::BINOCULAR:
        switch (input_type_) {
        case ht::BOTH:
            if (!frame->at(idf::image::LEFT_EYE).empty() && !frame->at(idf::image::RIGHT_EYE).empty()) {
                current_images_    = {{idf::image::LEFT_EYE, frame->at(idf::image::LEFT_EYE).clone()},
                                      {idf::image::RIGHT_EYE, frame->at(idf::image::RIGHT_EYE).clone()}};
                pose_img.eye_count = 2;
            } else if (frame->at(idf::image::LEFT_EYE).empty() && frame->at(idf::image::RIGHT_EYE).empty()) {
                spdlog::get("illixr")->info("[hand_tracking.plugin] Received empty frame, skipping");
                return;
            } else if (frame->at(idf::image::LEFT_EYE).empty()) {
                current_images_    = {{idf::image::LEFT_EYE, frame->at(idf::image::LEFT_EYE).clone()}};
                pose_img.eye_count = 1;
                pose_img.primary   = idf::units::LEFT_EYE;
            } else {
                if (frame->at(idf::image::RIGHT_EYE).empty()) {
                    spdlog::get("illixr")->info("[hand_tracking.plugin] Received empty frame, skipping");
                    return;
                }
                current_images_    = {{idf::image::RIGHT_EYE, frame->at(idf::image::RIGHT_EYE).clone()}};
                pose_img.eye_count = 1;
                pose_img.primary   = idf::units::RIGHT_EYE;
            }
            break;
        case ht::LEFT:
            if (frame->at(idf::image::LEFT_EYE).empty()) {
                spdlog::get("illixr")->info("[hand_tracking.plugin] Received empty frame, skipping");
                return;
            }
            current_images_    = {{idf::image::RIGHT_EYE, frame->at(idf::image::RIGHT_EYE).clone()}};
            pose_img.eye_count = 1;
            pose_img.primary   = idf::units::RIGHT_EYE;
            break;
        case ht::RIGHT:
            if (frame->at(idf::image::RIGHT_EYE).empty()) {
                spdlog::get("illixr")->info("[hand_tracking.plugin] Received empty frame, skipping");
                return;
            }
            current_images_    = {{idf::image::LEFT_EYE, frame->at(idf::image::LEFT_EYE).clone()}};
            pose_img.eye_count = 1;
            pose_img.primary   = idf::units::LEFT_EYE;
            break;
        case ht::RGB:
            spdlog::get("illixr")->warn("[hand_tracking.plugin] RGB not provided by binocular view");
            break;
        }
        pose_img.insert(current_images_.begin(), current_images_.end());
        break;
    case idf::camera::MONOCULAR: {
        if (frame->at(idf::image::RGB).empty()) {
            spdlog::get("illixr")->info("[hand_tracking.plugin] Received empty frame, skipping");
            return;
        }
        cv::Mat temp_img(frame->at(idf::image::RGB).clone());
        cv::flip(temp_img, temp_img, 1);
        img_convert(temp_img);
        current_images_    = {{idf::image::LEFT_EYE, temp_img}};
        pose_img.eye_count = 1;
        pose_img.primary   = idf::units::LEFT_EYE;
        pose_img.insert(current_images_.begin(), current_images_.end());
        break;
    }
    case idf::camera::RGB_DEPTH: {
        if (frame->at(idf::image::LEFT_EYE).empty() && frame->at(idf::image::RGB).empty()) {
            spdlog::get("illixr")->info("[hand_tracking.plugin] Received empty frame, skipping");
            return;
        }
        current_images_    = {{idf::image::LEFT_EYE, frame->at(idf::image::RGB).clone()}};
        pose_img.eye_count = 1;
        pose_img.primary   = idf::units::LEFT_EYE;
        pose_img.insert(current_images_.begin(), current_images_.end());
        break;
    }
    case idf::camera::ZED: {
#ifdef HAVE_ZED
        switch (input_type_) {
        case ht::BOTH: {
            if (!frame->at(idf::image::LEFT_EYE).empty() && !frame->at(idf::image::RIGHT_EYE).empty()) {
                cv::Mat tempL(frame->at(idf::image::LEFT_EYE).clone());
                cv::Mat tempR(frame->at(idf::image::RIGHT_EYE).clone());
                img_convert(tempL, true);
                img_convert(tempR, true);
                current_images_    = {{idf::image::LEFT_EYE, tempL}, {idf::image::RIGHT_EYE, tempR}};
                pose_img.eye_count = 2;
                pose_img.primary   = idf::units::LEFT_EYE;
            } else if (frame->at(idf::image::LEFT_EYE).empty() && frame->at(idf::image::RIGHT_EYE).empty()) {
                spdlog::get("illixr")->info("[hand_tracking.plugin] Received empty frame, skipping");
                return;
            } else if (frame->at(idf::image::LEFT_EYE).empty()) {
                cv::Mat temp(frame->at(idf::image::RIGHT_EYE).clone());
                img_convert(temp, true);
                current_images_    = {{idf::image::RIGHT_EYE, temp}};
                pose_img.eye_count = 1;
                pose_img.primary   = idf::units::RIGHT_EYE;
            } else {
                cv::Mat temp(frame->at(idf::image::LEFT_EYE).clone());
                img_convert(temp, true);
                current_images_    = {{idf::image::LEFT_EYE, temp}};
                pose_img.eye_count = 1;
                pose_img.primary   = idf::units::LEFT_EYE;
            }
            break;
        }
        case ht::LEFT: {
            if (frame->at(idf::image::LEFT_EYE).empty()) {
                spdlog::get("illixr")->info("[hand_tracking.plugin] Received empty frame, skipping");
                return;
            }

            cv::Mat temp(frame->at(idf::image::LEFT_EYE).clone());
            img_convert(temp, true);
            current_images_    = {{idf::image::LEFT_EYE, temp}};
            pose_img.eye_count = 1;
            pose_img.primary   = idf::units::LEFT_EYE;
            break;
        }
        case ht::RIGHT: {
            if (frame->at(idf::image::RIGHT_EYE).empty()) {
                spdlog::get("illixr")->info("[hand_tracking.plugin] Received empty frame, skipping");
                return;
            }
            cv::Mat temp(frame->at(idf::image::RIGHT_EYE).clone());
            img_convert(temp, true);
            current_images_    = {{idf::image::RIGHT_EYE, temp}};
            pose_img.eye_count = 1;
            pose_img.primary   = idf::units::RIGHT_EYE;
            break;
        }
        case ht::RGB: {
            if (frame->at(idf::image::LEFT_EYE).empty() && frame->at(idf::image::RGB).empty()) {
                spdlog::get("illixr")->info("[hand_tracking.plugin] Received empty frame, skipping");
                return;
            }
            cv::Mat temp(frame->at(idf::image::RGB).clone());
            img_convert(temp, true);
            current_images_    = {{idf::image::LEFT_EYE, temp}};
            pose_img.eye_count = 1;
            pose_img.primary   = idf::units::LEFT_EYE;
            break;
        }
        }
        if (frame->find(idf::image::DEPTH) != frame->end()) {
            if (!pose_img.images[idf::image::DEPTH].empty()) {
                pose_img.images[idf::image::DEPTH] = frame->at(idf::image::DEPTH).clone();
                pose_img.depth_valid               = true;
            }
        }
        if (frame->find(idf::image::CONFIDENCE) != frame->end()) {
            if (!pose_img.images[idf::image::CONFIDENCE].empty()) {
                pose_img.images[idf::image::CONFIDENCE] = frame->at(idf::image::CONFIDENCE).clone();
                pose_img.confidence_valid_              = true;
            }
        }
        pose_img.poses      = dynamic_cast<const idf::cam_type_zed*>(frame.get())->poses;
        pose_img.pose_valid = true;
        break;
#endif
    }
    default:
        throw std::runtime_error("Unexpected frame type");
    }
    pose_img.insert(current_images_.begin(), current_images_.end());

    size_t frame_id = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    for (const auto& input : current_images_) {
        auto input_frame =
            absl::make_unique<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGB, input.second.cols, input.second.rows,
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
        image_data.set_first_person(first_person_);

        auto img_ptr = absl::make_unique<mediapipe::ImageData>(image_data);
        auto img_status =
            graph_.at(input.first)
                ->AddPacketToInputStream(kImageDataTag,
                                         mediapipe::Adopt(img_ptr.release()).At(mediapipe::Timestamp(frame_timestamp_us)));

        if (!img_status.ok())
            throw std::runtime_error(std::string(img_status.message()));

#if !MEDIAPIPE_DISABLE_GPU
        auto gl_status =
            gpu_helper_.at(input.first)
                .RunInGlContext([&input_frame, &frame_timestamp_us, &graph = graph_.at(input.first),
                                 &gpu_helper = gpu_helper_.at(input.first)]() -> absl::Status {
                    // Convert ImageFrame to GpuBuffer.
                    auto texture   = gpu_helper.CreateSourceTexture(*input_frame.get());
                    auto gpu_frame = texture.GetFrame<mediapipe::GpuBuffer>();
                    glFlush();
                    texture.Release();
                    // Send GPU image packet into the graph.
                    auto submit_status = graph->AddPacketToInputStream(
                        kInputStream, mediapipe::Adopt(gpu_frame.release()).At(mediapipe::Timestamp(frame_timestamp_us)));
                    if (!submit_status.ok())
                        throw std::runtime_error(std::string(submit_status.message()));
                    return absl::OkStatus();
                });
        if (!gl_status.ok())
            throw std::runtime_error(std::string(gl_status.message()));
#else
        auto submit_status =
            graph_.at(input.first)
                ->AddPacketToInputStream(kInputStream,
                                         mediapipe::Adopt(input_frame.release()).At(mediapipe::Timestamp(frame_timestamp_us)));
        if (!submit_status.ok())
            throw std::runtime_error(std::string(submit_status.message()));
#endif
    }
    publisher_.add_raw(frame_id, pose_img);
}

// ###############################################################################################

PLUGIN_MAIN(hand_tracking)
