#include "func.h"

#include "external/openxr_headers/XR_MNDX_xdev_space.h"
#include "gl.h"

#include <stdio.h>
#include <string.h>

// function that initializes an extension struct basics like ext_name_string
typedef bool (*init_ext_struct)(struct base_extension_t** out_base);

init_ext_struct ext_init_funcs[] = {
    &init_opengl_t,        //
    &init_hand_tracking_t, //
    &init_refresh_rate_t,  //
    &init_xdev_space_t,    //
};

bool xr_check(XrInstance instance, XrResult result, const char* format, ...) {
    if (XR_SUCCEEDED(result))
        return true;

    char resultString[XR_MAX_RESULT_STRING_SIZE];
    xrResultToString(instance, result, resultString);

    char formatRes[XR_MAX_RESULT_STRING_SIZE + 1024];
    snprintf(formatRes, XR_MAX_RESULT_STRING_SIZE + 1023, "%s [%s]\n", format, resultString);

    va_list args;
    va_start(args, format);
    vprintf(formatRes, args);
    va_end(args);

    return false;
}

void print_system_properties(XrSystemProperties* system_properties) {
    printf("System properties for system %lu: \"%s\", vendor ID %d\n", system_properties->systemId,
           system_properties->systemName, system_properties->vendorId);
    printf("\tMax layers          : %d\n", system_properties->graphicsProperties.maxLayerCount);
    printf("\tMax swapchain height: %d\n", system_properties->graphicsProperties.maxSwapchainImageHeight);
    printf("\tMax swapchain width : %d\n", system_properties->graphicsProperties.maxSwapchainImageWidth);
    printf("\tOrientation Tracking: %d\n", system_properties->trackingProperties.orientationTracking);
    printf("\tPosition Tracking   : %d\n", system_properties->trackingProperties.positionTracking);

    const XrBaseInStructure* next = system_properties->next;
    while (next) {
        if (next->type == XR_TYPE_SYSTEM_HAND_TRACKING_PROPERTIES_EXT) {
            XrSystemHandTrackingPropertiesEXT* ht = (XrSystemHandTrackingPropertiesEXT*) next;
            printf("\tHand Tracking       : %d\n", ht->supportsHandTracking);
        }
        if (next->type == XR_TYPE_SYSTEM_XDEV_SPACE_PROPERTIES_MNDX) {
            XrSystemXDevSpacePropertiesMNDX* xd = (XrSystemXDevSpacePropertiesMNDX*) next;
            printf("\txdev space          : %d\n", xd->supportsXDevSpace);
        }
        next = next->next;
    }
}

void print_supported_view_configs(XrInstance instance, XrSystemId system_id) {
    XrResult result;

    uint32_t view_config_count;
    result = xrEnumerateViewConfigurations(instance, system_id, 0, &view_config_count, NULL);
    if (!xr_check(instance, result, "Failed to get view configuration count"))
        return;

    printf("Runtime supports %d view configurations\n", view_config_count);

    XrViewConfigurationType* view_configs =
        (XrViewConfigurationType*) malloc(view_config_count * sizeof(XrViewConfigurationType));
    result = xrEnumerateViewConfigurations(instance, system_id, view_config_count, &view_config_count, view_configs);
    if (!xr_check(instance, result, "Failed to enumerate view configurations!"))
        return;

    for (uint32_t i = 0; i < view_config_count; ++i) {
        XrViewConfigurationProperties props = {.type = XR_TYPE_VIEW_CONFIGURATION_PROPERTIES, .next = NULL};

        result = xrGetViewConfigurationProperties(instance, system_id, view_configs[i], &props);
        if (!xr_check(instance, result, "Failed to get view configuration info %d!", i))
            return;

        printf("type %d: FOV mutable: %d\n", props.viewConfigurationType, props.fovMutable);
    }
    free(view_configs);
}

void print_viewconfig_view_info(uint32_t view_count, XrViewConfigurationView* viewconfig_views) {
    for (uint32_t i = 0; i < view_count; i++) {
        printf("View Configuration View %d:\n", i);
        printf("\tResolution       : Recommended %dx%d, Max: %dx%d\n", viewconfig_views[0].recommendedImageRectWidth,
               viewconfig_views[0].recommendedImageRectHeight, viewconfig_views[0].maxImageRectWidth,
               viewconfig_views[0].maxImageRectHeight);
        printf("\tSwapchain Samples: Recommended: %d, Max: %d)\n", viewconfig_views[0].recommendedSwapchainSampleCount,
               viewconfig_views[0].maxSwapchainSampleCount);
    }
}

void print_reference_spaces(XrInstance instance, XrSession session) {
    XrResult result;

    uint32_t ref_space_count;
    result = xrEnumerateReferenceSpaces(session, 0, &ref_space_count, NULL);
    if (!xr_check(instance, result, "Getting number of reference spaces failed!"))
        return;

    XrReferenceSpaceType* ref_spaces = malloc(sizeof(XrReferenceSpaceType) * ref_space_count);
    result                           = xrEnumerateReferenceSpaces(session, ref_space_count, &ref_space_count, ref_spaces);
    if (!xr_check(instance, result, "Enumerating reference spaces failed!"))
        return;

    printf("Runtime supports %d reference spaces:\n", ref_space_count);
    for (uint32_t i = 0; i < ref_space_count; i++) {
        if (ref_spaces[i] == XR_REFERENCE_SPACE_TYPE_LOCAL) {
            printf("\tXR_REFERENCE_SPACE_TYPE_LOCAL\n");
        } else if (ref_spaces[i] == XR_REFERENCE_SPACE_TYPE_STAGE) {
            printf("\tXR_REFERENCE_SPACE_TYPE_STAGE\n");
        } else if (ref_spaces[i] == XR_REFERENCE_SPACE_TYPE_VIEW) {
            printf("\tXR_REFERENCE_SPACE_TYPE_VIEW\n");
        } else {
            printf("\tOther (extension?) refspace %u\\n", ref_spaces[i]);
        }
    }
    free(ref_spaces);
}

XrResult init_hand_tracking_fp(XrInstance instance, struct base_extension_t* base) {
    struct hand_tracking_t* hand_tracking = (struct hand_tracking_t*) base;
    LOAD_OR_RETURN(xrLocateHandJointsEXT, hand_tracking)
    LOAD_OR_RETURN(xrCreateHandTrackerEXT, hand_tracking)
    return XR_SUCCESS;
}

bool init_hand_tracking_t(struct base_extension_t** out_base) {
    *out_base = malloc(sizeof(struct hand_tracking_t));

    (*out_base)->ext_name_string = XR_EXT_HAND_TRACKING_EXTENSION_NAME;
    (*out_base)->init_fp         = &init_hand_tracking_fp;
    return true;
}

// wrapper struct to store everything related to one xdev
XrResult init_xdev_space_fp(XrInstance instance, struct base_extension_t* base) {
    struct xdev_space_t* xdev_space = (struct xdev_space_t*) base;
    LOAD_OR_RETURN(xrCreateXDevListMNDX, xdev_space)
    LOAD_OR_RETURN(xrGetXDevListGenerationNumberMNDX, xdev_space)
    LOAD_OR_RETURN(xrEnumerateXDevsMNDX, xdev_space)
    LOAD_OR_RETURN(xrGetXDevPropertiesMNDX, xdev_space)
    LOAD_OR_RETURN(xrDestroyXDevListMNDX, xdev_space)
    LOAD_OR_RETURN(xrCreateXDevSpaceMNDX, xdev_space)
    return XR_SUCCESS;
}

bool init_xdev_space_t(struct base_extension_t** out_base) {
    *out_base = malloc(sizeof(struct xdev_space_t));

    (*out_base)->ext_name_string = XR_MNDX_XDEV_SPACE_EXTENSION_NAME;
    (*out_base)->init_fp         = init_xdev_space_fp;

    ((struct xdev_space_t*) *out_base)->xdev_space_list    = NULL;
    ((struct xdev_space_t*) *out_base)->last_generation_id = 0;
    ((struct xdev_space_t*) *out_base)->system_supported   = false;

    return true;
}

// Convenience function
struct base_extension_t* get_ext(struct ApplicationState* app, char* ext_name_string) {
    for (uint32_t i = 0; i < 4; i++) {
        // even using the EXTENSION_NAME defines doesn't guarantee same string address
        if (app->oxr.ext[i]->ext_name_string == ext_name_string ||
            strcmp(app->oxr.ext[i]->ext_name_string, ext_name_string) == 0) {
            return app->oxr.ext[i];
        }
    }
    return NULL;
}

bool check_extension_support(struct base_extension_t* e, XrExtensionProperties* extension_props, uint32_t ext_count) {
    for (uint32_t i = 0; i < ext_count; i++) {
        if (strcmp(e->ext_name_string, extension_props[i].extensionName) == 0) {
            e->supported = true;
            e->version   = extension_props[i].extensionVersion;
            return true;
        }
    }
    return false;
}

bool alloc_extensions(struct ApplicationState* app) {
    for (uint32_t i = 0; i < 4; i++) {
        if (!ext_init_funcs[i](&app->oxr.ext[i])) {
            return false;
        }
    }
    return true;
}

XrResult check_extensions(struct ApplicationState* app) {
    XrResult result;

    uint32_t ext_count = 0;
    result             = xrEnumerateInstanceExtensionProperties(NULL, 0, &ext_count, NULL);

    if (!xr_check(NULL, result, "Failed to enumerate number of extension properties"))
        return result;

    XrExtensionProperties* ext_props = malloc(sizeof(XrExtensionProperties) * ext_count);
    for (uint32_t i = 0; i < ext_count; i++) {
        // we usually have to fill in the type (for validation) and set
        // next to NULL (or a pointer to an extension specific struct)
        ext_props[i].type = XR_TYPE_EXTENSION_PROPERTIES;
        ext_props[i].next = NULL;
    }

    result = xrEnumerateInstanceExtensionProperties(NULL, ext_count, &ext_count, ext_props);
    if (!xr_check(NULL, result, "Failed to enumerate extension properties")) {
        free(ext_props);
        return result;
    }

    printf("Runtime supports %d extensions\n", ext_count);
    for (uint32_t i = 0; i < ext_count; i++) {
        printf("\t%s v%d\n", ext_props[i].extensionName, ext_props[i].extensionVersion);
    }

    for (uint32_t i = 0; i < 4; i++) {
        app->oxr.ext[i]->supported = check_extension_support(app->oxr.ext[i], ext_props, ext_count);

        if (app->oxr.ext[i]->init_fp == init_opengl_fp && !app->oxr.ext[i]->supported) {
            printf("%s is required\n", app->oxr.ext[i]->ext_name_string);
            free(ext_props);
            return XR_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    free(ext_props);
    return XR_SUCCESS;
}

XrResult init_extensions(struct ApplicationState* app) {
    XrResult   result;
    XrInstance instance = app->oxr.instance;

    for (uint32_t i = 0; i < 4; i++) {
        if (app->oxr.ext[i]->supported) {
            printf("Loading function pointers for extension %s\n", app->oxr.ext[i]->ext_name_string);
            if (app->oxr.ext[i]->init_fp != NULL) { // some extensions need no init
                result = app->oxr.ext[i]->init_fp(instance, app->oxr.ext[i]);

                if (!xr_check(instance, result, "Failed to load function pointers for ext %s\n",
                              app->oxr.ext[i]->ext_name_string)) {
                    return result;
                }
            }
        } else {
            printf("Not loading function pointers for unsupported extension %s\n", app->oxr.ext[i]->ext_name_string);
        }
    }
    return XR_SUCCESS;
}

bool create_hand_trackers(XrInstance instance, XrSession session, struct hand_tracking_t* hand_tracking) {
    XrResult result;

    result =
        xrGetInstanceProcAddr(instance, "xrLocateHandJointsEXT", (PFN_xrVoidFunction*) &hand_tracking->xrLocateHandJointsEXT);

    if (XR_FAILED(result))
        return false;
    XrHandEXT hands[HAND_COUNT] = {[HAND_LEFT_INDEX] = XR_HAND_LEFT_EXT, [HAND_RIGHT_INDEX] = XR_HAND_RIGHT_EXT};

    for (int i = 0; i < HAND_COUNT; i++) {
        XrHandTrackerCreateInfoEXT hand_tracker_create_info = {.type         = XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT,
                                                               .next         = NULL,
                                                               .hand         = hands[i],
                                                               .handJointSet = XR_HAND_JOINT_SET_DEFAULT_EXT};
        result = hand_tracking->xrCreateHandTrackerEXT(session, &hand_tracker_create_info, &hand_tracking->trackers[i]);
        if (!xr_check(instance, result, "Failed to create hand tracker %d", i)) {
            return false;
        }

        hand_tracking->joint_locations[i] = (XrHandJointLocationsEXT) {
            .type           = XR_TYPE_HAND_JOINT_LOCATIONS_EXT,
            .jointCount     = XR_HAND_JOINT_COUNT_EXT,
            .jointLocations = hand_tracking->joints[i],
        };

        printf("Created hand tracker %d\n", i);
    }
    return true;
}

bool get_hand_tracking(XrInstance instance, XrSpace space, XrTime time, bool query_joint_velocities,
                       struct hand_tracking_t* hand_tracking, int hand) {
    if (query_joint_velocities) {
        hand_tracking->joint_velocities[hand].type            = XR_TYPE_HAND_JOINT_VELOCITIES_EXT;
        hand_tracking->joint_velocities[hand].next            = NULL;
        hand_tracking->joint_velocities[hand].jointCount      = XR_HAND_JOINT_COUNT_EXT;
        hand_tracking->joint_velocities[hand].jointVelocities = hand_tracking->joint_velocities_arr[hand];
        hand_tracking->joint_locations[hand].next             = &hand_tracking->joint_velocities[hand];
    } else {
        hand_tracking->joint_locations[hand].next = NULL;
    }

    XrHandJointsLocateInfoEXT locateInfo = {
        .type = XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT, .next = NULL, .baseSpace = space, .time = time};

    XrResult result;
    result =
        hand_tracking->xrLocateHandJointsEXT(hand_tracking->trackers[hand], &locateInfo, &hand_tracking->joint_locations[hand]);
    if (!xr_check(instance, result, "failed to locate hand joints!"))
        return false;

    return true;
}
