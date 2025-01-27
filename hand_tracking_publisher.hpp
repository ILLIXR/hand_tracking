#include "illixr/threadloop.hpp"
#include "illixr/data_format/camera_data.hpp"
#include "illixr/data_format/hand_tracking_data.hpp"
#include "illixr/data_format/pose.hpp"

#include "mediapipe/calculators/util/illixr_data.h"
#include "mediapipe/framework/calculator_graph.h"


namespace ILLIXR {

typedef std::map<data_format::image::image_type, cv::Mat> image_map;

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
    data_format:: multi_pose_map poses;
    bool depth_valid = false;
    bool confidence_valid_ = false;
    bool pose_valid = false;
    int eye_count = 0;
    data_format::units::eyes primary = data_format::units::LEFT_EYE;

    typedef std::map<data_format::image::image_type, cv::Mat>::const_iterator img_iterator;

    cv::Mat& operator[](data_format::image::image_type idx) {
        return images.at(idx);
    }

    int format(data_format::image::image_type idx) {
        return images.at(idx).type();
    }

    [[nodiscard]] size_t size() const {
        return images.size();
    }

    [[nodiscard]] cv::Mat at(const data_format::image::image_type idx) const {
        return images.at(idx);
    }

    [[nodiscard]] img_iterator find(data_format::image::image_type eye) const {
        return images.find(eye);
    }

    [[nodiscard]] img_iterator end() const {
        return images.end();
    }

    [[nodiscard]] img_iterator begin() const {
        return images.begin();
    }

    void insert(img_iterator start, img_iterator end) {
        images.insert(start, end);
    }

    [[nodiscard]] size_t count(data_format::image::image_type imgt) const {
        return images.count(imgt);
    }
};

void transform(const data_format::pose_data& pose, data_format::ht::hand_points& hp);

class hand_tracking_publisher : public threadloop {
public:
    hand_tracking_publisher(const std::string &name_, phonebook *pb_, ht::cam_type _c_type);

    void start() override;

    void stop() override;

    ~hand_tracking_publisher() override;

    void set_frame_count(ht::input_type it);

    void add_raw(size_t id, pose_image &pi);

    void set_poller(data_format::image::image_type im_type, mediapipe::OutputStreamPoller *plr) {
        _poller.at(im_type) = plr;
        _count++;
    }

protected:
    skip_option _p_should_skip() override;

    void _p_one_iteration() override;

private:
    void calculate_proper_position(std::map<data_format::ht::hand, data_format::ht::hand_points> &thp);

    const std::shared_ptr<switchboard>                 _switchboard;
    switchboard::writer <data_format::ht::ht_frame>    _ht_publisher;
    switchboard::reader <data_format::pose_type>       _pose_reader;
    switchboard::reader <data_format::camera_data>     _camera_reader;
    switchboard::reader <data_format::depth_type>      _depth_reader;
    switchboard::reader <data_format::rgb_depth_type>  _rgb_depth_reader;

    std::map<data_format::image::image_type, mediapipe::OutputStreamPoller *> _poller = {{data_format::image::LEFT_EYE,  nullptr},
                                                                                         {data_format::image::RIGHT_EYE, nullptr},
                                                                                         {data_format::image::RGB,       nullptr}};
    size_t _frame_count = 0;
    mediapipe::Packet _packet;
    std::map<data_format::image::image_type, cv::Mat> _results_images;
    std::map<data_format::units::eyes, data_format::ht::ht_detection> _detections;
    size_t _last_frame_id = 0;
    std::unordered_map<size_t, pose_image> _raw_data;
    data_format::pose_data _current_pose;
    data_format::pose_data _initial_pose;
    pose_image _current_raw;
    cv::Mat _current_confidence;
    cv::Mat _current_depth;
    int _img_size_x = 0;
    int _img_size_y = 0;
    data_format::ht::position _last_position;
    ht::input_type _last_input = ht::RIGHT;
    ushort _count = 0;
    data_format::camera_data cam_data_;
    ht::cam_type _cam_type;
};

}
