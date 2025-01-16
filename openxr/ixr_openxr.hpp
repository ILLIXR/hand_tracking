#include "openxr/openxr_loader_negotiation.h"
#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

const char* illixr_shm_name = "ILLIXR_OXR_SHM";
const char* illixr_shm_swap[2] = {"ILLIXR_SHM_SWAP1", "ILLIXR_SHM_SWAP2"};
const char* illixr_shm_current = "ILLIXR_SHM_CURRENT";
const char* illixr_shm_mutex_latest = "ILLIXR_OXR_MUTEX_L";
const char* illixr_shm_mutex_swap[2] = {"ILLIXR_OXR_MUTEX_S1", "ILLIXR_OXR_MUTEX_S2"};

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
