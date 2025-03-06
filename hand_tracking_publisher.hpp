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

namespace ht {\
/**
 * Enumeration of what type of image(s) are the input
 */
    enum input_type { LEFT, RIGHT, BOTH, RGB };

    /**
     * Enumeration of camera associates with the input images
     */
    enum cam_type { CAM, WEBCAM, ZED };
} // namespace ht

/**
 * Holds current input image(s) and pose
 */
struct pose_image {
    image_map                   images;                    //!< mapping of the current images
    data_format::multi_pose_map poses;                      //!< mapping of poses for each image
    bool                        depth_valid       = false;   //!< flag to indicate if there is a valid depth image
    bool                        confidence_valid_ = false;   //!< flags to indicate if there is a valid confidence image assocaited with the depth image
    bool                        pose_valid        = false;  //!< flags indicating if the poses are valid
    int                         eye_count         = 0;      //!< the number of "eyes" (input images)
    data_format::units::eyes    primary           = data_format::units::LEFT_EYE;  //!< the primary eye, will depend on the camera type

    typedef std::map<data_format::image::image_type, cv::Mat>::const_iterator img_iterator;

    /**
     * Access an image via index
     * @param idx The index of the image to get (must exist)
     * @return A reference to the image
     */
    cv::Mat& operator[](data_format::image::image_type idx) {
        return images.at(idx);
    }

    /**
     * Get the format code of the specified image
     * @param idx The image to query
     * @return The format code
     */
    int format(data_format::image::image_type idx) {
        return images.at(idx).type();
    }

    /**
     * Reports number of images
     * @return The number of images
     */
    [[nodiscard]] size_t size() const {
        return images.size();
    }

    /**
     * Access an image via index
     * @param idx The index of the image to get (must exist)
     * @return The image
     */
    [[nodiscard]] cv::Mat at(const data_format::image::image_type idx) const {
        return images.at(idx);
    }

    /**
     * Returns an iterator to the specified image
     * @param eye The image to get
     * @return An iterator to the requested image
     */
    [[nodiscard]] img_iterator find(data_format::image::image_type eye) const {
        return images.find(eye);
    }

    /**
     * Returns the iterator to the end of the image map
     * @return The "end" iterator
     */
    [[nodiscard]] img_iterator end() const {
        return images.end();
    }

    /**
     * Returns the iterator to the beginning of the image map
     * @return The "begin" iterator
     */
    [[nodiscard]] img_iterator begin() const {
        return images.begin();
    }

    /**
     * Insert images based on their iterators
     * @param start The start of the images to insert
     * @param end The end of the images to insert
     */
    void insert(img_iterator start, img_iterator end) {
        images.insert(start, end);
    }

    /**
     * Gets the number of instances of the specified image type
     * @param imgt The image type to search for
     * @return The number found
     */
    [[nodiscard]] size_t count(data_format::image::image_type imgt) const {
        return images.count(imgt);
    }
};

void transform(const data_format::pose_data& pose, data_format::ht::hand_points& hp);

/**
 * Plugin for hand tracking
 */
class hand_tracking_publisher : public threadloop {
public:
    /**
     * Basic constructor
     * @param name_ The name of the plugin
     * @param pb_ A phonebook instance
     */
    hand_tracking_publisher(const std::string& name_, phonebook* pb_);
    ~hand_tracking_publisher() override;

    /**
     * Add an input image to the raw image map
     * @param id The timesatmp of the data
     * @param pi The data to insert
     */
    void add_raw(size_t id, pose_image& pi);

    /**
     * Set the number of expected output froames from the mediapipe pipeline
     * @param it The number of expected frames (1 or 2)
     */
    void set_frame_count(ht::input_type it);

    /**
     * Add a poller to the list
     * @param im_type The image type this poller reports
     * @param plr The poller instance
     */
    void set_poller(data_format::image::image_type im_type, mediapipe::OutputStreamPoller* plr) {
        poller_.at(im_type) = plr;
        count_++;
    }

    /**
     * @copydoc threadloop::start()
     */
    void start() override;

    /**
     * @copydoc threadloop::stop()
     */
    void stop() override;

protected:
    /**
     * @copydoc threadloop::_p_should_skip()
     */
    skip_option _p_should_skip() override;
    /**
     * @copydoc threadloop::_p_one_iteration()
     */
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
    boost::interprocess::managed_shared_memory managed_shm_;                      //!< used to communicate with openXR interface
    boost::interprocess::named_mutex*          shm_mutex_[2]{nullptr, nullptr};   //!< locks for communication
    boost::interprocess::named_mutex*          current_shm_mutex_idx_ = nullptr;  //!< locks for communication
    ILLIXR::data_format::ht::raw_ht_data*      ht_raw_data_[2]{nullptr, nullptr}; //!< data type used for openXR
    int*                                       current_swap_idx_;                 //!< current active buffer
    bool                                       dump_data;                         //!< whether to dump data to stdout for testing
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
