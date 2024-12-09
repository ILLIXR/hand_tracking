#pragma once
#include <openxr/openxr.h>

//#include <openxr/openxr_reflection.h>

#ifdef __cplusplus
extern "C" {
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
    XrHandJointSetEXT hand_joints;
};
XrResult handle_create(struct ixr_session* session,
                       const XrHandTrackerCreateInfoEXT* info,
                       struct ixr_hand_tracker** handle);
void handle_destory(struct ixr_hand_tracker* handle);
XrResult locate_hand(struct ixr_hand_tracker* hand_tracker, const XrHandJointsLocateInfoEXT* info, XrHandJointLocationsEXT* locations);

XRAPI_ATTR XrResult XRAPI_CALL
ixrCreateHandTrackerEXT(XrSession session, const XrHandTrackerCreateInfoEXT* createInfo,
                        XrHandTrackerEXT* handTracker);
XRAPI_ATTR XrResult XRAPI_CALL
ixrDestroyHandTrackerEXT(XrHandTrackerEXT handTracker);

XRAPI_ATTR XrResult XRAPI_CALL
ixrLocateHandJointsEXT(XrHandTrackerEXT handTracker, const XrHandJointsLocateInfoEXT* locateInfo,
                       XrHandJointLocationsEXT* locations);

ht_illixr_handle create_ht_illixr();
#ifdef __cplusplus
}
#endif