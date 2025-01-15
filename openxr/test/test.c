// Copyright 2019-2021, Collabora, Ltd.
// SPDX-License-Identifier: BSL-1.0
/*!
 * @file
 * @brief OpenXR playground, exercising many areas of the OpenXR API.
 * Advanced version of the openxr-simple-example
 * @author Christoph Haag <christoph.haag@collabora.com>
 */


#include "gl.h"
#include "struct.h"
#include "func.h"

#include <unistd.h>
#include <SDL2/SDL_events.h>

#include "external/openxr_headers/openxr_platform.h"

extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
// we need an identity pose for creating spaces without offsets
static XrPosef identity_pose = {.orientation = {.x = 0.f, .y = 0.f, .z = 0.f, .w = 1.f},
        .position = {.x = 0, .y = 0, .z = 0}};

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    struct ApplicationState* app = malloc(sizeof(struct ApplicationState));
    *app = (struct ApplicationState){
            .oxr = {.form_factor = XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY,
                    .view_type = XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO,
                    .play_space_type = XR_REFERENCE_SPACE_TYPE_STAGE,

                    .instance = XR_NULL_HANDLE,
                    .session = XR_NULL_HANDLE,
                    .system_id = XR_NULL_SYSTEM_ID,
                    .state = XR_SESSION_STATE_UNKNOWN,
                    .play_space = XR_NULL_HANDLE,

                    .view_count = 0,
                    .viewconfig_views = NULL,
                    .projection_views = NULL,
                    .views = NULL},
            .quad_layer = {.pixel_width = 320, .pixel_height = 240},
            .gl_renderer =
                    {
                            .near_z = 0.01f,
                            .far_z = 100.0f,
                    },

    };

    // The runtime interacts with the OpenGL images (textures) via a Swapchain.
    XrGraphicsBindingOpenGLXlibKHR graphics_binding_gl = {0};

    XrResult result = XR_SUCCESS;

    if (!alloc_extensions(app)) {
        printf("allocating ext structs failed");
        return 1;
    }

    result = check_extensions(app);
    if (!xr_check(app->oxr.instance, result, "Extensions check failed!")) {
        return 1;
    }

    // --- Create XrInstance
    int enabled_ext_count = 0;
    const char* enabled_exts[4] = {0};

    for (uint32_t i = 0; i < 4; i++) {
        if (app->oxr.ext[i]->supported) {
            enabled_exts[enabled_ext_count++] = app->oxr.ext[i]->ext_name_string;
            printf("enabling extension %s\n", app->oxr.ext[i]->ext_name_string);
        }
    }

    // same can be done for API layers, but API layers can also be enabled by env var

    XrInstanceCreateInfo instance_create_info = {
            .type = XR_TYPE_INSTANCE_CREATE_INFO,
            .next = NULL,
            .createFlags = 0,
            .enabledExtensionCount = enabled_ext_count,
            .enabledExtensionNames = enabled_exts,
            .enabledApiLayerCount = 0,
            .enabledApiLayerNames = NULL,
            .applicationInfo =
                    {
                            // some compilers have trouble with char* initialization
                            .applicationName = "",
                            .engineName = "",
                            .applicationVersion = 1,
                            .engineVersion = 0,
                            .apiVersion = XR_MAKE_VERSION(1, 0, XR_VERSION_PATCH(XR_CURRENT_API_VERSION)),
                    },
    };
    strncpy(instance_create_info.applicationInfo.applicationName, "OpenXR OpenGL Example",
            XR_MAX_APPLICATION_NAME_SIZE);
    strncpy(instance_create_info.applicationInfo.engineName, "Custom", XR_MAX_ENGINE_NAME_SIZE);

    result = xrCreateInstance(&instance_create_info, &app->oxr.instance);
    if (!xr_check(NULL, result, "Failed to create XR instance."))
        return 1;

    result = init_extensions(app);
    if (!xr_check(app->oxr.instance, result, "Failed to init extensions!")) {
        return 1;
    }


    // Optionally get runtime name and version
    XrInstanceProperties instance_props = {
            .type = XR_TYPE_INSTANCE_PROPERTIES,
            .next = NULL,
    };

    result = xrGetInstanceProperties(app->oxr.instance, &instance_props);
    if (!xr_check(NULL, result, "Failed to get instance info"))
        return 1;

    printf("Runtime Name: %s\n", instance_props.runtimeName);
    printf("Runtime Version: %d.%d.%d\n", XR_VERSION_MAJOR(instance_props.runtimeVersion),
           XR_VERSION_MINOR(instance_props.runtimeVersion),
           XR_VERSION_PATCH(instance_props.runtimeVersion));

    // --- Create XrSystem
    XrSystemGetInfo system_get_info = {
            .type = XR_TYPE_SYSTEM_GET_INFO, .formFactor = app->oxr.form_factor, .next = NULL};

    result = xrGetSystem(app->oxr.instance, &system_get_info, &app->oxr.system_id);
    if (!xr_check(app->oxr.instance, result, "Failed to get system for HMD form factor."))
        return 1;

    printf("Successfully got XrSystem with id %lu for HMD form factor\n", app->oxr.system_id);


    // checking system properties is generally  optional, but we are interested in hand tracking
    // support
    {
        XrSystemProperties system_props = {
                .type = XR_TYPE_SYSTEM_PROPERTIES,
                .next = NULL,
                .graphicsProperties = {0},
                .trackingProperties = {0},
        };
        struct hand_tracking_t* ht_ext =
                (struct hand_tracking_t*)get_ext(app, XR_EXT_HAND_TRACKING_EXTENSION_NAME);

        XrSystemHandTrackingPropertiesEXT ht = {
                .type = XR_TYPE_SYSTEM_HAND_TRACKING_PROPERTIES_EXT,
                .next = system_props.next,
                .supportsHandTracking = 1
        };
        //if (ht_ext->base.supported) {
        system_props.next = &ht;
        //}



        result = xrGetSystemProperties(app->oxr.instance, app->oxr.system_id, &system_props);
        ht.supportsHandTracking = 1;
        if (!xr_check(app->oxr.instance, result, "Failed to get System properties"))
            return 1;

        //if (ht_ext->base.supported) {
        ht_ext->system_supported = ht.supportsHandTracking;
        //}


        print_system_properties(&system_props);
    }

    print_supported_view_configs(app->oxr.instance, app->oxr.system_id);

    // view_count usually depends on the form_factor / view_type.
    // dynamically allocating all view related structs hopefully allows this app to scale easily to
    // different view_counts.

    result = xrEnumerateViewConfigurationViews(app->oxr.instance, app->oxr.system_id,
                                               app->oxr.view_type, 0, &app->oxr.view_count, NULL);
    if (!xr_check(app->oxr.instance, result, "Failed to get view configuration view count!"))
        return 1;

    app->oxr.viewconfig_views = malloc(sizeof(XrViewConfigurationView) * app->oxr.view_count);
    for (uint32_t i = 0; i < app->oxr.view_count; i++) {
        app->oxr.viewconfig_views[i].type = XR_TYPE_VIEW_CONFIGURATION_VIEW;
        app->oxr.viewconfig_views[i].next = NULL;
    }

    result = xrEnumerateViewConfigurationViews(app->oxr.instance, app->oxr.system_id,
                                               app->oxr.view_type, app->oxr.view_count,
                                               &app->oxr.view_count, app->oxr.viewconfig_views);
    if (!xr_check(app->oxr.instance, result, "Failed to enumerate view configuration views!"))
        return 1;
    print_viewconfig_view_info(app->oxr.view_count, app->oxr.viewconfig_views);


    // OpenXR requires checking graphics requirements before creating a session.
    XrGraphicsRequirementsOpenGLKHR opengl_reqs = {.type = XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR,
            .next = NULL};

    // this function pointer was loaded with xrGetInstanceProcAddr
    struct opengl_t* opengl_ext = (struct opengl_t*)get_ext(app, XR_KHR_OPENGL_ENABLE_EXTENSION_NAME);
    result = opengl_ext->xrGetOpenGLGraphicsRequirementsKHR(app->oxr.instance, app->oxr.system_id,
                                                            &opengl_reqs);
    if (!xr_check(app->oxr.instance, result, "Failed to get OpenGL graphics requirements!"))
        return 1;

    // On OpenGL we never fail this check because the version requirement is not useful.
    // Other APIs may have more useful requirements.
    check_opengl_version(&opengl_reqs);


    uint32_t blend_mode_count = 0;
    result = xrEnumerateEnvironmentBlendModes(app->oxr.instance, app->oxr.system_id,
                                              app->oxr.view_type, 0, &blend_mode_count, NULL);
    if (!xr_check(app->oxr.instance, result, "failed to enumerate blend mode count!"))
        return 1;

    XrEnvironmentBlendMode* blend_modes = malloc(sizeof(XrEnvironmentBlendMode) * blend_mode_count);
    result =
            xrEnumerateEnvironmentBlendModes(app->oxr.instance, app->oxr.system_id, app->oxr.view_type,
                                             blend_mode_count, &blend_mode_count, blend_modes);
    if (!xr_check(app->oxr.instance, result, "failed to enumerate blend modes!"))
        return 1;

    // the environment blend modes our application can deal with
    XrEnvironmentBlendMode supported_blend_modes[] = {
            XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND,
            XR_ENVIRONMENT_BLEND_MODE_ADDITIVE,
            XR_ENVIRONMENT_BLEND_MODE_OPAQUE,
    };
    uint32_t supported_blend_mode_count = 3;

    printf("Runtime supported blend modes:\n");
    for (uint32_t i = 0; i < blend_mode_count; i++) {
        printf("\t%s\n", XrStr_XrEnvironmentBlendMode(blend_modes[i]));
    }

    // use the most preferred blend mode of the runtime that this app supports too
    if (!app->oxr.blend_mode_explicitly_set) {
        bool matched = false;
        for (uint32_t i = 0; i < blend_mode_count; i++) {
            for (uint32_t supported_i = 0; supported_i < supported_blend_mode_count; supported_i++) {
                if (blend_modes[i] == supported_blend_modes[supported_i]) {
                    app->oxr.blend_mode = blend_modes[i];
                    matched = true;
                    break;
                }
            }
            if (matched) {
                break;
            }
        }
    }

    printf("Using blend mode: %s\n", XrStr_XrEnvironmentBlendMode(app->oxr.blend_mode));
    free(blend_modes);


    // --- Create session
    graphics_binding_gl = (XrGraphicsBindingOpenGLXlibKHR){
            .type = XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR,
    };

    // create SDL window the size of the left eye & fill GL graphics binding info
    if (!init_sdl_window(&graphics_binding_gl.xDisplay, &graphics_binding_gl.glxDrawable,
                         &graphics_binding_gl.glxContext,
                         (int32_t)app->oxr.viewconfig_views[0].recommendedImageRectWidth,
                         (int32_t)app->oxr.viewconfig_views[0].recommendedImageRectHeight)) {
        printf("GLX init failed!\n");
        return 1;
    }

    printf("Using OpenGL version: %s\n", glGetString(GL_VERSION));
    printf("Using OpenGL Renderer: %s\n", glGetString(GL_RENDERER));

    app->oxr.state = XR_SESSION_STATE_UNKNOWN;

    XrSessionCreateInfo session_create_info = {.type = XR_TYPE_SESSION_CREATE_INFO,
            .next = &graphics_binding_gl,
            .systemId = app->oxr.system_id};

    result = xrCreateSession(app->oxr.instance, &session_create_info, &app->oxr.session);
    if (!xr_check(app->oxr.instance, result, "Failed to create session"))
        return 1;

    printf("Successfully created a session with OpenGL!\n");

    // Many runtimes support at least STAGE and LOCAL but not all do.
    // Sophisticated apps might check if the chosen one is supported and try another one if not.
    // Here we will get an error from xrCreateReferenceSpace() and exit.
    print_reference_spaces(app->oxr.instance, app->oxr.session);
    XrReferenceSpaceCreateInfo play_space_create_info = {.type = XR_TYPE_REFERENCE_SPACE_CREATE_INFO,
            .next = NULL,
            .referenceSpaceType =
            app->oxr.play_space_type,
            .poseInReferenceSpace = identity_pose};

    result = xrCreateReferenceSpace(app->oxr.session, &play_space_create_info, &app->oxr.play_space);
    if (!xr_check(app->oxr.instance, result, "Failed to create play space!"))
        return 1;


    XrPosef y1 = {.position = {0, 1, 0}, .orientation = {0, 0, 0, 1}};

    XrPosef z1 = {.position = {0, 0, -1}, .orientation = {0, 0, 0, 1}};

    {
        XrReferenceSpaceCreateInfo space_create_info = {.type = XR_TYPE_REFERENCE_SPACE_CREATE_INFO,
                .next = NULL,
                .referenceSpaceType =
                XR_REFERENCE_SPACE_TYPE_LOCAL,
                .poseInReferenceSpace = identity_pose};

        result = xrCreateReferenceSpace(app->oxr.session, &space_create_info, &app->ref_local_space);
        if (!xr_check(app->oxr.instance, result, "Failed to create play space!"))
            return 1;
    }
    {
        XrReferenceSpaceCreateInfo space_create_info = {.type = XR_TYPE_REFERENCE_SPACE_CREATE_INFO,
                .next = NULL,
                .referenceSpaceType =
                XR_REFERENCE_SPACE_TYPE_VIEW,
                .poseInReferenceSpace = identity_pose};

        result = xrCreateReferenceSpace(app->oxr.session, &space_create_info, &app->ref_view_space);
        if (!xr_check(app->oxr.instance, result, "Failed to create play space!"))
            return 1;
    }

    // --- Create Swapchains
    uint32_t swapchain_format_count;
    result = xrEnumerateSwapchainFormats(app->oxr.session, 0, &swapchain_format_count, NULL);
    if (!xr_check(app->oxr.instance, result, "Failed to get number of supported swapchain formats"))
        return 1;

    printf("Runtime supports %d swapchain formats\n", swapchain_format_count);
    int64_t* swapchain_formats = malloc(sizeof(int64_t) * swapchain_format_count);

    result = xrEnumerateSwapchainFormats(app->oxr.session, swapchain_format_count,
                                         &swapchain_format_count, swapchain_formats);

    free(swapchain_formats);
    if (!xr_check(app->oxr.instance, result, "Failed to enumerate swapchain formats"))
        return 1;

    // SRGB is usually a better choice than linear
    // a more sophisticated approach would iterate supported swapchain formats and choose from them
    int64_t color_format =
            get_swapchain_format(app->oxr.instance, app->oxr.session, GL_SRGB8_ALPHA8_EXT, true);

    int64_t quad_format =
            get_swapchain_format(app->oxr.instance, app->oxr.session, GL_RGBA8_EXT, true);

    XrSwapchainUsageFlags color_flags =
            XR_SWAPCHAIN_USAGE_SAMPLED_BIT | XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;
    if (!create_swapchain_from_views(app->oxr.instance, app->oxr.session,
                                     &app->vr_swapchains[SWAPCHAIN_PROJECTION], app->oxr.view_count,
                                     color_format, app->oxr.viewconfig_views, color_flags))
        return 1;


    if (!create_one_swapchain(app->oxr.instance, app->oxr.session, &app->quad_layer.swapchain,
                              quad_format, 1, app->quad_layer.pixel_width,
                              app->quad_layer.pixel_height, color_flags))
        return 1;

    // Do not allocate these every frame to save some resources
    app->oxr.views = (XrView*)malloc(sizeof(XrView) * app->oxr.view_count);
    app->oxr.projection_views = (XrCompositionLayerProjectionView*)malloc(
            sizeof(XrCompositionLayerProjectionView) * app->oxr.view_count);
    for (uint32_t i = 0; i < app->oxr.view_count; i++) {
        app->oxr.views[i].type = XR_TYPE_VIEW;
        app->oxr.views[i].next = NULL;

        app->oxr.projection_views[i].type = XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW;
        app->oxr.projection_views[i].next = NULL;

        app->oxr.projection_views[i].subImage.swapchain =
                app->vr_swapchains[SWAPCHAIN_PROJECTION].swapchains[i];
        app->oxr.projection_views[i].subImage.imageArrayIndex = 0;
        app->oxr.projection_views[i].subImage.imageRect.offset.x = 0;
        app->oxr.projection_views[i].subImage.imageRect.offset.y = 0;
        app->oxr.projection_views[i].subImage.imageRect.extent.width =
                (int32_t)app->oxr.viewconfig_views[i].recommendedImageRectWidth;
        app->oxr.projection_views[i].subImage.imageRect.extent.height =
                (int32_t)app->oxr.viewconfig_views[i].recommendedImageRectHeight;

        // projection_views[i].{pose, fov} have to be filled every frame in frame loop
    }

    struct refresh_rate_t* refresh_rate_ext =
            (struct refresh_rate_t*)get_ext(app, XR_FB_DISPLAY_REFRESH_RATE_EXTENSION_NAME);
    // get info from fb_refresh_rate
    if (refresh_rate_ext->base.supported) {
        uint32_t refresh_rate_count;
        result = refresh_rate_ext->xrEnumerateDisplayRefreshRatesFB(app->oxr.session, 0,
                                                                    &refresh_rate_count, NULL);
        if (!xr_check(app->oxr.instance, result, "failed to enumerate refresh rate count"))
            return 1;

        if (refresh_rate_count > 0) {
            float* refresh_rates = malloc(sizeof(float) * refresh_rate_count);
            result = refresh_rate_ext->xrEnumerateDisplayRefreshRatesFB(
                    app->oxr.session, refresh_rate_count, &refresh_rate_count, refresh_rates);
            if (!xr_check(app->oxr.instance, result, "failed to enumerate refresh rates")) {
                free(refresh_rates);
                return 1;
            }

            printf("Supported refresh rates:\n");
            for (uint32_t i = 0; i < refresh_rate_count; i++) {
                printf("\t%f Hz\n", refresh_rates[i]);
            }

            // refresh rates are ordered lowest to highest
            printf("Requesting refresh rate %f\n", refresh_rates[refresh_rate_count - 1]);
            result = refresh_rate_ext->xrRequestDisplayRefreshRateFB(
                    app->oxr.session, refresh_rates[refresh_rate_count - 1]);
            if (!xr_check(app->oxr.instance, result, "failed to request refresh rate %f",
                          refresh_rates[refresh_rate_count - 1]))
                return 1;

            free(refresh_rates);
        }

        float refresh_rate = 0;
        result = refresh_rate_ext->xrGetDisplayRefreshRateFB(app->oxr.session, &refresh_rate);
        if (!xr_check(app->oxr.instance, result, "failed to get refresh rate"))
            return 1;

        printf("Current refresh rate: %f Hz\n", refresh_rate);
    }

    struct hand_tracking_t* hand_tracking_ext =
            (struct hand_tracking_t*)get_ext(app, XR_EXT_HAND_TRACKING_EXTENSION_NAME);
    if (hand_tracking_ext->system_supported) {
        if (!create_hand_trackers(app->oxr.instance, app->oxr.session, hand_tracking_ext))
            return 1;
    }

    // Set up rendering (compile shaders, ...) before starting the app->oxr.session
    if (init_gl(app->oxr.view_count, app->vr_swapchains[SWAPCHAIN_PROJECTION].swapchain_lengths,
                &app->gl_renderer) != 0) {
        printf("OpenGl setup failed!\n");
        return 1;
    }

    XrEventDataBuffer* runtime_event = NULL;

    bool quit_renderloop = false;
    bool session_running = false; // to avoid beginning an already running app->oxr.session
    bool skip_polling = false;

    int frame_count = 0;
    while (!quit_renderloop && frame_count < 300) {

        // --- Poll SDL for events so we can exit with esc
        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_QUIT ||
                (sdl_event.type == SDL_KEYDOWN && sdl_event.key.keysym.sym == SDLK_ESCAPE)) {
                printf("Requesting exit...\n");
                xrRequestExitSession(app->oxr.session);
            }
        }

        // for several app->oxr.session app->oxr.states we want to skip the render loop
        bool skip_renderloop = false;

        // --- Handle runtime Events
        // we do this before xrWaitFrame() so we can go idle or
        // break out of the main render loop as early as possible and don't have to
        // uselessly render or submit one. Calling xrWaitFrame commits you to
        // calling xrBeginFrame eventually.
        if (!runtime_event)
            runtime_event = (XrEventDataBuffer*)malloc(sizeof(XrEventDataBuffer));
        runtime_event->type = XR_TYPE_EVENT_DATA_BUFFER;
        runtime_event->next = NULL;
        XrResult poll_result = xrPollEvent(app->oxr.instance, runtime_event);
        while (poll_result == XR_SUCCESS  && !skip_polling) {
            switch (runtime_event->type) {
                case XR_TYPE_EVENT_DATA_EVENTS_LOST: {
                    XrEventDataEventsLost* event = (XrEventDataEventsLost*)runtime_event;
                    printf("EVENT: %d events data lost!\n", event->lostEventCount);
                    // do we care if the runtime loses events?
                    break;
                }
                case XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING: {
                    XrEventDataInstanceLossPending* event = (XrEventDataInstanceLossPending*)runtime_event;
                    printf("EVENT: app->oxr.instance loss pending at %lu! Destroying app->oxr.instance.\n",
                           event->lossTime);
                    quit_renderloop = true;
                    continue;
                }
                case XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED: {
                    XrEventDataSessionStateChanged* event = (XrEventDataSessionStateChanged*)runtime_event;
                    printf("EVENT: app->oxr.session app->oxr.state changed from %d to %d\n", app->oxr.state,
                           event->state);
                    app->oxr.state = event->state;

                    // react to app->oxr.session app->oxr.state changes, see OpenXR spec 9.3 diagram
                    switch (app->oxr.state) {

                        // just keep polling, skip render loop
                        case XR_SESSION_STATE_MAX_ENUM:
                            // must be a bug, just keep polling
                        case XR_SESSION_STATE_IDLE:
                        case XR_SESSION_STATE_UNKNOWN: {
                            skip_renderloop = true;
                            break; // app->oxr.state handling switch
                        }

                            // do nothing, run render loop normally
                        case XR_SESSION_STATE_FOCUSED:
                        case XR_SESSION_STATE_SYNCHRONIZED:
                        case XR_SESSION_STATE_VISIBLE: {
                            skip_renderloop = false;
                            break; // app->oxr.state handling switch
                        }

                            // begin app->oxr.session and then run render loop
                        case XR_SESSION_STATE_READY: {
                            // start app->oxr.session only if it is not running, i.e. not when we already called
                            // xrBeginSession but the runtime did not switch to the next app->oxr.state yet
                            if (!session_running) {
                                XrSessionBeginInfo session_begin_info = {.type = XR_TYPE_SESSION_BEGIN_INFO,
                                        .next = NULL,
                                        .primaryViewConfigurationType =
                                        app->oxr.view_type};
                                result = xrBeginSession(app->oxr.session, &session_begin_info);
                                if (!xr_check(app->oxr.instance, result, "Failed to begin session!"))
                                    return 1;
                                printf("Session started!\n");
                                session_running = true;
                            }
                            skip_renderloop = false;
                            break; // app->oxr.state handling switch
                        }

                            // end app->oxr.session, skip render loop, keep polling for next app->oxr.state change
                        case XR_SESSION_STATE_STOPPING: {
                            // end app->oxr.session only if it is running, i.e. not when we already called
                            // xrEndSession but the runtime did not switch to the next app->oxr.state yet
                            if (session_running) {
                                result = xrEndSession(app->oxr.session);
                                if (!xr_check(app->oxr.instance, result, "Failed to end app->oxr.session!"))
                                    return 1;
                                session_running = false;
                            }
                            skip_renderloop = true;
                            break; // app->oxr.state handling switch
                        }

                            // destroy app->oxr.session, skip render loop, exit render loop and quit
                        case XR_SESSION_STATE_LOSS_PENDING:
                        case XR_SESSION_STATE_EXITING:
                            result = xrDestroySession(app->oxr.session);
                            if (!xr_check(app->oxr.instance, result, "Failed to destroy app->oxr.session!"))
                                return 1;
                            quit_renderloop = true;
                            skip_renderloop = true;
                            break; // app->oxr.state handling switch
                    }
                    break;
                }
                case XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING: {
                    printf("EVENT: reference space change pending!\n");
                    XrEventDataReferenceSpaceChangePending* event =
                            (XrEventDataReferenceSpaceChangePending*)runtime_event;
                    (void)event;
                    // TODO: do something
                    break;
                }
                case XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED: {
                    break;
                }

                case XR_TYPE_EVENT_DATA_VISIBILITY_MASK_CHANGED_KHR: {
                    printf("EVENT: visibility mask changed!!\n");
                    XrEventDataVisibilityMaskChangedKHR* event =
                            (XrEventDataVisibilityMaskChangedKHR*)runtime_event;
                    (void)event;
                    // this event is from an extension
                    break;
                }
                case XR_TYPE_EVENT_DATA_PERF_SETTINGS_EXT: {
                    printf("EVENT: perf settings!\n");
                    XrEventDataPerfSettingsEXT* event = (XrEventDataPerfSettingsEXT*)runtime_event;
                    (void)event;
                    // this event is from an extension
                    break;
                }
                default: printf("Unhandled event type %d\n", runtime_event->type);
            }

            runtime_event->type = XR_TYPE_EVENT_DATA_BUFFER;
            poll_result = xrPollEvent(app->oxr.instance, runtime_event);
        }
        if (poll_result == XR_EVENT_UNAVAILABLE) {
            // processed all events in the queue
        } else {
            printf("Failed to poll events!\n");
            break;
        }

        if (skip_renderloop) {
            continue;
        }

        skip_polling = true;
        for (int i = 0; i < HAND_COUNT; i++) {
            if (hand_tracking_ext->system_supported) {
                get_hand_tracking(app->oxr.instance, app->oxr.play_space,
                                  app->oxr.frameState.predictedDisplayTime,
                                  false, hand_tracking_ext, i);
            }
        }
        frame_count++;
        usleep(35 * 1000); // sleep for 35 ms
    }



    // --- Clean up after render loop quits
    if (runtime_event)
        free(runtime_event);

    for (uint32_t i = 0; i < app->oxr.view_count; i++) {
        free(app->vr_swapchains[SWAPCHAIN_PROJECTION].images[i]);

        glDeleteFramebuffers((GLsizei)app->vr_swapchains[SWAPCHAIN_PROJECTION].swapchain_lengths[i],
                             app->gl_renderer.framebuffers[i]);
        free(app->gl_renderer.framebuffers[i]);
    }
    xrDestroyInstance(app->oxr.instance);

    free(app->oxr.viewconfig_views);
    free(app->oxr.projection_views);
    free(app->oxr.views);

    destroy_swapchain(&app->vr_swapchains[SWAPCHAIN_PROJECTION]);
    destroy_swapchain(&app->vr_swapchains[SWAPCHAIN_DEPTH]);
    free(app->gl_renderer.framebuffers);



    free(app);

    printf("Cleaned up!\n");
    return 0;
}
