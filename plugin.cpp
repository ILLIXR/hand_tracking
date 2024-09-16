#include "absl/flags/parse.h"

#include "plugin.hpp"

#include "mediapipe/framework/deps/status_macros.h"
#include "mediapipe/framework/deps/file_helpers.h"
#include "mediapipe/framework/calculator.pb.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/calculators/util/illixr_data.h"

using namespace ILLIXR;

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "illixr_data";

void img_convert(cv::Mat& img) {
    switch (img.type()) {
        case CV_8UC1:
            cv::cvtColor(img, img, cv::COLOR_GRAY2RGB);
            break;
        case CV_8UC3:
            break;
        case CV_8UC4:
            cv::cvtColor(img, img, cv::COLOR_RGBA2RGB);
            break;
    }
}

[[maybe_unused]] hand_tracking::hand_tracking(const std::string& name_, phonebook* pb_)
        : plugin{name_, pb_}
        , _switchboard{pb_->lookup_impl<switchboard>()}
        , _ht_publisher{_switchboard->get_writer<ht_frame>("ht")} {
    const char* in_type = std::getenv("HT_INPUT_TYPE");
    if (in_type) {
        if (strcmp(in_type, "LEFT") == 0 || strcmp(in_type, "SINGLE") == 0) {
            _input_type = ht::LEFT;
        } else if (strcmp(in_type, "RIGHT") == 0) {
            _input_type = ht::RIGHT;
        } else if (strcmp(in_type, "MULTI") == 0) {
            _input_type = ht::BOTH;
        }
    } else {
        _input_type = ht::BOTH;
    }

}

void hand_tracking::start() {
    plugin::start();
    std::string calculator_graph_config_contents;
    const char* cfile = std::getenv("CALCULATOR_CONFIG_FILE");

    auto status = mediapipe::file::GetContents(cfile, &calculator_graph_config_contents);
    if (!status.ok())
        throw std::runtime_error("Failed to get config contents");
    auto config = mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(calculator_graph_config_contents);

    status = _graph.Initialize(config);
    if (!status.ok())
        throw std::runtime_error("Graph initialize failed");

    auto status_or_poller = _graph.AddOutputStreamPoller(kOutputStream);
    if (!status_or_poller.ok())
        throw std::runtime_error("Error with output poller");
    _poller = new mediapipe::OutputStreamPoller(std::move(status_or_poller).value());

    status = _graph.StartRun({});
    if (!status.ok())
        throw std::runtime_error("Error starting graph");
    // subscribe to any possible input types
    _switchboard->schedule<monocular_cam_type>(id, "webcam", [this](const switchboard::ptr<const monocular_cam_type>& frame, std::size_t) {
        this->process(frame);
    });
    _switchboard->schedule<binocular_cam_type>(id, "cam", [this](const switchboard::ptr<const binocular_cam_type>& img, std::size_t) {
        this->process(img);
    });
    _switchboard->schedule<cam_type_zed>(id, "cam_zed", [this](const switchboard::ptr<const cam_type_zed>& img, std::size_t) {
        this->process(img);
    });

}

void hand_tracking::process(const switchboard::ptr<const cam_base_type>& frame) {
    time_point start_time(std::chrono::duration<long, std::nano>{std::chrono::system_clock::now().time_since_epoch().count()});
    _current_images.clear();
    switch(frame->type) {
        case BINOCULAR:
            switch (_input_type) {
                case ht::BOTH:
                    _current_images = {{LEFT,  frame->at(LEFT).clone()},
                                       {RIGHT, frame->at(RIGHT).clone()}};
                    break;
                case ht::LEFT:
                    _current_images = {{LEFT, frame->at(LEFT).clone()}};
                    break;
                case ht::RIGHT:
                    _current_images = {{RIGHT, frame->at(RIGHT).clone()}};
                    break;
                case ht::RGB:
                    std::cout << "RGB not provided by binocular view";
                    break;
            }
            break;
        case MONOCULAR: {
            cv::Mat temp_img(frame->at(RGB).clone());
            cv::flip(temp_img, temp_img, 1);
            img_convert(temp_img);
            _current_images = {{RGB, temp_img}};
            break;
        }
        case RGB_DEPTH: {
            _current_images = {{RGB, frame->at(RGB).clone()}};
            break;
        }
        case ZED: {
            switch (_input_type) {
                case ht::BOTH: {
                    cv::Mat tempL(frame->at(LEFT).clone());
                    cv::Mat tempR(frame->at(RIGHT).clone());
                    img_convert(tempL);
                    img_convert(tempR);
                    _current_images = {{LEFT,  tempL},
                                       {RIGHT, tempR}};
                    break;
                }
                case ht::LEFT: {
                    cv::Mat temp(frame->at(LEFT).clone());
                    img_convert(temp);
                    _current_images = {{LEFT, temp}};
                    break;
                }
                case ht::RIGHT: {
                    cv::Mat temp(frame->at(RIGHT).clone());
                    img_convert(temp);
                    _current_images = {{RIGHT, temp}};
                    break;
                }
                case ht::RGB: {
                    _current_images = {{RGB, frame->at(RGB).clone()}};
                    break;
                }
            }
            break;
        }
    }

    std::map<image_type, cv::Mat> results_images;
    std::map<image_type, ht_detection> detections;
    for(const auto &input: _current_images) {
        auto input_frame = absl::make_unique<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGB, input.second.cols,
                                                                    input.second.rows,
                                                                    mediapipe::ImageFrame::kDefaultAlignmentBoundary);
        cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());
        input.second.copyTo(input_frame_mat);

        // Send image packet into the graph.
        size_t frame_timestamp_us = (double) cv::getTickCount() / (double) cv::getTickFrequency() * 1e6;

        MP_RAISE_IF_ERROR(
                _graph.AddPacketToInputStream(kInputStream,
                                              mediapipe::Adopt(input_frame.release()).At(
                                                      mediapipe::Timestamp(frame_timestamp_us))),
                "Add to input stream failed");

        // Get the graph result packet, or stop if that fails.
        mediapipe::Packet packet;
        if (!_poller->Next(&packet))
            return;
        auto &output_frame = packet.Get<mediapipe::ILLIXR::illixr_ht_frame>();
        results_images.emplace(input.first, input.second.clone());
        image_type out_type;
        switch(input.first) {
            case LEFT:
                out_type = LEFT_PROCESSED;
                break;
            case RIGHT:
                out_type = RIGHT_PROCESSED;
                break;
            case RGB:
                out_type = RGB_PROCESSED;
                break;
            default:
                break;
        }
        results_images.emplace(out_type, *output_frame.image);
        detections.emplace(out_type, ht_detection{output_frame.left_palm, output_frame.right_palm,
                                                  output_frame.left_hand, output_frame.right_hand, output_frame.left_confidence,
                                                  output_frame.right_confidence, output_frame.left_hand_points,
                                                  output_frame.right_hand_points});
    }
    // Convert back to opencv for display or saving.
    time_point current_time(std::chrono::duration<long, std::nano>{std::chrono::system_clock::now().time_since_epoch().count()});
    _ht_publisher.put(_ht_publisher.allocate<ht_frame>(ht_frame{start_time, current_time, results_images, detections}));
}


PLUGIN_MAIN(hand_tracking)
