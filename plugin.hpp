#pragma once

#include "illixr/plugin.hpp"
#include "illixr/phonebook.hpp"
#include "illixr/switchboard.hpp"
#include "hand_tracking_publisher.hpp"

#include "mediapipe/framework/calculator_graph.h"

#include <opencv2/opencv.hpp>

#if !MEDIAPIPE_DISABLE_GPU
#include "mediapipe/gpu/gl_calculator_helper.h"
#endif

namespace ILLIXR {

class hand_tracking : public plugin {
public:
    [[maybe_unused]] hand_tracking(const std::string& name_, phonebook* pb_);

    void start() override;
    void process(const switchboard::ptr<const cam_base_type>& frame);
    void stop() override;
    ~hand_tracking() override;
private:
    const std::shared_ptr<switchboard> _switchboard;
    std::map<::ILLIXR::image::image_type, mediapipe::CalculatorGraph*> _graph;
    ht::cam_type _cam_type;
    hand_tracking_publisher _publisher;
    std::string _ht_config_file;
    ht::input_type _input_type;
    image_map _current_images;
    bool _first_person = true;
#if !MEDIAPIPE_DISABLE_GPU
    std::map<::ILLIXR::image::image_type, mediapipe::GlCalculatorHelper> _gpu_helper;
#endif
};
}
