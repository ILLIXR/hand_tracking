#pragma once

#include "illixr/plugin.hpp"
#include "illixr/phonebook.hpp"
#include "illixr/switchboard.hpp"
#include "illixr/opencv_data_types.hpp"
#include "illixr/hand_tracking_data.hpp"
#include "illixr/threadloop.hpp"

#include "mediapipe/framework/calculator_graph.h"

#include <opencv2/opencv.hpp>

#if !MEDIAPIPE_DISABLE_GPU
#include "mediapipe/gpu/gl_calculator_helper.h"
#endif
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
    hand_tracking_publisher(const std::string& name_, phonebook *pb_);
    ~hand_tracking_publisher() override;
    void set_framecount(ht::input_type it);
    void add_raw(size_t id, image_map&& img);
    void set_poller(::ILLIXR::image::image_type im_type, mediapipe::OutputStreamPoller* plr) {
        _poller.at(im_type) = plr;
        _count++;
    }

protected:
    skip_option _p_should_skip() override;
    void _p_one_iteration() override;

private:
    const std::shared_ptr<switchboard> _switchboard;
    switchboard::writer<ht_frame> _ht_publisher;
    std::map<::ILLIXR::image::image_type, mediapipe::OutputStreamPoller*> _poller = {{::ILLIXR::image::LEFT, nullptr},
                                                                                     {::ILLIXR::image::RIGHT, nullptr},
                                                                                     {::ILLIXR::image::RGB, nullptr}};
    int _framecount = 0;
    mediapipe::Packet _packet;
    std::map<image::image_type, cv::Mat> _results_images;
    std::map<image::image_type, ht_detection> _detections;
    size_t _last_frame_id = 0;
    std::unordered_map<size_t, image_map> _raw_images;
    image_map _current_raw;
    ht::input_type _last_input = ht::RIGHT;
    ushort _count = 0;
};


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
    hand_tracking_publisher _publisher;
    std::string _ht_config_file;
    ht::input_type _input_type;
    ht::cam_type _cam_type;
    image_map _current_images;
    bool _first_person;
#if !MEDIAPIPE_DISABLE_GPU
    std::map<::ILLIXR::image::image_type, mediapipe::GlCalculatorHelper> _gpu_helper;
#endif
};
}
