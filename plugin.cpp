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

constexpr char kInputStream[] = "input_video";
constexpr char kOutputStream[] = "illixr_data";


[[maybe_unused]] hand_tracking::hand_tracking(const std::string& name_, phonebook* pb_)
    : plugin{name_, pb_}
    , _switchboard{pb_->lookup_impl<switchboard>()}
    //, _frame{_switchboard->get_buffered_reader<frame_type>("webcam")}
    , _ht_publisher{_switchboard->get_writer<ht_frame>("ht")}
    , _clock{pb->lookup_impl<RelativeClock>()} {}

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
    _switchboard->schedule<frame_type>(id, "webcam", [this](const switchboard::ptr<const frame_type>& frame, std::size_t) {
        this->process(frame);
    });

}

void hand_tracking::process(const switchboard::ptr<const cam_base_type>& frame) {
    cv::Mat image = frame->img().clone();
    cv::Mat camera_frame;
    cv::cvtColor(image, camera_frame, cv::COLOR_BGR2RGB);
    cv::flip(camera_frame, camera_frame, /*flipcode=HORIZONTAL*/ 1);
    auto input_frame = absl::make_unique<mediapipe::ImageFrame>(mediapipe::ImageFormat::SRGB, camera_frame.cols, camera_frame.rows, mediapipe::ImageFrame::kDefaultAlignmentBoundary);
    cv::Mat input_frame_mat = mediapipe::formats::MatView(input_frame.get());
    camera_frame.copyTo(input_frame_mat);

        // Send image packet into the graph.
    size_t frame_timestamp_us = (double)cv::getTickCount() / (double) cv::getTickFrequency() * 1e6;

    MP_RAISE_IF_ERROR(
            _graph.AddPacketToInputStream(kInputStream,
                                          mediapipe::Adopt(input_frame.release()).At(mediapipe::Timestamp(frame_timestamp_us))),
            "Add to input stream failed");

    // Get the graph result packet, or stop if that fails.
    mediapipe::Packet packet;
    if (!_poller->Next(&packet))
        return;
    auto& output_frame = packet.Get<mediapipe::ILLIXR::illixr_ht_frame>();
    // Convert back to opencv for display or saving.

    _ht_publisher.put(_ht_publisher.allocate<ht_frame>(
            ht_frame{_clock->now(), output_frame.image, output_frame.left_palm, output_frame.right_palm,
                     output_frame.left_hand, output_frame.right_hand, output_frame.left_confidence,
                     output_frame.right_confidence, output_frame.left_hand_points,
                     output_frame.right_hand_points}));
}


PLUGIN_MAIN(hand_tracking)
