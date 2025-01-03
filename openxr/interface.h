#pragma once
#ifdef BUILD_OXR
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
XrResult handle_create(ixr_session* session,
                       const XrHandTrackerCreateInfoEXT* info,
                       ixr_hand_tracker* handle);
void handle_destory(ixr_hand_tracker* handle);

XrResult locate_hand(ixr_hand_tracker* hand_tracker, const XrHandJointsLocateInfoEXT* info,
                     XrHandJointLocationsEXT* locations);

EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
ixrCreateHandTrackerEXT(XrSession session,
                        const XrHandTrackerCreateInfoEXT* createInfo,
                        XrHandTrackerEXT* handTracker);

EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
ixrDestroyHandTrackerEXT(XrHandTrackerEXT handTracker);

EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
ixrLocateHandJointsEXT(XrHandTrackerEXT handTracker,
                       const XrHandJointsLocateInfoEXT* locateInfo,
                       XrHandJointLocationsEXT* locations);


EXTERNC ht_illixr_handle create_ht_illixr();

#endif  // BUILD_OXR
