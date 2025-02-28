#ifndef XR_NO_PROTOTYPES
#define XR_NO_PROTOTYPES
#endif

#include <malloc.h>
#include <cstring>
#include <string>

#include "interface.h"
#include "openxr/openxr_loader_negotiation.h"

#define INTERFACE_VERSION 1
#define API_VERSION 1

#define PRINT_ERROR(...)              \
    do {                              \
        fprintf(stderr, __VA_ARGS__); \
    } while (0)


const std::string kLayerName = "ILLIXR_HT";

PFN_xrGetInstanceProcAddr nextXrGetInstanceProcAddr = nullptr;
PFN_xrEnumerateInstanceExtensionProperties NextEnumerateInstanceExtensionProperties{ nullptr };

XrResult illixr_xrEnumerateInstanceExtensionProperties(
        const char*                                 layerName,
        uint32_t                                    propertyCapacityInput,
        uint32_t*                                   propertyCountOutput,
        XrExtensionProperties*                      properties) {

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

    if (layerName == NULL && NextEnumerateInstanceExtensionProperties) {
        return NextEnumerateInstanceExtensionProperties(layerName, propertyCapacityInput, propertyCountOutput,
                                                        properties);
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
	std::strncpy(properties->layerName, kLayerName.c_str(), XR_MAX_API_LAYER_NAME_SIZE);
	*propertyCountOutput = 1;

	return XR_SUCCESS;
}

XrResult illixr_xrCreateApiLayerInstance(
        const XrInstanceCreateInfo*                 info,
        const XrApiLayerCreateInfo*                 layerInfo,
        XrInstance*                                 instance) {
    std::string lname = layerInfo->nextInfo->layerName;
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
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    auto nextLayerCreateInfo = *layerInfo;
    nextLayerCreateInfo.nextInfo = layerInfo->nextInfo->next;


    auto res = layerInfo->nextInfo->nextCreateApiLayerInstance(info, &nextLayerCreateInfo, instance);
    if (XR_FAILED(res)) {
        return res;
    }
    nextXrGetInstanceProcAddr = layerInfo->nextInfo->nextGetInstanceProcAddr;
    if (nextXrGetInstanceProcAddr == NULL)
        return XR_ERROR_HANDLE_INVALID;
    nextXrGetInstanceProcAddr(*instance,
                               "xrEnumerateInstanceExtensionProperties",
                               reinterpret_cast<PFN_xrVoidFunction *>(
                                       &NextEnumerateInstanceExtensionProperties));

    return res;
}




XrResult XRAPI_CALL illixr_xrGetInstanceProcAddr(
        XrInstance                                  instance,
        const char*                                 name,
        PFN_xrVoidFunction*                         function) {

    std::string f_name = name;

    // Must be supported without an instance

    if (f_name == "xrEnumerateInstanceExtensionProperties") {
        *function = (PFN_xrVoidFunction) &illixr_xrEnumerateInstanceExtensionProperties;
        return XR_SUCCESS;
    }

    if (f_name == "xrEnumerateApiLayerProperties") {
        *function = reinterpret_cast<PFN_xrVoidFunction>(&illixr_xrEnumerateApiLayerProperties);
        return XR_SUCCESS;
    }

    if (!(instance && nextXrGetInstanceProcAddr)) {
        return XR_ERROR_HANDLE_INVALID;
    }

    *function = nullptr;
    const auto ret = nextXrGetInstanceProcAddr(instance, name, function);
    if (XR_FAILED(ret) || !*function) {
        return ret;
    }

    if (f_name == "xrCreateHandTrackerEXT") {
        *function = reinterpret_cast<PFN_xrVoidFunction>(&illixr_xrCreateHandTrackerEXT);
        return ret;
    }

    if (f_name == "xrDestroyHandTrackerEXT") {
        *function = reinterpret_cast<PFN_xrVoidFunction>(&illixr_xrDestroyHandTrackerEXT);
        return ret;
    }

    if (f_name == "xrLocateHandJointsEXT") {
        *function = reinterpret_cast<PFN_xrVoidFunction>(&illixr_xrLocateHandJointsEXT);
        return ret;
    }

    return ret;
}



#ifdef __cplusplus
extern "C" {
#endif
[[maybe_unused]]XrResult illixr_xrNegotiateLoaderApiLayerInterface(const XrNegotiateLoaderInfo* loaderInfo,
                                                   const char* layerName,
                                                   XrNegotiateApiLayerRequest* layerRequest) {
    std::string lname = layerName;
    if (lname !=  kLayerName)
        return XR_ERROR_INITIALIZATION_FAILED;

    if (loaderInfo == ((void *) 0) ||
        loaderInfo->structType != XR_LOADER_INTERFACE_STRUCT_LOADER_INFO ||
        loaderInfo->structSize != sizeof(XrNegotiateLoaderInfo) ||
        loaderInfo->structVersion != XR_LOADER_INFO_STRUCT_VERSION) {
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    if (layerRequest == ((void *) 0) ||
        layerRequest->structType != XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST ||
        layerRequest->structVersion != XR_API_LAYER_INFO_STRUCT_VERSION ||
        layerRequest->structSize != sizeof(XrNegotiateApiLayerRequest)) {
        return XR_ERROR_INITIALIZATION_FAILED;
    }

    if (loaderInfo->minInterfaceVersion > INTERFACE_VERSION || loaderInfo->maxInterfaceVersion < INTERFACE_VERSION) {
        PRINT_ERROR("ILLIXR ht only supports OpenXR version %d which is not between the requested %d and %d\n",
                  INTERFACE_VERSION, loaderInfo->minInterfaceVersion, loaderInfo->maxInterfaceVersion
        );
        return XR_ERROR_INITIALIZATION_FAILED;
    }
    layerRequest->layerInterfaceVersion = XR_CURRENT_LOADER_API_LAYER_VERSION;
    layerRequest->layerApiVersion = API_VERSION;
    layerRequest->getInstanceProcAddr = reinterpret_cast<PFN_xrGetInstanceProcAddr>(illixr_xrGetInstanceProcAddr);
    layerRequest->createApiLayerInstance = reinterpret_cast<PFN_xrCreateApiLayerInstance>(illixr_xrCreateApiLayerInstance);
    return XR_SUCCESS;
}

#ifdef __cplusplus
}
#endif
