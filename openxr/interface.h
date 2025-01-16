#pragma once
#include <openxr/openxr.h>


#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

struct ht_illixr_handle_t;
typedef struct ht_illixr_handle_t* ht_illixr_handle;

struct ixr_session {
    XrSessionState state;
};

struct ixr_hand_tracker {
    struct ixr_session *session;

    ht_illixr_handle ht_handle;
    XrHandEXT hand;
    int ixr_hand;
    [[maybe_unused]] XrHandJointSetEXT hand_joints;
};

XrResult illixr_xrCreateHandTrackerEXT(XrSession session,
                                       const XrHandTrackerCreateInfoEXT* createInfo,
                                       XrHandTrackerEXT* handTracker);

XrResult XRAPI_CALL illixr_xrDestroyHandTrackerEXT(XrHandTrackerEXT handTracker);

XrResult XRAPI_CALL illixr_xrLocateHandJointsEXT(XrHandTrackerEXT handTracker,
                                                 const XrHandJointsLocateInfoEXT* locateInfo,
                                                 XrHandJointLocationsEXT* locations);
