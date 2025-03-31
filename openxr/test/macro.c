#include "macro.h"

#include "external/openxr_headers/openxr_reflection.h"
#include "GL/glcorearb.h"

#include <SDL2/SDL.h>

#define XR_ENUM_CASE_STR(name, val) \
    case name:                      \
        return #name;

#define XR_ENUM_STR(enumType)                                                                \
    const char* XrStr_##enumType(uint64_t e) {                                               \
        switch (e) { XR_LIST_ENUM_##enumType(XR_ENUM_CASE_STR) default : return "Unknown"; } \
    }

#define XR_STR_IF_ENUM(name, val) \
    if (strcmp(#name, e) == 0)    \
        return val;

#define XR_STR_ENUM(enumType)                                      \
    uint64_t XrEnum_##enumType(const char* e) {                    \
        XR_LIST_ENUM_##enumType(XR_STR_IF_ENUM) return 0x7FFFFFFF; \
    }

#define XR_PRINT_ENUM(name, val) \
    if (val != 0x7FFFFFFF)       \
        printf("\t\t%s\n", #name);

#define XR_ENUM_PRINT_VALS(enumType)           \
    void XrPrintEnum_##enumType() {            \
        XR_LIST_ENUM_##enumType(XR_PRINT_ENUM) \
    }

// instead of invoking each of the macros for every type, make a meta macro
#define XR_MACROS(enumType) \
    XR_ENUM_STR(enumType)   \
    XR_STR_ENUM(enumType)   \
    XR_ENUM_PRINT_VALS(enumType)

XR_MACROS(XrResult)
XR_MACROS(XrFormFactor)
XR_MACROS(XrReferenceSpaceType)
XR_MACROS(XrViewConfigurationType)
XR_MACROS(XrEnvironmentBlendMode)
XR_MACROS(XrPlaneDetectionStateEXT)
