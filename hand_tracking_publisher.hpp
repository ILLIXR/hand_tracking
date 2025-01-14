#include "illixr/threadloop.hpp"
#include "illixr/data_format/camera_data.hpp"
#include "illixr/data_format/hand_tracking_data.hpp"
#include "illixr/data_format/pose.hpp"

#include "mediapipe/calculators/util/illixr_data.h"
#include "mediapipe/framework/calculator_graph.h"

#ifdef BUILD_OXR
//#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
//#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#endif

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

    [[nodiscard]] std::map<data_format::image::image_type, cv::Mat>::const_iterator find(const data_format::image::image_type idx) const {
        return images.find(idx);
    }

    void insert(std::map<data_format::image::image_type, cv::Mat>::const_iterator start, std::map<data_format::image::image_type, cv::Mat>::const_iterator end) {
        images.insert(start, end);
    }

    int count(data_format::image::image_type imgt) const {
        return images.count(imgt);
    }
};

void transform(const data_format::pose_data& pose, data_format::ht::hand_points& hp);

class hand_tracking_publisher : public threadloop {
public:
    hand_tracking_publisher(const std::string &name_, phonebook *pb_, ht::cam_type _c_type);

    void start() override;

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
#ifdef BUILD_OXR
    boost::interprocess::managed_shared_memory managed_shm;
    //boost::interprocess::mapped_region* swap1;
    //boost::interprocess::mapped_region* swap2;
    //boost::interprocess::mapped_region latest;
    //boost::interprocess::mapped_region* current_region = nullptr;
    boost::interprocess::named_mutex*          m_swap[2];
    boost::interprocess::named_mutex*          m_current_swap_idx;
    ILLIXR::data_format::ht::raw_ht_data*      htdb[2];
    //boost::interprocess::named_mutex*          current_mutex = nullptr;
    //bool use_swap1 = true;
    //boost::interprocess::mapped_region mutex;
#endif
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
    int* current_swap_idx;
    data_format::ht::position _last_position;
    ht::input_type _last_input = ht::RIGHT;
    ushort _count = 0;
    data_format::camera_data cam_data_;
    ht::cam_type _cam_type;
};

}
