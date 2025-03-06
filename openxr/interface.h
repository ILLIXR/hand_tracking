#pragma once
#include <openxr/openxr.h>

#ifdef __cplusplus
    #define EXTERNC extern "C"
#else
    #define EXTERNC
#endif

/**
 * These are interface functions between OpenXR and the hand tracker.
 */

struct ht_illixr_handle_t;
typedef struct ht_illixr_handle_t* ht_illixr_handle;

/**
 * Wrapper for XrSessionState
 */
struct ixr_session {
    XrSessionState state;
};

/**
 * Struct for holdingdata on a hand tracking instance
 */
struct ixr_hand_tracker {
    struct ixr_session* session; //!< the session associated with this instance

    ht_illixr_handle                   ht_handle;   //!< handle to the hand tracker
    XrHandEXT                          hand;        //!< th hand this instance is associated with
    int                                ixr_hand;    //!< illixr enumeration of `hand`
    [[maybe_unused]] XrHandJointSetEXT hand_joints; //!< holds the actual joint positions for the hand
};

/**
 * Create a hand joints handle.
 * @param session An XrSession in which the hand tracker will be active.
 * @param createInfo The XrHandTrackerCreateInfoEXT used to specify the hand tracker.
 * @param handTracker The returned XrHandTrackerEXT handle.
 * @return XrResult instance.
 */
XrResult illixr_xrCreateHandTrackerEXT(XrSession session, const XrHandTrackerCreateInfoEXT* createInfo,
                                       XrHandTrackerEXT* handTracker);

/**
 * Destroy a hand joints handle
 * @param handTracker An XrHandTrackerEXT previously created by illixr_xrCreateHandTrackerEXT.
 * @return XrResult instance.
 */
XrResult XRAPI_CALL illixr_xrDestroyHandTrackerEXT(XrHandTrackerEXT handTracker);

/**
 * Locate hand joint locations
 * @param handTracker An XrHandTrackerEXT previously created by illixr_xrCreateHandTrackerEXT.
 * @param locateInfo Pointer to XrHandJointsLocateInfoEXT describing information to locate hand joints.
 * @param locations Pointer to XrHandJointLocationsEXT receiving the returned hand joint locations.
 * @return XrResult instance.
 */
XrResult XRAPI_CALL illixr_xrLocateHandJointsEXT(XrHandTrackerEXT handTracker, const XrHandJointsLocateInfoEXT* locateInfo,
                                                 XrHandJointLocationsEXT* locations);
