#pragma once

#include "illixr/threadloop.hpp"
#include "illixr/phonebook.hpp"
#include "illixr/switchboard.hpp"
#include "illixr/opencv_data_types.hpp"
#include "illixr/hand_tracking_data.hpp"

#include "mediapipe/framework/calculator_graph.h"


const int _image_count = 2;

namespace ILLIXR {
class hand_tracking : public threadloop {
public:
    [[maybe_unused]] hand_tracking(const std::string& name_, phonebook* pb_);

    void _p_thread_setup() override {}
    void _p_one_iteration() override;
private:
    const std::shared_ptr<switchboard> _switchboard;
    std::string _ht_config_file;

    mediapipe::CalculatorGraph _graph;
    switchboard::buffered_reader<cam_type> _camera;
    switchboard::ptr<const cam_type> _cam;
    switchboard::writer<ht_type> _ht_publisher;
    mediapipe::OutputStreamPoller* _poller = nullptr;

};
}
