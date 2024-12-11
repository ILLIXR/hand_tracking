#ifndef XR_NO_PROTOTYPES
#define XR_NO_PROTOTYPES
#endif

#include <malloc.h>
#include <cstring>
#include <string>
#include "interface.h"
#include "oxr_objects.h"
#include "openxr/openxr_loader_negotiation.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#define INTERFACE_VERSION 1
#define API_VERSION 1

#define PRINT_ERROR(...)              \
    do {                              \
        fprintf(stderr, __VA_ARGS__); \
    } while (0)

const char* kLayerName = "ILLIXR_HT";

PFN_xrGetInstanceProcAddr _nextXrGetInstanceProcAddr = nullptr;
static XrInstanceCreateInfo instanceInfo;
static XrInstance xrInstance;


static inline XrHandTrackerEXT ixr_ht_to_oxr(struct ixr_hand_tracker* tracker) {
    return ((XrHandTrackerEXT) (uint64_t) (uintptr_t) (tracker));
}

EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
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

EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
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

EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
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


EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
ixrCreateApiLayerInstance(
        const XrInstanceCreateInfo*                 info,
        const XrApiLayerCreateInfo*                 layerInfo,
        XrInstance*                                 instance) {
    if (!layerInfo ||
        layerInfo->structType != XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO ||
        layerInfo->structVersion != XR_API_LAYER_CREATE_INFO_STRUCT_VERSION ||
        layerInfo->structSize < sizeof(XrApiLayerCreateInfo) ||
        !layerInfo->nextInfo ||
        layerInfo->nextInfo->structType != XR_LOADER_INTERFACE_STRUCT_API_LAYER_NEXT_INFO ||
        layerInfo->nextInfo->structVersion != XR_API_LAYER_NEXT_INFO_STRUCT_VERSION ||
        layerInfo->nextInfo->structSize < sizeof(XrApiLayerNextInfo) ||
        strcmp(kLayerName, layerInfo->nextInfo->layerName) ||
        layerInfo->nextInfo->nextGetInstanceProcAddr == nullptr ||
        layerInfo->nextInfo->nextCreateApiLayerInstance == nullptr)
        return XR_ERROR_INITIALIZATION_FAILED;


    // Get the function pointers we need
    _nextXrGetInstanceProcAddr = layerInfo->nextInfo->nextGetInstanceProcAddr;
    XrResult res;
    res = layerInfo->nextInfo->nextCreateApiLayerInstance(info, layerInfo, instance);
    if (XR_FAILED(res)) {
        return res;
    }

    //res = _nextXrGetInstanceProcAddr(*instance, "xrCreateSession", (PFN_xrVoidFunction *)&ixrCreateSession);
    //if (XR_FAILED(res)) {
    //    return res;
    //}

    res = _nextXrGetInstanceProcAddr(*instance, "xrCreateHandTrackerEXT", (PFN_xrVoidFunction *)&ixrCreateHandTrackerEXT);
    if (XR_FAILED(res)) {
        return res;
    }

    res = _nextXrGetInstanceProcAddr(*instance, "xrDestroyHandTrackerEXT", (PFN_xrVoidFunction *)&ixrDestroyHandTrackerEXT);
    if (XR_FAILED(res)) {
        return res;
    }

    res = _nextXrGetInstanceProcAddr(*instance, "xrLocateHandJointsEXT", (PFN_xrVoidFunction *)&ixrLocateHandJointsEXT);

    instanceInfo = *info;
    xrInstance = *instance;
    return res;
}


EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
ixrEnumerateInstanceExtensionProperties(
        const char*                                 layerName,
        uint32_t                                    propertyCapacityInput,
        uint32_t*                                   propertyCountOutput,
        XrExtensionProperties*                      properties) {
    XrResult result = XR_ERROR_RUNTIME_FAILURE;

    if (propertyCountOutput == ((void *) nullptr)) {
        return XR_ERROR_VALIDATION_FAILURE;
    }

    if (!layerName || std::string_view(layerName) == "ILLIXR_HT") {
        const uint32_t baseOffset = *propertyCountOutput;
        *propertyCountOutput += 1;
        if (propertyCapacityInput) {
            if (propertyCapacityInput < *propertyCountOutput) {
                result = XR_ERROR_SIZE_INSUFFICIENT;
            } else {
                result = XR_SUCCESS;
                properties[*propertyCountOutput - 1] = extension_props;
            }
        }
    }

    return result;
}

EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
ixrGetInstanceProcAddr(
        XrInstance                                  instance,
        const char*                                 name,
        PFN_xrVoidFunction*                         function) {

    std::string f_name = name;

    *function = NULL;

    if (instance == XR_NULL_HANDLE) {
        if (f_name == "xrEnumerateInstanceExtensionProperties") {
            *function = (PFN_xrVoidFunction) &ixrEnumerateInstanceExtensionProperties;
            return XR_SUCCESS;
        }
        return XR_ERROR_HANDLE_INVALID;
    }
    auto* inst = (struct oxr_instance*) ((uintptr_t) instance);
    if (f_name == "xrCreateHandTrackerEXT" == 0) {
        if (inst->extensions.EXT_hand_tracking) {
            PFN_xrCreateHandTrackerEXT ret = &ixrCreateHandTrackerEXT;
            *function = (PFN_xrVoidFunction) (ret);
            return XR_SUCCESS;
        }
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
    if (f_name == "xrDestroyHandTrackerEXT") {
        if (inst->extensions.EXT_hand_tracking) {
            PFN_xrDestroyHandTrackerEXT ret = &ixrDestroyHandTrackerEXT;
            *function = (PFN_xrVoidFunction) (ret);
            return XR_SUCCESS;
        }
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
    if (f_name == "xrLocateHandJointsEXT") {
        if (inst->extensions.EXT_hand_tracking) {
            PFN_xrLocateHandJointsEXT ret = &ixrLocateHandJointsEXT;
            *function = (PFN_xrVoidFunction) (ret);
            return XR_SUCCESS;
        }
        return XR_ERROR_FUNCTION_UNSUPPORTED;
    }
    return _nextXrGetInstanceProcAddr(instance, name, function);
}


EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
ixrNegotiateLoaderApiLayerInterface(const XrNegotiateLoaderInfo* loaderInfo,
                                    const char* layerName,
                                    XrNegotiateApiLayerRequest* layerRequest) {
    if (layerName) {
        if (strncmp(layerName, kLayerName, strlen(kLayerName)) != 0)
            return XR_ERROR_INITIALIZATION_FAILED;
    }

    if (!loaderInfo ||
        loaderInfo->structType != XR_LOADER_INTERFACE_STRUCT_LOADER_INFO ||
        loaderInfo->structSize != sizeof(XrNegotiateLoaderInfo) ||
        loaderInfo->structVersion != XR_LOADER_INFO_STRUCT_VERSION) {
        PRINT_ERROR("Bad loader info");
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    if (!layerRequest ||
        layerRequest->structType != XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST ||
        layerRequest->structVersion != XR_API_LAYER_INFO_STRUCT_VERSION ||
        layerRequest->structSize != sizeof(XrNegotiateApiLayerRequest)) {
        PRINT_ERROR("Bad api layer info");
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    if (loaderInfo->minInterfaceVersion > INTERFACE_VERSION || loaderInfo->maxInterfaceVersion < INTERFACE_VERSION) {
        PRINT_ERROR("ILLIXR ht only supports OpenXR version %d which is not between the requested %d and %d",
                    INTERFACE_VERSION, loaderInfo->minInterfaceVersion, loaderInfo->maxInterfaceVersion
        );
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    layerRequest->layerInterfaceVersion = XR_CURRENT_LOADER_API_LAYER_VERSION;
    layerRequest->layerApiVersion = API_VERSION;
    layerRequest->getInstanceProcAddr = reinterpret_cast<PFN_xrGetInstanceProcAddr>(ixrGetInstanceProcAddr);
    layerRequest->createApiLayerInstance = reinterpret_cast<PFN_xrCreateApiLayerInstance>(ixrCreateApiLayerInstance);
    return XR_SUCCESS;
}
