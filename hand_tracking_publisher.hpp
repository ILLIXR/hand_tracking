#define DOUBLE_INCLUDE
#include "illixr/data_format/camera_data.hpp"
#include "illixr/data_format/hand_tracking_data.hpp"
#include "illixr/data_format/pose.hpp"
#include "illixr/threadloop.hpp"
#include "mediapipe/calculators/util/illixr_data.h"
#include "mediapipe/framework/calculator_graph.h"
#undef DOUBLE_INCLUDE

// if we are building the openXR interface
#ifdef ENABLE_OXR
    #include <boost/interprocess/managed_shared_memory.hpp>
    #include <boost/interprocess/sync/named_mutex.hpp>
#endif

namespace ILLIXR {

typedef std::map<data_format::image::image_type, cv::Mat> image_map;

namespace ht {
    enum input_type { LEFT, RIGHT, BOTH, RGB };

    enum cam_type { CAM, WEBCAM, ZED };
} // namespace ht

struct pose_image {
    image_map                   images;
    data_format::multi_pose_map poses;
    bool                        depth_valid       = false;
    bool                        confidence_valid_ = false;
    bool                        pose_valid        = false;
    int                         eye_count         = 0;
    data_format::units::eyes    primary           = data_format::units::LEFT_EYE;

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
    hand_tracking_publisher(const std::string& name_, phonebook* pb_);
    ~hand_tracking_publisher() override;

    void add_raw(size_t id, pose_image& pi);
    void set_frame_count(ht::input_type it);

    void set_poller(data_format::image::image_type im_type, mediapipe::OutputStreamPoller* plr) {
        poller_.at(im_type) = plr;
        count_++;
    }

    void start() override;
    void stop() override;

protected:
    skip_option _p_should_skip() override;
    void        _p_one_iteration() override;

private:
    void calculate_proper_position(std::map<data_format::ht::hand, data_format::ht::hand_points>& thp);

    const std::shared_ptr<switchboard>               switchboard_;
    switchboard::writer<data_format::ht::ht_frame>   ht_publisher_;
    switchboard::reader<data_format::pose_type>      pose_reader_;
    switchboard::reader<data_format::camera_data>    camera_reader_;
    switchboard::reader<data_format::depth_type>     depth_reader_;
    switchboard::reader<data_format::rgb_depth_type> rgb_depth_reader_;

    std::map<data_format::image::image_type, mediapipe::OutputStreamPoller*> poller_ = {
        {data_format::image::LEFT_EYE, nullptr}, {data_format::image::RIGHT_EYE, nullptr}, {data_format::image::RGB, nullptr}};
// if we are building the openXR interface
#ifdef ENABLE_OXR
    boost::interprocess::managed_shared_memory managed_shm_;
    boost::interprocess::named_mutex*          shm_mutex_[2]{nullptr, nullptr};
    boost::interprocess::named_mutex*          current_shm_mutex_idx_ = nullptr;
    ILLIXR::data_format::ht::raw_ht_data*      ht_raw_data_[2]{nullptr, nullptr};
    int*                                       current_swap_idx_;
    bool                                       dump_data;
#endif
    ushort            count_         = 0;
    size_t            frame_count_   = 0;
    int               img_size_x_    = 0;
    int               img_size_y_    = 0;
    size_t            last_frame_id_ = 0;
    mediapipe::Packet packet_;

    std::map<data_format::image::image_type, cv::Mat>                 results_images_;
    std::map<data_format::units::eyes, data_format::ht::ht_detection> detections_;

    std::unordered_map<size_t, pose_image> raw_data_;

    data_format::pose_data    current_pose_;
    data_format::pose_data    initial_pose_;
    pose_image                current_raw_;
    cv::Mat                   current_confidence_;
    cv::Mat                   current_depth_;
    data_format::ht::position last_position_;
    ht::input_type            last_input_ = ht::RIGHT;

    data_format::camera_data cam_data_;
};

} // namespace ILLIXR
