#ifdef BUILD_OXR

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
FILE *fptr;
#define PRINT_ERROR(...)              \
    do {                              \
        fprintf(stderr, __VA_ARGS__); \
    } while (0)

#define PRINT_MSG(...) \
    do {               \
        fptr = fopen("/home/friedel/oxr.log", "a"); \
        fprintf(fptr, __VA_ARGS__);                 \
        fclose(fptr);\
        } while(0)

const std::string kLayerName = "ILLIXR_HT";

PFN_xrGetInstanceProcAddr _nextXrGetInstanceProcAddr = nullptr;
static XrInstanceCreateInfo instanceInfo;
static XrInstance xrInstance;


EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
ixrCreateHandTrackerEXT(XrSession session,
                        const XrHandTrackerCreateInfoEXT* createInfo,
                        XrHandTrackerEXT* handTracker) {
    PRINT_MSG("createHandle\n");
    ixr_hand_tracker* tracker_handle = nullptr;
    ixr_session *sess = nullptr;

    XrResult ret;

    if (!session) {
        PRINT_MSG("session == NULL\n");
        return XR_ERROR_HANDLE_INVALID;
    }
    sess = reinterpret_cast<ixr_session *>(session);
    if (createInfo == ((void *) 0)) {
        PRINT_MSG("create_info == NULL\n");
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (createInfo->type != XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT) {
        PRINT_MSG("create info bad type %u\n", createInfo->type);
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (handTracker == ((void *) 0)) {
        PRINT_MSG("handTracker == NULL\n");
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (createInfo->hand != XR_HAND_LEFT_EXT && createInfo->hand != XR_HAND_RIGHT_EXT) {
        PRINT_MSG("Invalid hand %d\n", createInfo->hand);
        return XR_ERROR_VALIDATION_FAILURE;
    }
    ret = handle_create(sess, createInfo, tracker_handle);
    if (ret != XR_SUCCESS)
        return ret;

    *handTracker = reinterpret_cast<XrHandTrackerEXT>(tracker_handle);
    return XR_SUCCESS;
}

EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
ixrDestroyHandTrackerEXT(XrHandTrackerEXT handTracker) {
    ixr_hand_tracker* hand_tracker;

    if (handTracker == NULL) {
        PRINT_MSG("handTracker == NULL\n");
        return XR_ERROR_HANDLE_INVALID;
    }
    hand_tracker = reinterpret_cast<ixr_hand_tracker*>(handTracker);
    handle_destory(hand_tracker);
    return XR_SUCCESS;
}

EXTERNC XRAPI_ATTR XrResult XRAPI_CALL
ixrLocateHandJointsEXT(XrHandTrackerEXT handTracker,
                       const XrHandJointsLocateInfoEXT* locateInfo,
                       XrHandJointLocationsEXT* locations) {
    struct ixr_hand_tracker* hand_tracker;
    if (handTracker == ((void *) 0)) {
        PRINT_MSG("handTracker == NULL\n");
        return XR_ERROR_HANDLE_INVALID;
    }
    hand_tracker = reinterpret_cast<ixr_hand_tracker*>(handTracker);
    if (locateInfo == ((void *) 0)) {
        PRINT_MSG("locateInfo == NULL\n");
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (locateInfo->type != XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT) {
        PRINT_MSG("Bad type for locateInfo %u\n", locateInfo->type);
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (locations == ((void *) 0)) {
        PRINT_MSG("locateInfo == NULL\n");
        return XR_ERROR_VALIDATION_FAILURE;
    }
    if (locations->type != XR_TYPE_HAND_JOINT_LOCATIONS_EXT) {
        PRINT_MSG("Bad type for location %u\n", locations->type);
        return XR_ERROR_VALIDATION_FAILURE;
    }

    if (locations->jointCount != 25 && locations->jointCount != 21) {
        PRINT_MSG("Bad joint count\n");
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
    std::string lname = layerInfo->nextInfo->layerName;
    PRINT_MSG("A0  %s  %s\n", layerInfo->nextInfo->layerName, kLayerName.c_str());
    PRINT_MSG("ixrCreate\n");
    if (layerInfo->structType != XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO ||
        layerInfo->structVersion != XR_API_LAYER_CREATE_INFO_STRUCT_VERSION ||
        layerInfo->structSize < sizeof(XrApiLayerCreateInfo) ||
        layerInfo->nextInfo == ((void *) 0)||
        layerInfo->nextInfo->structType != XR_LOADER_INTERFACE_STRUCT_API_LAYER_NEXT_INFO ||
        layerInfo->nextInfo->structVersion != XR_API_LAYER_NEXT_INFO_STRUCT_VERSION ||
        layerInfo->nextInfo->structSize < sizeof(XrApiLayerNextInfo) ||
        kLayerName != lname ||
        layerInfo->nextInfo->nextGetInstanceProcAddr == ((void *) 0) ||
        layerInfo->nextInfo->nextCreateApiLayerInstance == ((void *) 0)) {
        PRINT_MSG("X1\n");
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    PRINT_MSG("XX0\n");

    // Get the function pointers we need
    XrResult res;
    res = layerInfo->nextInfo->nextCreateApiLayerInstance(info, layerInfo, instance);
    if (XR_FAILED(res)) {
        PRINT_MSG("X2\n");
        return res;
    }
    _nextXrGetInstanceProcAddr = layerInfo->nextInfo->nextGetInstanceProcAddr;
    PRINT_MSG("XX01\n");
    if(_nextXrGetInstanceProcAddr == NULL)
        PRINT_MSG("IS NULL");
    //res = _nextXrGetInstanceProcAddr(*instance, "xrCreateSession", (PFN_xrVoidFunction *)&ixrCreateSession);
    //if (XR_FAILED(res)) {
    //    return res;
    //}

    res = _nextXrGetInstanceProcAddr(*instance, "xrCreateHandTrackerEXT", (PFN_xrVoidFunction *)&ixrCreateHandTrackerEXT);
    PRINT_MSG("XX01.5");
    PRINT_MSG(std::to_string(res).c_str());
    if (XR_FAILED(res)) {
        PRINT_MSG("X3\n");
        return res;
    }
    PRINT_MSG("XX02\n");

    res = _nextXrGetInstanceProcAddr(*instance, "xrDestroyHandTrackerEXT", (PFN_xrVoidFunction *)&ixrDestroyHandTrackerEXT);
    if (XR_FAILED(res)) {
        PRINT_MSG("X4\n");
        return res;
    }
    PRINT_MSG("XX03\n");

    res = _nextXrGetInstanceProcAddr(*instance, "xrLocateHandJointsEXT", (PFN_xrVoidFunction *)&ixrLocateHandJointsEXT);
    PRINT_MSG("XX04\n");

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
    PRINT_MSG("enumerate\n");

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
    auto* inst = reinterpret_cast<oxr_instance*>(instance);
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
    PRINT_MSG("Negotiate\n");
    std::string lname = layerName;
    if (lname !=  kLayerName)
        return XR_ERROR_INITIALIZATION_FAILED;


    if (loaderInfo == ((void *) 0) ||
        loaderInfo->structType != XR_LOADER_INTERFACE_STRUCT_LOADER_INFO ||
        loaderInfo->structSize != sizeof(XrNegotiateLoaderInfo) ||
        loaderInfo->structVersion != XR_LOADER_INFO_STRUCT_VERSION) {
        PRINT_MSG("Bad loader info\n");
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    if (layerRequest == ((void *) 0) ||
        layerRequest->structType != XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST ||
        layerRequest->structVersion != XR_API_LAYER_INFO_STRUCT_VERSION ||
        layerRequest->structSize != sizeof(XrNegotiateApiLayerRequest)) {
        PRINT_MSG("Bad api layer info\n");
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    if (loaderInfo->minInterfaceVersion > INTERFACE_VERSION || loaderInfo->maxInterfaceVersion < INTERFACE_VERSION) {
        PRINT_MSG("ILLIXR ht only supports OpenXR version %d which is not between the requested %d and %d\n",
                  INTERFACE_VERSION, loaderInfo->minInterfaceVersion, loaderInfo->maxInterfaceVersion
        );
        return XR_ERROR_INITIALIZATION_FAILED;
    }
    PRINT_MSG("SETTING INFO\n");
    layerRequest->layerInterfaceVersion = XR_CURRENT_LOADER_API_LAYER_VERSION;
    layerRequest->layerApiVersion = API_VERSION;
    layerRequest->getInstanceProcAddr = reinterpret_cast<PFN_xrGetInstanceProcAddr>(ixrGetInstanceProcAddr);
    layerRequest->createApiLayerInstance = reinterpret_cast<PFN_xrCreateApiLayerInstance>(ixrCreateApiLayerInstance);
    PRINT_MSG("DONE\n");
    return XR_SUCCESS;
}

#endif  // BUILD_OXR
