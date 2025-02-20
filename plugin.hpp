#pragma once

#include "hand_tracking_publisher.hpp"
#include "illixr/phonebook.hpp"
#include "illixr/plugin.hpp"
#include "illixr/switchboard.hpp"
#include "mediapipe/framework/calculator_graph.h"
#if !MEDIAPIPE_DISABLE_GPU
    #include "mediapipe/gpu/gl_calculator_helper.h"
#endif

#include <opencv2/opencv.hpp>

namespace ILLIXR {

class hand_tracking : public plugin {
public:
    [[maybe_unused]] hand_tracking(const std::string& name_, phonebook* pb_);
    ~hand_tracking() override;

    void process(const switchboard::ptr<const data_format::cam_base_type>& frame);
    void start() override;
    void stop() override;

private:
    ht::cam_type get_cam_type();

    const std::shared_ptr<switchboard>                                    switchboard_;
    std::map<data_format::image::image_type, mediapipe::CalculatorGraph*> graph_;
    ht::cam_type                                                          cam_type_;
    hand_tracking_publisher                                               publisher_;
    std::string                                                           ht_config_file_;
    ht::input_type                                                        input_type_;
    image_map                                                             current_images_;
    bool                                                                  first_person_ = true;
#if !MEDIAPIPE_DISABLE_GPU
    std::map<data_format::image::image_type, mediapipe::GlCalculatorHelper> gpu_helper_;
#endif
};
} // namespace ILLIXR
