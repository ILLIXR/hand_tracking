#include "interface.h"
#include "illixr/data_format/hand_tracking_data.hpp"
#include "ixr_openxr.hpp"
#include "oxr_objects.h"

#include "illixr/math_util.hpp"
#include "illixr/phonebook.hpp"
#include "illixr/switchboard.hpp"

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <sstream>

namespace b_intp = boost::interprocess;

const std::map<int, int> oxr_to_ixr_points = {{XR_HAND_JOINT_WRIST_EXT, ILLIXR::data_format::ht::WRIST},
                                              {XR_HAND_JOINT_THUMB_METACARPAL_EXT, ILLIXR::data_format::ht::THUMB_CMC},
                                              {XR_HAND_JOINT_THUMB_PROXIMAL_EXT, ILLIXR::data_format::ht::THUMB_MCP},
                                              {XR_HAND_JOINT_THUMB_DISTAL_EXT, ILLIXR::data_format::ht::THUMB_IP},
                                              {XR_HAND_JOINT_THUMB_TIP_EXT, ILLIXR::data_format::ht::THUMB_TIP},
                                              {XR_HAND_JOINT_INDEX_PROXIMAL_EXT, ILLIXR::data_format::ht::INDEX_FINGER_MCP},
                                              {XR_HAND_JOINT_INDEX_INTERMEDIATE_EXT, ILLIXR::data_format::ht::INDEX_FINGER_PIP},
                                              {XR_HAND_JOINT_INDEX_DISTAL_EXT, ILLIXR::data_format::ht::INDEX_FINGER_DIP},
                                              {XR_HAND_JOINT_INDEX_TIP_EXT, ILLIXR::data_format::ht::INDEX_FINGER_TIP},
                                              {XR_HAND_JOINT_MIDDLE_PROXIMAL_EXT, ILLIXR::data_format::ht::MIDDLE_FINGER_MCP},
                                              {XR_HAND_JOINT_MIDDLE_INTERMEDIATE_EXT, ILLIXR::data_format::ht::MIDDLE_FINGER_PIP},
                                              {XR_HAND_JOINT_MIDDLE_DISTAL_EXT, ILLIXR::data_format::ht::MIDDLE_FINGER_DIP},
                                              {XR_HAND_JOINT_MIDDLE_TIP_EXT, ILLIXR::data_format::ht::MIDDLE_FINGER_TIP},
                                              {XR_HAND_JOINT_RING_PROXIMAL_EXT, ILLIXR::data_format::ht::RING_FINGER_MCP},
                                              {XR_HAND_JOINT_RING_INTERMEDIATE_EXT, ILLIXR::data_format::ht::RING_FINGER_PIP},
                                              {XR_HAND_JOINT_RING_DISTAL_EXT, ILLIXR::data_format::ht::RING_FINGER_DIP},
                                              {XR_HAND_JOINT_RING_TIP_EXT, ILLIXR::data_format::ht::RING_FINGER_TIP},
                                              {XR_HAND_JOINT_LITTLE_PROXIMAL_EXT, ILLIXR::data_format::ht::PINKY_MCP},
                                              {XR_HAND_JOINT_LITTLE_INTERMEDIATE_EXT, ILLIXR::data_format::ht::PINKY_PIP},
                                              {XR_HAND_JOINT_LITTLE_DISTAL_EXT, ILLIXR::data_format::ht::PINKY_DIP},
                                              {XR_HAND_JOINT_LITTLE_TIP_EXT, ILLIXR::data_format::ht::PINKY_TIP}
};

const std::vector<int>invalid = {XR_HAND_JOINT_PALM_EXT,
                                 XR_HAND_JOINT_INDEX_METACARPAL_EXT,
                                 XR_HAND_JOINT_MIDDLE_METACARPAL_EXT,
                                 XR_HAND_JOINT_RING_METACARPAL_EXT,
                                 XR_HAND_JOINT_LITTLE_METACARPAL_EXT
};

struct valid_points {
    ILLIXR::data_format::raw_point points[ILLIXR::data_format::ht::NUM_LANDMARKS];
    bool valid = false;

    valid_points() = default;

    valid_points(ILLIXR::data_format::raw_point pnts[ILLIXR::data_format::ht::NUM_LANDMARKS], bool is_valid) {
        for (auto i = 0; i < ILLIXR::data_format::ht::NUM_LANDMARKS; i++) {
            points[i] = pnts[i];
        }
        valid = is_valid;
    }
};

struct ht_illixr_handle_t {
    boost::interprocess::named_mutex*          m_swap[2]{nullptr, nullptr};
    boost::interprocess::named_mutex*          m_current_swap_idx = nullptr;
    boost::interprocess::managed_shared_memory managed_shm;
    ILLIXR::data_format::coordinates::frame    ref = ILLIXR::data_format::coordinates::RIGHT_HANDED_Y_UP;
    valid_points                               last_valid_frame[2];
    Eigen::Matrix3f                            convert;
    bool                                       do_convert;

    explicit ht_illixr_handle_t() {
        managed_shm = b_intp::managed_shared_memory(b_intp::open_only, illixr_shm_name);
        m_current_swap_idx = new b_intp::named_mutex(b_intp::open_only, illixr_shm_mutex_latest);
        m_swap[0] = new b_intp::named_mutex(b_intp::open_only, illixr_shm_mutex_swap[0]);
        m_swap[1] = new b_intp::named_mutex(b_intp::open_only, illixr_shm_mutex_swap[1]);

        if (ref == ILLIXR::data_format::coordinates::RIGHT_HANDED_Y_UP) {
            convert = ILLIXR::math_util::identity;
            do_convert = false;
        } else {
            convert = ILLIXR::math_util::conversion[ref][ILLIXR::data_format::coordinates::RIGHT_HANDED_Y_UP];
            do_convert = true;
        }
    }

};


XrResult illixr_xrCreateHandTrackerEXT(XrSession session,
                                       const XrHandTrackerCreateInfoEXT* createInfo,
                                       XrHandTrackerEXT* handTracker) {
    ixr_hand_tracker* tracker_handle = nullptr;
    ixr_session *sess = nullptr;

    if (!session)
        return XR_ERROR_HANDLE_INVALID;

    sess = reinterpret_cast<ixr_session *>(session);
    if (createInfo == ((void *) 0) ||
        createInfo->type != XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT ||
        handTracker == ((void *) 0) ||
        (createInfo->hand != XR_HAND_LEFT_EXT && createInfo->hand != XR_HAND_RIGHT_EXT)) {
        return XR_ERROR_VALIDATION_FAILURE;
    }
    tracker_handle = new ixr_hand_tracker();


    try {
        tracker_handle->session = sess;
        tracker_handle->hand = createInfo->hand;
        tracker_handle->ixr_hand = (tracker_handle->hand == XR_HAND_LEFT_EXT) ? ILLIXR::data_format::ht::LEFT_HAND
                                                              : ILLIXR::data_format::ht::RIGHT_HAND;
        tracker_handle->hand_joints = createInfo->handJointSet;
        tracker_handle->ht_handle =  new ht_illixr_handle_t();

    } catch (std::exception &e) {
        return XR_ERROR_HANDLE_INVALID;
    }

    *handTracker = reinterpret_cast<XrHandTrackerEXT>(tracker_handle);
    return XR_SUCCESS;
}

XrResult XRAPI_CALL illixr_xrDestroyHandTrackerEXT(XrHandTrackerEXT handTracker) {
    ixr_hand_tracker* hand_tracker;

    if (handTracker == NULL)
        return XR_ERROR_HANDLE_INVALID;

    hand_tracker = reinterpret_cast<ixr_hand_tracker*>(handTracker);
    delete hand_tracker->ht_handle;
    delete hand_tracker;
    hand_tracker = NULL;

    return XR_SUCCESS;
}

XrResult XRAPI_CALL illixr_xrLocateHandJointsEXT(XrHandTrackerEXT handTracker,
                                                 const XrHandJointsLocateInfoEXT* locateInfo,
                                                 XrHandJointLocationsEXT* locations) {
    struct ixr_hand_tracker* hand_tracker;
    if (handTracker == ((void *) 0))
        return XR_ERROR_HANDLE_INVALID;

    hand_tracker = reinterpret_cast<ixr_hand_tracker*>(handTracker);
    if (locateInfo == ((void *) 0) ||
        locateInfo->type != XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT ||
        locations == ((void *) 0) ||
        locations->type != XR_TYPE_HAND_JOINT_LOCATIONS_EXT ||
        (locations->jointCount != 26 && locations->jointCount != 21)) {
        return XR_ERROR_VALIDATION_FAILURE;
    }
    ILLIXR::data_format::ht::raw_ht_data* data;
    int idx;
    {
        b_intp::scoped_lock<b_intp::named_mutex> lock(*hand_tracker->ht_handle->m_current_swap_idx);
        idx = *hand_tracker->ht_handle->managed_shm.find<int>(illixr_shm_current).first;
        b_intp::scoped_lock<b_intp::named_mutex> d_lock(*hand_tracker->ht_handle->m_swap[idx]);
        data = hand_tracker->ht_handle->managed_shm.find<ILLIXR::data_format::ht::raw_ht_data>(
                illixr_shm_swap[idx]).first;
    }
    int flags = 0;
    if (data == nullptr) {
        locations->isActive = false;
        return XR_SUCCESS;
    }

    bool is_valid;

    valid_points h_pts{&data->h_points[hand_tracker->ixr_hand][0], data->hp_valid[hand_tracker->ixr_hand]};
    is_valid = data->hp_valid[hand_tracker->ixr_hand];
    if (!is_valid) {

        if (hand_tracker->ht_handle->last_valid_frame[hand_tracker->ixr_hand].valid) {
            h_pts = hand_tracker->ht_handle->last_valid_frame[hand_tracker->ixr_hand];
        } else {
            locations->isActive = false;
            return XR_SUCCESS;
        }
    } else {
        if (hand_tracker->ht_handle->do_convert) {
            for (auto i = 0; i < ILLIXR::data_format::ht::NUM_LANDMARKS; i++) {
                h_pts.points[i].mult(hand_tracker->ht_handle->convert);
            }
        }
        auto *space = reinterpret_cast<oxr_space *>(locateInfo->baseSpace);
        if (space->space_type == OXR_SPACE_TYPE_REFERENCE_VIEW) {
            ILLIXR::data_format::pose_data wcs_offset{{data->wcs_origin.x, data->wcs_origin.y, data->wcs_origin.z},
                                                      {data->wcs_origin.w, data->wcs_origin.wx, data->wcs_origin.wy,
                                                       data->wcs_origin.wz}, data->unit};
            for (auto i = 0; i < ILLIXR::data_format::ht::NUM_LANDMARKS; i++) {
                h_pts.points[i].transform(wcs_offset);
            }

        }
        hand_tracker->ht_handle->last_valid_frame[hand_tracker->ixr_hand] = h_pts;

        flags |= XR_SPACE_LOCATION_POSITION_TRACKED_BIT;
    }

    if (locations->jointCount == 21) {
        for (int i = ILLIXR::data_format::ht::WRIST; i <= ILLIXR::data_format::ht::PINKY_TIP; i++) {
            locations->jointLocations[i].locationFlags = (h_pts.points[i].valid) ? (XR_SPACE_LOCATION_POSITION_VALID_BIT |
                                                                                    flags)
                                                                                 : 0;
            locations->jointLocations[i].pose.position = {h_pts.points[i].x, h_pts.points[i].y, h_pts.points[i].z};
            locations->jointLocations[i].pose.orientation = {0., 0., 0., 0.};
        }
    } else {
        for (auto &m: oxr_to_ixr_points) {
            locations->jointLocations[m.first].locationFlags = (h_pts.points[m.second].valid) ? (
                    XR_SPACE_LOCATION_POSITION_VALID_BIT | flags)
                                                                                              : 0;
            locations->jointLocations[m.first].pose.position = {h_pts.points[m.second].x, h_pts.points[m.second].y,
                                                                h_pts.points[m.second].z};
            locations->jointLocations[m.first].pose.orientation = {0., 0., 0., 0.};
        }
        for (auto pnt: invalid) {
            locations->jointLocations[pnt].locationFlags = 0;
            locations->jointLocations[pnt].pose.position = {0., 0., 0.};
            locations->jointLocations[pnt].pose.orientation = {0., 0., 0., 0.};
        }
    }
#ifdef ENABLE_OXR_TEST
    std::ostringstream oss;
    oss << std::setprecision(6) << "HT Data" << std::endl << "  Time: " << data->time << std::endl;
    if (hand_tracker->ixr_hand == 0) {
        oss << "  Left Hand:";
    } else {
        oss << "  Right Hand:";
    }
    for (auto i = 0; i < locations->jointCount; i++) {
        oss << std::endl << "    " << i << ": " << locations->jointLocations[i].pose.position.x << ", "
            << locations->jointLocations[i].pose.position.y
            << ", " << locations->jointLocations[i].pose.position.z << "  " << locations->jointLocations[i].locationFlags;
    }
    oss << std::endl << std::endl;
    printf("%s", oss.str().c_str());
#endif

    return XR_SUCCESS;
}
