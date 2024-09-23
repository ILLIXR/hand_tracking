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
constexpr char kPointOfView[] = "first_person";

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
        , _graph{mediapipe::CalculatorGraph()}
        , _publisher{"hand_tracking_publisher", pb_} {
    if (const char* in_type = _switchboard->get_env_char("HT_INPUT_TYPE")) {
        if (strcmp(in_type, "LEFT") == 0 || strcmp(in_type, "SINGLE") == 0) {
            _input_type = ht::LEFT;
        } else if (strcmp(in_type, "RIGHT") == 0) {
            _input_type = ht::RIGHT;
        } else if (strcmp(in_type, "MULTI") == 0 || strcmp(in_type, "BOTH") == 0) {
            _input_type = ht::BOTH;
        } else if(strcmp(in_type, "RGB") == 0) {
            _input_type = ht::RGB;
        }
    } else {
        _input_type = ht::BOTH;
    }

    if (const char* in_src = _switchboard->get_env_char("HT_INPUT")) {
        if (strcmp(in_src, "zed") == 0) {
            _cam_type = ht::ZED;
            _first_person = true;
        } else if (strcmp(in_src, "cam") == 0) {
            _cam_type = ht::CAM;
            _first_person = true;
        } else if (strcmp(in_src, "webcam") == 0) {
            _cam_type = ht::WEBCAM;
            _input_type = ht::RGB;
            _first_person = false;
        } else {
            throw std::runtime_error("HT_INPUT did not have a valid type");
        }
    } else {
        throw std::runtime_error("HT_INPUT was not specified");
    }
    _publisher.set_framecount(_input_type);
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
        throw std::runtime_error(std::string(status.message()));

    auto status_or_poller = _graph.AddOutputStreamPoller(kOutputStream);
    if (!status_or_poller.ok())
        throw std::runtime_error("Error with output poller");
    _publisher.set_poller(new mediapipe::OutputStreamPoller(std::move(status_or_poller).value()));

    status = _graph.StartRun({});
    if (!status.ok())
        throw std::runtime_error("Error starting graph");
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

void hand_tracking::process(const switchboard::ptr<const cam_base_type>& frame) {
    _current_images.clear();
    switch (frame->type) {
        case ::ILLIXR::image::BINOCULAR:
            switch (_input_type) {
                case ht::BOTH:
                    _current_images = {{::ILLIXR::image::LEFT,  frame->at(::ILLIXR::image::LEFT).clone()},
                                       {::ILLIXR::image::RIGHT, frame->at(::ILLIXR::image::RIGHT).clone()}};
                    break;
                case ht::LEFT:
                    _current_images = {{::ILLIXR::image::LEFT, frame->at(::ILLIXR::image::LEFT).clone()}};
                    break;
                case ht::RIGHT:
                    _current_images = {{::ILLIXR::image::RIGHT, frame->at(::ILLIXR::image::RIGHT).clone()}};
                    break;
                case ht::RGB:
                    std::cout << "RGB not provided by binocular view";
                    break;
            }
            break;
        case ::ILLIXR::image::MONOCULAR: {
            cv::Mat temp_img(frame->at(::ILLIXR::image::RGB).clone());
            cv::flip(temp_img, temp_img, 1);
            img_convert(temp_img);
            _current_images = {{::ILLIXR::image::RGB, temp_img}};
            break;
        }
        case ::ILLIXR::image::RGB_DEPTH: {
            _current_images = {{::ILLIXR::image::RGB, frame->at(::ILLIXR::image::RGB).clone()}};
            break;
        }
        case ::ILLIXR::image::ZED: {
            switch (_input_type) {
                case ht::BOTH: {
                    cv::Mat tempL(frame->at(::ILLIXR::image::LEFT).clone());
                    cv::Mat tempR(frame->at(::ILLIXR::image::RIGHT).clone());
                    img_convert(tempL);
                    img_convert(tempR);
                    _current_images = {{::ILLIXR::image::LEFT,  tempL},
                                       {::ILLIXR::image::RIGHT, tempR}};
                    break;
                }
                case ht::LEFT: {
                    cv::Mat temp(frame->at(::ILLIXR::image::LEFT).clone());
                    img_convert(temp);
                    _current_images = {{::ILLIXR::image::LEFT, temp}};
                    break;
                }
                case ht::RIGHT: {
                    cv::Mat temp(frame->at(::ILLIXR::image::RIGHT).clone());
                    img_convert(temp);
                    _current_images = {{::ILLIXR::image::RIGHT, temp}};
                    break;
                }
                case ht::RGB: {
                    _current_images = {{::ILLIXR::image::RGB, frame->at(::ILLIXR::image::RGB).clone()}};
                    break;
                }
            }
            break;
        }
    }

    size_t frame_id = std::chrono::high_resolution_clock::now().time_since_epoch().count();

    for (const auto &input: _current_images) {
        auto input_frame = absl::make_unique<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGB,
                                                                    input.second.cols,
                                                                    input.second.rows,
                                                                    mediapipe::ImageFrame::kDefaultAlignmentBoundary,
                                                                    input.first,
                                                                    frame_id);
        cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());
        input.second.copyTo(input_frame_mat);

        // Send image _packet into the graph.
        size_t frame_timestamp_us = std::chrono::high_resolution_clock::now().time_since_epoch().count();

        MP_RAISE_IF_ERROR(
                _graph.AddPacketToInputStream(kInputStream,
                                              mediapipe::Adopt(input_frame.release()).At(
                                                      mediapipe::Timestamp(frame_timestamp_us))),
                "Add to input stream failed");
        auto pov = absl::make_unique<bool>(_first_person);
        MP_RAISE_IF_ERROR(
                _graph.AddPacketToInputStream(kPointOfView,
                                              mediapipe::Adopt(pov.release()).At(
                                                      mediapipe::Timestamp(frame_timestamp_us))),
                "Add pov failed");
    }
    _publisher.add_raw(frame_id, std::move(_current_images));
}

hand_tracking_publisher::hand_tracking_publisher(const std::string &name_, ILLIXR::phonebook *pb_)
        : threadloop(name_, pb_)
        , _switchboard{pb_->lookup_impl<switchboard>()}
        , _ht_publisher{_switchboard->get_writer<ht_frame>("ht")} { }

hand_tracking_publisher::~hand_tracking_publisher() {
    delete _poller;
}

void hand_tracking_publisher::add_raw(const size_t id, image_map&& img) {
    _raw_images.emplace(id, img);
}

threadloop::skip_option hand_tracking_publisher::_p_should_skip() {
    // Get the graph result _packet, or stop if that fails.
    if (_poller->Next(&_packet))
        return threadloop::skip_option::run;
    return threadloop::skip_option::skip_and_spin;
}

void hand_tracking_publisher::_p_one_iteration() {
    auto &output_frame = _packet.Get<mediapipe::ILLIXR::illixr_ht_frame>();
    size_t end_time = _packet.Timestamp().Value();
    size_t start_time = output_frame.image_id;
    std::cout << end_time << "  " << start_time << "  " << end_time - start_time<< std::endl;

    ::ILLIXR::image::image_type out_type;
    switch(output_frame.type) {
        case ::ILLIXR::image::LEFT:
            out_type = ::ILLIXR::image::LEFT_PROCESSED;
            break;
        case ::ILLIXR::image::RIGHT:
            out_type = ::ILLIXR::image::RIGHT_PROCESSED;
            break;
        case ::ILLIXR::image::RGB:
            out_type = ::ILLIXR::image::RGB_PROCESSED;
            break;
        default:
            break;
    }

    if (_last_frame_id != output_frame.image_id) {
        _current_raw = _raw_images.extract(output_frame.image_id).mapped();
        if (_framecount == 2 && _detections.size() == 1) {
            // we are missing a component so drop the partial frame
            _results_images.clear();
            _detections.clear();
        }
    }
    _results_images.emplace(output_frame.type, _current_raw.at(output_frame.type));
    _results_images.emplace(out_type, *output_frame.image);

    _detections.emplace(out_type, ht_detection{end_time - start_time, output_frame.left_palm, output_frame.right_palm,
                                               output_frame.left_hand, output_frame.right_hand, output_frame.left_confidence,
                                               output_frame.right_confidence, output_frame.left_hand_points,
                                               output_frame.right_hand_points});
    _last_frame_id = output_frame.image_id;
    if (_detections.size() == _framecount) {
        // Convert back to opencv for display or saving.
        time_point current_time(
                std::chrono::duration<long, std::nano>{std::chrono::system_clock::now().time_since_epoch().count()});
        _ht_publisher.put(_ht_publisher.allocate<ht_frame>(
                ht_frame{current_time, _results_images, _detections}));
        _results_images.clear();
        _detections.clear();
    }
}


void hand_tracking_publisher::set_framecount(ht::input_type it) {
    if (it == ht::BOTH) {
        _framecount = 2;
    } else {
        _framecount = 1;
    }
}

PLUGIN_MAIN(hand_tracking)
