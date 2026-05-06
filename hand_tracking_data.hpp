#pragma once

#include "illixr/data_format/coordinate.hpp"
#include "illixr/data_format/camera_data.hpp"
#include "illixr/data_format/normalize.hpp"
#include "illixr/data_format/opencv_data_types.hpp"
#include "illixr/data_format/poses/hand_pose.hpp"
#include "illixr/data_format/poses/pose_base.hpp"
#include "illixr/data_format/shape.hpp"
#include "illixr/switchboard.hpp"
#include "point.hpp"

#include <eigen3/Eigen/Dense>
#include <iomanip>
#include <map>
#include <opencv2/core/mat.hpp>
#include <sstream>
#include <utility>

namespace ILLIXR {
namespace ht {
const int NUM_LANDMARKS = 21;

/*
 * Enum for the landmark points on a hand
 */
enum landmark_points : int {
    WRIST,             // = 0,
    THUMB_CMC,         // = 1,
    THUMB_MCP,         // = 2,
    THUMB_IP,          // = 3,
    THUMB_TIP,         // = 4,
    INDEX_FINGER_MCP,  // = 5,
    INDEX_FINGER_PIP,  // = 6,
    INDEX_FINGER_DIP,  // = 7,
    INDEX_FINGER_TIP,  // = 8,
    MIDDLE_FINGER_MCP, // = 9,
    MIDDLE_FINGER_PIP, // = 10,
    MIDDLE_FINGER_DIP, // = 11,
    MIDDLE_FINGER_TIP, // = 12,
    RING_FINGER_MCP,   // = 13,
    RING_FINGER_PIP,   // = 14,
    RING_FINGER_DIP,   // = 15,
    RING_FINGER_TIP,   // = 16,
    PINKY_MCP,         // = 17,
    PINKY_PIP,         // = 18,
    PINKY_DIP,         // = 19,
    PINKY_TIP,         // = 20
};

/**
 * Mapping of the hand landmark points to strings, useful for display purposes
 */
const std::map<int, std::string> point_str_map{{WRIST, "Wrist"},
                                               {THUMB_CMC, "Thumb CMC"},
                                               {THUMB_MCP, "Thumb MCP"},
                                               {THUMB_IP, "Thumb IP"},
                                               {THUMB_TIP, "Thumb Tip"},
                                               {INDEX_FINGER_MCP, "Index MCP"},
                                               {INDEX_FINGER_PIP, "Index PIP"},
                                               {INDEX_FINGER_DIP, "Index DIP"},
                                               {INDEX_FINGER_TIP, "Index Tip"},
                                               {MIDDLE_FINGER_MCP, "Middle MCP"},
                                               {MIDDLE_FINGER_PIP, "Middle PIP"},
                                               {MIDDLE_FINGER_DIP, "Middle DIP"},
                                               {MIDDLE_FINGER_TIP, "Middle Tip"},
                                               {RING_FINGER_MCP, "Ring MCP"},
                                               {RING_FINGER_PIP, "Ring PIP"},
                                               {RING_FINGER_DIP, "Ring DIP"},
                                               {RING_FINGER_TIP, "Ring Tip"},
                                               {PINKY_MCP, "Pinky MCP"},
                                               {PINKY_PIP, "Pinky PIP"},
                                               {PINKY_DIP, "Pinky DIP"},
                                               {PINKY_TIP, "Pinky Tip"}};

const std::vector<data_format::pose::side> hand_map{data_format::pose::LEFT, data_format::pose::RIGHT};

/**
 * Listing of each hand point's coordinates
 */
struct hand_points : point::points {
    /**
     * Constructor, creates list of 21 empty points
     */
    explicit hand_points()
        : points(NUM_LANDMARKS) { }

    /**
     * Constructor, with existing points and validity
     * @param pnts The points to use
     * @param valid_ Flag indicating the validity of all points, will be true if at least one point is valid
     */
    explicit hand_points(std::vector<point::point>& pnts, bool vld = true)
        : points(pnts, vld) {
        check();
    }

    /**
     * Verify the size of the input data, resizing as necessary
     */
    void check() {
        if (points_.size() < NUM_LANDMARKS) {
            std::cout << "Resizing to " << NUM_LANDMARKS << std::endl;
            points_.resize(NUM_LANDMARKS);
        } else if (points_.size() > NUM_LANDMARKS) {
            std::cout << "Shrinking to " << NUM_LANDMARKS << std::endl;
            points_.resize(NUM_LANDMARKS);
        }
    }

    /**
     * Clear the internal storage
     */
    void clear() {
        points_.clear();
    }

    /**
     * Flip the y-coordinate over the central axis
     * @param im_height The height of the bounding box
     */
    [[maybe_unused]] void flip_y(const uint im_height = 0) {
        if (normalized) {
            for (auto& pnt : points_) {
                if (pnt.y() != 0.)
                    pnt.y() = 1.0f - pnt.y();
            }
            return;
        }
        if (im_height == 0)
            throw std::runtime_error("Cannot flip the y coordinate if no height given.");
        for (auto& pnt : points_) {
            if (pnt.y() != 0.)
                pnt.y() = (float) im_height - pnt.y();
        }
    }
};

/**
 * Representation of hand points from both hands
 */
struct position {
    std::map<data_format::pose::side, hand_points> points;        //!< Hand points for each hand
    uint64_t                    time;          //!< Associated time stamp
    bool                        valid = false; //!< Validity flag, false = not valid

    /**
     * Raw constructor
     */
    position()
        : points{}
        , time{0}
        , valid{false} { }

    /**
     * Construct the position object with the given data
     * @param pnts The points to use
     * @param time_ Timestamp associated with the data
     */
    position(const std::map<data_format::pose::side, hand_points>& pnts, uint64_t time_)
        : points{pnts}
        , time{time_}
        , valid{true} { }
};

/**
 * Representation of current velocity of head hand point.
 */
struct velocity : hand_points {
    /**
     * Constructor, creates list of 21 empty points
     */
    velocity()
        : hand_points() { }

    /**
     * Constructor, calculates the velocities from the given points. Both sets of points must be the same size and have the same
     * normalization
     * @param h1 The initial position of the points
     * @param h2 The final position of the points
     * @param time The time difference between `h1` and `h2` in seconds
     */
    velocity(const hand_points& h1, const hand_points& h2, const float time)
        : hand_points() {
        if (h1.normalized || h2.normalized)
            throw std::runtime_error("Cannot calculate velocity from normalized points.");

        if (h1.points_.size() != h2.points_.size())
            throw std::runtime_error("Differing number of points in velocity calculation");

        for (int i = WRIST; i != PINKY_TIP; i++) {
            points_[i] = (h2.at(i) - h1.at(i)) / time;
        }
    }
};

/**
 * Struct containing all the data from a hand detection
 */
struct ht_detection {
    size_t                       proc_time; //!< nanoseconds of processing time
    std::map<data_format::pose::side, data_format::shapes::rect> palms;     //!< left palm detection
    std::map<data_format::pose::side, data_format::shapes::rect> hands;     //!< left hand detection

    std::map<data_format::pose::side, float> confidence; //!< confidence of the hand detection 0..1, where 0 means no confidence

    std::map<data_format::pose::side, hand_points> points; //!< the points detected for each hand

    /**
     * Basic constructor
     */
    ht_detection()
        : proc_time{0}
        , palms{{data_format::pose::LEFT, data_format::shapes::rect()}, {data_format::pose::RIGHT, data_format::shapes::rect()}}
        , hands{{data_format::pose::LEFT, data_format::shapes::rect()}, {data_format::pose::RIGHT, data_format::shapes::rect()}}
        , confidence{{data_format::pose::LEFT, 0.}, {data_format::pose::RIGHT, 0.}}
        , points{{data_format::pose::LEFT, hand_points()}, {data_format::pose::RIGHT, hand_points()}} { }

    /**
     * Create an instance from the given inputs
     * @param ptime Time associated with these data
     * @param lp shapes::rectangle enclosing the left palm
     * @param rp shapes::rectangle enclosing the right palm
     * @param lh shapes::rectangle enclosing the entire left hand
     * @param rh shapes::rectangle enclosing the entire right hand
     * @param lc Left hand confidence (0..1, where 0 means no confidence)
     * @param rc Right hand confidence (0..1, where 0 means no confidence)
     * @param lhp Left hand points
     * @param rhp Right hand points
     */
    ht_detection(size_t ptime, data_format::shapes::rect* lp, data_format::shapes::rect* rp, data_format::shapes::rect* lh, data_format::shapes::rect* rh, float lc, float rc,
                 hand_points* lhp, hand_points* rhp)
        : proc_time{ptime}
        , palms{{data_format::pose::LEFT, (lp) ? *lp : data_format::shapes::rect()}, {data_format::pose::RIGHT, (rp) ? *rp : data_format::shapes::rect()}}
        , hands{{data_format::pose::LEFT, (lh) ? *lh : data_format::shapes::rect()}, {data_format::pose::RIGHT, (rh) ? *rh : data_format::shapes::rect()}}
        , confidence{{data_format::pose::LEFT, lc}, {data_format::pose::RIGHT, rc}}
        , points{{data_format::pose::LEFT, (lhp) ? *lhp : hand_points()}, {data_format::pose::RIGHT, (rhp) ? *rhp : hand_points()}} { }
};

/**
 * Representation of all hand data for a frame
 */
struct ht_frame : data_format::cam_base_type {
    std::map<data_format::pose::side, ht_detection> detections;      //!< The raw detection data
    std::map<data_format::pose::side, hand_points>         hand_positions;  //!< The hand points in real world coordinates
    std::map<data_format::pose::side, velocity>            hand_velocities; //!< The velocity of each hand point
    data_format::pose::pose_base        wcs_offset;      //!< The offset between the current pose and the origin
    coordinates::reference_space        reference;       //!< The coordinate system being used

    /**
     * Construct an instance from the given data
     * @param time Time associated with these data
     * @param images The images associated with these data
     * @param _detections The hand detections
     * @param points The real-world points of the hands
     * @param velocities The velocities of the hands
     * @param _pose Offset pose between the current location and the world coordinate origin
     * @param ref_sp The reference space being used, default is VIEWER
     */
    ht_frame(time_point time, std::map<data_format::image::image_type, cv::Mat> images,
             std::map<data_format::pose::side, ht_detection> _detections, std::map<data_format::pose::side, hand_points> points,
             std::map<data_format::pose::side, velocity> velocities = {}, data_format::pose::pose_base _pose = {},
             coordinates::reference_space ref_sp = coordinates::VIEWER)
        : cam_base_type(time, std::move(images),
                        (images.size() == 2) ? data_format::camera::BINOCULAR : data_format::camera::MONOCULAR)
        , detections(std::move(_detections))
        , hand_positions{std::move(points)}
        , hand_velocities{std::move(velocities)}
        , wcs_offset{std::move(_pose)}
        , reference{ref_sp} {}
};

#ifdef ENABLE_OXR2
/*
 * This struct is utilized when working as an OpenXR shim. The internal variables are in a basic form since OpenXR uses
 * C, rather than C++ (e.g. vectors are replaced with arrays)
 */
struct raw_ht_data {
    uint64_t                     time;                                         //!< Time associated with these data
    raw_point                    h_points[2][NUM_LANDMARKS];                   //!< list of points for each hand
    raw_point                    h_velocities[2][NUM_LANDMARKS];               //!< list of velocities for each hand
    raw_pose                     wcs_origin;                                   //!< the offset pose
    coordinates::reference_space reference   = coordinates::VIEWER;            //!< the reference space
    coordinates::frame           frame       = coordinates::RIGHT_HANDED_Y_UP; //!< the coordinate system for all data
    bool                         hp_valid[2] = {false, false};                 //!< validity of hand points
    bool                         hv_valid[2] = {false, false};                 //!< validity of hand velocities
    bool                         valid       = false;                          //!< validity of all data

    /**
     * Basic constructor
     */
    raw_ht_data()
        : time{0} { }

    /**
     * Create an instance from the given data
     * @param time Time associated with these data
     * @param points The points for each hand
     * @param velocities The velocities for each hand
     * @param pose The offset pose
     * @param ref_sp The reference space, default is VIEWER
     */
    raw_ht_data(const time_point time, const std::map<data_format::pose::side, hand_points>& points,
                const std::map<data_format::pose::side, velocity>& velocities, const head_pose_data& pose,
                coordinates::reference_space ref_sp = coordinates::VIEWER)
        : time{static_cast<uint64_t>(time.time_since_epoch().count())}
        , reference{ref_sp}
        , valid{true} {
        for (auto i = 0; i < NUM_LANDMARKS; i++) {
            h_points[data_format::pose::LEFT][i].copy(points.at(data_format::pose::LEFT).at(i));
            hp_valid[data_format::pose::LEFT] |= points.at(data_format::pose::LEFT).at(i).valid;
            h_points[data_format::pose::RIGHT][i].copy(points.at(data_format::pose::RIGHT).at(i));
            hp_valid[data_format::pose::RIGHT] |= points.at(data_format::pose::RIGHT).at(i).valid;
            h_velocities[data_format::pose::LEFT][i].copy(velocities.at(data_format::pose::LEFT).at(i));
            hv_valid[data_format::pose::LEFT] |= velocities.at(data_format::pose::LEFT).at(i).valid;
            h_velocities[data_format::pose::RIGHT][i].copy(velocities.at(data_format::pose::RIGHT).at(i));
            hv_valid[data_format::pose::RIGHT] |= velocities.at(data_format::pose::RIGHT).at(i).valid;
        }

        wcs_origin.copy(pose);
    }

    /**
     * Create an instance from the given `ht_frame`
     * @param frame_ The data to use
     */
    explicit raw_ht_data(const ht_frame& frame_)
        : raw_ht_data(frame_.time, frame_.hand_positions, frame_.hand_velocities, frame_.wcs_offset, frame_.reference) { }

    /**
     * Copy the data from an `ht_frame` instance into this structure
     * @param frame_ The frame to copy
     */
    void copy(const ht_frame& frame_) {
        time      = static_cast<uint64_t>(frame_.time.time_since_epoch().count());
        reference = frame_.reference;

        for (auto i = 0; i < NUM_LANDMARKS; i++) {
            h_points[data_format::pose::LEFT][i].copy(frame_.hand_positions.at(data_format::pose::LEFT).at(i));
            hp_valid[data_format::pose::LEFT] = hp_valid[data_format::pose::LEFT] || frame_.hand_positions.at(data_format::pose::LEFT).at(i).valid;
            h_points[data_format::pose::RIGHT][i].copy(frame_.hand_positions.at(data_format::pose::RIGHT).at(i));
            hp_valid[data_format::pose::RIGHT] = hp_valid[data_format::pose::RIGHT] || frame_.hand_positions.at(data_format::pose::RIGHT).at(i).valid;
            h_velocities[data_format::pose::LEFT][i].copy(frame_.hand_velocities.at(data_format::pose::LEFT).at(i));
            hv_valid[data_format::pose::LEFT] = hv_valid[data_format::pose::LEFT] || frame_.hand_velocities.at(data_format::pose::LEFT).at(i).valid;
            h_velocities[data_format::pose::RIGHT][i].copy(frame_.hand_velocities.at(data_format::pose::RIGHT).at(i));
            hv_valid[data_format::pose::RIGHT] = hv_valid[data_format::pose::RIGHT] || frame_.hand_velocities.at(data_format::pose::RIGHT).at(i).valid;
        }

        wcs_origin.copy(frame_.wcs_offset);
    }
};

inline std::ostream& operator<<(std::ostream& os, const raw_ht_data& data) {
    const auto def_precision{os.precision()};

    os << std::setprecision(6) << "HT Data" << std::endl << "  Time: " << data.time << std::endl;
    os << "  WCS origin: ";
    if (data.wcs_origin.valid) {
        os << std::endl
           << "    position: " << data.wcs_origin.x << ", " << data.wcs_origin.y << ", " << data.wcs_origin.z << std::endl;
        os << "    orientation: " << data.wcs_origin.w << ", " << data.wcs_origin.wx << ", " << data.wcs_origin.wy << ", "
           << data.wcs_origin.z;
    } else {
        os << "not valid";
    }
    os << std::endl << "  Ref space: " << data.reference << std::endl;
    os << "  Left Hand:";
    if (data.hp_valid[data_format::pose::LEFT]) {
        for (auto i = 0; i < NUM_LANDMARKS; i++) {
            os << std::endl
               << "    " << i << ": " << data.h_points[data_format::pose::LEFT][i].x << ", " << data.h_points[data_format::pose::LEFT][i].y << ", "
               << data.h_points[data_format::pose::LEFT][i].z << "  " << ((data.h_points[data_format::pose::LEFT][i].valid) ? "valid" : "not valid");
        }
    } else {
        os << "not valid";
    }
    os << std::endl << "  Right Hand:";
    if (data.hp_valid[data_format::pose::RIGHT]) {
        for (auto i = 0; i < NUM_LANDMARKS; i++) {
            os << std::endl
               << "    " << i << ": " << data.h_points[data_format::pose::RIGHT][i].x << ", " << data.h_points[data_format::pose::RIGHT][i].y << ", "
               << data.h_points[data_format::pose::RIGHT][i].z << "  " << ((data.h_points[data_format::pose::RIGHT][i].valid) ? "valid" : "not valid");
        }
    } else {
        os << "not valid";
    }
    os << std::endl << "  Left Hand (vel):";
    if (data.hv_valid[data_format::pose::LEFT]) {
        for (auto i = 0; i < NUM_LANDMARKS; i++) {
            os << std::endl
               << "    " << i << ": " << data.h_velocities[data_format::pose::LEFT][i].x << ", " << data.h_velocities[data_format::pose::LEFT][i].y << ", "
               << data.h_velocities[data_format::pose::LEFT][i].z << "  "
               << ((data.h_velocities[data_format::pose::LEFT][i].valid) ? "valid" : "not valid");
        }
    } else {
        os << "not valid";
    }
    os << std::endl << "  Right Hand (vel):";
    if (data.hv_valid[data_format::pose::RIGHT]) {
        for (auto i = 0; i < NUM_LANDMARKS; i++) {
            os << std::endl
               << "    " << i << ": " << data.h_velocities[data_format::pose::RIGHT][i].x << ", " << data.h_velocities[data_format::pose::RIGHT][i].y
               << ", " << data.h_velocities[data_format::pose::RIGHT][i].z << "  "
               << ((data.h_velocities[data_format::pose::RIGHT][i].valid) ? "valid" : "not valid");
        }
    } else {
        os << "not valid";
    }
    os << std::endl << std::endl;
    os << std::setprecision(def_precision);
    return os;
}

#endif

/**
 * Transform a point from its current position using the given pose
 * @param pnt Point to transform
 * @param pose Pose to use for the transformation
 */
[[maybe_unused]] inline void transform_point(point::point& pnt, const data_format::pose::pose_base& pose) {
    Eigen::Vector3f new_pnt = pose.orientation * pnt;
    pnt.set(new_pnt + pose.position);
}

/**
 * transform multiple points from their original position using the given pose
 * @param points The points to transform
 * @param pose Pose to use for the transformation
 * @param from The coordinate frame to convert from
 * @param to The coordinate from to convert to
 */
[[maybe_unused]] inline static void transform_points(point::points& points_, const ILLIXR::data_format::pose::pose_base& pose,
                                                     coordinates::reference_space from, coordinates::reference_space to) {
    if (to == from)
        return;
    if (to == coordinates::WORLD) {
        for (auto& pnt : points_.points_) {
            Eigen::Vector3f newpnt = pose.orientation * pnt;
            pnt.set(newpnt + pose.position);
        }
    } else {
    }
}
}  // namespace ht

template<>
inline void normalize<ht::hand_points>(ht::hand_points& obj, const float width, const float height, const float depth) {
    if (obj.normalized)
        return;

    for (auto& pnt : obj.points_)
        normalize(pnt, width, height, depth);
    obj.normalized = true;
}

template<>
inline void denormalize<ht::hand_points>(ht::hand_points& obj, const float width, const float height, const float depth) {
    if (!obj.normalized)
        return;
    for (auto& pnt : obj.points_)
        denormalize(pnt, width, height, depth);
    obj.normalized = false;
}

template<>
inline void normalize<ht::velocity>(ht::velocity& obj, const float width, const float height, const float depth) {
    if (obj.normalized)
        return;

    for (auto& pnt : obj.points_)
        normalize(pnt, width, height, depth);
    obj.normalized = true;
}

template<>
inline void denormalize<ht::velocity>(ht::velocity& obj, const float width, const float height, const float depth) {
    if (!obj.normalized)
        return;

    for (auto& pnt : obj.points_)
        denormalize(pnt, width, height, depth);
    obj.normalized = false;
}

template<>
inline void normalize<ht::ht_detection>(ht::ht_detection& obj, const float width, const float height, const float depth) {
    for (auto& palm : obj.palms)
        normalize(palm.second, width, height, depth);
    for (auto& hnd : obj.hands)
        normalize(hnd.second, width, height, depth);
    for (auto& pnts : obj.points)
        normalize(pnts.second, width, height, depth);
}

template<>
[[maybe_unused]] inline void normalize<ht::ht_frame>(ht::ht_frame& obj, const float width, const float height, const float depth) {
    for (auto& det : obj.detections)
        normalize(det.second, width, height, depth);
    for (auto& hp : obj.hand_positions)
        normalize(hp.second, width, height, depth);
    for (auto& hv : obj.hand_velocities)
        normalize(hv.second, width, height, depth);
}

template<>
inline void denormalize<ht::ht_detection>(ht::ht_detection& obj, const float width, const float height, const float depth) {
    for (auto& palm : obj.palms)
        denormalize(palm.second, width, height, depth);
    for (auto& hnd : obj.hands)
        denormalize(hnd.second, width, height, depth);
    for (auto& pnts : obj.points)
        denormalize(pnts.second, width, height, depth);
}

template<>
[[maybe_unused]] inline void denormalize<ht::ht_frame>(ht::ht_frame& obj, const float width, const float height, const float depth) {
    for (auto& det : obj.detections)
        denormalize(det.second, width, height, depth);
    for (auto& hp : obj.hand_positions)
        denormalize(hp.second, width, height, depth);
    for (auto& hv : obj.hand_velocities)
        denormalize(hv.second, width, height, depth);
}
} // namespace ILLIXR::hand_tracking
