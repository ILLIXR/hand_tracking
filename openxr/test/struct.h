#pragma once
// Required headers for OpenGL rendering, as well as for including openxr_platform
#include "external/openxr_headers/openxr.h"
#include "external/openxr_headers/openxr_platform.h"
#include "external/openxr_headers/XR_MNDX_xdev_space.h"
#include "macro.h"

#include <GL/glcorearb.h>
#include <GL/glext.h>
#include <GL/glx.h>
#include <stdbool.h>
#include <X11/Xlib.h>

enum Swapchain { SWAPCHAIN_PROJECTION = 0, SWAPCHAIN_DEPTH, SWAPCHAIN_LAST };

// =============================================================================
// OpenGL rendering code at the end of the file
// =============================================================================
struct gl_renderer_t {
    // To render into a texture we need a framebuffer (one per texture to make it easy)
    GLuint** framebuffers;

    float near_z;
    float far_z;

    GLuint shader_program_id;
    GLuint VAO;
};

struct base_extension_t;

// function that gets the function pointers for an extension struct
typedef XrResult (*init_ext_fp)(XrInstance instance, struct base_extension_t* base);

struct base_extension_t {
    bool     supported;
    uint32_t version;

    char* ext_name_string;

    init_ext_fp init_fp;
};

struct opengl_t {
    struct base_extension_t base;

    // functions belonging to extensions must be loaded with xrGetInstanceProcAddr before use
    PFN_xrGetOpenGLGraphicsRequirementsKHR xrGetOpenGLGraphicsRequirementsKHR;
};

struct hand_tracking_t {
    struct base_extension_t base;

    // whether the current VR system in use has hand tracking
    bool             system_supported;
    XrHandTrackerEXT trackers[HAND_COUNT];

    // out data
    XrHandJointLocationEXT  joints[HAND_COUNT][XR_HAND_JOINT_COUNT_EXT];
    XrHandJointLocationsEXT joint_locations[HAND_COUNT];

    // optional
    XrHandJointVelocitiesEXT joint_velocities[HAND_COUNT];
    XrHandJointVelocityEXT   joint_velocities_arr[HAND_COUNT][XR_HAND_JOINT_COUNT_EXT];

    PFN_xrLocateHandJointsEXT  xrLocateHandJointsEXT;
    PFN_xrCreateHandTrackerEXT xrCreateHandTrackerEXT;
};

struct refresh_rate_t {
    struct base_extension_t              base;
    PFN_xrEnumerateDisplayRefreshRatesFB xrEnumerateDisplayRefreshRatesFB;
    PFN_xrGetDisplayRefreshRateFB        xrGetDisplayRefreshRateFB;
    PFN_xrRequestDisplayRefreshRateFB    xrRequestDisplayRefreshRateFB;
};

struct xdev_space_element {
    XrSpace                    space;
    struct xdev_space_element* next;
};

struct xdev_space_t {
    struct base_extension_t base;

    PFN_xrCreateXDevListMNDX              xrCreateXDevListMNDX;
    PFN_xrGetXDevListGenerationNumberMNDX xrGetXDevListGenerationNumberMNDX;
    PFN_xrEnumerateXDevsMNDX              xrEnumerateXDevsMNDX;
    PFN_xrGetXDevPropertiesMNDX           xrGetXDevPropertiesMNDX;
    PFN_xrDestroyXDevListMNDX             xrDestroyXDevListMNDX;
    PFN_xrCreateXDevSpaceMNDX             xrCreateXDevSpaceMNDX;

    struct xdev_space_element* xdev_space_list;

    // only need to check for new/disappeared xdevs when the generation id changes
    uint64_t last_generation_id;

    // true if both the runtime supports the extension and the current system (hardware) in use
    // supports it too.
    bool system_supported;
};

struct OpenXRState {
    struct base_extension_t* ext[4];

    XrFormFactor            form_factor;
    XrViewConfigurationType view_type;
    XrReferenceSpaceType    play_space_type;

    XrInstance     instance;
    XrSession      session;
    XrSystemId     system_id;
    XrSessionState state;

    XrEnvironmentBlendMode blend_mode;
    bool                   blend_mode_explicitly_set;

    XrSpace play_space;

    // Each physical Display/Eye is described by a view
    uint32_t                          view_count;
    XrViewConfigurationView*          viewconfig_views;
    XrCompositionLayerProjectionView* projection_views;
    XrView*                           views;

    XrFrameState frameState;
};

struct swapchain_t {
    uint32_t*                   swapchain_lengths;
    XrSwapchainImageOpenGLKHR** images;
    XrSwapchain*                swapchains;
    uint32_t                    swapchain_count;
};

struct quad_layer_t {
    // quad layers are placed into world space, no need to render them per eye
    struct swapchain_t swapchain;
    uint32_t           pixel_width, pixel_height;
};

struct ApplicationState {
    struct OpenXRState oxr;

    struct swapchain_t vr_swapchains[SWAPCHAIN_LAST];

    struct quad_layer_t quad_layer;

    XrSpace ref_local_space;

    XrSpace ref_view_space;

    struct gl_renderer_t gl_renderer;
};
