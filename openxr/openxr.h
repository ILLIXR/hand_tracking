#include "openxr/openxr_loader_negotiation.h"
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

XrResult illixr_xrEnumerateInstanceExtensionProperties(
        const char*                                 layerName,
        uint32_t                                    propertyCapacityInput,
        uint32_t*                                   propertyCountOutput,
        XrExtensionProperties*                      properties);

XrResult illixr_xrEnumerateApiLayerProperties(
        uint32_t propertyCapacityInput,
        uint32_t* propertyCountOutput,
        XrApiLayerProperties* properties);

XrResult illixr_xrCreateApiLayerInstance(
        const XrInstanceCreateInfo*                 info,
        const XrApiLayerCreateInfo*                 layerInfo,
        XrInstance*                                 instance);

EXTERNC XrResult illixr_xrNegotiateLoaderApiLayerInterface(
        const XrNegotiateLoaderInfo* loaderInfo,
        const char* layerName,
        XrNegotiateApiLayerRequest* layerRequest);

XrResult XRAPI_CALL illixr_xrGetInstanceProcAddr(
        XrInstance instance,
        const char *name,
        PFN_xrVoidFunction *function);
