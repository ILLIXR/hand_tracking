#include <stdio.h>
#include <openxr/openxr.h>
#include <malloc.h>
#include "interface.h"
#include "openxr/openxr_loader_negotiation.h"

#define INTERFACE_VERSION 1
#define API_VERSION 1
#define PRINT_ERROR(...)              \
    do {                              \
        fprintf(stderr, __VA_ARGS__); \
    } while (0)

#ifdef __cplusplus
extern "C" {
#endif
/*
XRAPI_ATTR XrResult XRAPI_CALL get_instance_address(XrInstance instance, const char* name, PFN_xrVoidFunction* func) {
    *func = NULL;

    if (instance == XR_NULL_HANDLE) {
        return ;
    }

    struct oxr_instance *inst;
    return ;
}

XRAPI_ATTR XrResult XRAPI_CALL xrNegotiateLoaderApiLayerInterface(const XrNegotiateLoaderInfo* info, const char* layerName,
                                            XrNegotiateApiLayerRequest* layerRequest) {
    if (info->structType != XR_LOADER_INTERFACE_STRUCT_LOADER_INFO ||
        info->structSize != sizeof(XrNegotiateLoaderInfo) ||
        info->structVersion != XR_LOADER_INFO_STRUCT_VERSION) {
        PRINT_ERROR("Bad loader info");
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    if (layerRequest->structType != XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST ||
        layerRequest->structVersion != XR_API_LAYER_INFO_STRUCT_VERSION ||
        layerRequest->structSize != sizeof(XrNegotiateApiLayerRequest)) {
        PRINT_ERROR("Bad api layer info");
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    if (info->minInterfaceVersion > INTERFACE_VERSION || info->maxInterfaceVersion < INTERFACE_VERSION) {
        PRINT_ERROR("ILLIXR ht only supports OpenXR version %d which is not between the requested %d and %d",
                    INTERFACE_VERSION, info->minInterfaceVersion, info->maxInterfaceVersion
        );
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    layerRequest->layerInterfaceVersion = XR_CURRENT_LOADER_API_LAYER_VERSION;
    layerRequest->layerApiVersion = API_VERSION;
    layerRequest->getInstanceProcAddr;
    layerRequest->createApiLayerInstance;
    return XR_SUCCESS;
}


if (strcmp(name, "xrCreateHandTrackerEXT") == 0) {
if (inst->extensions.EXT_hand_tracking) {
PFN_xrCreateHandTrackerEXT ret = &oxr_xrCreateHandTrackerEXT;
*out_function = (PFN_xrVoidFunction) (ret);
return XR_SUCCESS;
}
return XR_ERROR_FUNCTION_UNSUPPORTED;
}*/

static inline XrHandTrackerEXT ixr_ht_to_oxr(struct ixr_hand_tracker* tracker) {
    return ((XrHandTrackerEXT) (uint64_t) (uintptr_t) (tracker));
}

XRAPI_ATTR XrResult XRAPI_CALL
ixrCreateHandTrackerEXT(XrSession session, const XrHandTrackerCreateInfoEXT* createInfo,
                                XrHandTrackerEXT* handTracker) {
    struct ixr_hand_tracker* tracker_handle = NULL;
    struct ixr_session *sess = NULL;

    XrResult ret;

    if (session == 0) {
        PRINT_ERROR("session == NULL");
         return XR_ERROR_HANDLE_INVALID;
    }
    sess = (struct ixr_session *) ((uintptr_t) session);
    if (createInfo == ((void *) 0)) {
        PRINT_ERROR("create_info == NULL");
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (createInfo->type != XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT) {
        PRINT_ERROR("create info bad type %u", createInfo->type);
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (handTracker == ((void *) 0)) {
        PRINT_ERROR("handTracker == NULL");
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (createInfo->hand != XR_HAND_LEFT_EXT && createInfo->hand != XR_HAND_RIGHT_EXT) {
        PRINT_ERROR("Invalid hand %d", createInfo->hand);
        return XR_ERROR_VALIDATION_FAILURE;
    }
    ret = handle_create(sess, createInfo, &tracker_handle);
    if (ret != XR_SUCCESS)
        return ret;

    *handTracker = ixr_ht_to_oxr(tracker_handle);
    return XR_SUCCESS;
}

XRAPI_ATTR XrResult XRAPI_CALL
ixrDestroyHandTrackerEXT(XrHandTrackerEXT handTracker) {
    struct ixr_hand_tracker* hand_tracker;

    if (handTracker == 0) {
        PRINT_ERROR("handTracker == NULL");
        return XR_ERROR_HANDLE_INVALID;
    }
    hand_tracker = (struct ixr_hand_tracker*) ((uintptr_t) handTracker);
    handle_destory(hand_tracker);
    return XR_SUCCESS;
}

XRAPI_ATTR XrResult XRAPI_CALL
ixrLocateHandJointsEXT(XrHandTrackerEXT handTracker, const XrHandJointsLocateInfoEXT* locateInfo,
                       XrHandJointLocationsEXT* locations) {
    struct ixr_hand_tracker* hand_tracker;
    if (handTracker == 0) {
        PRINT_ERROR("handTracker == NULL");
        return XR_ERROR_HANDLE_INVALID;
    }
    hand_tracker = (struct ixr_hand_tracker*) ((uintptr_t) handTracker);
    if (locateInfo == ((void *) 0)) {
        PRINT_ERROR("locateInfo == NULL");
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (locateInfo->type != XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT) {
        PRINT_ERROR("Bad type for locateInfo %u", locateInfo->type);
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (locations == ((void *) 0)) {
        PRINT_ERROR("locateInfo == NULL");
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (locations->type != XR_TYPE_HAND_JOINT_LOCATIONS_EXT) {
        PRINT_ERROR("Bad type for location %u", locations->type);
        return XR_ERROR_VALIDATION_FAILURE;
    }

    if (locations->jointCount != 25 && locations->jointCount != 21) {
        PRINT_ERROR("Bad joint count");
        return XR_ERROR_VALIDATION_FAILURE;
    }

    locate_hand(hand_tracker, locateInfo, locations);
    return XR_SUCCESS;
}


#ifdef __cplusplus
}
#endif