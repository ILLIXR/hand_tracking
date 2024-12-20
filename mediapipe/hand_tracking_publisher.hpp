#include "illixr/threadloop.hpp"
#include "illixr/camera_data.hpp"
#include "illixr/data_format.hpp"
#include "illixr/hand_tracking_data.hpp"

#include "mediapipe/calculators/util/illixr_data.h"
#include "mediapipe/framework/calculator_graph.h"



namespace ILLIXR {

typedef std::map<image::image_type, cv::Mat> image_map;

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


struct pose_image {
    image_map images;
    multi_pose_map poses;
    bool depth_valid = false;
    bool confidence_valid_ = false;
    bool pose_valid = false;
    int eye_count = 0;
    units::eyes primary = units::LEFT_EYE;

    cv::Mat& operator[](image::image_type idx) {
        return images.at(idx);
    }

    int format(image::image_type idx) {
        return images.at(idx).type();
    }

    [[nodiscard]] size_t size() const {
        return images.size();
    }

    [[nodiscard]] cv::Mat at(const image::image_type idx) const {
        return images.at(idx);
    }

    [[nodiscard]] std::map<image::image_type, cv::Mat>::const_iterator find(const image::image_type idx) const {
        return images.find(idx);
    }

    void insert(std::map<image::image_type, cv::Mat>::const_iterator start, std::map<image::image_type, cv::Mat>::const_iterator end) {
        images.insert(start, end);
    }

    int count(image::image_type imgt) const {
        return images.count(imgt);
    }
};

class hand_tracking_publisher : public threadloop {
public:
    hand_tracking_publisher(const std::string &name_, phonebook *pb_, ht::cam_type _c_type);

    void start() override;

    ~hand_tracking_publisher() override;

    void set_framecount(ht::input_type it);

    void add_raw(size_t id, pose_image &pi);

    void set_poller(::ILLIXR::image::image_type im_type, mediapipe::OutputStreamPoller *plr) {
        _poller.at(im_type) = plr;
        _count++;
    }

protected:
    skip_option _p_should_skip() override;

    void _p_one_iteration() override;

private:
    void calculate_proper_position(std::map<HandTracking::hand, HandTracking::hand_points> &thp);

    const std::shared_ptr<switchboard>           _switchboard;
    switchboard::writer <HandTracking::ht_frame> _ht_publisher;
    switchboard::reader <pose_type>              _initial_pose_reader;
    switchboard::reader <pose_type>              _pose_reader;
    switchboard::reader <camera_data>            _camera_reader;
    switchboard::reader <depth_type>             _depth_reader;
    switchboard::reader <rgb_depth_type>         _rgb_depth_reader;

    std::map<::ILLIXR::image::image_type, mediapipe::OutputStreamPoller *> _poller = {{::ILLIXR::image::LEFT_EYE,  nullptr},
                                                                                      {::ILLIXR::image::RIGHT_EYE, nullptr},
                                                                                      {::ILLIXR::image::RGB,       nullptr}};
    int _framecount = 0;
    mediapipe::Packet _packet;
    std::map<image::image_type, cv::Mat> _results_images;
    std::map<units::eyes, HandTracking::ht_detection> _detections;
    size_t _last_frame_id = 0;
    std::unordered_map<size_t, pose_image> _raw_data;
    pose_data _current_pose;
    pose_data _initial_pose;
    pose_image _current_raw;
    cv::Mat _current_confidence;
    cv::Mat _current_depth;
    int _img_size_x = 0;
    int _img_size_y = 0;
    HandTracking::position _last_position;
    ht::input_type _last_input = ht::RIGHT;
    ushort _count = 0;
    ::ILLIXR::camera_data cam_data_;
    ht::cam_type _cam_type;
    //HandTracking::camera_params combined_params_;
};

}