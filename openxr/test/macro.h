#pragma once

/*
This file contains expansion macros (X Macros) for OpenXR enumerations and structures.
Example of how to use expansion macros to make an enum-to-string function:
*/

#define XR_ENUM_STR_DCL(enumType) const char* XrStr_##enumType(uint64_t e);

#define XR_STR_ENUM_DCL(enumType) uint64_t XrEnum_##enumType(const char* e);

#define XR_ENUM_PRINT_VALS_DCL(enumType) void XrPrintEnum_##enumType();

// instead of invoking each of the macros for every type, make a meta macro
#define XR_MACROS_DCL(enumType)       \
	XR_ENUM_STR_DCL(enumType)         \
	XR_STR_ENUM_DCL(enumType)         \
	XR_ENUM_PRINT_VALS_DCL(enumType)

XR_MACROS_DCL(XrResult)
XR_MACROS_DCL(XrFormFactor)
XR_MACROS_DCL(XrReferenceSpaceType)
XR_MACROS_DCL(XrViewConfigurationType)
XR_MACROS_DCL(XrEnvironmentBlendMode)
XR_MACROS_DCL(XrPlaneDetectionStateEXT)


#define LOAD_OR_RETURN(NAME, LOCATION)                                                     \
	{                                                                                      \
		XrResult result =                                                                  \
		    xrGetInstanceProcAddr(instance, #NAME, (PFN_xrVoidFunction*)&LOCATION->NAME);  \
		if (!xr_check(instance, result, "Failed to get %s function!", #NAME))              \
			return result;                                                                 \
	}

#define HAND_LEFT_INDEX 0
#define HAND_RIGHT_INDEX 1
#define HAND_COUNT 2
