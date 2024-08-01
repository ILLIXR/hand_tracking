#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include "plugin.hpp"

#include "mediapipe/framework/deps/status_macros.h"
#include "mediapipe/framework/deps/file_helpers.h"
#include "mediapipe/framework/calculator.pb.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image_frame_opencv.h"
#include "mediapipe/calculators/util/illixr_data.h"

#include <opencv2/opencv.hpp>

using namespace ILLIXR;

ABSL_FLAG(std::string, calculator_graph_config_file, "",
          "Name of the file containing text formatted CalculatorGraphConfig proto.");

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "output_video";


[[maybe_unused]] hand_tracking::hand_tracking(const std::string& name_, phonebook* pb_)
        : threadloop{name_, pb_}
        , _switchboard{pb_->lookup_impl<switchboard>()}
        , _ht_config_file{getenv("HT_CONFIG_FILE")}
        , _camera{_switchboard->get_buffered_reader<cam_type>("cam")}
        , _ht_publisher{_switchboard->get_writer<ht_frame>("ht")} {
    std::string calculator_graph_config_contents;
    MP_RAISE_IF_ERROR(mediapipe::file::GetContents(
            std::getenv("CALCULATOR_CONFIG_FILE"),
            &calculator_graph_config_contents), "Failed to get config contents");
    auto config = mediapipe::ParseTextProtoOrDie<mediapipe::CalculatorGraphConfig>(calculator_graph_config_contents);

    MP_RAISE_IF_ERROR(_graph.Initialize(config), "Graph initialize failed");

    MP_ASSIGN_OR_RAISE(mediapipe::OutputStreamPoller, _poller,
                       _graph.AddOutputStreamPoller(kOutputStream),
                       "Error with ourpur poller");
    MP_RAISE_IF_ERROR(_graph.StartRun({}), "Error starting graph");
}

void hand_tracking::_p_one_iteration() {
    _cam = _camera.size() == 0 ? nullptr : _camera.dequeue();
    if(_cam == nullptr)
        return;
    cv::Mat images[] = {_cam->img0.clone(),
                        _cam->img1.clone()};
    cv::Mat camera_frame[_image_count];
    cv::Mat input_frame_mat[_image_count];
    std::unique_ptr<mediapipe::ImageFrame> input_frame[2];
    for(auto i = 0; i < _image_count; i++) {
        cv::cvtColor(images[i], camera_frame[i], cv::COLOR_BGR2RGB);
        input_frame[i] = absl::make_unique<mediapipe::ImageFrame>(
                mediapipe::ImageFormat::SRGB, camera_frame[i].cols, camera_frame[i].rows,
                mediapipe::ImageFrame::kDefaultAlignmentBoundary);
        input_frame_mat[i] = mediapipe::formats::MatView(input_frame[i].get());
        camera_frame[i].copyTo(input_frame_mat[i]);

// Send image packet into the graph.
        size_t frame_timestamp_us = cv::getTickCount() / (double) cv::getTickFrequency() * 1e6;


        MP_RAISE_IF_ERROR(_graph.AddPacketToInputStream(
                kInputStream, mediapipe::Adopt(input_frame[i].release())
                        .At(mediapipe::Timestamp(frame_timestamp_us))), "Add to input stream failed");

        // Get the graph result packet, or stop if that fails.
        mediapipe::Packet packet;
        if(!_poller->Next(&packet)) break;
        auto& output_frame = packet.Get<mediapipe::ILLIXR::illixr_ht_frame>();
        // Convert back to opencv for display or saving.

        _ht_publisher.put(_ht_publisher.allocate<ht_frame>(ht_frame{output_frame.image,
                                                                    output_frame.left_palm,
                                                                    output_frame.right_palm,
                                                                    output_frame.left_hand,
                                                                    output_frame.right_hand,
                                                                    output_frame.left_confidence,
                                                                    output_frame.right_confidence,
                                                                    output_frame.left_hand_points,
                                                                    output_frame.right_hand_points}));


    }
}


PLUGIN_MAIN(hand_tracking)
