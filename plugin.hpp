#pragma once

#include "illixr/plugin.hpp"
#include "illixr/phonebook.hpp"
#include "illixr/switchboard.hpp"
#include "illixr/opencv_data_types.hpp"
#include "illixr/hand_tracking_data.hpp"
#include "illixr/threadloop.hpp"

#include "mediapipe/framework/calculator_graph.h"

#include <opencv2/opencv.hpp>


namespace ILLIXR {
namespace ht {
    enum input_type {
        LEFT,
        RIGHT,
        BOTH,
        RGB
    };

    enum cam_type {
        CAM,
        WEBCAM,
        ZED
    };
}

typedef std::map<image::image_type, cv::Mat> image_map;

class hand_tracking_publisher : public threadloop {
    public:
        hand_tracking_publisher(const std::string& name_, phonebook *pb_,
                                std::shared_ptr<mediapipe::CalculatorGraph> graph_);
        ~hand_tracking_publisher() override;
        void set_framecount(ht::input_type it);
        void start() override;
        void add_raw(size_t id, image_map&& img);
    protected:
        skip_option _p_should_skip() override;
        void _p_one_iteration() override;
    private:
        const std::shared_ptr<switchboard> _switchboard;
        switchboard::writer<ht_frame> _ht_publisher;
        mediapipe::OutputStreamPoller* _poller = nullptr;
        std::shared_ptr<mediapipe::CalculatorGraph> _graph;
        int _framecount = 0;
        mediapipe::Packet _packet;
        std::map<image::image_type, cv::Mat> _results_images;
        std::map<image::image_type, ht_detection> _detections;
        size_t _last_frame_id = 0;
        std::unordered_map<size_t, image_map> _raw_images;
        image_map _current_raw;
    };


class hand_tracking : public plugin {
public:
    [[maybe_unused]] hand_tracking(const std::string& name_, phonebook* pb_);

    void start() override;
    void process(const switchboard::ptr<const cam_base_type>& frame);
    void stop() override;
private:
    const std::shared_ptr<switchboard> _switchboard;
    std::shared_ptr<mediapipe::CalculatorGraph> _graph;
    hand_tracking_publisher _publisher;
    std::string _ht_config_file;
    ht::input_type _input_type;
    ht::cam_type _cam_type;
    image_map _current_images;
};
}
