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

//-------------------
PFN_xrEnumerateInstanceExtensionProperties
        _NextEnumerateInstanceExtensionProperties{ nullptr };
//-------------------


XrResult illixr_xrEnumerateInstanceExtensionProperties(
        const char*                                 layerName,
        uint32_t                                    propertyCapacityInput,
        uint32_t*                                   propertyCountOutput,
        XrExtensionProperties*                      properties) {
    //XrResult result = XR_ERROR_RUNTIME_FAILURE;
    PRINT_MSG("enumerate\n");

    // The OpenXR specification says that this should work without an instance,
    // however, a 'next' pointer is needed to query extensions that might be
    // provided by another API layer, and the OpenXR *Loader* spec says:
    //
    // "an implicit API layer, it must add its own instance extension
    // contents to the list of extensions."; this means we - and any lower
    // layers - need the 'next' pointer.

    if (propertyCountOutput == ((void *) nullptr)) {
        return XR_ERROR_VALIDATION_FAILURE;
    }

    if (layerName == NULL && _NextEnumerateInstanceExtensionProperties) {
        return _NextEnumerateInstanceExtensionProperties(
		    layerName, propertyCapacityInput, propertyCountOutput, properties);


        /* || std::string_view(layerName) == "ILLIXR_HT") {
        const uint32_t baseOffset = *propertyCountOutput;
        *propertyCountOutput += 1;
        if (propertyCapacityInput) {
            if (propertyCapacityInput < *propertyCountOutput) {
                result = XR_ERROR_SIZE_INSUFFICIENT;
            } else {
                result = XR_SUCCESS;
                properties[*propertyCountOutput - 1] = extension_props;
            }
        }*/
    }

    *propertyCountOutput = 0;
    return XR_SUCCESS;

}


XrResult illixr_xrEnumerateApiLayerProperties(
        uint32_t propertyCapacityInput,
        uint32_t* propertyCountOutput,
        XrApiLayerProperties* properties) {
	if (propertyCapacityInput == 0) {
		return XR_ERROR_SIZE_INSUFFICIENT;
	}

	*properties = XrApiLayerProperties{
		.type = XR_TYPE_API_LAYER_PROPERTIES,
		.specVersion = XR_CURRENT_API_VERSION,
		.layerVersion = 1,
		.description = "ILLIXR hand tracking",
	};
	std::strncpy(
	    properties->layerName, kLayerName.c_str(), XR_MAX_API_LAYER_NAME_SIZE);
	*propertyCountOutput = 1;

	return XR_SUCCESS;
}

XrResult illixr_xrCreateApiLayerInstance(
        const XrInstanceCreateInfo*                 info,
        const XrApiLayerCreateInfo*                 layerInfo,
        XrInstance*                                 instance) {
    std::string lname = layerInfo->nextInfo->layerName;
    PRINT_MSG("A0  %s  %s\n", layerInfo->nextInfo->layerName, kLayerName.c_str());
    PRINT_MSG("ixrCreate\n");
    if (layerInfo->structType != XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO ||
        layerInfo->structVersion != XR_API_LAYER_CREATE_INFO_STRUCT_VERSION ||
        layerInfo->structSize < sizeof(XrApiLayerCreateInfo) ||
        layerInfo->nextInfo == ((void *) 0) ||
        layerInfo->nextInfo->structType != XR_LOADER_INTERFACE_STRUCT_API_LAYER_NEXT_INFO ||
        layerInfo->nextInfo->structVersion != XR_API_LAYER_NEXT_INFO_STRUCT_VERSION ||
        layerInfo->nextInfo->structSize < sizeof(XrApiLayerNextInfo) ||
        kLayerName != lname ||
        layerInfo->nextInfo->nextGetInstanceProcAddr == ((void *) 0) ||
        layerInfo->nextInfo->nextCreateApiLayerInstance == ((void *) 0)) {
        PRINT_MSG("X1\n");
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    auto nextLayerCreateInfo = *layerInfo;
    nextLayerCreateInfo.nextInfo = layerInfo->nextInfo->next;

    PRINT_MSG("XX0\n");

    auto res = layerInfo->nextInfo->nextCreateApiLayerInstance(info, &nextLayerCreateInfo, instance);
    if (XR_FAILED(res)) {
        PRINT_MSG("X2\n");
        return res;
    }

    xrInstance = *instance;
    PRINT_MSG("XX01\n");
    _nextXrGetInstanceProcAddr = layerInfo->nextInfo->nextGetInstanceProcAddr;
    if (_nextXrGetInstanceProcAddr == NULL)
        PRINT_MSG("IS NULL");
    _nextXrGetInstanceProcAddr(*instance,
                               "xrEnumerateInstanceExtensionProperties",
                               reinterpret_cast<PFN_xrVoidFunction *>(
                                       &_NextEnumerateInstanceExtensionProperties));

    return res;
}


XrResult XRAPI_CALL illixr_xrCreateHandTrackerEXT(XrSession session,
                                                  const XrHandTrackerCreateInfoEXT* createInfo,
                                                  XrHandTrackerEXT* handTracker) {
    PRINT_MSG("createHandle\n");
    ixr_hand_tracker* tracker_handle = nullptr;
    ixr_session *sess = nullptr;

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
    auto ret = handle_create(sess, createInfo, tracker_handle);
    if (XR_FAILED(ret))
        return ret;

    *handTracker = reinterpret_cast<XrHandTrackerEXT>(tracker_handle);
    return ret;
}

XrResult XRAPI_CALL illixr_xrDestroyHandTrackerEXT(XrHandTrackerEXT handTracker) {
    ixr_hand_tracker* hand_tracker;

    if (handTracker == NULL) {
        PRINT_MSG("handTracker == NULL\n");
        return XR_ERROR_HANDLE_INVALID;
    }
    hand_tracker = reinterpret_cast<ixr_hand_tracker*>(handTracker);
    handle_destory(hand_tracker);
    return XR_SUCCESS;
}

XrResult XRAPI_CALL illixr_xrLocateHandJointsEXT(XrHandTrackerEXT handTracker,
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


XrResult XRAPI_CALL illixr_xrGetInstanceProcAddr(
        XrInstance                                  instance,
        const char*                                 name,
        PFN_xrVoidFunction*                         function) {

    std::string f_name = name;

    // Must be supported without an instance

    //*function = NULL;

    if (f_name == "xrEnumerateInstanceExtensionProperties") {
        *function = (PFN_xrVoidFunction) &illixr_xrEnumerateInstanceExtensionProperties;
        return XR_SUCCESS;
    }

    if (f_name == "xrEnumerateApiLayerProperties") {
        *function = reinterpret_cast<PFN_xrVoidFunction>(&illixr_xrEnumerateApiLayerProperties);
        return XR_SUCCESS;
    }

    if (!(instance && _nextXrGetInstanceProcAddr)) {
        return XR_ERROR_HANDLE_INVALID;
    }

    *function = nullptr;
    const auto ret = _nextXrGetInstanceProcAddr(instance, name, function);
    if (XR_FAILED(ret) || !*function) {
        return ret;
    }

    if (f_name == "xrCreateHandTrackerEXT") {
        //next_xrCreateHandTrackerEXT = reinterpret_cast<PFN_xrCreateHandTrackerEXT>(*function);
        *function = reinterpret_cast<PFN_xrVoidFunction>(&illixr_xrCreateHandTrackerEXT);
        return ret;
    }

    if (f_name == "xrDestroyHandTrackerEXT") {
        //next_xrDestroyHandTrackerEXT = reinterpret_cast<PFN_xrDestroyHandTrackerEXT>(*function);
        *function = reinterpret_cast<PFN_xrVoidFunction>(&illixr_xrDestroyHandTrackerEXT);
        return ret;
    }

    if (f_name == "xrLocateHandJointsEXT") {
        //next_xrLocateHandJointsEXT = reinterpret_cast<PFN_xrLocateHandJointsEXT>(*function);
        *function = reinterpret_cast<PFN_xrVoidFunction>(&illixr_xrLocateHandJointsEXT);
        return ret;
    }

    return ret;
}



#ifdef __cplusplus
extern "C" {
#endif
XrResult illixr_xrNegotiateLoaderApiLayerInterface(const XrNegotiateLoaderInfo* loaderInfo,
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
    layerRequest->getInstanceProcAddr = reinterpret_cast<PFN_xrGetInstanceProcAddr>(illixr_xrGetInstanceProcAddr);
    layerRequest->createApiLayerInstance = reinterpret_cast<PFN_xrCreateApiLayerInstance>(illixr_xrCreateApiLayerInstance);
    PRINT_MSG("DONE\n");
    return XR_SUCCESS;
}

#ifdef __cplusplus
}
#endif
