#include "interface.h"
#include "../hand_tracking_publisher.hpp"
#include "illixr/math_util.hpp"
#include "illixr/phonebook.hpp"
#include "illixr/switchboard.hpp"
#include "oxr_objects.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>

namespace bt_int = boost::interprocess;

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

struct ht_illixr_handle_t {
    ILLIXR::switchboard::reader <ILLIXR::data_format::ht::ht_frame> frame_reader;
    ILLIXR::data_format::coordinates::frame ref;
    Eigen::Matrix3f convert;
    bool do_convert;

    explicit ht_illixr_handle_t(ILLIXR::switchboard* sb) :
            frame_reader{sb->get_reader<ILLIXR::data_format::ht::ht_frame>("ht")} {
        auto rf = sb-> root_coordinates;
        if (ref == ILLIXR::data_format::coordinates::RIGHT_HANDED_Y_UP) {
            convert = ILLIXR::math_util::identity;
            do_convert = false;
        } else {
            convert = ILLIXR::math_util::conversion[ref][ILLIXR::data_format::coordinates::RIGHT_HANDED_Y_UP];
            do_convert = true;
        }
    }

};

XrResult handle_create(ixr_session* session,
                       const XrHandTrackerCreateInfoEXT* info,
                       ixr_hand_tracker *handle) {
    try {
        handle = new ixr_hand_tracker();
        handle->session = session;
        handle->hand = info->hand;
        handle->ixr_hand = (handle->hand == XR_HAND_LEFT_EXT) ? ILLIXR::data_format::ht::LEFT_HAND
                                                              : ILLIXR::data_format::ht::RIGHT_HAND;
        handle->hand_joints = info->handJointSet;
        handle->ht_handle = create_ht_illixr();

    } catch (...) {
        return XR_ERROR_HANDLE_INVALID;
    }
    return XR_SUCCESS;
}

void handle_destory(ixr_hand_tracker* handle) {
    delete handle->ht_handle;
    delete handle;
    handle = NULL;
}


XrResult locate_hand(struct ixr_hand_tracker* hand_tracker, const XrHandJointsLocateInfoEXT* info, XrHandJointLocationsEXT* locations) {
    auto data = hand_tracker->ht_handle->frame_reader.get_ro_nullable();
    if (data == nullptr) {
        locations->isActive = false;
        return XR_SUCCESS;
    }
    ILLIXR::data_format::points_with_units h_pts(data->hand_positions.at(static_cast<const ILLIXR::data_format::ht::hand>(hand_tracker->ixr_hand)));
    if (!h_pts.valid) {
        locations->isActive = false;
        return XR_SUCCESS;
    }

    if (hand_tracker->ht_handle->do_convert)
        h_pts.mult(hand_tracker->ht_handle->convert);
    auto* space = reinterpret_cast<oxr_space *>(info->baseSpace);
    if (space->space_type != OXR_SPACE_TYPE_REFERENCE_VIEW)
        h_pts.transform(data->offset_pose);
    if (locations->jointCount == 21) {
        for (int i = ILLIXR::data_format::ht::WRIST; i <= ILLIXR::data_format::ht::PINKY_TIP; i++) {
            locations->jointLocations[i].locationFlags = (h_pts[i].valid) ? (XR_SPACE_LOCATION_POSITION_VALID_BIT | XR_SPACE_LOCATION_POSITION_TRACKED_BIT) : XR_SPACE_LOCATION_POSITION_VALID_BIT;
            locations->jointLocations[i].pose.position = {h_pts[i].x(), h_pts[i].y(), h_pts[i].z()};
            locations->jointLocations[i].pose.orientation = {0., 0., 0., 0.};
        }
    } else {
        for (auto& m : oxr_to_ixr_points) {
            locations->jointLocations[m.first].locationFlags = (h_pts[m.second].valid) ? (XR_SPACE_LOCATION_POSITION_VALID_BIT | XR_SPACE_LOCATION_POSITION_TRACKED_BIT) : XR_SPACE_LOCATION_POSITION_VALID_BIT;
            locations->jointLocations[m.first].pose.position = {h_pts[m.second].x(), h_pts[m.second].y(), h_pts[m.second].z()};
            locations->jointLocations[m.first].pose.orientation = {0., 0., 0., 0.};
        }
        for (auto pnt : invalid) {
            locations->jointLocations[pnt].locationFlags = 0;
            locations->jointLocations[pnt].pose.position = {0., 0., 0.};
            locations->jointLocations[pnt].pose.orientation = {0., 0., 0., 0.};
        }
    }
    return XR_SUCCESS;
}

ht_illixr_handle_t* create_ht_illixr() {
    // get phonebook somehow
    bt_int::shared_memory_object shm_obj(bt_int::open_only, "ILLIXR_OPENXR_SHM", bt_int::read_only);
    bt_int::mapped_region region(shm_obj, bt_int::read_only);

    auto* sb = reinterpret_cast<ILLIXR::switchboard*>(reinterpret_cast<std::uintptr_t>(region.get_address()));
    auto* hth = new ht_illixr_handle_t(sb);


    return hth;
}