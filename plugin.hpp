#pragma once

#include "illixr/plugin.hpp"
#include "illixr/phonebook.hpp"
#include "illixr/switchboard.hpp"
#include "illixr/opencv_data_types.hpp"
#include "illixr/hand_tracking_data.hpp"

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
}
class hand_tracking : public plugin {
public:
    [[maybe_unused]] hand_tracking(const std::string& name_, phonebook* pb_);

    void start() override;
    void process(const switchboard::ptr<const cam_base_type>& frame);
    //void _p_one_iteration() override;
private:
    const std::shared_ptr<switchboard> _switchboard;
    std::string _ht_config_file;
    mediapipe::CalculatorGraph _graph;
    //switchboard::buffered_reader<frame_type> _frame;
    switchboard::writer<ht_frame> _ht_publisher;
    std::shared_ptr<RelativeClock> _clock;
    mediapipe::OutputStreamPoller* _poller = nullptr;
    ht::input_type _input_type;
    std::map<image_type, cv::Mat> _current_images;
};
}
