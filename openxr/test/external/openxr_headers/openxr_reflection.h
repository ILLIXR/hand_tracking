#ifndef OPENXR_REFLECTION_H_
#define OPENXR_REFLECTION_H_ 1

/*
** Copyright (c) 2017-2024, The Khronos Group Inc.
**
** SPDX-License-Identifier: Apache-2.0 OR MIT
*/

/*
** This header is generated from the Khronos OpenXR XML API Registry.
**
*/

#include "openxr.h"

/*
This file contains expansion macros (X Macros) for OpenXR enumerations and structures.
Example of how to use expansion macros to make an enum-to-string function:

#define XR_ENUM_CASE_STR(name, val) case name: return #name;
#define XR_ENUM_STR(enumType)                         \
    constexpr const char* XrEnumStr(enumType e) {     \
        switch (e) {                                  \
            XR_LIST_ENUM_##enumType(XR_ENUM_CASE_STR) \
            default: return "Unknown";                \
        }                                             \
    }                                                 \

XR_ENUM_STR(XrResult);
*/

#define XR_LIST_ENUM_XrResult(_)                                                 \
    _(XR_SUCCESS, 0)                                                             \
    _(XR_TIMEOUT_EXPIRED, 1)                                                     \
    _(XR_SESSION_LOSS_PENDING, 3)                                                \
    _(XR_EVENT_UNAVAILABLE, 4)                                                   \
    _(XR_SPACE_BOUNDS_UNAVAILABLE, 7)                                            \
    _(XR_SESSION_NOT_FOCUSED, 8)                                                 \
    _(XR_FRAME_DISCARDED, 9)                                                     \
    _(XR_ERROR_VALIDATION_FAILURE, -1)                                           \
    _(XR_ERROR_RUNTIME_FAILURE, -2)                                              \
    _(XR_ERROR_OUT_OF_MEMORY, -3)                                                \
    _(XR_ERROR_API_VERSION_UNSUPPORTED, -4)                                      \
    _(XR_ERROR_INITIALIZATION_FAILED, -6)                                        \
    _(XR_ERROR_FUNCTION_UNSUPPORTED, -7)                                         \
    _(XR_ERROR_FEATURE_UNSUPPORTED, -8)                                          \
    _(XR_ERROR_EXTENSION_NOT_PRESENT, -9)                                        \
    _(XR_ERROR_LIMIT_REACHED, -10)                                               \
    _(XR_ERROR_SIZE_INSUFFICIENT, -11)                                           \
    _(XR_ERROR_HANDLE_INVALID, -12)                                              \
    _(XR_ERROR_INSTANCE_LOST, -13)                                               \
    _(XR_ERROR_SESSION_RUNNING, -14)                                             \
    _(XR_ERROR_SESSION_NOT_RUNNING, -16)                                         \
    _(XR_ERROR_SESSION_LOST, -17)                                                \
    _(XR_ERROR_SYSTEM_INVALID, -18)                                              \
    _(XR_ERROR_PATH_INVALID, -19)                                                \
    _(XR_ERROR_PATH_COUNT_EXCEEDED, -20)                                         \
    _(XR_ERROR_PATH_FORMAT_INVALID, -21)                                         \
    _(XR_ERROR_PATH_UNSUPPORTED, -22)                                            \
    _(XR_ERROR_LAYER_INVALID, -23)                                               \
    _(XR_ERROR_LAYER_LIMIT_EXCEEDED, -24)                                        \
    _(XR_ERROR_SWAPCHAIN_RECT_INVALID, -25)                                      \
    _(XR_ERROR_SWAPCHAIN_FORMAT_UNSUPPORTED, -26)                                \
    _(XR_ERROR_ACTION_TYPE_MISMATCH, -27)                                        \
    _(XR_ERROR_SESSION_NOT_READY, -28)                                           \
    _(XR_ERROR_SESSION_NOT_STOPPING, -29)                                        \
    _(XR_ERROR_TIME_INVALID, -30)                                                \
    _(XR_ERROR_REFERENCE_SPACE_UNSUPPORTED, -31)                                 \
    _(XR_ERROR_FILE_ACCESS_ERROR, -32)                                           \
    _(XR_ERROR_FILE_CONTENTS_INVALID, -33)                                       \
    _(XR_ERROR_FORM_FACTOR_UNSUPPORTED, -34)                                     \
    _(XR_ERROR_FORM_FACTOR_UNAVAILABLE, -35)                                     \
    _(XR_ERROR_API_LAYER_NOT_PRESENT, -36)                                       \
    _(XR_ERROR_CALL_ORDER_INVALID, -37)                                          \
    _(XR_ERROR_GRAPHICS_DEVICE_INVALID, -38)                                     \
    _(XR_ERROR_POSE_INVALID, -39)                                                \
    _(XR_ERROR_INDEX_OUT_OF_RANGE, -40)                                          \
    _(XR_ERROR_VIEW_CONFIGURATION_TYPE_UNSUPPORTED, -41)                         \
    _(XR_ERROR_ENVIRONMENT_BLEND_MODE_UNSUPPORTED, -42)                          \
    _(XR_ERROR_NAME_DUPLICATED, -44)                                             \
    _(XR_ERROR_NAME_INVALID, -45)                                                \
    _(XR_ERROR_ACTIONSET_NOT_ATTACHED, -46)                                      \
    _(XR_ERROR_ACTIONSETS_ALREADY_ATTACHED, -47)                                 \
    _(XR_ERROR_LOCALIZED_NAME_DUPLICATED, -48)                                   \
    _(XR_ERROR_LOCALIZED_NAME_INVALID, -49)                                      \
    _(XR_ERROR_GRAPHICS_REQUIREMENTS_CALL_MISSING, -50)                          \
    _(XR_ERROR_RUNTIME_UNAVAILABLE, -51)                                         \
    _(XR_ERROR_EXTENSION_DEPENDENCY_NOT_ENABLED, -1000710001)                    \
    _(XR_ERROR_PERMISSION_INSUFFICIENT, -1000710000)                             \
    _(XR_ERROR_ANDROID_THREAD_SETTINGS_ID_INVALID_KHR, -1000003000)              \
    _(XR_ERROR_ANDROID_THREAD_SETTINGS_FAILURE_KHR, -1000003001)                 \
    _(XR_ERROR_CREATE_SPATIAL_ANCHOR_FAILED_MSFT, -1000039001)                   \
    _(XR_ERROR_SECONDARY_VIEW_CONFIGURATION_TYPE_NOT_ENABLED_MSFT, -1000053000)  \
    _(XR_ERROR_CONTROLLER_MODEL_KEY_INVALID_MSFT, -1000055000)                   \
    _(XR_ERROR_REPROJECTION_MODE_UNSUPPORTED_MSFT, -1000066000)                  \
    _(XR_ERROR_COMPUTE_NEW_SCENE_NOT_COMPLETED_MSFT, -1000097000)                \
    _(XR_ERROR_SCENE_COMPONENT_ID_INVALID_MSFT, -1000097001)                     \
    _(XR_ERROR_SCENE_COMPONENT_TYPE_MISMATCH_MSFT, -1000097002)                  \
    _(XR_ERROR_SCENE_MESH_BUFFER_ID_INVALID_MSFT, -1000097003)                   \
    _(XR_ERROR_SCENE_COMPUTE_FEATURE_INCOMPATIBLE_MSFT, -1000097004)             \
    _(XR_ERROR_SCENE_COMPUTE_CONSISTENCY_MISMATCH_MSFT, -1000097005)             \
    _(XR_ERROR_DISPLAY_REFRESH_RATE_UNSUPPORTED_FB, -1000101000)                 \
    _(XR_ERROR_COLOR_SPACE_UNSUPPORTED_FB, -1000108000)                          \
    _(XR_ERROR_SPACE_COMPONENT_NOT_SUPPORTED_FB, -1000113000)                    \
    _(XR_ERROR_SPACE_COMPONENT_NOT_ENABLED_FB, -1000113001)                      \
    _(XR_ERROR_SPACE_COMPONENT_STATUS_PENDING_FB, -1000113002)                   \
    _(XR_ERROR_SPACE_COMPONENT_STATUS_ALREADY_SET_FB, -1000113003)               \
    _(XR_ERROR_UNEXPECTED_STATE_PASSTHROUGH_FB, -1000118000)                     \
    _(XR_ERROR_FEATURE_ALREADY_CREATED_PASSTHROUGH_FB, -1000118001)              \
    _(XR_ERROR_FEATURE_REQUIRED_PASSTHROUGH_FB, -1000118002)                     \
    _(XR_ERROR_NOT_PERMITTED_PASSTHROUGH_FB, -1000118003)                        \
    _(XR_ERROR_INSUFFICIENT_RESOURCES_PASSTHROUGH_FB, -1000118004)               \
    _(XR_ERROR_UNKNOWN_PASSTHROUGH_FB, -1000118050)                              \
    _(XR_ERROR_RENDER_MODEL_KEY_INVALID_FB, -1000119000)                         \
    _(XR_RENDER_MODEL_UNAVAILABLE_FB, 1000119020)                                \
    _(XR_ERROR_MARKER_NOT_TRACKED_VARJO, -1000124000)                            \
    _(XR_ERROR_MARKER_ID_INVALID_VARJO, -1000124001)                             \
    _(XR_ERROR_MARKER_DETECTOR_PERMISSION_DENIED_ML, -1000138000)                \
    _(XR_ERROR_MARKER_DETECTOR_LOCATE_FAILED_ML, -1000138001)                    \
    _(XR_ERROR_MARKER_DETECTOR_INVALID_DATA_QUERY_ML, -1000138002)               \
    _(XR_ERROR_MARKER_DETECTOR_INVALID_CREATE_INFO_ML, -1000138003)              \
    _(XR_ERROR_MARKER_INVALID_ML, -1000138004)                                   \
    _(XR_ERROR_LOCALIZATION_MAP_INCOMPATIBLE_ML, -1000139000)                    \
    _(XR_ERROR_LOCALIZATION_MAP_UNAVAILABLE_ML, -1000139001)                     \
    _(XR_ERROR_LOCALIZATION_MAP_FAIL_ML, -1000139002)                            \
    _(XR_ERROR_LOCALIZATION_MAP_IMPORT_EXPORT_PERMISSION_DENIED_ML, -1000139003) \
    _(XR_ERROR_LOCALIZATION_MAP_PERMISSION_DENIED_ML, -1000139004)               \
    _(XR_ERROR_LOCALIZATION_MAP_ALREADY_EXISTS_ML, -1000139005)                  \
    _(XR_ERROR_LOCALIZATION_MAP_CANNOT_EXPORT_CLOUD_MAP_ML, -1000139006)         \
    _(XR_ERROR_SPATIAL_ANCHOR_NAME_NOT_FOUND_MSFT, -1000142001)                  \
    _(XR_ERROR_SPATIAL_ANCHOR_NAME_INVALID_MSFT, -1000142002)                    \
    _(XR_SCENE_MARKER_DATA_NOT_STRING_MSFT, 1000147000)                          \
    _(XR_ERROR_SPACE_MAPPING_INSUFFICIENT_FB, -1000169000)                       \
    _(XR_ERROR_SPACE_LOCALIZATION_FAILED_FB, -1000169001)                        \
    _(XR_ERROR_SPACE_NETWORK_TIMEOUT_FB, -1000169002)                            \
    _(XR_ERROR_SPACE_NETWORK_REQUEST_FAILED_FB, -1000169003)                     \
    _(XR_ERROR_SPACE_CLOUD_STORAGE_DISABLED_FB, -1000169004)                     \
    _(XR_ERROR_PASSTHROUGH_COLOR_LUT_BUFFER_SIZE_MISMATCH_META, -1000266000)     \
    _(XR_ENVIRONMENT_DEPTH_NOT_AVAILABLE_META, 1000291000)                       \
    _(XR_ERROR_HINT_ALREADY_SET_QCOM, -1000306000)                               \
    _(XR_ERROR_NOT_AN_ANCHOR_HTC, -1000319000)                                   \
    _(XR_ERROR_SPACE_NOT_LOCATABLE_EXT, -1000429000)                             \
    _(XR_ERROR_PLANE_DETECTION_PERMISSION_DENIED_EXT, -1000429001)               \
    _(XR_ERROR_FUTURE_PENDING_EXT, -1000469001)                                  \
    _(XR_ERROR_FUTURE_INVALID_EXT, -1000469002)                                  \
    _(XR_RESULT_MAX_ENUM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrStructureType(_)                                            \
    _(XR_TYPE_UNKNOWN, 0)                                                          \
    _(XR_TYPE_API_LAYER_PROPERTIES, 1)                                             \
    _(XR_TYPE_EXTENSION_PROPERTIES, 2)                                             \
    _(XR_TYPE_INSTANCE_CREATE_INFO, 3)                                             \
    _(XR_TYPE_SYSTEM_GET_INFO, 4)                                                  \
    _(XR_TYPE_SYSTEM_PROPERTIES, 5)                                                \
    _(XR_TYPE_VIEW_LOCATE_INFO, 6)                                                 \
    _(XR_TYPE_VIEW, 7)                                                             \
    _(XR_TYPE_SESSION_CREATE_INFO, 8)                                              \
    _(XR_TYPE_SWAPCHAIN_CREATE_INFO, 9)                                            \
    _(XR_TYPE_SESSION_BEGIN_INFO, 10)                                              \
    _(XR_TYPE_VIEW_STATE, 11)                                                      \
    _(XR_TYPE_FRAME_END_INFO, 12)                                                  \
    _(XR_TYPE_HAPTIC_VIBRATION, 13)                                                \
    _(XR_TYPE_EVENT_DATA_BUFFER, 16)                                               \
    _(XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING, 17)                                \
    _(XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED, 18)                                \
    _(XR_TYPE_ACTION_STATE_BOOLEAN, 23)                                            \
    _(XR_TYPE_ACTION_STATE_FLOAT, 24)                                              \
    _(XR_TYPE_ACTION_STATE_VECTOR2F, 25)                                           \
    _(XR_TYPE_ACTION_STATE_POSE, 27)                                               \
    _(XR_TYPE_ACTION_SET_CREATE_INFO, 28)                                          \
    _(XR_TYPE_ACTION_CREATE_INFO, 29)                                              \
    _(XR_TYPE_INSTANCE_PROPERTIES, 32)                                             \
    _(XR_TYPE_FRAME_WAIT_INFO, 33)                                                 \
    _(XR_TYPE_COMPOSITION_LAYER_PROJECTION, 35)                                    \
    _(XR_TYPE_COMPOSITION_LAYER_QUAD, 36)                                          \
    _(XR_TYPE_REFERENCE_SPACE_CREATE_INFO, 37)                                     \
    _(XR_TYPE_ACTION_SPACE_CREATE_INFO, 38)                                        \
    _(XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING, 40)                       \
    _(XR_TYPE_VIEW_CONFIGURATION_VIEW, 41)                                         \
    _(XR_TYPE_SPACE_LOCATION, 42)                                                  \
    _(XR_TYPE_SPACE_VELOCITY, 43)                                                  \
    _(XR_TYPE_FRAME_STATE, 44)                                                     \
    _(XR_TYPE_VIEW_CONFIGURATION_PROPERTIES, 45)                                   \
    _(XR_TYPE_FRAME_BEGIN_INFO, 46)                                                \
    _(XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW, 48)                               \
    _(XR_TYPE_EVENT_DATA_EVENTS_LOST, 49)                                          \
    _(XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING, 51)                           \
    _(XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED, 52)                          \
    _(XR_TYPE_INTERACTION_PROFILE_STATE, 53)                                       \
    _(XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO, 55)                                    \
    _(XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO, 56)                                       \
    _(XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO, 57)                                    \
    _(XR_TYPE_ACTION_STATE_GET_INFO, 58)                                           \
    _(XR_TYPE_HAPTIC_ACTION_INFO, 59)                                              \
    _(XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO, 60)                                 \
    _(XR_TYPE_ACTIONS_SYNC_INFO, 61)                                               \
    _(XR_TYPE_BOUND_SOURCES_FOR_ACTION_ENUMERATE_INFO, 62)                         \
    _(XR_TYPE_INPUT_SOURCE_LOCALIZED_NAME_GET_INFO, 63)                            \
    _(XR_TYPE_SPACES_LOCATE_INFO, 1000471000)                                      \
    _(XR_TYPE_SPACE_LOCATIONS, 1000471001)                                         \
    _(XR_TYPE_SPACE_VELOCITIES, 1000471002)                                        \
    _(XR_TYPE_COMPOSITION_LAYER_CUBE_KHR, 1000006000)                              \
    _(XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR, 1000008000)                        \
    _(XR_TYPE_COMPOSITION_LAYER_DEPTH_INFO_KHR, 1000010000)                        \
    _(XR_TYPE_VULKAN_SWAPCHAIN_FORMAT_LIST_CREATE_INFO_KHR, 1000014000)            \
    _(XR_TYPE_EVENT_DATA_PERF_SETTINGS_EXT, 1000015000)                            \
    _(XR_TYPE_COMPOSITION_LAYER_CYLINDER_KHR, 1000017000)                          \
    _(XR_TYPE_COMPOSITION_LAYER_EQUIRECT_KHR, 1000018000)                          \
    _(XR_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT, 1000019000)                        \
    _(XR_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT, 1000019001)                 \
    _(XR_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT, 1000019002)                   \
    _(XR_TYPE_DEBUG_UTILS_LABEL_EXT, 1000019003)                                   \
    _(XR_TYPE_GRAPHICS_BINDING_OPENGL_WIN32_KHR, 1000023000)                       \
    _(XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR, 1000023001)                        \
    _(XR_TYPE_GRAPHICS_BINDING_OPENGL_XCB_KHR, 1000023002)                         \
    _(XR_TYPE_GRAPHICS_BINDING_OPENGL_WAYLAND_KHR, 1000023003)                     \
    _(XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR, 1000023004)                              \
    _(XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR, 1000023005)                        \
    _(XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR, 1000024001)                  \
    _(XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR, 1000024002)                           \
    _(XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR, 1000024003)                     \
    _(XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR, 1000025000)                             \
    _(XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR, 1000025001)                              \
    _(XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN_KHR, 1000025002)                        \
    _(XR_TYPE_GRAPHICS_BINDING_D3D11_KHR, 1000027000)                              \
    _(XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR, 1000027001)                               \
    _(XR_TYPE_GRAPHICS_REQUIREMENTS_D3D11_KHR, 1000027002)                         \
    _(XR_TYPE_GRAPHICS_BINDING_D3D12_KHR, 1000028000)                              \
    _(XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR, 1000028001)                               \
    _(XR_TYPE_GRAPHICS_REQUIREMENTS_D3D12_KHR, 1000028002)                         \
    _(XR_TYPE_SYSTEM_EYE_GAZE_INTERACTION_PROPERTIES_EXT, 1000030000)              \
    _(XR_TYPE_EYE_GAZE_SAMPLE_TIME_EXT, 1000030001)                                \
    _(XR_TYPE_VISIBILITY_MASK_KHR, 1000031000)                                     \
    _(XR_TYPE_EVENT_DATA_VISIBILITY_MASK_CHANGED_KHR, 1000031001)                  \
    _(XR_TYPE_SESSION_CREATE_INFO_OVERLAY_EXTX, 1000033000)                        \
    _(XR_TYPE_EVENT_DATA_MAIN_SESSION_VISIBILITY_CHANGED_EXTX, 1000033003)         \
    _(XR_TYPE_COMPOSITION_LAYER_COLOR_SCALE_BIAS_KHR, 1000034000)                  \
    _(XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_MSFT, 1000039000)                         \
    _(XR_TYPE_SPATIAL_ANCHOR_SPACE_CREATE_INFO_MSFT, 1000039001)                   \
    _(XR_TYPE_COMPOSITION_LAYER_IMAGE_LAYOUT_FB, 1000040000)                       \
    _(XR_TYPE_COMPOSITION_LAYER_ALPHA_BLEND_FB, 1000041001)                        \
    _(XR_TYPE_VIEW_CONFIGURATION_DEPTH_RANGE_EXT, 1000046000)                      \
    _(XR_TYPE_GRAPHICS_BINDING_EGL_MNDX, 1000048004)                               \
    _(XR_TYPE_SPATIAL_GRAPH_NODE_SPACE_CREATE_INFO_MSFT, 1000049000)               \
    _(XR_TYPE_SPATIAL_GRAPH_STATIC_NODE_BINDING_CREATE_INFO_MSFT, 1000049001)      \
    _(XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_GET_INFO_MSFT, 1000049002)     \
    _(XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_MSFT, 1000049003)              \
    _(XR_TYPE_SYSTEM_HAND_TRACKING_PROPERTIES_EXT, 1000051000)                     \
    _(XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT, 1000051001)                            \
    _(XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT, 1000051002)                             \
    _(XR_TYPE_HAND_JOINT_LOCATIONS_EXT, 1000051003)                                \
    _(XR_TYPE_HAND_JOINT_VELOCITIES_EXT, 1000051004)                               \
    _(XR_TYPE_SYSTEM_HAND_TRACKING_MESH_PROPERTIES_MSFT, 1000052000)               \
    _(XR_TYPE_HAND_MESH_SPACE_CREATE_INFO_MSFT, 1000052001)                        \
    _(XR_TYPE_HAND_MESH_UPDATE_INFO_MSFT, 1000052002)                              \
    _(XR_TYPE_HAND_MESH_MSFT, 1000052003)                                          \
    _(XR_TYPE_HAND_POSE_TYPE_INFO_MSFT, 1000052004)                                \
    _(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SESSION_BEGIN_INFO_MSFT, 1000053000)    \
    _(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_STATE_MSFT, 1000053001)                 \
    _(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_STATE_MSFT, 1000053002)           \
    _(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_END_INFO_MSFT, 1000053003)        \
    _(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_LAYER_INFO_MSFT, 1000053004)            \
    _(XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SWAPCHAIN_CREATE_INFO_MSFT, 1000053005) \
    _(XR_TYPE_CONTROLLER_MODEL_KEY_STATE_MSFT, 1000055000)                         \
    _(XR_TYPE_CONTROLLER_MODEL_NODE_PROPERTIES_MSFT, 1000055001)                   \
    _(XR_TYPE_CONTROLLER_MODEL_PROPERTIES_MSFT, 1000055002)                        \
    _(XR_TYPE_CONTROLLER_MODEL_NODE_STATE_MSFT, 1000055003)                        \
    _(XR_TYPE_CONTROLLER_MODEL_STATE_MSFT, 1000055004)                             \
    _(XR_TYPE_VIEW_CONFIGURATION_VIEW_FOV_EPIC, 1000059000)                        \
    _(XR_TYPE_HOLOGRAPHIC_WINDOW_ATTACHMENT_MSFT, 1000063000)                      \
    _(XR_TYPE_COMPOSITION_LAYER_REPROJECTION_INFO_MSFT, 1000066000)                \
    _(XR_TYPE_COMPOSITION_LAYER_REPROJECTION_PLANE_OVERRIDE_MSFT, 1000066001)      \
    _(XR_TYPE_ANDROID_SURFACE_SWAPCHAIN_CREATE_INFO_FB, 1000070000)                \
    _(XR_TYPE_COMPOSITION_LAYER_SECURE_CONTENT_FB, 1000072000)                     \
    _(XR_TYPE_BODY_TRACKER_CREATE_INFO_FB, 1000076001)                             \
    _(XR_TYPE_BODY_JOINTS_LOCATE_INFO_FB, 1000076002)                              \
    _(XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_FB, 1000076004)                      \
    _(XR_TYPE_BODY_JOINT_LOCATIONS_FB, 1000076005)                                 \
    _(XR_TYPE_BODY_SKELETON_FB, 1000076006)                                        \
    _(XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT, 1000078000)                    \
    _(XR_TYPE_INTERACTION_PROFILE_ANALOG_THRESHOLD_VALVE, 1000079000)              \
    _(XR_TYPE_HAND_JOINTS_MOTION_RANGE_INFO_EXT, 1000080000)                       \
    _(XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR, 1000089000)                            \
    _(XR_TYPE_VULKAN_INSTANCE_CREATE_INFO_KHR, 1000090000)                         \
    _(XR_TYPE_VULKAN_DEVICE_CREATE_INFO_KHR, 1000090001)                           \
    _(XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR, 1000090003)                     \
    _(XR_TYPE_COMPOSITION_LAYER_EQUIRECT2_KHR, 1000091000)                         \
    _(XR_TYPE_SCENE_OBSERVER_CREATE_INFO_MSFT, 1000097000)                         \
    _(XR_TYPE_SCENE_CREATE_INFO_MSFT, 1000097001)                                  \
    _(XR_TYPE_NEW_SCENE_COMPUTE_INFO_MSFT, 1000097002)                             \
    _(XR_TYPE_VISUAL_MESH_COMPUTE_LOD_INFO_MSFT, 1000097003)                       \
    _(XR_TYPE_SCENE_COMPONENTS_MSFT, 1000097004)                                   \
    _(XR_TYPE_SCENE_COMPONENTS_GET_INFO_MSFT, 1000097005)                          \
    _(XR_TYPE_SCENE_COMPONENT_LOCATIONS_MSFT, 1000097006)                          \
    _(XR_TYPE_SCENE_COMPONENTS_LOCATE_INFO_MSFT, 1000097007)                       \
    _(XR_TYPE_SCENE_OBJECTS_MSFT, 1000097008)                                      \
    _(XR_TYPE_SCENE_COMPONENT_PARENT_FILTER_INFO_MSFT, 1000097009)                 \
    _(XR_TYPE_SCENE_OBJECT_TYPES_FILTER_INFO_MSFT, 1000097010)                     \
    _(XR_TYPE_SCENE_PLANES_MSFT, 1000097011)                                       \
    _(XR_TYPE_SCENE_PLANE_ALIGNMENT_FILTER_INFO_MSFT, 1000097012)                  \
    _(XR_TYPE_SCENE_MESHES_MSFT, 1000097013)                                       \
    _(XR_TYPE_SCENE_MESH_BUFFERS_GET_INFO_MSFT, 1000097014)                        \
    _(XR_TYPE_SCENE_MESH_BUFFERS_MSFT, 1000097015)                                 \
    _(XR_TYPE_SCENE_MESH_VERTEX_BUFFER_MSFT, 1000097016)                           \
    _(XR_TYPE_SCENE_MESH_INDICES_UINT32_MSFT, 1000097017)                          \
    _(XR_TYPE_SCENE_MESH_INDICES_UINT16_MSFT, 1000097018)                          \
    _(XR_TYPE_SERIALIZED_SCENE_FRAGMENT_DATA_GET_INFO_MSFT, 1000098000)            \
    _(XR_TYPE_SCENE_DESERIALIZE_INFO_MSFT, 1000098001)                             \
    _(XR_TYPE_EVENT_DATA_DISPLAY_REFRESH_RATE_CHANGED_FB, 1000101000)              \
    _(XR_TYPE_VIVE_TRACKER_PATHS_HTCX, 1000103000)                                 \
    _(XR_TYPE_EVENT_DATA_VIVE_TRACKER_CONNECTED_HTCX, 1000103001)                  \
    _(XR_TYPE_SYSTEM_FACIAL_TRACKING_PROPERTIES_HTC, 1000104000)                   \
    _(XR_TYPE_FACIAL_TRACKER_CREATE_INFO_HTC, 1000104001)                          \
    _(XR_TYPE_FACIAL_EXPRESSIONS_HTC, 1000104002)                                  \
    _(XR_TYPE_SYSTEM_COLOR_SPACE_PROPERTIES_FB, 1000108000)                        \
    _(XR_TYPE_HAND_TRACKING_MESH_FB, 1000110001)                                   \
    _(XR_TYPE_HAND_TRACKING_SCALE_FB, 1000110003)                                  \
    _(XR_TYPE_HAND_TRACKING_AIM_STATE_FB, 1000111001)                              \
    _(XR_TYPE_HAND_TRACKING_CAPSULES_STATE_FB, 1000112000)                         \
    _(XR_TYPE_SYSTEM_SPATIAL_ENTITY_PROPERTIES_FB, 1000113004)                     \
    _(XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_FB, 1000113003)                           \
    _(XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB, 1000113007)                      \
    _(XR_TYPE_SPACE_COMPONENT_STATUS_FB, 1000113001)                               \
    _(XR_TYPE_EVENT_DATA_SPATIAL_ANCHOR_CREATE_COMPLETE_FB, 1000113005)            \
    _(XR_TYPE_EVENT_DATA_SPACE_SET_STATUS_COMPLETE_FB, 1000113006)                 \
    _(XR_TYPE_FOVEATION_PROFILE_CREATE_INFO_FB, 1000114000)                        \
    _(XR_TYPE_SWAPCHAIN_CREATE_INFO_FOVEATION_FB, 1000114001)                      \
    _(XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB, 1000114002)                            \
    _(XR_TYPE_FOVEATION_LEVEL_PROFILE_CREATE_INFO_FB, 1000115000)                  \
    _(XR_TYPE_KEYBOARD_SPACE_CREATE_INFO_FB, 1000116009)                           \
    _(XR_TYPE_KEYBOARD_TRACKING_QUERY_FB, 1000116004)                              \
    _(XR_TYPE_SYSTEM_KEYBOARD_TRACKING_PROPERTIES_FB, 1000116002)                  \
    _(XR_TYPE_TRIANGLE_MESH_CREATE_INFO_FB, 1000117001)                            \
    _(XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES_FB, 1000118000)                        \
    _(XR_TYPE_PASSTHROUGH_CREATE_INFO_FB, 1000118001)                              \
    _(XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_FB, 1000118002)                        \
    _(XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB, 1000118003)                        \
    _(XR_TYPE_GEOMETRY_INSTANCE_CREATE_INFO_FB, 1000118004)                        \
    _(XR_TYPE_GEOMETRY_INSTANCE_TRANSFORM_FB, 1000118005)                          \
    _(XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES2_FB, 1000118006)                       \
    _(XR_TYPE_PASSTHROUGH_STYLE_FB, 1000118020)                                    \
    _(XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_RGBA_FB, 1000118021)                   \
    _(XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_MONO_FB, 1000118022)                   \
    _(XR_TYPE_PASSTHROUGH_BRIGHTNESS_CONTRAST_SATURATION_FB, 1000118023)           \
    _(XR_TYPE_EVENT_DATA_PASSTHROUGH_STATE_CHANGED_FB, 1000118030)                 \
    _(XR_TYPE_RENDER_MODEL_PATH_INFO_FB, 1000119000)                               \
    _(XR_TYPE_RENDER_MODEL_PROPERTIES_FB, 1000119001)                              \
    _(XR_TYPE_RENDER_MODEL_BUFFER_FB, 1000119002)                                  \
    _(XR_TYPE_RENDER_MODEL_LOAD_INFO_FB, 1000119003)                               \
    _(XR_TYPE_SYSTEM_RENDER_MODEL_PROPERTIES_FB, 1000119004)                       \
    _(XR_TYPE_RENDER_MODEL_CAPABILITIES_REQUEST_FB, 1000119005)                    \
    _(XR_TYPE_BINDING_MODIFICATIONS_KHR, 1000120000)                               \
    _(XR_TYPE_VIEW_LOCATE_FOVEATED_RENDERING_VARJO, 1000121000)                    \
    _(XR_TYPE_FOVEATED_VIEW_CONFIGURATION_VIEW_VARJO, 1000121001)                  \
    _(XR_TYPE_SYSTEM_FOVEATED_RENDERING_PROPERTIES_VARJO, 1000121002)              \
    _(XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_VARJO, 1000122000)                      \
    _(XR_TYPE_SYSTEM_MARKER_TRACKING_PROPERTIES_VARJO, 1000124000)                 \
    _(XR_TYPE_EVENT_DATA_MARKER_TRACKING_UPDATE_VARJO, 1000124001)                 \
    _(XR_TYPE_MARKER_SPACE_CREATE_INFO_VARJO, 1000124002)                          \
    _(XR_TYPE_FRAME_END_INFO_ML, 1000135000)                                       \
    _(XR_TYPE_GLOBAL_DIMMER_FRAME_END_INFO_ML, 1000136000)                         \
    _(XR_TYPE_COORDINATE_SPACE_CREATE_INFO_ML, 1000137000)                         \
    _(XR_TYPE_SYSTEM_MARKER_UNDERSTANDING_PROPERTIES_ML, 1000138000)               \
    _(XR_TYPE_MARKER_DETECTOR_CREATE_INFO_ML, 1000138001)                          \
    _(XR_TYPE_MARKER_DETECTOR_ARUCO_INFO_ML, 1000138002)                           \
    _(XR_TYPE_MARKER_DETECTOR_SIZE_INFO_ML, 1000138003)                            \
    _(XR_TYPE_MARKER_DETECTOR_APRIL_TAG_INFO_ML, 1000138004)                       \
    _(XR_TYPE_MARKER_DETECTOR_CUSTOM_PROFILE_INFO_ML, 1000138005)                  \
    _(XR_TYPE_MARKER_DETECTOR_SNAPSHOT_INFO_ML, 1000138006)                        \
    _(XR_TYPE_MARKER_DETECTOR_STATE_ML, 1000138007)                                \
    _(XR_TYPE_MARKER_SPACE_CREATE_INFO_ML, 1000138008)                             \
    _(XR_TYPE_LOCALIZATION_MAP_ML, 1000139000)                                     \
    _(XR_TYPE_EVENT_DATA_LOCALIZATION_CHANGED_ML, 1000139001)                      \
    _(XR_TYPE_MAP_LOCALIZATION_REQUEST_INFO_ML, 1000139002)                        \
    _(XR_TYPE_LOCALIZATION_MAP_IMPORT_INFO_ML, 1000139003)                         \
    _(XR_TYPE_LOCALIZATION_ENABLE_EVENTS_INFO_ML, 1000139004)                      \
    _(XR_TYPE_EVENT_DATA_HEADSET_FIT_CHANGED_ML, 1000472000)                       \
    _(XR_TYPE_EVENT_DATA_EYE_CALIBRATION_CHANGED_ML, 1000472001)                   \
    _(XR_TYPE_USER_CALIBRATION_ENABLE_EVENTS_INFO_ML, 1000472002)                  \
    _(XR_TYPE_SPATIAL_ANCHOR_PERSISTENCE_INFO_MSFT, 1000142000)                    \
    _(XR_TYPE_SPATIAL_ANCHOR_FROM_PERSISTED_ANCHOR_CREATE_INFO_MSFT, 1000142001)   \
    _(XR_TYPE_SCENE_MARKERS_MSFT, 1000147000)                                      \
    _(XR_TYPE_SCENE_MARKER_TYPE_FILTER_MSFT, 1000147001)                           \
    _(XR_TYPE_SCENE_MARKER_QR_CODES_MSFT, 1000147002)                              \
    _(XR_TYPE_SPACE_QUERY_INFO_FB, 1000156001)                                     \
    _(XR_TYPE_SPACE_QUERY_RESULTS_FB, 1000156002)                                  \
    _(XR_TYPE_SPACE_STORAGE_LOCATION_FILTER_INFO_FB, 1000156003)                   \
    _(XR_TYPE_SPACE_UUID_FILTER_INFO_FB, 1000156054)                               \
    _(XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB, 1000156052)                          \
    _(XR_TYPE_EVENT_DATA_SPACE_QUERY_RESULTS_AVAILABLE_FB, 1000156103)             \
    _(XR_TYPE_EVENT_DATA_SPACE_QUERY_COMPLETE_FB, 1000156104)                      \
    _(XR_TYPE_SPACE_SAVE_INFO_FB, 1000158000)                                      \
    _(XR_TYPE_SPACE_ERASE_INFO_FB, 1000158001)                                     \
    _(XR_TYPE_EVENT_DATA_SPACE_SAVE_COMPLETE_FB, 1000158106)                       \
    _(XR_TYPE_EVENT_DATA_SPACE_ERASE_COMPLETE_FB, 1000158107)                      \
    _(XR_TYPE_SWAPCHAIN_IMAGE_FOVEATION_VULKAN_FB, 1000160000)                     \
    _(XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB, 1000161000)           \
    _(XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB, 1000162000)                    \
    _(XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB, 1000163000)                       \
    _(XR_TYPE_SPACE_SHARE_INFO_FB, 1000169001)                                     \
    _(XR_TYPE_EVENT_DATA_SPACE_SHARE_COMPLETE_FB, 1000169002)                      \
    _(XR_TYPE_COMPOSITION_LAYER_SPACE_WARP_INFO_FB, 1000171000)                    \
    _(XR_TYPE_SYSTEM_SPACE_WARP_PROPERTIES_FB, 1000171001)                         \
    _(XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB, 1000173001)                  \
    _(XR_TYPE_SEMANTIC_LABELS_FB, 1000175000)                                      \
    _(XR_TYPE_ROOM_LAYOUT_FB, 1000175001)                                          \
    _(XR_TYPE_BOUNDARY_2D_FB, 1000175002)                                          \
    _(XR_TYPE_SEMANTIC_LABELS_SUPPORT_INFO_FB, 1000175010)                         \
    _(XR_TYPE_DIGITAL_LENS_CONTROL_ALMALENCE, 1000196000)                          \
    _(XR_TYPE_EVENT_DATA_SCENE_CAPTURE_COMPLETE_FB, 1000198001)                    \
    _(XR_TYPE_SCENE_CAPTURE_REQUEST_INFO_FB, 1000198050)                           \
    _(XR_TYPE_SPACE_CONTAINER_FB, 1000199000)                                      \
    _(XR_TYPE_FOVEATION_EYE_TRACKED_PROFILE_CREATE_INFO_META, 1000200000)          \
    _(XR_TYPE_FOVEATION_EYE_TRACKED_STATE_META, 1000200001)                        \
    _(XR_TYPE_SYSTEM_FOVEATION_EYE_TRACKED_PROPERTIES_META, 1000200002)            \
    _(XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES_FB, 1000201004)                      \
    _(XR_TYPE_FACE_TRACKER_CREATE_INFO_FB, 1000201005)                             \
    _(XR_TYPE_FACE_EXPRESSION_INFO_FB, 1000201002)                                 \
    _(XR_TYPE_FACE_EXPRESSION_WEIGHTS_FB, 1000201006)                              \
    _(XR_TYPE_EYE_TRACKER_CREATE_INFO_FB, 1000202001)                              \
    _(XR_TYPE_EYE_GAZES_INFO_FB, 1000202002)                                       \
    _(XR_TYPE_EYE_GAZES_FB, 1000202003)                                            \
    _(XR_TYPE_SYSTEM_EYE_TRACKING_PROPERTIES_FB, 1000202004)                       \
    _(XR_TYPE_PASSTHROUGH_KEYBOARD_HANDS_INTENSITY_FB, 1000203002)                 \
    _(XR_TYPE_COMPOSITION_LAYER_SETTINGS_FB, 1000204000)                           \
    _(XR_TYPE_HAPTIC_PCM_VIBRATION_FB, 1000209001)                                 \
    _(XR_TYPE_DEVICE_PCM_SAMPLE_RATE_STATE_FB, 1000209002)                         \
    _(XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_FB, 1000212000)                         \
    _(XR_TYPE_LOCAL_DIMMING_FRAME_END_INFO_META, 1000216000)                       \
    _(XR_TYPE_PASSTHROUGH_PREFERENCES_META, 1000217000)                            \
    _(XR_TYPE_SYSTEM_VIRTUAL_KEYBOARD_PROPERTIES_META, 1000219001)                 \
    _(XR_TYPE_VIRTUAL_KEYBOARD_CREATE_INFO_META, 1000219002)                       \
    _(XR_TYPE_VIRTUAL_KEYBOARD_SPACE_CREATE_INFO_META, 1000219003)                 \
    _(XR_TYPE_VIRTUAL_KEYBOARD_LOCATION_INFO_META, 1000219004)                     \
    _(XR_TYPE_VIRTUAL_KEYBOARD_MODEL_VISIBILITY_SET_INFO_META, 1000219005)         \
    _(XR_TYPE_VIRTUAL_KEYBOARD_ANIMATION_STATE_META, 1000219006)                   \
    _(XR_TYPE_VIRTUAL_KEYBOARD_MODEL_ANIMATION_STATES_META, 1000219007)            \
    _(XR_TYPE_VIRTUAL_KEYBOARD_TEXTURE_DATA_META, 1000219009)                      \
    _(XR_TYPE_VIRTUAL_KEYBOARD_INPUT_INFO_META, 1000219010)                        \
    _(XR_TYPE_VIRTUAL_KEYBOARD_TEXT_CONTEXT_CHANGE_INFO_META, 1000219011)          \
    _(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_COMMIT_TEXT_META, 1000219014)            \
    _(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_BACKSPACE_META, 1000219015)              \
    _(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_ENTER_META, 1000219016)                  \
    _(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_SHOWN_META, 1000219017)                  \
    _(XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_HIDDEN_META, 1000219018)                 \
    _(XR_TYPE_EXTERNAL_CAMERA_OCULUS, 1000226000)                                  \
    _(XR_TYPE_VULKAN_SWAPCHAIN_CREATE_INFO_META, 1000227000)                       \
    _(XR_TYPE_PERFORMANCE_METRICS_STATE_META, 1000232001)                          \
    _(XR_TYPE_PERFORMANCE_METRICS_COUNTER_META, 1000232002)                        \
    _(XR_TYPE_SPACE_LIST_SAVE_INFO_FB, 1000238000)                                 \
    _(XR_TYPE_EVENT_DATA_SPACE_LIST_SAVE_COMPLETE_FB, 1000238001)                  \
    _(XR_TYPE_SPACE_USER_CREATE_INFO_FB, 1000241001)                               \
    _(XR_TYPE_SYSTEM_HEADSET_ID_PROPERTIES_META, 1000245000)                       \
    _(XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_META, 1000254000)                       \
    _(XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_GET_INFO_META, 1000254001)              \
    _(XR_TYPE_SYSTEM_PASSTHROUGH_COLOR_LUT_PROPERTIES_META, 1000266000)            \
    _(XR_TYPE_PASSTHROUGH_COLOR_LUT_CREATE_INFO_META, 1000266001)                  \
    _(XR_TYPE_PASSTHROUGH_COLOR_LUT_UPDATE_INFO_META, 1000266002)                  \
    _(XR_TYPE_PASSTHROUGH_COLOR_MAP_LUT_META, 1000266100)                          \
    _(XR_TYPE_PASSTHROUGH_COLOR_MAP_INTERPOLATED_LUT_META, 1000266101)             \
    _(XR_TYPE_SPACE_TRIANGLE_MESH_GET_INFO_META, 1000269001)                       \
    _(XR_TYPE_SPACE_TRIANGLE_MESH_META, 1000269002)                                \
    _(XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES2_FB, 1000287013)                     \
    _(XR_TYPE_FACE_TRACKER_CREATE_INFO2_FB, 1000287014)                            \
    _(XR_TYPE_FACE_EXPRESSION_INFO2_FB, 1000287015)                                \
    _(XR_TYPE_FACE_EXPRESSION_WEIGHTS2_FB, 1000287016)                             \
    _(XR_TYPE_ENVIRONMENT_DEPTH_PROVIDER_CREATE_INFO_META, 1000291000)             \
    _(XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_CREATE_INFO_META, 1000291001)            \
    _(XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_STATE_META, 1000291002)                  \
    _(XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_ACQUIRE_INFO_META, 1000291003)               \
    _(XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META, 1000291004)                       \
    _(XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_META, 1000291005)                            \
    _(XR_TYPE_ENVIRONMENT_DEPTH_HAND_REMOVAL_SET_INFO_META, 1000291006)            \
    _(XR_TYPE_SYSTEM_ENVIRONMENT_DEPTH_PROPERTIES_META, 1000291007)                \
    _(XR_TYPE_PASSTHROUGH_CREATE_INFO_HTC, 1000317001)                             \
    _(XR_TYPE_PASSTHROUGH_COLOR_HTC, 1000317002)                                   \
    _(XR_TYPE_PASSTHROUGH_MESH_TRANSFORM_INFO_HTC, 1000317003)                     \
    _(XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_HTC, 1000317004)                       \
    _(XR_TYPE_FOVEATION_APPLY_INFO_HTC, 1000318000)                                \
    _(XR_TYPE_FOVEATION_DYNAMIC_MODE_INFO_HTC, 1000318001)                         \
    _(XR_TYPE_FOVEATION_CUSTOM_MODE_INFO_HTC, 1000318002)                          \
    _(XR_TYPE_SYSTEM_ANCHOR_PROPERTIES_HTC, 1000319000)                            \
    _(XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_HTC, 1000319001)                          \
    _(XR_TYPE_ACTIVE_ACTION_SET_PRIORITIES_EXT, 1000373000)                        \
    _(XR_TYPE_SYSTEM_FORCE_FEEDBACK_CURL_PROPERTIES_MNDX, 1000375000)              \
    _(XR_TYPE_FORCE_FEEDBACK_CURL_APPLY_LOCATIONS_MNDX, 1000375001)                \
    _(XR_TYPE_HAND_TRACKING_DATA_SOURCE_INFO_EXT, 1000428000)                      \
    _(XR_TYPE_HAND_TRACKING_DATA_SOURCE_STATE_EXT, 1000428001)                     \
    _(XR_TYPE_PLANE_DETECTOR_CREATE_INFO_EXT, 1000429001)                          \
    _(XR_TYPE_PLANE_DETECTOR_BEGIN_INFO_EXT, 1000429002)                           \
    _(XR_TYPE_PLANE_DETECTOR_GET_INFO_EXT, 1000429003)                             \
    _(XR_TYPE_PLANE_DETECTOR_LOCATIONS_EXT, 1000429004)                            \
    _(XR_TYPE_PLANE_DETECTOR_LOCATION_EXT, 1000429005)                             \
    _(XR_TYPE_PLANE_DETECTOR_POLYGON_BUFFER_EXT, 1000429006)                       \
    _(XR_TYPE_SYSTEM_PLANE_DETECTION_PROPERTIES_EXT, 1000429007)                   \
    _(XR_TYPE_FUTURE_CANCEL_INFO_EXT, 1000469000)                                  \
    _(XR_TYPE_FUTURE_POLL_INFO_EXT, 1000469001)                                    \
    _(XR_TYPE_FUTURE_COMPLETION_EXT, 1000469002)                                   \
    _(XR_TYPE_FUTURE_POLL_RESULT_EXT, 1000469003)                                  \
    _(XR_TYPE_EVENT_DATA_USER_PRESENCE_CHANGED_EXT, 1000470000)                    \
    _(XR_TYPE_SYSTEM_USER_PRESENCE_PROPERTIES_EXT, 1000470001)                     \
    _(XR_STRUCTURE_TYPE_MAX_ENUM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFormFactor(_)          \
    _(XR_FORM_FACTOR_HEAD_MOUNTED_DISPLAY, 1) \
    _(XR_FORM_FACTOR_HANDHELD_DISPLAY, 2)     \
    _(XR_FORM_FACTOR_MAX_ENUM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrViewConfigurationType(_)                                         \
    _(XR_VIEW_CONFIGURATION_TYPE_PRIMARY_MONO, 1)                                       \
    _(XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO, 2)                                     \
    _(XR_VIEW_CONFIGURATION_TYPE_PRIMARY_STEREO_WITH_FOVEATED_INSET, 1000037000)        \
    _(XR_VIEW_CONFIGURATION_TYPE_SECONDARY_MONO_FIRST_PERSON_OBSERVER_MSFT, 1000054000) \
    _(XR_VIEW_CONFIGURATION_TYPE_MAX_ENUM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrEnvironmentBlendMode(_)  \
    _(XR_ENVIRONMENT_BLEND_MODE_OPAQUE, 1)      \
    _(XR_ENVIRONMENT_BLEND_MODE_ADDITIVE, 2)    \
    _(XR_ENVIRONMENT_BLEND_MODE_ALPHA_BLEND, 3) \
    _(XR_ENVIRONMENT_BLEND_MODE_MAX_ENUM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrReferenceSpaceType(_)                   \
    _(XR_REFERENCE_SPACE_TYPE_VIEW, 1)                         \
    _(XR_REFERENCE_SPACE_TYPE_LOCAL, 2)                        \
    _(XR_REFERENCE_SPACE_TYPE_STAGE, 3)                        \
    _(XR_REFERENCE_SPACE_TYPE_LOCAL_FLOOR, 1000426000)         \
    _(XR_REFERENCE_SPACE_TYPE_UNBOUNDED_MSFT, 1000038000)      \
    _(XR_REFERENCE_SPACE_TYPE_COMBINED_EYE_VARJO, 1000121000)  \
    _(XR_REFERENCE_SPACE_TYPE_LOCALIZATION_MAP_ML, 1000139000) \
    _(XR_REFERENCE_SPACE_TYPE_MAX_ENUM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrActionType(_)        \
    _(XR_ACTION_TYPE_BOOLEAN_INPUT, 1)      \
    _(XR_ACTION_TYPE_FLOAT_INPUT, 2)        \
    _(XR_ACTION_TYPE_VECTOR2F_INPUT, 3)     \
    _(XR_ACTION_TYPE_POSE_INPUT, 4)         \
    _(XR_ACTION_TYPE_VIBRATION_OUTPUT, 100) \
    _(XR_ACTION_TYPE_MAX_ENUM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrEyeVisibility(_) \
    _(XR_EYE_VISIBILITY_BOTH, 0)        \
    _(XR_EYE_VISIBILITY_LEFT, 1)        \
    _(XR_EYE_VISIBILITY_RIGHT, 2)       \
    _(XR_EYE_VISIBILITY_MAX_ENUM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSessionState(_)  \
    _(XR_SESSION_STATE_UNKNOWN, 0)      \
    _(XR_SESSION_STATE_IDLE, 1)         \
    _(XR_SESSION_STATE_READY, 2)        \
    _(XR_SESSION_STATE_SYNCHRONIZED, 3) \
    _(XR_SESSION_STATE_VISIBLE, 4)      \
    _(XR_SESSION_STATE_FOCUSED, 5)      \
    _(XR_SESSION_STATE_STOPPING, 6)     \
    _(XR_SESSION_STATE_LOSS_PENDING, 7) \
    _(XR_SESSION_STATE_EXITING, 8)      \
    _(XR_SESSION_STATE_MAX_ENUM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrObjectType(_)                                   \
    _(XR_OBJECT_TYPE_UNKNOWN, 0)                                       \
    _(XR_OBJECT_TYPE_INSTANCE, 1)                                      \
    _(XR_OBJECT_TYPE_SESSION, 2)                                       \
    _(XR_OBJECT_TYPE_SWAPCHAIN, 3)                                     \
    _(XR_OBJECT_TYPE_SPACE, 4)                                         \
    _(XR_OBJECT_TYPE_ACTION_SET, 5)                                    \
    _(XR_OBJECT_TYPE_ACTION, 6)                                        \
    _(XR_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT, 1000019000)            \
    _(XR_OBJECT_TYPE_SPATIAL_ANCHOR_MSFT, 1000039000)                  \
    _(XR_OBJECT_TYPE_SPATIAL_GRAPH_NODE_BINDING_MSFT, 1000049000)      \
    _(XR_OBJECT_TYPE_HAND_TRACKER_EXT, 1000051000)                     \
    _(XR_OBJECT_TYPE_BODY_TRACKER_FB, 1000076000)                      \
    _(XR_OBJECT_TYPE_SCENE_OBSERVER_MSFT, 1000097000)                  \
    _(XR_OBJECT_TYPE_SCENE_MSFT, 1000097001)                           \
    _(XR_OBJECT_TYPE_FACIAL_TRACKER_HTC, 1000104000)                   \
    _(XR_OBJECT_TYPE_FOVEATION_PROFILE_FB, 1000114000)                 \
    _(XR_OBJECT_TYPE_TRIANGLE_MESH_FB, 1000117000)                     \
    _(XR_OBJECT_TYPE_PASSTHROUGH_FB, 1000118000)                       \
    _(XR_OBJECT_TYPE_PASSTHROUGH_LAYER_FB, 1000118002)                 \
    _(XR_OBJECT_TYPE_GEOMETRY_INSTANCE_FB, 1000118004)                 \
    _(XR_OBJECT_TYPE_MARKER_DETECTOR_ML, 1000138000)                   \
    _(XR_OBJECT_TYPE_EXPORTED_LOCALIZATION_MAP_ML, 1000139000)         \
    _(XR_OBJECT_TYPE_SPATIAL_ANCHOR_STORE_CONNECTION_MSFT, 1000142000) \
    _(XR_OBJECT_TYPE_FACE_TRACKER_FB, 1000201000)                      \
    _(XR_OBJECT_TYPE_EYE_TRACKER_FB, 1000202000)                       \
    _(XR_OBJECT_TYPE_VIRTUAL_KEYBOARD_META, 1000219000)                \
    _(XR_OBJECT_TYPE_SPACE_USER_FB, 1000241000)                        \
    _(XR_OBJECT_TYPE_PASSTHROUGH_COLOR_LUT_META, 1000266000)           \
    _(XR_OBJECT_TYPE_FACE_TRACKER2_FB, 1000287012)                     \
    _(XR_OBJECT_TYPE_ENVIRONMENT_DEPTH_PROVIDER_META, 1000291000)      \
    _(XR_OBJECT_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_META, 1000291001)     \
    _(XR_OBJECT_TYPE_PASSTHROUGH_HTC, 1000317000)                      \
    _(XR_OBJECT_TYPE_PLANE_DETECTOR_EXT, 1000429000)                   \
    _(XR_OBJECT_TYPE_MAX_ENUM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrLoaderInterfaceStructs(_)           \
    _(XR_LOADER_INTERFACE_STRUCT_UNINTIALIZED, 0)          \
    _(XR_LOADER_INTERFACE_STRUCT_LOADER_INFO, 1)           \
    _(XR_LOADER_INTERFACE_STRUCT_API_LAYER_REQUEST, 2)     \
    _(XR_LOADER_INTERFACE_STRUCT_RUNTIME_REQUEST, 3)       \
    _(XR_LOADER_INTERFACE_STRUCT_API_LAYER_CREATE_INFO, 4) \
    _(XR_LOADER_INTERFACE_STRUCT_API_LAYER_NEXT_INFO, 5)   \
    _(XR_LOADER_INTERFACE_STRUCTS_MAX_ENUM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrAndroidThreadTypeKHR(_)          \
    _(XR_ANDROID_THREAD_TYPE_APPLICATION_MAIN_KHR, 1)   \
    _(XR_ANDROID_THREAD_TYPE_APPLICATION_WORKER_KHR, 2) \
    _(XR_ANDROID_THREAD_TYPE_RENDERER_MAIN_KHR, 3)      \
    _(XR_ANDROID_THREAD_TYPE_RENDERER_WORKER_KHR, 4)    \
    _(XR_ANDROID_THREAD_TYPE_MAX_ENUM_KHR, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrVisibilityMaskTypeKHR(_)             \
    _(XR_VISIBILITY_MASK_TYPE_HIDDEN_TRIANGLE_MESH_KHR, 1)  \
    _(XR_VISIBILITY_MASK_TYPE_VISIBLE_TRIANGLE_MESH_KHR, 2) \
    _(XR_VISIBILITY_MASK_TYPE_LINE_LOOP_KHR, 3)             \
    _(XR_VISIBILITY_MASK_TYPE_MAX_ENUM_KHR, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrPerfSettingsDomainEXT(_) \
    _(XR_PERF_SETTINGS_DOMAIN_CPU_EXT, 1)       \
    _(XR_PERF_SETTINGS_DOMAIN_GPU_EXT, 2)       \
    _(XR_PERF_SETTINGS_DOMAIN_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrPerfSettingsSubDomainEXT(_)    \
    _(XR_PERF_SETTINGS_SUB_DOMAIN_COMPOSITING_EXT, 1) \
    _(XR_PERF_SETTINGS_SUB_DOMAIN_RENDERING_EXT, 2)   \
    _(XR_PERF_SETTINGS_SUB_DOMAIN_THERMAL_EXT, 3)     \
    _(XR_PERF_SETTINGS_SUB_DOMAIN_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrPerfSettingsLevelEXT(_)       \
    _(XR_PERF_SETTINGS_LEVEL_POWER_SAVINGS_EXT, 0)   \
    _(XR_PERF_SETTINGS_LEVEL_SUSTAINED_LOW_EXT, 25)  \
    _(XR_PERF_SETTINGS_LEVEL_SUSTAINED_HIGH_EXT, 50) \
    _(XR_PERF_SETTINGS_LEVEL_BOOST_EXT, 75)          \
    _(XR_PERF_SETTINGS_LEVEL_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrPerfSettingsNotificationLevelEXT(_) \
    _(XR_PERF_SETTINGS_NOTIF_LEVEL_NORMAL_EXT, 0)          \
    _(XR_PERF_SETTINGS_NOTIF_LEVEL_WARNING_EXT, 25)        \
    _(XR_PERF_SETTINGS_NOTIF_LEVEL_IMPAIRED_EXT, 75)       \
    _(XR_PERF_SETTINGS_NOTIFICATION_LEVEL_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrBlendFactorFB(_)          \
    _(XR_BLEND_FACTOR_ZERO_FB, 0)                \
    _(XR_BLEND_FACTOR_ONE_FB, 1)                 \
    _(XR_BLEND_FACTOR_SRC_ALPHA_FB, 2)           \
    _(XR_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA_FB, 3) \
    _(XR_BLEND_FACTOR_DST_ALPHA_FB, 4)           \
    _(XR_BLEND_FACTOR_ONE_MINUS_DST_ALPHA_FB, 5) \
    _(XR_BLEND_FACTOR_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSpatialGraphNodeTypeMSFT(_) \
    _(XR_SPATIAL_GRAPH_NODE_TYPE_STATIC_MSFT, 1)   \
    _(XR_SPATIAL_GRAPH_NODE_TYPE_DYNAMIC_MSFT, 2)  \
    _(XR_SPATIAL_GRAPH_NODE_TYPE_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrHandEXT(_) \
    _(XR_HAND_LEFT_EXT, 1)        \
    _(XR_HAND_RIGHT_EXT, 2)       \
    _(XR_HAND_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrHandJointEXT(_)           \
    _(XR_HAND_JOINT_PALM_EXT, 0)                 \
    _(XR_HAND_JOINT_WRIST_EXT, 1)                \
    _(XR_HAND_JOINT_THUMB_METACARPAL_EXT, 2)     \
    _(XR_HAND_JOINT_THUMB_PROXIMAL_EXT, 3)       \
    _(XR_HAND_JOINT_THUMB_DISTAL_EXT, 4)         \
    _(XR_HAND_JOINT_THUMB_TIP_EXT, 5)            \
    _(XR_HAND_JOINT_INDEX_METACARPAL_EXT, 6)     \
    _(XR_HAND_JOINT_INDEX_PROXIMAL_EXT, 7)       \
    _(XR_HAND_JOINT_INDEX_INTERMEDIATE_EXT, 8)   \
    _(XR_HAND_JOINT_INDEX_DISTAL_EXT, 9)         \
    _(XR_HAND_JOINT_INDEX_TIP_EXT, 10)           \
    _(XR_HAND_JOINT_MIDDLE_METACARPAL_EXT, 11)   \
    _(XR_HAND_JOINT_MIDDLE_PROXIMAL_EXT, 12)     \
    _(XR_HAND_JOINT_MIDDLE_INTERMEDIATE_EXT, 13) \
    _(XR_HAND_JOINT_MIDDLE_DISTAL_EXT, 14)       \
    _(XR_HAND_JOINT_MIDDLE_TIP_EXT, 15)          \
    _(XR_HAND_JOINT_RING_METACARPAL_EXT, 16)     \
    _(XR_HAND_JOINT_RING_PROXIMAL_EXT, 17)       \
    _(XR_HAND_JOINT_RING_INTERMEDIATE_EXT, 18)   \
    _(XR_HAND_JOINT_RING_DISTAL_EXT, 19)         \
    _(XR_HAND_JOINT_RING_TIP_EXT, 20)            \
    _(XR_HAND_JOINT_LITTLE_METACARPAL_EXT, 21)   \
    _(XR_HAND_JOINT_LITTLE_PROXIMAL_EXT, 22)     \
    _(XR_HAND_JOINT_LITTLE_INTERMEDIATE_EXT, 23) \
    _(XR_HAND_JOINT_LITTLE_DISTAL_EXT, 24)       \
    _(XR_HAND_JOINT_LITTLE_TIP_EXT, 25)          \
    _(XR_HAND_JOINT_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrHandJointSetEXT(_)                        \
    _(XR_HAND_JOINT_SET_DEFAULT_EXT, 0)                          \
    _(XR_HAND_JOINT_SET_HAND_WITH_FOREARM_ULTRALEAP, 1000149000) \
    _(XR_HAND_JOINT_SET_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrHandPoseTypeMSFT(_)           \
    _(XR_HAND_POSE_TYPE_TRACKED_MSFT, 0)             \
    _(XR_HAND_POSE_TYPE_REFERENCE_OPEN_PALM_MSFT, 1) \
    _(XR_HAND_POSE_TYPE_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrReprojectionModeMSFT(_)        \
    _(XR_REPROJECTION_MODE_DEPTH_MSFT, 1)             \
    _(XR_REPROJECTION_MODE_PLANAR_FROM_DEPTH_MSFT, 2) \
    _(XR_REPROJECTION_MODE_PLANAR_MANUAL_MSFT, 3)     \
    _(XR_REPROJECTION_MODE_ORIENTATION_ONLY_MSFT, 4)  \
    _(XR_REPROJECTION_MODE_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrBodyJointFB(_)                      \
    _(XR_BODY_JOINT_ROOT_FB, 0)                            \
    _(XR_BODY_JOINT_HIPS_FB, 1)                            \
    _(XR_BODY_JOINT_SPINE_LOWER_FB, 2)                     \
    _(XR_BODY_JOINT_SPINE_MIDDLE_FB, 3)                    \
    _(XR_BODY_JOINT_SPINE_UPPER_FB, 4)                     \
    _(XR_BODY_JOINT_CHEST_FB, 5)                           \
    _(XR_BODY_JOINT_NECK_FB, 6)                            \
    _(XR_BODY_JOINT_HEAD_FB, 7)                            \
    _(XR_BODY_JOINT_LEFT_SHOULDER_FB, 8)                   \
    _(XR_BODY_JOINT_LEFT_SCAPULA_FB, 9)                    \
    _(XR_BODY_JOINT_LEFT_ARM_UPPER_FB, 10)                 \
    _(XR_BODY_JOINT_LEFT_ARM_LOWER_FB, 11)                 \
    _(XR_BODY_JOINT_LEFT_HAND_WRIST_TWIST_FB, 12)          \
    _(XR_BODY_JOINT_RIGHT_SHOULDER_FB, 13)                 \
    _(XR_BODY_JOINT_RIGHT_SCAPULA_FB, 14)                  \
    _(XR_BODY_JOINT_RIGHT_ARM_UPPER_FB, 15)                \
    _(XR_BODY_JOINT_RIGHT_ARM_LOWER_FB, 16)                \
    _(XR_BODY_JOINT_RIGHT_HAND_WRIST_TWIST_FB, 17)         \
    _(XR_BODY_JOINT_LEFT_HAND_PALM_FB, 18)                 \
    _(XR_BODY_JOINT_LEFT_HAND_WRIST_FB, 19)                \
    _(XR_BODY_JOINT_LEFT_HAND_THUMB_METACARPAL_FB, 20)     \
    _(XR_BODY_JOINT_LEFT_HAND_THUMB_PROXIMAL_FB, 21)       \
    _(XR_BODY_JOINT_LEFT_HAND_THUMB_DISTAL_FB, 22)         \
    _(XR_BODY_JOINT_LEFT_HAND_THUMB_TIP_FB, 23)            \
    _(XR_BODY_JOINT_LEFT_HAND_INDEX_METACARPAL_FB, 24)     \
    _(XR_BODY_JOINT_LEFT_HAND_INDEX_PROXIMAL_FB, 25)       \
    _(XR_BODY_JOINT_LEFT_HAND_INDEX_INTERMEDIATE_FB, 26)   \
    _(XR_BODY_JOINT_LEFT_HAND_INDEX_DISTAL_FB, 27)         \
    _(XR_BODY_JOINT_LEFT_HAND_INDEX_TIP_FB, 28)            \
    _(XR_BODY_JOINT_LEFT_HAND_MIDDLE_METACARPAL_FB, 29)    \
    _(XR_BODY_JOINT_LEFT_HAND_MIDDLE_PROXIMAL_FB, 30)      \
    _(XR_BODY_JOINT_LEFT_HAND_MIDDLE_INTERMEDIATE_FB, 31)  \
    _(XR_BODY_JOINT_LEFT_HAND_MIDDLE_DISTAL_FB, 32)        \
    _(XR_BODY_JOINT_LEFT_HAND_MIDDLE_TIP_FB, 33)           \
    _(XR_BODY_JOINT_LEFT_HAND_RING_METACARPAL_FB, 34)      \
    _(XR_BODY_JOINT_LEFT_HAND_RING_PROXIMAL_FB, 35)        \
    _(XR_BODY_JOINT_LEFT_HAND_RING_INTERMEDIATE_FB, 36)    \
    _(XR_BODY_JOINT_LEFT_HAND_RING_DISTAL_FB, 37)          \
    _(XR_BODY_JOINT_LEFT_HAND_RING_TIP_FB, 38)             \
    _(XR_BODY_JOINT_LEFT_HAND_LITTLE_METACARPAL_FB, 39)    \
    _(XR_BODY_JOINT_LEFT_HAND_LITTLE_PROXIMAL_FB, 40)      \
    _(XR_BODY_JOINT_LEFT_HAND_LITTLE_INTERMEDIATE_FB, 41)  \
    _(XR_BODY_JOINT_LEFT_HAND_LITTLE_DISTAL_FB, 42)        \
    _(XR_BODY_JOINT_LEFT_HAND_LITTLE_TIP_FB, 43)           \
    _(XR_BODY_JOINT_RIGHT_HAND_PALM_FB, 44)                \
    _(XR_BODY_JOINT_RIGHT_HAND_WRIST_FB, 45)               \
    _(XR_BODY_JOINT_RIGHT_HAND_THUMB_METACARPAL_FB, 46)    \
    _(XR_BODY_JOINT_RIGHT_HAND_THUMB_PROXIMAL_FB, 47)      \
    _(XR_BODY_JOINT_RIGHT_HAND_THUMB_DISTAL_FB, 48)        \
    _(XR_BODY_JOINT_RIGHT_HAND_THUMB_TIP_FB, 49)           \
    _(XR_BODY_JOINT_RIGHT_HAND_INDEX_METACARPAL_FB, 50)    \
    _(XR_BODY_JOINT_RIGHT_HAND_INDEX_PROXIMAL_FB, 51)      \
    _(XR_BODY_JOINT_RIGHT_HAND_INDEX_INTERMEDIATE_FB, 52)  \
    _(XR_BODY_JOINT_RIGHT_HAND_INDEX_DISTAL_FB, 53)        \
    _(XR_BODY_JOINT_RIGHT_HAND_INDEX_TIP_FB, 54)           \
    _(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_METACARPAL_FB, 55)   \
    _(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_PROXIMAL_FB, 56)     \
    _(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_INTERMEDIATE_FB, 57) \
    _(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_DISTAL_FB, 58)       \
    _(XR_BODY_JOINT_RIGHT_HAND_MIDDLE_TIP_FB, 59)          \
    _(XR_BODY_JOINT_RIGHT_HAND_RING_METACARPAL_FB, 60)     \
    _(XR_BODY_JOINT_RIGHT_HAND_RING_PROXIMAL_FB, 61)       \
    _(XR_BODY_JOINT_RIGHT_HAND_RING_INTERMEDIATE_FB, 62)   \
    _(XR_BODY_JOINT_RIGHT_HAND_RING_DISTAL_FB, 63)         \
    _(XR_BODY_JOINT_RIGHT_HAND_RING_TIP_FB, 64)            \
    _(XR_BODY_JOINT_RIGHT_HAND_LITTLE_METACARPAL_FB, 65)   \
    _(XR_BODY_JOINT_RIGHT_HAND_LITTLE_PROXIMAL_FB, 66)     \
    _(XR_BODY_JOINT_RIGHT_HAND_LITTLE_INTERMEDIATE_FB, 67) \
    _(XR_BODY_JOINT_RIGHT_HAND_LITTLE_DISTAL_FB, 68)       \
    _(XR_BODY_JOINT_RIGHT_HAND_LITTLE_TIP_FB, 69)          \
    _(XR_BODY_JOINT_COUNT_FB, 70)                          \
    _(XR_BODY_JOINT_NONE_FB, -1)                           \
    _(XR_BODY_JOINT_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrBodyJointSetFB(_) \
    _(XR_BODY_JOINT_SET_DEFAULT_FB, 0)   \
    _(XR_BODY_JOINT_SET_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrHandJointsMotionRangeEXT(_)                 \
    _(XR_HAND_JOINTS_MOTION_RANGE_UNOBSTRUCTED_EXT, 1)             \
    _(XR_HAND_JOINTS_MOTION_RANGE_CONFORMING_TO_CONTROLLER_EXT, 2) \
    _(XR_HAND_JOINTS_MOTION_RANGE_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSceneComputeFeatureMSFT(_)                \
    _(XR_SCENE_COMPUTE_FEATURE_PLANE_MSFT, 1)                    \
    _(XR_SCENE_COMPUTE_FEATURE_PLANE_MESH_MSFT, 2)               \
    _(XR_SCENE_COMPUTE_FEATURE_VISUAL_MESH_MSFT, 3)              \
    _(XR_SCENE_COMPUTE_FEATURE_COLLIDER_MESH_MSFT, 4)            \
    _(XR_SCENE_COMPUTE_FEATURE_SERIALIZE_SCENE_MSFT, 1000098000) \
    _(XR_SCENE_COMPUTE_FEATURE_MARKER_MSFT, 1000147000)          \
    _(XR_SCENE_COMPUTE_FEATURE_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSceneComputeConsistencyMSFT(_)                \
    _(XR_SCENE_COMPUTE_CONSISTENCY_SNAPSHOT_COMPLETE_MSFT, 1)        \
    _(XR_SCENE_COMPUTE_CONSISTENCY_SNAPSHOT_INCOMPLETE_FAST_MSFT, 2) \
    _(XR_SCENE_COMPUTE_CONSISTENCY_OCCLUSION_OPTIMIZED_MSFT, 3)      \
    _(XR_SCENE_COMPUTE_CONSISTENCY_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrMeshComputeLodMSFT(_) \
    _(XR_MESH_COMPUTE_LOD_COARSE_MSFT, 1)    \
    _(XR_MESH_COMPUTE_LOD_MEDIUM_MSFT, 2)    \
    _(XR_MESH_COMPUTE_LOD_FINE_MSFT, 3)      \
    _(XR_MESH_COMPUTE_LOD_UNLIMITED_MSFT, 4) \
    _(XR_MESH_COMPUTE_LOD_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSceneComponentTypeMSFT(_)                          \
    _(XR_SCENE_COMPONENT_TYPE_INVALID_MSFT, -1)                           \
    _(XR_SCENE_COMPONENT_TYPE_OBJECT_MSFT, 1)                             \
    _(XR_SCENE_COMPONENT_TYPE_PLANE_MSFT, 2)                              \
    _(XR_SCENE_COMPONENT_TYPE_VISUAL_MESH_MSFT, 3)                        \
    _(XR_SCENE_COMPONENT_TYPE_COLLIDER_MESH_MSFT, 4)                      \
    _(XR_SCENE_COMPONENT_TYPE_SERIALIZED_SCENE_FRAGMENT_MSFT, 1000098000) \
    _(XR_SCENE_COMPONENT_TYPE_MARKER_MSFT, 1000147000)                    \
    _(XR_SCENE_COMPONENT_TYPE_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSceneObjectTypeMSFT(_)      \
    _(XR_SCENE_OBJECT_TYPE_UNCATEGORIZED_MSFT, -1) \
    _(XR_SCENE_OBJECT_TYPE_BACKGROUND_MSFT, 1)     \
    _(XR_SCENE_OBJECT_TYPE_WALL_MSFT, 2)           \
    _(XR_SCENE_OBJECT_TYPE_FLOOR_MSFT, 3)          \
    _(XR_SCENE_OBJECT_TYPE_CEILING_MSFT, 4)        \
    _(XR_SCENE_OBJECT_TYPE_PLATFORM_MSFT, 5)       \
    _(XR_SCENE_OBJECT_TYPE_INFERRED_MSFT, 6)       \
    _(XR_SCENE_OBJECT_TYPE_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrScenePlaneAlignmentTypeMSFT(_)       \
    _(XR_SCENE_PLANE_ALIGNMENT_TYPE_NON_ORTHOGONAL_MSFT, 0) \
    _(XR_SCENE_PLANE_ALIGNMENT_TYPE_HORIZONTAL_MSFT, 1)     \
    _(XR_SCENE_PLANE_ALIGNMENT_TYPE_VERTICAL_MSFT, 2)       \
    _(XR_SCENE_PLANE_ALIGNMENT_TYPE_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSceneComputeStateMSFT(_)            \
    _(XR_SCENE_COMPUTE_STATE_NONE_MSFT, 0)                 \
    _(XR_SCENE_COMPUTE_STATE_UPDATING_MSFT, 1)             \
    _(XR_SCENE_COMPUTE_STATE_COMPLETED_MSFT, 2)            \
    _(XR_SCENE_COMPUTE_STATE_COMPLETED_WITH_ERROR_MSFT, 3) \
    _(XR_SCENE_COMPUTE_STATE_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrEyeExpressionHTC(_)    \
    _(XR_EYE_EXPRESSION_LEFT_BLINK_HTC, 0)    \
    _(XR_EYE_EXPRESSION_LEFT_WIDE_HTC, 1)     \
    _(XR_EYE_EXPRESSION_RIGHT_BLINK_HTC, 2)   \
    _(XR_EYE_EXPRESSION_RIGHT_WIDE_HTC, 3)    \
    _(XR_EYE_EXPRESSION_LEFT_SQUEEZE_HTC, 4)  \
    _(XR_EYE_EXPRESSION_RIGHT_SQUEEZE_HTC, 5) \
    _(XR_EYE_EXPRESSION_LEFT_DOWN_HTC, 6)     \
    _(XR_EYE_EXPRESSION_RIGHT_DOWN_HTC, 7)    \
    _(XR_EYE_EXPRESSION_LEFT_OUT_HTC, 8)      \
    _(XR_EYE_EXPRESSION_RIGHT_IN_HTC, 9)      \
    _(XR_EYE_EXPRESSION_LEFT_IN_HTC, 10)      \
    _(XR_EYE_EXPRESSION_RIGHT_OUT_HTC, 11)    \
    _(XR_EYE_EXPRESSION_LEFT_UP_HTC, 12)      \
    _(XR_EYE_EXPRESSION_RIGHT_UP_HTC, 13)     \
    _(XR_EYE_EXPRESSION_MAX_ENUM_HTC, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrLipExpressionHTC(_)              \
    _(XR_LIP_EXPRESSION_JAW_RIGHT_HTC, 0)               \
    _(XR_LIP_EXPRESSION_JAW_LEFT_HTC, 1)                \
    _(XR_LIP_EXPRESSION_JAW_FORWARD_HTC, 2)             \
    _(XR_LIP_EXPRESSION_JAW_OPEN_HTC, 3)                \
    _(XR_LIP_EXPRESSION_MOUTH_APE_SHAPE_HTC, 4)         \
    _(XR_LIP_EXPRESSION_MOUTH_UPPER_RIGHT_HTC, 5)       \
    _(XR_LIP_EXPRESSION_MOUTH_UPPER_LEFT_HTC, 6)        \
    _(XR_LIP_EXPRESSION_MOUTH_LOWER_RIGHT_HTC, 7)       \
    _(XR_LIP_EXPRESSION_MOUTH_LOWER_LEFT_HTC, 8)        \
    _(XR_LIP_EXPRESSION_MOUTH_UPPER_OVERTURN_HTC, 9)    \
    _(XR_LIP_EXPRESSION_MOUTH_LOWER_OVERTURN_HTC, 10)   \
    _(XR_LIP_EXPRESSION_MOUTH_POUT_HTC, 11)             \
    _(XR_LIP_EXPRESSION_MOUTH_SMILE_RIGHT_HTC, 12)      \
    _(XR_LIP_EXPRESSION_MOUTH_SMILE_LEFT_HTC, 13)       \
    _(XR_LIP_EXPRESSION_MOUTH_SAD_RIGHT_HTC, 14)        \
    _(XR_LIP_EXPRESSION_MOUTH_SAD_LEFT_HTC, 15)         \
    _(XR_LIP_EXPRESSION_CHEEK_PUFF_RIGHT_HTC, 16)       \
    _(XR_LIP_EXPRESSION_CHEEK_PUFF_LEFT_HTC, 17)        \
    _(XR_LIP_EXPRESSION_CHEEK_SUCK_HTC, 18)             \
    _(XR_LIP_EXPRESSION_MOUTH_UPPER_UPRIGHT_HTC, 19)    \
    _(XR_LIP_EXPRESSION_MOUTH_UPPER_UPLEFT_HTC, 20)     \
    _(XR_LIP_EXPRESSION_MOUTH_LOWER_DOWNRIGHT_HTC, 21)  \
    _(XR_LIP_EXPRESSION_MOUTH_LOWER_DOWNLEFT_HTC, 22)   \
    _(XR_LIP_EXPRESSION_MOUTH_UPPER_INSIDE_HTC, 23)     \
    _(XR_LIP_EXPRESSION_MOUTH_LOWER_INSIDE_HTC, 24)     \
    _(XR_LIP_EXPRESSION_MOUTH_LOWER_OVERLAY_HTC, 25)    \
    _(XR_LIP_EXPRESSION_TONGUE_LONGSTEP1_HTC, 26)       \
    _(XR_LIP_EXPRESSION_TONGUE_LEFT_HTC, 27)            \
    _(XR_LIP_EXPRESSION_TONGUE_RIGHT_HTC, 28)           \
    _(XR_LIP_EXPRESSION_TONGUE_UP_HTC, 29)              \
    _(XR_LIP_EXPRESSION_TONGUE_DOWN_HTC, 30)            \
    _(XR_LIP_EXPRESSION_TONGUE_ROLL_HTC, 31)            \
    _(XR_LIP_EXPRESSION_TONGUE_LONGSTEP2_HTC, 32)       \
    _(XR_LIP_EXPRESSION_TONGUE_UPRIGHT_MORPH_HTC, 33)   \
    _(XR_LIP_EXPRESSION_TONGUE_UPLEFT_MORPH_HTC, 34)    \
    _(XR_LIP_EXPRESSION_TONGUE_DOWNRIGHT_MORPH_HTC, 35) \
    _(XR_LIP_EXPRESSION_TONGUE_DOWNLEFT_MORPH_HTC, 36)  \
    _(XR_LIP_EXPRESSION_MAX_ENUM_HTC, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFacialTrackingTypeHTC(_)   \
    _(XR_FACIAL_TRACKING_TYPE_EYE_DEFAULT_HTC, 1) \
    _(XR_FACIAL_TRACKING_TYPE_LIP_DEFAULT_HTC, 2) \
    _(XR_FACIAL_TRACKING_TYPE_MAX_ENUM_HTC, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrColorSpaceFB(_) \
    _(XR_COLOR_SPACE_UNMANAGED_FB, 0)  \
    _(XR_COLOR_SPACE_REC2020_FB, 1)    \
    _(XR_COLOR_SPACE_REC709_FB, 2)     \
    _(XR_COLOR_SPACE_RIFT_CV1_FB, 3)   \
    _(XR_COLOR_SPACE_RIFT_S_FB, 4)     \
    _(XR_COLOR_SPACE_QUEST_FB, 5)      \
    _(XR_COLOR_SPACE_P3_FB, 6)         \
    _(XR_COLOR_SPACE_ADOBE_RGB_FB, 7)  \
    _(XR_COLOR_SPACE_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSpaceComponentTypeFB(_)                \
    _(XR_SPACE_COMPONENT_TYPE_LOCATABLE_FB, 0)                \
    _(XR_SPACE_COMPONENT_TYPE_STORABLE_FB, 1)                 \
    _(XR_SPACE_COMPONENT_TYPE_SHARABLE_FB, 2)                 \
    _(XR_SPACE_COMPONENT_TYPE_BOUNDED_2D_FB, 3)               \
    _(XR_SPACE_COMPONENT_TYPE_BOUNDED_3D_FB, 4)               \
    _(XR_SPACE_COMPONENT_TYPE_SEMANTIC_LABELS_FB, 5)          \
    _(XR_SPACE_COMPONENT_TYPE_ROOM_LAYOUT_FB, 6)              \
    _(XR_SPACE_COMPONENT_TYPE_SPACE_CONTAINER_FB, 7)          \
    _(XR_SPACE_COMPONENT_TYPE_TRIANGLE_MESH_META, 1000269000) \
    _(XR_SPACE_COMPONENT_TYPE_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFoveationLevelFB(_) \
    _(XR_FOVEATION_LEVEL_NONE_FB, 0)       \
    _(XR_FOVEATION_LEVEL_LOW_FB, 1)        \
    _(XR_FOVEATION_LEVEL_MEDIUM_FB, 2)     \
    _(XR_FOVEATION_LEVEL_HIGH_FB, 3)       \
    _(XR_FOVEATION_LEVEL_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFoveationDynamicFB(_)    \
    _(XR_FOVEATION_DYNAMIC_DISABLED_FB, 0)      \
    _(XR_FOVEATION_DYNAMIC_LEVEL_ENABLED_FB, 1) \
    _(XR_FOVEATION_DYNAMIC_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrWindingOrderFB(_) \
    _(XR_WINDING_ORDER_UNKNOWN_FB, 0)    \
    _(XR_WINDING_ORDER_CW_FB, 1)         \
    _(XR_WINDING_ORDER_CCW_FB, 2)        \
    _(XR_WINDING_ORDER_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrPassthroughLayerPurposeFB(_)                              \
    _(XR_PASSTHROUGH_LAYER_PURPOSE_RECONSTRUCTION_FB, 0)                         \
    _(XR_PASSTHROUGH_LAYER_PURPOSE_PROJECTED_FB, 1)                              \
    _(XR_PASSTHROUGH_LAYER_PURPOSE_TRACKED_KEYBOARD_HANDS_FB, 1000203001)        \
    _(XR_PASSTHROUGH_LAYER_PURPOSE_TRACKED_KEYBOARD_MASKED_HANDS_FB, 1000203002) \
    _(XR_PASSTHROUGH_LAYER_PURPOSE_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrMarkerDetectorProfileML(_)     \
    _(XR_MARKER_DETECTOR_PROFILE_DEFAULT_ML, 0)       \
    _(XR_MARKER_DETECTOR_PROFILE_SPEED_ML, 1)         \
    _(XR_MARKER_DETECTOR_PROFILE_ACCURACY_ML, 2)      \
    _(XR_MARKER_DETECTOR_PROFILE_SMALL_TARGETS_ML, 3) \
    _(XR_MARKER_DETECTOR_PROFILE_LARGE_FOV_ML, 4)     \
    _(XR_MARKER_DETECTOR_PROFILE_CUSTOM_ML, 5)        \
    _(XR_MARKER_DETECTOR_PROFILE_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrMarkerTypeML(_) \
    _(XR_MARKER_TYPE_ARUCO_ML, 0)      \
    _(XR_MARKER_TYPE_APRIL_TAG_ML, 1)  \
    _(XR_MARKER_TYPE_QR_ML, 2)         \
    _(XR_MARKER_TYPE_EAN_13_ML, 3)     \
    _(XR_MARKER_TYPE_UPC_A_ML, 4)      \
    _(XR_MARKER_TYPE_CODE_128_ML, 5)   \
    _(XR_MARKER_TYPE_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrMarkerArucoDictML(_) \
    _(XR_MARKER_ARUCO_DICT_4X4_50_ML, 0)    \
    _(XR_MARKER_ARUCO_DICT_4X4_100_ML, 1)   \
    _(XR_MARKER_ARUCO_DICT_4X4_250_ML, 2)   \
    _(XR_MARKER_ARUCO_DICT_4X4_1000_ML, 3)  \
    _(XR_MARKER_ARUCO_DICT_5X5_50_ML, 4)    \
    _(XR_MARKER_ARUCO_DICT_5X5_100_ML, 5)   \
    _(XR_MARKER_ARUCO_DICT_5X5_250_ML, 6)   \
    _(XR_MARKER_ARUCO_DICT_5X5_1000_ML, 7)  \
    _(XR_MARKER_ARUCO_DICT_6X6_50_ML, 8)    \
    _(XR_MARKER_ARUCO_DICT_6X6_100_ML, 9)   \
    _(XR_MARKER_ARUCO_DICT_6X6_250_ML, 10)  \
    _(XR_MARKER_ARUCO_DICT_6X6_1000_ML, 11) \
    _(XR_MARKER_ARUCO_DICT_7X7_50_ML, 12)   \
    _(XR_MARKER_ARUCO_DICT_7X7_100_ML, 13)  \
    _(XR_MARKER_ARUCO_DICT_7X7_250_ML, 14)  \
    _(XR_MARKER_ARUCO_DICT_7X7_1000_ML, 15) \
    _(XR_MARKER_ARUCO_DICT_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrMarkerAprilTagDictML(_) \
    _(XR_MARKER_APRIL_TAG_DICT_16H5_ML, 0)     \
    _(XR_MARKER_APRIL_TAG_DICT_25H9_ML, 1)     \
    _(XR_MARKER_APRIL_TAG_DICT_36H10_ML, 2)    \
    _(XR_MARKER_APRIL_TAG_DICT_36H11_ML, 3)    \
    _(XR_MARKER_APRIL_TAG_DICT_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrMarkerDetectorFpsML(_) \
    _(XR_MARKER_DETECTOR_FPS_LOW_ML, 0)       \
    _(XR_MARKER_DETECTOR_FPS_MEDIUM_ML, 1)    \
    _(XR_MARKER_DETECTOR_FPS_HIGH_ML, 2)      \
    _(XR_MARKER_DETECTOR_FPS_MAX_ML, 3)       \
    _(XR_MARKER_DETECTOR_FPS_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrMarkerDetectorResolutionML(_) \
    _(XR_MARKER_DETECTOR_RESOLUTION_LOW_ML, 0)       \
    _(XR_MARKER_DETECTOR_RESOLUTION_MEDIUM_ML, 1)    \
    _(XR_MARKER_DETECTOR_RESOLUTION_HIGH_ML, 2)      \
    _(XR_MARKER_DETECTOR_RESOLUTION_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrMarkerDetectorCameraML(_)     \
    _(XR_MARKER_DETECTOR_CAMERA_RGB_CAMERA_ML, 0)    \
    _(XR_MARKER_DETECTOR_CAMERA_WORLD_CAMERAS_ML, 1) \
    _(XR_MARKER_DETECTOR_CAMERA_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrMarkerDetectorCornerRefineMethodML(_)   \
    _(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_NONE_ML, 0)      \
    _(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_SUBPIX_ML, 1)    \
    _(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_CONTOUR_ML, 2)   \
    _(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_APRIL_TAG_ML, 3) \
    _(XR_MARKER_DETECTOR_CORNER_REFINE_METHOD_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrMarkerDetectorFullAnalysisIntervalML(_) \
    _(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MAX_ML, 0)     \
    _(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_FAST_ML, 1)    \
    _(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MEDIUM_ML, 2)  \
    _(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_SLOW_ML, 3)    \
    _(XR_MARKER_DETECTOR_FULL_ANALYSIS_INTERVAL_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrMarkerDetectorStatusML(_) \
    _(XR_MARKER_DETECTOR_STATUS_PENDING_ML, 0)   \
    _(XR_MARKER_DETECTOR_STATUS_READY_ML, 1)     \
    _(XR_MARKER_DETECTOR_STATUS_ERROR_ML, 2)     \
    _(XR_MARKER_DETECTOR_STATUS_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrLocalizationMapStateML(_)                          \
    _(XR_LOCALIZATION_MAP_STATE_NOT_LOCALIZED_ML, 0)                      \
    _(XR_LOCALIZATION_MAP_STATE_LOCALIZED_ML, 1)                          \
    _(XR_LOCALIZATION_MAP_STATE_LOCALIZATION_PENDING_ML, 2)               \
    _(XR_LOCALIZATION_MAP_STATE_LOCALIZATION_SLEEPING_BEFORE_RETRY_ML, 3) \
    _(XR_LOCALIZATION_MAP_STATE_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrLocalizationMapTypeML(_) \
    _(XR_LOCALIZATION_MAP_TYPE_ON_DEVICE_ML, 0) \
    _(XR_LOCALIZATION_MAP_TYPE_CLOUD_ML, 1)     \
    _(XR_LOCALIZATION_MAP_TYPE_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrLocalizationMapConfidenceML(_) \
    _(XR_LOCALIZATION_MAP_CONFIDENCE_POOR_ML, 0)      \
    _(XR_LOCALIZATION_MAP_CONFIDENCE_FAIR_ML, 1)      \
    _(XR_LOCALIZATION_MAP_CONFIDENCE_GOOD_ML, 2)      \
    _(XR_LOCALIZATION_MAP_CONFIDENCE_EXCELLENT_ML, 3) \
    _(XR_LOCALIZATION_MAP_CONFIDENCE_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSceneMarkerTypeMSFT(_) \
    _(XR_SCENE_MARKER_TYPE_QR_CODE_MSFT, 1)   \
    _(XR_SCENE_MARKER_TYPE_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSceneMarkerQRCodeSymbolTypeMSFT(_)        \
    _(XR_SCENE_MARKER_QR_CODE_SYMBOL_TYPE_QR_CODE_MSFT, 1)       \
    _(XR_SCENE_MARKER_QR_CODE_SYMBOL_TYPE_MICRO_QR_CODE_MSFT, 2) \
    _(XR_SCENE_MARKER_QRCODE_SYMBOL_TYPE_MAX_ENUM_MSFT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrHandForearmJointULTRALEAP(_)            \
    _(XR_HAND_FOREARM_JOINT_PALM_ULTRALEAP, 0)                 \
    _(XR_HAND_FOREARM_JOINT_WRIST_ULTRALEAP, 1)                \
    _(XR_HAND_FOREARM_JOINT_THUMB_METACARPAL_ULTRALEAP, 2)     \
    _(XR_HAND_FOREARM_JOINT_THUMB_PROXIMAL_ULTRALEAP, 3)       \
    _(XR_HAND_FOREARM_JOINT_THUMB_DISTAL_ULTRALEAP, 4)         \
    _(XR_HAND_FOREARM_JOINT_THUMB_TIP_ULTRALEAP, 5)            \
    _(XR_HAND_FOREARM_JOINT_INDEX_METACARPAL_ULTRALEAP, 6)     \
    _(XR_HAND_FOREARM_JOINT_INDEX_PROXIMAL_ULTRALEAP, 7)       \
    _(XR_HAND_FOREARM_JOINT_INDEX_INTERMEDIATE_ULTRALEAP, 8)   \
    _(XR_HAND_FOREARM_JOINT_INDEX_DISTAL_ULTRALEAP, 9)         \
    _(XR_HAND_FOREARM_JOINT_INDEX_TIP_ULTRALEAP, 10)           \
    _(XR_HAND_FOREARM_JOINT_MIDDLE_METACARPAL_ULTRALEAP, 11)   \
    _(XR_HAND_FOREARM_JOINT_MIDDLE_PROXIMAL_ULTRALEAP, 12)     \
    _(XR_HAND_FOREARM_JOINT_MIDDLE_INTERMEDIATE_ULTRALEAP, 13) \
    _(XR_HAND_FOREARM_JOINT_MIDDLE_DISTAL_ULTRALEAP, 14)       \
    _(XR_HAND_FOREARM_JOINT_MIDDLE_TIP_ULTRALEAP, 15)          \
    _(XR_HAND_FOREARM_JOINT_RING_METACARPAL_ULTRALEAP, 16)     \
    _(XR_HAND_FOREARM_JOINT_RING_PROXIMAL_ULTRALEAP, 17)       \
    _(XR_HAND_FOREARM_JOINT_RING_INTERMEDIATE_ULTRALEAP, 18)   \
    _(XR_HAND_FOREARM_JOINT_RING_DISTAL_ULTRALEAP, 19)         \
    _(XR_HAND_FOREARM_JOINT_RING_TIP_ULTRALEAP, 20)            \
    _(XR_HAND_FOREARM_JOINT_LITTLE_METACARPAL_ULTRALEAP, 21)   \
    _(XR_HAND_FOREARM_JOINT_LITTLE_PROXIMAL_ULTRALEAP, 22)     \
    _(XR_HAND_FOREARM_JOINT_LITTLE_INTERMEDIATE_ULTRALEAP, 23) \
    _(XR_HAND_FOREARM_JOINT_LITTLE_DISTAL_ULTRALEAP, 24)       \
    _(XR_HAND_FOREARM_JOINT_LITTLE_TIP_ULTRALEAP, 25)          \
    _(XR_HAND_FOREARM_JOINT_ELBOW_ULTRALEAP, 26)               \
    _(XR_HAND_FOREARM_JOINT_MAX_ENUM_ULTRALEAP, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSpaceQueryActionFB(_) \
    _(XR_SPACE_QUERY_ACTION_LOAD_FB, 0)      \
    _(XR_SPACE_QUERY_ACTION_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSpaceStorageLocationFB(_) \
    _(XR_SPACE_STORAGE_LOCATION_INVALID_FB, 0)   \
    _(XR_SPACE_STORAGE_LOCATION_LOCAL_FB, 1)     \
    _(XR_SPACE_STORAGE_LOCATION_CLOUD_FB, 2)     \
    _(XR_SPACE_STORAGE_LOCATION_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrSpacePersistenceModeFB(_)  \
    _(XR_SPACE_PERSISTENCE_MODE_INVALID_FB, 0)    \
    _(XR_SPACE_PERSISTENCE_MODE_INDEFINITE_FB, 1) \
    _(XR_SPACE_PERSISTENCE_MODE_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFaceExpressionFB(_)              \
    _(XR_FACE_EXPRESSION_BROW_LOWERER_L_FB, 0)          \
    _(XR_FACE_EXPRESSION_BROW_LOWERER_R_FB, 1)          \
    _(XR_FACE_EXPRESSION_CHEEK_PUFF_L_FB, 2)            \
    _(XR_FACE_EXPRESSION_CHEEK_PUFF_R_FB, 3)            \
    _(XR_FACE_EXPRESSION_CHEEK_RAISER_L_FB, 4)          \
    _(XR_FACE_EXPRESSION_CHEEK_RAISER_R_FB, 5)          \
    _(XR_FACE_EXPRESSION_CHEEK_SUCK_L_FB, 6)            \
    _(XR_FACE_EXPRESSION_CHEEK_SUCK_R_FB, 7)            \
    _(XR_FACE_EXPRESSION_CHIN_RAISER_B_FB, 8)           \
    _(XR_FACE_EXPRESSION_CHIN_RAISER_T_FB, 9)           \
    _(XR_FACE_EXPRESSION_DIMPLER_L_FB, 10)              \
    _(XR_FACE_EXPRESSION_DIMPLER_R_FB, 11)              \
    _(XR_FACE_EXPRESSION_EYES_CLOSED_L_FB, 12)          \
    _(XR_FACE_EXPRESSION_EYES_CLOSED_R_FB, 13)          \
    _(XR_FACE_EXPRESSION_EYES_LOOK_DOWN_L_FB, 14)       \
    _(XR_FACE_EXPRESSION_EYES_LOOK_DOWN_R_FB, 15)       \
    _(XR_FACE_EXPRESSION_EYES_LOOK_LEFT_L_FB, 16)       \
    _(XR_FACE_EXPRESSION_EYES_LOOK_LEFT_R_FB, 17)       \
    _(XR_FACE_EXPRESSION_EYES_LOOK_RIGHT_L_FB, 18)      \
    _(XR_FACE_EXPRESSION_EYES_LOOK_RIGHT_R_FB, 19)      \
    _(XR_FACE_EXPRESSION_EYES_LOOK_UP_L_FB, 20)         \
    _(XR_FACE_EXPRESSION_EYES_LOOK_UP_R_FB, 21)         \
    _(XR_FACE_EXPRESSION_INNER_BROW_RAISER_L_FB, 22)    \
    _(XR_FACE_EXPRESSION_INNER_BROW_RAISER_R_FB, 23)    \
    _(XR_FACE_EXPRESSION_JAW_DROP_FB, 24)               \
    _(XR_FACE_EXPRESSION_JAW_SIDEWAYS_LEFT_FB, 25)      \
    _(XR_FACE_EXPRESSION_JAW_SIDEWAYS_RIGHT_FB, 26)     \
    _(XR_FACE_EXPRESSION_JAW_THRUST_FB, 27)             \
    _(XR_FACE_EXPRESSION_LID_TIGHTENER_L_FB, 28)        \
    _(XR_FACE_EXPRESSION_LID_TIGHTENER_R_FB, 29)        \
    _(XR_FACE_EXPRESSION_LIP_CORNER_DEPRESSOR_L_FB, 30) \
    _(XR_FACE_EXPRESSION_LIP_CORNER_DEPRESSOR_R_FB, 31) \
    _(XR_FACE_EXPRESSION_LIP_CORNER_PULLER_L_FB, 32)    \
    _(XR_FACE_EXPRESSION_LIP_CORNER_PULLER_R_FB, 33)    \
    _(XR_FACE_EXPRESSION_LIP_FUNNELER_LB_FB, 34)        \
    _(XR_FACE_EXPRESSION_LIP_FUNNELER_LT_FB, 35)        \
    _(XR_FACE_EXPRESSION_LIP_FUNNELER_RB_FB, 36)        \
    _(XR_FACE_EXPRESSION_LIP_FUNNELER_RT_FB, 37)        \
    _(XR_FACE_EXPRESSION_LIP_PRESSOR_L_FB, 38)          \
    _(XR_FACE_EXPRESSION_LIP_PRESSOR_R_FB, 39)          \
    _(XR_FACE_EXPRESSION_LIP_PUCKER_L_FB, 40)           \
    _(XR_FACE_EXPRESSION_LIP_PUCKER_R_FB, 41)           \
    _(XR_FACE_EXPRESSION_LIP_STRETCHER_L_FB, 42)        \
    _(XR_FACE_EXPRESSION_LIP_STRETCHER_R_FB, 43)        \
    _(XR_FACE_EXPRESSION_LIP_SUCK_LB_FB, 44)            \
    _(XR_FACE_EXPRESSION_LIP_SUCK_LT_FB, 45)            \
    _(XR_FACE_EXPRESSION_LIP_SUCK_RB_FB, 46)            \
    _(XR_FACE_EXPRESSION_LIP_SUCK_RT_FB, 47)            \
    _(XR_FACE_EXPRESSION_LIP_TIGHTENER_L_FB, 48)        \
    _(XR_FACE_EXPRESSION_LIP_TIGHTENER_R_FB, 49)        \
    _(XR_FACE_EXPRESSION_LIPS_TOWARD_FB, 50)            \
    _(XR_FACE_EXPRESSION_LOWER_LIP_DEPRESSOR_L_FB, 51)  \
    _(XR_FACE_EXPRESSION_LOWER_LIP_DEPRESSOR_R_FB, 52)  \
    _(XR_FACE_EXPRESSION_MOUTH_LEFT_FB, 53)             \
    _(XR_FACE_EXPRESSION_MOUTH_RIGHT_FB, 54)            \
    _(XR_FACE_EXPRESSION_NOSE_WRINKLER_L_FB, 55)        \
    _(XR_FACE_EXPRESSION_NOSE_WRINKLER_R_FB, 56)        \
    _(XR_FACE_EXPRESSION_OUTER_BROW_RAISER_L_FB, 57)    \
    _(XR_FACE_EXPRESSION_OUTER_BROW_RAISER_R_FB, 58)    \
    _(XR_FACE_EXPRESSION_UPPER_LID_RAISER_L_FB, 59)     \
    _(XR_FACE_EXPRESSION_UPPER_LID_RAISER_R_FB, 60)     \
    _(XR_FACE_EXPRESSION_UPPER_LIP_RAISER_L_FB, 61)     \
    _(XR_FACE_EXPRESSION_UPPER_LIP_RAISER_R_FB, 62)     \
    _(XR_FACE_EXPRESSION_COUNT_FB, 63)                  \
    _(XR_FACE_EXPRESSION_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFaceExpressionSetFB(_) \
    _(XR_FACE_EXPRESSION_SET_DEFAULT_FB, 0)   \
    _(XR_FACE_EXPRESSION_SET_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFaceConfidenceFB(_) \
    _(XR_FACE_CONFIDENCE_LOWER_FACE_FB, 0) \
    _(XR_FACE_CONFIDENCE_UPPER_FACE_FB, 1) \
    _(XR_FACE_CONFIDENCE_COUNT_FB, 2)      \
    _(XR_FACE_CONFIDENCE_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrEyePositionFB(_) \
    _(XR_EYE_POSITION_LEFT_FB, 0)       \
    _(XR_EYE_POSITION_RIGHT_FB, 1)      \
    _(XR_EYE_POSITION_COUNT_FB, 2)      \
    _(XR_EYE_POSITION_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrCompareOpFB(_)       \
    _(XR_COMPARE_OP_NEVER_FB, 0)            \
    _(XR_COMPARE_OP_LESS_FB, 1)             \
    _(XR_COMPARE_OP_EQUAL_FB, 2)            \
    _(XR_COMPARE_OP_LESS_OR_EQUAL_FB, 3)    \
    _(XR_COMPARE_OP_GREATER_FB, 4)          \
    _(XR_COMPARE_OP_NOT_EQUAL_FB, 5)        \
    _(XR_COMPARE_OP_GREATER_OR_EQUAL_FB, 6) \
    _(XR_COMPARE_OP_ALWAYS_FB, 7)           \
    _(XR_COMPARE_OPFB_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrLocalDimmingModeMETA(_) \
    _(XR_LOCAL_DIMMING_MODE_OFF_META, 0)       \
    _(XR_LOCAL_DIMMING_MODE_ON_META, 1)        \
    _(XR_LOCAL_DIMMING_MODE_MAX_ENUM_META, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrVirtualKeyboardLocationTypeMETA(_) \
    _(XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_CUSTOM_META, 0)   \
    _(XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_FAR_META, 1)      \
    _(XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_DIRECT_META, 2)   \
    _(XR_VIRTUAL_KEYBOARD_LOCATION_TYPE_MAX_ENUM_META, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrVirtualKeyboardInputSourceMETA(_)                    \
    _(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_RAY_LEFT_META, 1)         \
    _(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_RAY_RIGHT_META, 2)        \
    _(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_RAY_LEFT_META, 3)               \
    _(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_RAY_RIGHT_META, 4)              \
    _(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_DIRECT_LEFT_META, 5)      \
    _(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_CONTROLLER_DIRECT_RIGHT_META, 6)     \
    _(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_DIRECT_INDEX_TIP_LEFT_META, 7)  \
    _(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_HAND_DIRECT_INDEX_TIP_RIGHT_META, 8) \
    _(XR_VIRTUAL_KEYBOARD_INPUT_SOURCE_MAX_ENUM_META, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrExternalCameraAttachedToDeviceOCULUS(_) \
    _(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_NONE_OCULUS, 0)    \
    _(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_HMD_OCULUS, 1)     \
    _(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_LTOUCH_OCULUS, 2)  \
    _(XR_EXTERNAL_CAMERA_ATTACHED_TO_DEVICE_RTOUCH_OCULUS, 3)  \
    _(XR_EXTERNAL_CAMERA_ATTACHED_TODEVICE_MAX_ENUM_OCULUS, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrPerformanceMetricsCounterUnitMETA(_)     \
    _(XR_PERFORMANCE_METRICS_COUNTER_UNIT_GENERIC_META, 0)      \
    _(XR_PERFORMANCE_METRICS_COUNTER_UNIT_PERCENTAGE_META, 1)   \
    _(XR_PERFORMANCE_METRICS_COUNTER_UNIT_MILLISECONDS_META, 2) \
    _(XR_PERFORMANCE_METRICS_COUNTER_UNIT_BYTES_META, 3)        \
    _(XR_PERFORMANCE_METRICS_COUNTER_UNIT_HERTZ_META, 4)        \
    _(XR_PERFORMANCE_METRICS_COUNTER_UNIT_MAX_ENUM_META, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrPassthroughColorLutChannelsMETA(_) \
    _(XR_PASSTHROUGH_COLOR_LUT_CHANNELS_RGB_META, 1)      \
    _(XR_PASSTHROUGH_COLOR_LUT_CHANNELS_RGBA_META, 2)     \
    _(XR_PASSTHROUGH_COLOR_LUT_CHANNELS_MAX_ENUM_META, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFaceExpression2FB(_)                  \
    _(XR_FACE_EXPRESSION2_BROW_LOWERER_L_FB, 0)              \
    _(XR_FACE_EXPRESSION2_BROW_LOWERER_R_FB, 1)              \
    _(XR_FACE_EXPRESSION2_CHEEK_PUFF_L_FB, 2)                \
    _(XR_FACE_EXPRESSION2_CHEEK_PUFF_R_FB, 3)                \
    _(XR_FACE_EXPRESSION2_CHEEK_RAISER_L_FB, 4)              \
    _(XR_FACE_EXPRESSION2_CHEEK_RAISER_R_FB, 5)              \
    _(XR_FACE_EXPRESSION2_CHEEK_SUCK_L_FB, 6)                \
    _(XR_FACE_EXPRESSION2_CHEEK_SUCK_R_FB, 7)                \
    _(XR_FACE_EXPRESSION2_CHIN_RAISER_B_FB, 8)               \
    _(XR_FACE_EXPRESSION2_CHIN_RAISER_T_FB, 9)               \
    _(XR_FACE_EXPRESSION2_DIMPLER_L_FB, 10)                  \
    _(XR_FACE_EXPRESSION2_DIMPLER_R_FB, 11)                  \
    _(XR_FACE_EXPRESSION2_EYES_CLOSED_L_FB, 12)              \
    _(XR_FACE_EXPRESSION2_EYES_CLOSED_R_FB, 13)              \
    _(XR_FACE_EXPRESSION2_EYES_LOOK_DOWN_L_FB, 14)           \
    _(XR_FACE_EXPRESSION2_EYES_LOOK_DOWN_R_FB, 15)           \
    _(XR_FACE_EXPRESSION2_EYES_LOOK_LEFT_L_FB, 16)           \
    _(XR_FACE_EXPRESSION2_EYES_LOOK_LEFT_R_FB, 17)           \
    _(XR_FACE_EXPRESSION2_EYES_LOOK_RIGHT_L_FB, 18)          \
    _(XR_FACE_EXPRESSION2_EYES_LOOK_RIGHT_R_FB, 19)          \
    _(XR_FACE_EXPRESSION2_EYES_LOOK_UP_L_FB, 20)             \
    _(XR_FACE_EXPRESSION2_EYES_LOOK_UP_R_FB, 21)             \
    _(XR_FACE_EXPRESSION2_INNER_BROW_RAISER_L_FB, 22)        \
    _(XR_FACE_EXPRESSION2_INNER_BROW_RAISER_R_FB, 23)        \
    _(XR_FACE_EXPRESSION2_JAW_DROP_FB, 24)                   \
    _(XR_FACE_EXPRESSION2_JAW_SIDEWAYS_LEFT_FB, 25)          \
    _(XR_FACE_EXPRESSION2_JAW_SIDEWAYS_RIGHT_FB, 26)         \
    _(XR_FACE_EXPRESSION2_JAW_THRUST_FB, 27)                 \
    _(XR_FACE_EXPRESSION2_LID_TIGHTENER_L_FB, 28)            \
    _(XR_FACE_EXPRESSION2_LID_TIGHTENER_R_FB, 29)            \
    _(XR_FACE_EXPRESSION2_LIP_CORNER_DEPRESSOR_L_FB, 30)     \
    _(XR_FACE_EXPRESSION2_LIP_CORNER_DEPRESSOR_R_FB, 31)     \
    _(XR_FACE_EXPRESSION2_LIP_CORNER_PULLER_L_FB, 32)        \
    _(XR_FACE_EXPRESSION2_LIP_CORNER_PULLER_R_FB, 33)        \
    _(XR_FACE_EXPRESSION2_LIP_FUNNELER_LB_FB, 34)            \
    _(XR_FACE_EXPRESSION2_LIP_FUNNELER_LT_FB, 35)            \
    _(XR_FACE_EXPRESSION2_LIP_FUNNELER_RB_FB, 36)            \
    _(XR_FACE_EXPRESSION2_LIP_FUNNELER_RT_FB, 37)            \
    _(XR_FACE_EXPRESSION2_LIP_PRESSOR_L_FB, 38)              \
    _(XR_FACE_EXPRESSION2_LIP_PRESSOR_R_FB, 39)              \
    _(XR_FACE_EXPRESSION2_LIP_PUCKER_L_FB, 40)               \
    _(XR_FACE_EXPRESSION2_LIP_PUCKER_R_FB, 41)               \
    _(XR_FACE_EXPRESSION2_LIP_STRETCHER_L_FB, 42)            \
    _(XR_FACE_EXPRESSION2_LIP_STRETCHER_R_FB, 43)            \
    _(XR_FACE_EXPRESSION2_LIP_SUCK_LB_FB, 44)                \
    _(XR_FACE_EXPRESSION2_LIP_SUCK_LT_FB, 45)                \
    _(XR_FACE_EXPRESSION2_LIP_SUCK_RB_FB, 46)                \
    _(XR_FACE_EXPRESSION2_LIP_SUCK_RT_FB, 47)                \
    _(XR_FACE_EXPRESSION2_LIP_TIGHTENER_L_FB, 48)            \
    _(XR_FACE_EXPRESSION2_LIP_TIGHTENER_R_FB, 49)            \
    _(XR_FACE_EXPRESSION2_LIPS_TOWARD_FB, 50)                \
    _(XR_FACE_EXPRESSION2_LOWER_LIP_DEPRESSOR_L_FB, 51)      \
    _(XR_FACE_EXPRESSION2_LOWER_LIP_DEPRESSOR_R_FB, 52)      \
    _(XR_FACE_EXPRESSION2_MOUTH_LEFT_FB, 53)                 \
    _(XR_FACE_EXPRESSION2_MOUTH_RIGHT_FB, 54)                \
    _(XR_FACE_EXPRESSION2_NOSE_WRINKLER_L_FB, 55)            \
    _(XR_FACE_EXPRESSION2_NOSE_WRINKLER_R_FB, 56)            \
    _(XR_FACE_EXPRESSION2_OUTER_BROW_RAISER_L_FB, 57)        \
    _(XR_FACE_EXPRESSION2_OUTER_BROW_RAISER_R_FB, 58)        \
    _(XR_FACE_EXPRESSION2_UPPER_LID_RAISER_L_FB, 59)         \
    _(XR_FACE_EXPRESSION2_UPPER_LID_RAISER_R_FB, 60)         \
    _(XR_FACE_EXPRESSION2_UPPER_LIP_RAISER_L_FB, 61)         \
    _(XR_FACE_EXPRESSION2_UPPER_LIP_RAISER_R_FB, 62)         \
    _(XR_FACE_EXPRESSION2_TONGUE_TIP_INTERDENTAL_FB, 63)     \
    _(XR_FACE_EXPRESSION2_TONGUE_TIP_ALVEOLAR_FB, 64)        \
    _(XR_FACE_EXPRESSION2_TONGUE_FRONT_DORSAL_PALATE_FB, 65) \
    _(XR_FACE_EXPRESSION2_TONGUE_MID_DORSAL_PALATE_FB, 66)   \
    _(XR_FACE_EXPRESSION2_TONGUE_BACK_DORSAL_VELAR_FB, 67)   \
    _(XR_FACE_EXPRESSION2_TONGUE_OUT_FB, 68)                 \
    _(XR_FACE_EXPRESSION2_TONGUE_RETREAT_FB, 69)             \
    _(XR_FACE_EXPRESSION2_COUNT_FB, 70)                      \
    _(XR_FACE_EXPRESSION_2FB_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFaceExpressionSet2FB(_) \
    _(XR_FACE_EXPRESSION_SET2_DEFAULT_FB, 0)   \
    _(XR_FACE_EXPRESSION_SET_2FB_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFaceTrackingDataSource2FB(_) \
    _(XR_FACE_TRACKING_DATA_SOURCE2_VISUAL_FB, 0)   \
    _(XR_FACE_TRACKING_DATA_SOURCE2_AUDIO_FB, 1)    \
    _(XR_FACE_TRACKING_DATA_SOURCE_2FB_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFaceConfidence2FB(_) \
    _(XR_FACE_CONFIDENCE2_LOWER_FACE_FB, 0) \
    _(XR_FACE_CONFIDENCE2_UPPER_FACE_FB, 1) \
    _(XR_FACE_CONFIDENCE2_COUNT_FB, 2)      \
    _(XR_FACE_CONFIDENCE_2FB_MAX_ENUM_FB, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrTrackingOptimizationSettingsDomainQCOM(_) \
    _(XR_TRACKING_OPTIMIZATION_SETTINGS_DOMAIN_ALL_QCOM, 1)      \
    _(XR_TRACKING_OPTIMIZATION_SETTINGS_DOMAIN_MAX_ENUM_QCOM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrTrackingOptimizationSettingsHintQCOM(_)                 \
    _(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_NONE_QCOM, 0)                     \
    _(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_LONG_RANGE_PRIORIZATION_QCOM, 1)  \
    _(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_CLOSE_RANGE_PRIORIZATION_QCOM, 2) \
    _(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_LOW_POWER_PRIORIZATION_QCOM, 3)   \
    _(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_HIGH_POWER_PRIORIZATION_QCOM, 4)  \
    _(XR_TRACKING_OPTIMIZATION_SETTINGS_HINT_MAX_ENUM_QCOM, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrPassthroughFormHTC(_) \
    _(XR_PASSTHROUGH_FORM_PLANAR_HTC, 0)     \
    _(XR_PASSTHROUGH_FORM_PROJECTED_HTC, 1)  \
    _(XR_PASSTHROUGH_FORM_MAX_ENUM_HTC, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFoveationModeHTC(_) \
    _(XR_FOVEATION_MODE_DISABLE_HTC, 0)    \
    _(XR_FOVEATION_MODE_FIXED_HTC, 1)      \
    _(XR_FOVEATION_MODE_DYNAMIC_HTC, 2)    \
    _(XR_FOVEATION_MODE_CUSTOM_HTC, 3)     \
    _(XR_FOVEATION_MODE_MAX_ENUM_HTC, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFoveationLevelHTC(_) \
    _(XR_FOVEATION_LEVEL_NONE_HTC, 0)       \
    _(XR_FOVEATION_LEVEL_LOW_HTC, 1)        \
    _(XR_FOVEATION_LEVEL_MEDIUM_HTC, 2)     \
    _(XR_FOVEATION_LEVEL_HIGH_HTC, 3)       \
    _(XR_FOVEATION_LEVEL_MAX_ENUM_HTC, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrForceFeedbackCurlLocationMNDX(_)    \
    _(XR_FORCE_FEEDBACK_CURL_LOCATION_THUMB_CURL_MNDX, 0)  \
    _(XR_FORCE_FEEDBACK_CURL_LOCATION_INDEX_CURL_MNDX, 1)  \
    _(XR_FORCE_FEEDBACK_CURL_LOCATION_MIDDLE_CURL_MNDX, 2) \
    _(XR_FORCE_FEEDBACK_CURL_LOCATION_RING_CURL_MNDX, 3)   \
    _(XR_FORCE_FEEDBACK_CURL_LOCATION_LITTLE_CURL_MNDX, 4) \
    _(XR_FORCE_FEEDBACK_CURL_LOCATION_MAX_ENUM_MNDX, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrHandTrackingDataSourceEXT(_)     \
    _(XR_HAND_TRACKING_DATA_SOURCE_UNOBSTRUCTED_EXT, 1) \
    _(XR_HAND_TRACKING_DATA_SOURCE_CONTROLLER_EXT, 2)   \
    _(XR_HAND_TRACKING_DATA_SOURCE_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrPlaneDetectorOrientationEXT(_)           \
    _(XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_UPWARD_EXT, 0)   \
    _(XR_PLANE_DETECTOR_ORIENTATION_HORIZONTAL_DOWNWARD_EXT, 1) \
    _(XR_PLANE_DETECTOR_ORIENTATION_VERTICAL_EXT, 2)            \
    _(XR_PLANE_DETECTOR_ORIENTATION_ARBITRARY_EXT, 3)           \
    _(XR_PLANE_DETECTOR_ORIENTATION_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrPlaneDetectorSemanticTypeEXT(_)  \
    _(XR_PLANE_DETECTOR_SEMANTIC_TYPE_UNDEFINED_EXT, 0) \
    _(XR_PLANE_DETECTOR_SEMANTIC_TYPE_CEILING_EXT, 1)   \
    _(XR_PLANE_DETECTOR_SEMANTIC_TYPE_FLOOR_EXT, 2)     \
    _(XR_PLANE_DETECTOR_SEMANTIC_TYPE_WALL_EXT, 3)      \
    _(XR_PLANE_DETECTOR_SEMANTIC_TYPE_PLATFORM_EXT, 4)  \
    _(XR_PLANE_DETECTOR_SEMANTIC_TYPE_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrPlaneDetectionStateEXT(_) \
    _(XR_PLANE_DETECTION_STATE_NONE_EXT, 0)      \
    _(XR_PLANE_DETECTION_STATE_PENDING_EXT, 1)   \
    _(XR_PLANE_DETECTION_STATE_DONE_EXT, 2)      \
    _(XR_PLANE_DETECTION_STATE_ERROR_EXT, 3)     \
    _(XR_PLANE_DETECTION_STATE_FATAL_EXT, 4)     \
    _(XR_PLANE_DETECTION_STATE_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrFutureStateEXT(_) \
    _(XR_FUTURE_STATE_PENDING_EXT, 1)    \
    _(XR_FUTURE_STATE_READY_EXT, 2)      \
    _(XR_FUTURE_STATE_MAX_ENUM_EXT, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrHeadsetFitStatusML(_) \
    _(XR_HEADSET_FIT_STATUS_UNKNOWN_ML, 0)   \
    _(XR_HEADSET_FIT_STATUS_NOT_WORN_ML, 1)  \
    _(XR_HEADSET_FIT_STATUS_GOOD_FIT_ML, 2)  \
    _(XR_HEADSET_FIT_STATUS_BAD_FIT_ML, 3)   \
    _(XR_HEADSET_FIT_STATUS_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_ENUM_XrEyeCalibrationStatusML(_) \
    _(XR_EYE_CALIBRATION_STATUS_UNKNOWN_ML, 0)   \
    _(XR_EYE_CALIBRATION_STATUS_NONE_ML, 1)      \
    _(XR_EYE_CALIBRATION_STATUS_COARSE_ML, 2)    \
    _(XR_EYE_CALIBRATION_STATUS_FINE_ML, 3)      \
    _(XR_EYE_CALIBRATION_STATUS_MAX_ENUM_ML, 0x7FFFFFFF)

#define XR_LIST_BITS_XrInstanceCreateFlags(_)

#define XR_LIST_BITS_XrSessionCreateFlags(_)

#define XR_LIST_BITS_XrSpaceVelocityFlags(_)          \
    _(XR_SPACE_VELOCITY_LINEAR_VALID_BIT, 0x00000001) \
    _(XR_SPACE_VELOCITY_ANGULAR_VALID_BIT, 0x00000002)

#define XR_LIST_BITS_XrSpaceLocationFlags(_)                 \
    _(XR_SPACE_LOCATION_ORIENTATION_VALID_BIT, 0x00000001)   \
    _(XR_SPACE_LOCATION_POSITION_VALID_BIT, 0x00000002)      \
    _(XR_SPACE_LOCATION_ORIENTATION_TRACKED_BIT, 0x00000004) \
    _(XR_SPACE_LOCATION_POSITION_TRACKED_BIT, 0x00000008)

#define XR_LIST_BITS_XrSwapchainCreateFlags(_)               \
    _(XR_SWAPCHAIN_CREATE_PROTECTED_CONTENT_BIT, 0x00000001) \
    _(XR_SWAPCHAIN_CREATE_STATIC_IMAGE_BIT, 0x00000002)

#define XR_LIST_BITS_XrSwapchainUsageFlags(_)                      \
    _(XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT, 0x00000001)         \
    _(XR_SWAPCHAIN_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, 0x00000002) \
    _(XR_SWAPCHAIN_USAGE_UNORDERED_ACCESS_BIT, 0x00000004)         \
    _(XR_SWAPCHAIN_USAGE_TRANSFER_SRC_BIT, 0x00000008)             \
    _(XR_SWAPCHAIN_USAGE_TRANSFER_DST_BIT, 0x00000010)             \
    _(XR_SWAPCHAIN_USAGE_SAMPLED_BIT, 0x00000020)                  \
    _(XR_SWAPCHAIN_USAGE_MUTABLE_FORMAT_BIT, 0x00000040)           \
    _(XR_SWAPCHAIN_USAGE_INPUT_ATTACHMENT_BIT_MND, 0x00000080)     \
    _(XR_SWAPCHAIN_USAGE_INPUT_ATTACHMENT_BIT_KHR, XR_SWAPCHAIN_USAGE_INPUT_ATTACHMENT_BIT_MND)

#define XR_LIST_BITS_XrCompositionLayerFlags(_)                          \
    _(XR_COMPOSITION_LAYER_CORRECT_CHROMATIC_ABERRATION_BIT, 0x00000001) \
    _(XR_COMPOSITION_LAYER_BLEND_TEXTURE_SOURCE_ALPHA_BIT, 0x00000002)   \
    _(XR_COMPOSITION_LAYER_UNPREMULTIPLIED_ALPHA_BIT, 0x00000004)

#define XR_LIST_BITS_XrViewStateFlags(_)                 \
    _(XR_VIEW_STATE_ORIENTATION_VALID_BIT, 0x00000001)   \
    _(XR_VIEW_STATE_POSITION_VALID_BIT, 0x00000002)      \
    _(XR_VIEW_STATE_ORIENTATION_TRACKED_BIT, 0x00000004) \
    _(XR_VIEW_STATE_POSITION_TRACKED_BIT, 0x00000008)

#define XR_LIST_BITS_XrInputSourceLocalizedNameFlags(_)                   \
    _(XR_INPUT_SOURCE_LOCALIZED_NAME_USER_PATH_BIT, 0x00000001)           \
    _(XR_INPUT_SOURCE_LOCALIZED_NAME_INTERACTION_PROFILE_BIT, 0x00000002) \
    _(XR_INPUT_SOURCE_LOCALIZED_NAME_COMPONENT_BIT, 0x00000004)

#define XR_LIST_BITS_XrVulkanInstanceCreateFlagsKHR(_)

#define XR_LIST_BITS_XrVulkanDeviceCreateFlagsKHR(_)

#define XR_LIST_BITS_XrDebugUtilsMessageSeverityFlagsEXT(_)        \
    _(XR_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT, 0x00000001) \
    _(XR_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT, 0x00000010)    \
    _(XR_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT, 0x00000100) \
    _(XR_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT, 0x00001000)

#define XR_LIST_BITS_XrDebugUtilsMessageTypeFlagsEXT(_)            \
    _(XR_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT, 0x00000001)     \
    _(XR_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT, 0x00000002)  \
    _(XR_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT, 0x00000004) \
    _(XR_DEBUG_UTILS_MESSAGE_TYPE_CONFORMANCE_BIT_EXT, 0x00000008)

#define XR_LIST_BITS_XrOverlaySessionCreateFlagsEXTX(_)

#define XR_LIST_BITS_XrOverlayMainSessionFlagsEXTX(_) \
    _(XR_OVERLAY_MAIN_SESSION_ENABLED_COMPOSITION_LAYER_INFO_DEPTH_BIT_EXTX, 0x00000001)

#define XR_LIST_BITS_XrCompositionLayerImageLayoutFlagsFB(_) \
    _(XR_COMPOSITION_LAYER_IMAGE_LAYOUT_VERTICAL_FLIP_BIT_FB, 0x00000001)

#define XR_LIST_BITS_XrAndroidSurfaceSwapchainFlagsFB(_)           \
    _(XR_ANDROID_SURFACE_SWAPCHAIN_SYNCHRONOUS_BIT_FB, 0x00000001) \
    _(XR_ANDROID_SURFACE_SWAPCHAIN_USE_TIMESTAMPS_BIT_FB, 0x00000002)

#define XR_LIST_BITS_XrCompositionLayerSecureContentFlagsFB(_)              \
    _(XR_COMPOSITION_LAYER_SECURE_CONTENT_EXCLUDE_LAYER_BIT_FB, 0x00000001) \
    _(XR_COMPOSITION_LAYER_SECURE_CONTENT_REPLACE_LAYER_BIT_FB, 0x00000002)

#define XR_LIST_BITS_XrHandTrackingAimFlagsFB(_)               \
    _(XR_HAND_TRACKING_AIM_COMPUTED_BIT_FB, 0x00000001)        \
    _(XR_HAND_TRACKING_AIM_VALID_BIT_FB, 0x00000002)           \
    _(XR_HAND_TRACKING_AIM_INDEX_PINCHING_BIT_FB, 0x00000004)  \
    _(XR_HAND_TRACKING_AIM_MIDDLE_PINCHING_BIT_FB, 0x00000008) \
    _(XR_HAND_TRACKING_AIM_RING_PINCHING_BIT_FB, 0x00000010)   \
    _(XR_HAND_TRACKING_AIM_LITTLE_PINCHING_BIT_FB, 0x00000020) \
    _(XR_HAND_TRACKING_AIM_SYSTEM_GESTURE_BIT_FB, 0x00000040)  \
    _(XR_HAND_TRACKING_AIM_DOMINANT_HAND_BIT_FB, 0x00000080)   \
    _(XR_HAND_TRACKING_AIM_MENU_PRESSED_BIT_FB, 0x00000100)

#define XR_LIST_BITS_XrSwapchainCreateFoveationFlagsFB(_)          \
    _(XR_SWAPCHAIN_CREATE_FOVEATION_SCALED_BIN_BIT_FB, 0x00000001) \
    _(XR_SWAPCHAIN_CREATE_FOVEATION_FRAGMENT_DENSITY_MAP_BIT_FB, 0x00000002)

#define XR_LIST_BITS_XrSwapchainStateFoveationFlagsFB(_)

#define XR_LIST_BITS_XrKeyboardTrackingFlagsFB(_)     \
    _(XR_KEYBOARD_TRACKING_EXISTS_BIT_FB, 0x00000001) \
    _(XR_KEYBOARD_TRACKING_LOCAL_BIT_FB, 0x00000002)  \
    _(XR_KEYBOARD_TRACKING_REMOTE_BIT_FB, 0x00000004) \
    _(XR_KEYBOARD_TRACKING_CONNECTED_BIT_FB, 0x00000008)

#define XR_LIST_BITS_XrKeyboardTrackingQueryFlagsFB(_)     \
    _(XR_KEYBOARD_TRACKING_QUERY_LOCAL_BIT_FB, 0x00000002) \
    _(XR_KEYBOARD_TRACKING_QUERY_REMOTE_BIT_FB, 0x00000004)

#define XR_LIST_BITS_XrTriangleMeshFlagsFB(_) _(XR_TRIANGLE_MESH_MUTABLE_BIT_FB, 0x00000001)

#define XR_LIST_BITS_XrPassthroughCapabilityFlagsFB(_)    \
    _(XR_PASSTHROUGH_CAPABILITY_BIT_FB, 0x00000001)       \
    _(XR_PASSTHROUGH_CAPABILITY_COLOR_BIT_FB, 0x00000002) \
    _(XR_PASSTHROUGH_CAPABILITY_LAYER_DEPTH_BIT_FB, 0x00000004)

#define XR_LIST_BITS_XrPassthroughFlagsFB(_)                    \
    _(XR_PASSTHROUGH_IS_RUNNING_AT_CREATION_BIT_FB, 0x00000001) \
    _(XR_PASSTHROUGH_LAYER_DEPTH_BIT_FB, 0x00000002)

#define XR_LIST_BITS_XrPassthroughStateChangedFlagsFB(_)                     \
    _(XR_PASSTHROUGH_STATE_CHANGED_REINIT_REQUIRED_BIT_FB, 0x00000001)       \
    _(XR_PASSTHROUGH_STATE_CHANGED_NON_RECOVERABLE_ERROR_BIT_FB, 0x00000002) \
    _(XR_PASSTHROUGH_STATE_CHANGED_RECOVERABLE_ERROR_BIT_FB, 0x00000004)     \
    _(XR_PASSTHROUGH_STATE_CHANGED_RESTORED_ERROR_BIT_FB, 0x00000008)

#define XR_LIST_BITS_XrRenderModelFlagsFB(_)                         \
    _(XR_RENDER_MODEL_SUPPORTS_GLTF_2_0_SUBSET_1_BIT_FB, 0x00000001) \
    _(XR_RENDER_MODEL_SUPPORTS_GLTF_2_0_SUBSET_2_BIT_FB, 0x00000002)

#define XR_LIST_BITS_XrFrameEndInfoFlagsML(_)         \
    _(XR_FRAME_END_INFO_PROTECTED_BIT_ML, 0x00000001) \
    _(XR_FRAME_END_INFO_VIGNETTE_BIT_ML, 0x00000002)

#define XR_LIST_BITS_XrGlobalDimmerFrameEndInfoFlagsML(_) _(XR_GLOBAL_DIMMER_FRAME_END_INFO_ENABLED_BIT_ML, 0x00000001)

#define XR_LIST_BITS_XrLocalizationMapErrorFlagsML(_)                  \
    _(XR_LOCALIZATION_MAP_ERROR_UNKNOWN_BIT_ML, 0x00000001)            \
    _(XR_LOCALIZATION_MAP_ERROR_OUT_OF_MAPPED_AREA_BIT_ML, 0x00000002) \
    _(XR_LOCALIZATION_MAP_ERROR_LOW_FEATURE_COUNT_BIT_ML, 0x00000004)  \
    _(XR_LOCALIZATION_MAP_ERROR_EXCESSIVE_MOTION_BIT_ML, 0x00000008)   \
    _(XR_LOCALIZATION_MAP_ERROR_LOW_LIGHT_BIT_ML, 0x00000010)          \
    _(XR_LOCALIZATION_MAP_ERROR_HEADPOSE_BIT_ML, 0x00000020)

#define XR_LIST_BITS_XrCompositionLayerSpaceWarpInfoFlagsFB(_) \
    _(XR_COMPOSITION_LAYER_SPACE_WARP_INFO_FRAME_SKIP_BIT_FB, 0x00000001)

#define XR_LIST_BITS_XrSemanticLabelsSupportFlagsFB(_)                              \
    _(XR_SEMANTIC_LABELS_SUPPORT_MULTIPLE_SEMANTIC_LABELS_BIT_FB, 0x00000001)       \
    _(XR_SEMANTIC_LABELS_SUPPORT_ACCEPT_DESK_TO_TABLE_MIGRATION_BIT_FB, 0x00000002) \
    _(XR_SEMANTIC_LABELS_SUPPORT_ACCEPT_INVISIBLE_WALL_FACE_BIT_FB, 0x00000004)

#define XR_LIST_BITS_XrDigitalLensControlFlagsALMALENCE(_) \
    _(XR_DIGITAL_LENS_CONTROL_PROCESSING_DISABLE_BIT_ALMALENCE, 0x00000001)

#define XR_LIST_BITS_XrFoveationEyeTrackedProfileCreateFlagsMETA(_)

#define XR_LIST_BITS_XrFoveationEyeTrackedStateFlagsMETA(_) _(XR_FOVEATION_EYE_TRACKED_STATE_VALID_BIT_META, 0x00000001)

#define XR_LIST_BITS_XrCompositionLayerSettingsFlagsFB(_)                      \
    _(XR_COMPOSITION_LAYER_SETTINGS_NORMAL_SUPER_SAMPLING_BIT_FB, 0x00000001)  \
    _(XR_COMPOSITION_LAYER_SETTINGS_QUALITY_SUPER_SAMPLING_BIT_FB, 0x00000002) \
    _(XR_COMPOSITION_LAYER_SETTINGS_NORMAL_SHARPENING_BIT_FB, 0x00000004)      \
    _(XR_COMPOSITION_LAYER_SETTINGS_QUALITY_SHARPENING_BIT_FB, 0x00000008)     \
    _(XR_COMPOSITION_LAYER_SETTINGS_AUTO_LAYER_FILTER_BIT_META, 0x00000020)

#define XR_LIST_BITS_XrPassthroughPreferenceFlagsMETA(_) _(XR_PASSTHROUGH_PREFERENCE_DEFAULT_TO_ACTIVE_BIT_META, 0x00000001)

#define XR_LIST_BITS_XrVirtualKeyboardInputStateFlagsMETA(_) _(XR_VIRTUAL_KEYBOARD_INPUT_STATE_PRESSED_BIT_META, 0x00000001)

#define XR_LIST_BITS_XrExternalCameraStatusFlagsOCULUS(_)                  \
    _(XR_EXTERNAL_CAMERA_STATUS_CONNECTED_BIT_OCULUS, 0x00000001)          \
    _(XR_EXTERNAL_CAMERA_STATUS_CALIBRATING_BIT_OCULUS, 0x00000002)        \
    _(XR_EXTERNAL_CAMERA_STATUS_CALIBRATION_FAILED_BIT_OCULUS, 0x00000004) \
    _(XR_EXTERNAL_CAMERA_STATUS_CALIBRATED_BIT_OCULUS, 0x00000008)         \
    _(XR_EXTERNAL_CAMERA_STATUS_CAPTURING_BIT_OCULUS, 0x00000010)

#define XR_LIST_BITS_XrPerformanceMetricsCounterFlagsMETA(_)                \
    _(XR_PERFORMANCE_METRICS_COUNTER_ANY_VALUE_VALID_BIT_META, 0x00000001)  \
    _(XR_PERFORMANCE_METRICS_COUNTER_UINT_VALUE_VALID_BIT_META, 0x00000002) \
    _(XR_PERFORMANCE_METRICS_COUNTER_FLOAT_VALUE_VALID_BIT_META, 0x00000004)

#define XR_LIST_BITS_XrEnvironmentDepthProviderCreateFlagsMETA(_)

#define XR_LIST_BITS_XrEnvironmentDepthSwapchainCreateFlagsMETA(_)

#define XR_LIST_BITS_XrFoveationDynamicFlagsHTC(_)                \
    _(XR_FOVEATION_DYNAMIC_LEVEL_ENABLED_BIT_HTC, 0x00000001)     \
    _(XR_FOVEATION_DYNAMIC_CLEAR_FOV_ENABLED_BIT_HTC, 0x00000002) \
    _(XR_FOVEATION_DYNAMIC_FOCAL_CENTER_OFFSET_ENABLED_BIT_HTC, 0x00000004)

#define XR_LIST_BITS_XrPlaneDetectionCapabilityFlagsEXT(_)                 \
    _(XR_PLANE_DETECTION_CAPABILITY_PLANE_DETECTION_BIT_EXT, 0x00000001)   \
    _(XR_PLANE_DETECTION_CAPABILITY_PLANE_HOLES_BIT_EXT, 0x00000002)       \
    _(XR_PLANE_DETECTION_CAPABILITY_SEMANTIC_CEILING_BIT_EXT, 0x00000004)  \
    _(XR_PLANE_DETECTION_CAPABILITY_SEMANTIC_FLOOR_BIT_EXT, 0x00000008)    \
    _(XR_PLANE_DETECTION_CAPABILITY_SEMANTIC_WALL_BIT_EXT, 0x00000010)     \
    _(XR_PLANE_DETECTION_CAPABILITY_SEMANTIC_PLATFORM_BIT_EXT, 0x00000020) \
    _(XR_PLANE_DETECTION_CAPABILITY_ORIENTATION_BIT_EXT, 0x00000040)

#define XR_LIST_BITS_XrPlaneDetectorFlagsEXT(_) _(XR_PLANE_DETECTOR_ENABLE_CONTOUR_BIT_EXT, 0x00000001)

/// Calls your macro with the name of each member of XrApiLayerProperties, in order.
#define XR_LIST_STRUCT_XrApiLayerProperties(_) \
    _(type)                                    \
    _(next)                                    \
    _(layerName)                               \
    _(specVersion)                             \
    _(layerVersion)                            \
    _(description)

/// Calls your macro with the name of each member of XrExtensionProperties, in order.
#define XR_LIST_STRUCT_XrExtensionProperties(_) \
    _(type)                                     \
    _(next)                                     \
    _(extensionName)                            \
    _(extensionVersion)

/// Calls your macro with the name of each member of XrApplicationInfo, in order.
#define XR_LIST_STRUCT_XrApplicationInfo(_) \
    _(applicationName)                      \
    _(applicationVersion)                   \
    _(engineName)                           \
    _(engineVersion)                        \
    _(apiVersion)

/// Calls your macro with the name of each member of XrInstanceCreateInfo, in order.
#define XR_LIST_STRUCT_XrInstanceCreateInfo(_) \
    _(type)                                    \
    _(next)                                    \
    _(createFlags)                             \
    _(applicationInfo)                         \
    _(enabledApiLayerCount)                    \
    _(enabledApiLayerNames)                    \
    _(enabledExtensionCount)                   \
    _(enabledExtensionNames)

/// Calls your macro with the name of each member of XrInstanceProperties, in order.
#define XR_LIST_STRUCT_XrInstanceProperties(_) \
    _(type)                                    \
    _(next)                                    \
    _(runtimeVersion)                          \
    _(runtimeName)

/// Calls your macro with the name of each member of XrEventDataBuffer, in order.
#define XR_LIST_STRUCT_XrEventDataBuffer(_) \
    _(type)                                 \
    _(next)                                 \
    _(varying)

/// Calls your macro with the name of each member of XrSystemGetInfo, in order.
#define XR_LIST_STRUCT_XrSystemGetInfo(_) \
    _(type)                               \
    _(next)                               \
    _(formFactor)

/// Calls your macro with the name of each member of XrSystemGraphicsProperties, in order.
#define XR_LIST_STRUCT_XrSystemGraphicsProperties(_) \
    _(maxSwapchainImageHeight)                       \
    _(maxSwapchainImageWidth)                        \
    _(maxLayerCount)

/// Calls your macro with the name of each member of XrSystemTrackingProperties, in order.
#define XR_LIST_STRUCT_XrSystemTrackingProperties(_) \
    _(orientationTracking)                           \
    _(positionTracking)

/// Calls your macro with the name of each member of XrSystemProperties, in order.
#define XR_LIST_STRUCT_XrSystemProperties(_) \
    _(type)                                  \
    _(next)                                  \
    _(systemId)                              \
    _(vendorId)                              \
    _(systemName)                            \
    _(graphicsProperties)                    \
    _(trackingProperties)

/// Calls your macro with the name of each member of XrSessionCreateInfo, in order.
#define XR_LIST_STRUCT_XrSessionCreateInfo(_) \
    _(type)                                   \
    _(next)                                   \
    _(createFlags)                            \
    _(systemId)

/// Calls your macro with the name of each member of XrVector3f, in order.
#define XR_LIST_STRUCT_XrVector3f(_) \
    _(x)                             \
    _(y)                             \
    _(z)

/// Calls your macro with the name of each member of XrSpaceVelocity, in order.
#define XR_LIST_STRUCT_XrSpaceVelocity(_) \
    _(type)                               \
    _(next)                               \
    _(velocityFlags)                      \
    _(linearVelocity)                     \
    _(angularVelocity)

/// Calls your macro with the name of each member of XrQuaternionf, in order.
#define XR_LIST_STRUCT_XrQuaternionf(_) \
    _(x)                                \
    _(y)                                \
    _(z)                                \
    _(w)

/// Calls your macro with the name of each member of XrPosef, in order.
#define XR_LIST_STRUCT_XrPosef(_) \
    _(orientation)                \
    _(position)

/// Calls your macro with the name of each member of XrReferenceSpaceCreateInfo, in order.
#define XR_LIST_STRUCT_XrReferenceSpaceCreateInfo(_) \
    _(type)                                          \
    _(next)                                          \
    _(referenceSpaceType)                            \
    _(poseInReferenceSpace)

/// Calls your macro with the name of each member of XrExtent2Df, in order.
#define XR_LIST_STRUCT_XrExtent2Df(_) \
    _(width)                          \
    _(height)

/// Calls your macro with the name of each member of XrActionSpaceCreateInfo, in order.
#define XR_LIST_STRUCT_XrActionSpaceCreateInfo(_) \
    _(type)                                       \
    _(next)                                       \
    _(action)                                     \
    _(subactionPath)                              \
    _(poseInActionSpace)

/// Calls your macro with the name of each member of XrSpaceLocation, in order.
#define XR_LIST_STRUCT_XrSpaceLocation(_) \
    _(type)                               \
    _(next)                               \
    _(locationFlags)                      \
    _(pose)

/// Calls your macro with the name of each member of XrViewConfigurationProperties, in order.
#define XR_LIST_STRUCT_XrViewConfigurationProperties(_) \
    _(type)                                             \
    _(next)                                             \
    _(viewConfigurationType)                            \
    _(fovMutable)

/// Calls your macro with the name of each member of XrViewConfigurationView, in order.
#define XR_LIST_STRUCT_XrViewConfigurationView(_) \
    _(type)                                       \
    _(next)                                       \
    _(recommendedImageRectWidth)                  \
    _(maxImageRectWidth)                          \
    _(recommendedImageRectHeight)                 \
    _(maxImageRectHeight)                         \
    _(recommendedSwapchainSampleCount)            \
    _(maxSwapchainSampleCount)

/// Calls your macro with the name of each member of XrSwapchainCreateInfo, in order.
#define XR_LIST_STRUCT_XrSwapchainCreateInfo(_) \
    _(type)                                     \
    _(next)                                     \
    _(createFlags)                              \
    _(usageFlags)                               \
    _(format)                                   \
    _(sampleCount)                              \
    _(width)                                    \
    _(height)                                   \
    _(faceCount)                                \
    _(arraySize)                                \
    _(mipCount)

/// Calls your macro with the name of each member of XrSwapchainImageBaseHeader, in order.
#define XR_LIST_STRUCT_XrSwapchainImageBaseHeader(_) \
    _(type)                                          \
    _(next)

/// Calls your macro with the name of each member of XrSwapchainImageAcquireInfo, in order.
#define XR_LIST_STRUCT_XrSwapchainImageAcquireInfo(_) \
    _(type)                                           \
    _(next)

/// Calls your macro with the name of each member of XrSwapchainImageWaitInfo, in order.
#define XR_LIST_STRUCT_XrSwapchainImageWaitInfo(_) \
    _(type)                                        \
    _(next)                                        \
    _(timeout)

/// Calls your macro with the name of each member of XrSwapchainImageReleaseInfo, in order.
#define XR_LIST_STRUCT_XrSwapchainImageReleaseInfo(_) \
    _(type)                                           \
    _(next)

/// Calls your macro with the name of each member of XrSessionBeginInfo, in order.
#define XR_LIST_STRUCT_XrSessionBeginInfo(_) \
    _(type)                                  \
    _(next)                                  \
    _(primaryViewConfigurationType)

/// Calls your macro with the name of each member of XrFrameWaitInfo, in order.
#define XR_LIST_STRUCT_XrFrameWaitInfo(_) \
    _(type)                               \
    _(next)

/// Calls your macro with the name of each member of XrFrameState, in order.
#define XR_LIST_STRUCT_XrFrameState(_) \
    _(type)                            \
    _(next)                            \
    _(predictedDisplayTime)            \
    _(predictedDisplayPeriod)          \
    _(shouldRender)

/// Calls your macro with the name of each member of XrFrameBeginInfo, in order.
#define XR_LIST_STRUCT_XrFrameBeginInfo(_) \
    _(type)                                \
    _(next)

/// Calls your macro with the name of each member of XrCompositionLayerBaseHeader, in order.
#define XR_LIST_STRUCT_XrCompositionLayerBaseHeader(_) \
    _(type)                                            \
    _(next)                                            \
    _(layerFlags)                                      \
    _(space)

/// Calls your macro with the name of each member of XrFrameEndInfo, in order.
#define XR_LIST_STRUCT_XrFrameEndInfo(_) \
    _(type)                              \
    _(next)                              \
    _(displayTime)                       \
    _(environmentBlendMode)              \
    _(layerCount)                        \
    _(layers)

/// Calls your macro with the name of each member of XrViewLocateInfo, in order.
#define XR_LIST_STRUCT_XrViewLocateInfo(_) \
    _(type)                                \
    _(next)                                \
    _(viewConfigurationType)               \
    _(displayTime)                         \
    _(space)

/// Calls your macro with the name of each member of XrViewState, in order.
#define XR_LIST_STRUCT_XrViewState(_) \
    _(type)                           \
    _(next)                           \
    _(viewStateFlags)

/// Calls your macro with the name of each member of XrFovf, in order.
#define XR_LIST_STRUCT_XrFovf(_) \
    _(angleLeft)                 \
    _(angleRight)                \
    _(angleUp)                   \
    _(angleDown)

/// Calls your macro with the name of each member of XrView, in order.
#define XR_LIST_STRUCT_XrView(_) \
    _(type)                      \
    _(next)                      \
    _(pose)                      \
    _(fov)

/// Calls your macro with the name of each member of XrActionSetCreateInfo, in order.
#define XR_LIST_STRUCT_XrActionSetCreateInfo(_) \
    _(type)                                     \
    _(next)                                     \
    _(actionSetName)                            \
    _(localizedActionSetName)                   \
    _(priority)

/// Calls your macro with the name of each member of XrActionCreateInfo, in order.
#define XR_LIST_STRUCT_XrActionCreateInfo(_) \
    _(type)                                  \
    _(next)                                  \
    _(actionName)                            \
    _(actionType)                            \
    _(countSubactionPaths)                   \
    _(subactionPaths)                        \
    _(localizedActionName)

/// Calls your macro with the name of each member of XrActionSuggestedBinding, in order.
#define XR_LIST_STRUCT_XrActionSuggestedBinding(_) \
    _(action)                                      \
    _(binding)

/// Calls your macro with the name of each member of XrInteractionProfileSuggestedBinding, in order.
#define XR_LIST_STRUCT_XrInteractionProfileSuggestedBinding(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(interactionProfile)                                      \
    _(countSuggestedBindings)                                  \
    _(suggestedBindings)

/// Calls your macro with the name of each member of XrSessionActionSetsAttachInfo, in order.
#define XR_LIST_STRUCT_XrSessionActionSetsAttachInfo(_) \
    _(type)                                             \
    _(next)                                             \
    _(countActionSets)                                  \
    _(actionSets)

/// Calls your macro with the name of each member of XrInteractionProfileState, in order.
#define XR_LIST_STRUCT_XrInteractionProfileState(_) \
    _(type)                                         \
    _(next)                                         \
    _(interactionProfile)

/// Calls your macro with the name of each member of XrActionStateGetInfo, in order.
#define XR_LIST_STRUCT_XrActionStateGetInfo(_) \
    _(type)                                    \
    _(next)                                    \
    _(action)                                  \
    _(subactionPath)

/// Calls your macro with the name of each member of XrActionStateBoolean, in order.
#define XR_LIST_STRUCT_XrActionStateBoolean(_) \
    _(type)                                    \
    _(next)                                    \
    _(currentState)                            \
    _(changedSinceLastSync)                    \
    _(lastChangeTime)                          \
    _(isActive)

/// Calls your macro with the name of each member of XrActionStateFloat, in order.
#define XR_LIST_STRUCT_XrActionStateFloat(_) \
    _(type)                                  \
    _(next)                                  \
    _(currentState)                          \
    _(changedSinceLastSync)                  \
    _(lastChangeTime)                        \
    _(isActive)

/// Calls your macro with the name of each member of XrVector2f, in order.
#define XR_LIST_STRUCT_XrVector2f(_) \
    _(x)                             \
    _(y)

/// Calls your macro with the name of each member of XrActionStateVector2f, in order.
#define XR_LIST_STRUCT_XrActionStateVector2f(_) \
    _(type)                                     \
    _(next)                                     \
    _(currentState)                             \
    _(changedSinceLastSync)                     \
    _(lastChangeTime)                           \
    _(isActive)

/// Calls your macro with the name of each member of XrActionStatePose, in order.
#define XR_LIST_STRUCT_XrActionStatePose(_) \
    _(type)                                 \
    _(next)                                 \
    _(isActive)

/// Calls your macro with the name of each member of XrActiveActionSet, in order.
#define XR_LIST_STRUCT_XrActiveActionSet(_) \
    _(actionSet)                            \
    _(subactionPath)

/// Calls your macro with the name of each member of XrActionsSyncInfo, in order.
#define XR_LIST_STRUCT_XrActionsSyncInfo(_) \
    _(type)                                 \
    _(next)                                 \
    _(countActiveActionSets)                \
    _(activeActionSets)

/// Calls your macro with the name of each member of XrBoundSourcesForActionEnumerateInfo, in order.
#define XR_LIST_STRUCT_XrBoundSourcesForActionEnumerateInfo(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(action)

/// Calls your macro with the name of each member of XrInputSourceLocalizedNameGetInfo, in order.
#define XR_LIST_STRUCT_XrInputSourceLocalizedNameGetInfo(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(sourcePath)                                           \
    _(whichComponents)

/// Calls your macro with the name of each member of XrHapticActionInfo, in order.
#define XR_LIST_STRUCT_XrHapticActionInfo(_) \
    _(type)                                  \
    _(next)                                  \
    _(action)                                \
    _(subactionPath)

/// Calls your macro with the name of each member of XrHapticBaseHeader, in order.
#define XR_LIST_STRUCT_XrHapticBaseHeader(_) \
    _(type)                                  \
    _(next)

/// Calls your macro with the name of each member of XrBaseInStructure, in order.
#define XR_LIST_STRUCT_XrBaseInStructure(_) \
    _(type)                                 \
    _(next)

/// Calls your macro with the name of each member of XrBaseOutStructure, in order.
#define XR_LIST_STRUCT_XrBaseOutStructure(_) \
    _(type)                                  \
    _(next)

/// Calls your macro with the name of each member of XrOffset2Di, in order.
#define XR_LIST_STRUCT_XrOffset2Di(_) \
    _(x)                              \
    _(y)

/// Calls your macro with the name of each member of XrExtent2Di, in order.
#define XR_LIST_STRUCT_XrExtent2Di(_) \
    _(width)                          \
    _(height)

/// Calls your macro with the name of each member of XrRect2Di, in order.
#define XR_LIST_STRUCT_XrRect2Di(_) \
    _(offset)                       \
    _(extent)

/// Calls your macro with the name of each member of XrSwapchainSubImage, in order.
#define XR_LIST_STRUCT_XrSwapchainSubImage(_) \
    _(swapchain)                              \
    _(imageRect)                              \
    _(imageArrayIndex)

/// Calls your macro with the name of each member of XrCompositionLayerProjectionView, in order.
#define XR_LIST_STRUCT_XrCompositionLayerProjectionView(_) \
    _(type)                                                \
    _(next)                                                \
    _(pose)                                                \
    _(fov)                                                 \
    _(subImage)

/// Calls your macro with the name of each member of XrCompositionLayerProjection, in order.
#define XR_LIST_STRUCT_XrCompositionLayerProjection(_) \
    _(type)                                            \
    _(next)                                            \
    _(layerFlags)                                      \
    _(space)                                           \
    _(viewCount)                                       \
    _(views)

/// Calls your macro with the name of each member of XrCompositionLayerQuad, in order.
#define XR_LIST_STRUCT_XrCompositionLayerQuad(_) \
    _(type)                                      \
    _(next)                                      \
    _(layerFlags)                                \
    _(space)                                     \
    _(eyeVisibility)                             \
    _(subImage)                                  \
    _(pose)                                      \
    _(size)

/// Calls your macro with the name of each member of XrEventDataBaseHeader, in order.
#define XR_LIST_STRUCT_XrEventDataBaseHeader(_) \
    _(type)                                     \
    _(next)

/// Calls your macro with the name of each member of XrEventDataEventsLost, in order.
#define XR_LIST_STRUCT_XrEventDataEventsLost(_) \
    _(type)                                     \
    _(next)                                     \
    _(lostEventCount)

/// Calls your macro with the name of each member of XrEventDataInstanceLossPending, in order.
#define XR_LIST_STRUCT_XrEventDataInstanceLossPending(_) \
    _(type)                                              \
    _(next)                                              \
    _(lossTime)

/// Calls your macro with the name of each member of XrEventDataSessionStateChanged, in order.
#define XR_LIST_STRUCT_XrEventDataSessionStateChanged(_) \
    _(type)                                              \
    _(next)                                              \
    _(session)                                           \
    _(state)                                             \
    _(time)

/// Calls your macro with the name of each member of XrEventDataReferenceSpaceChangePending, in order.
#define XR_LIST_STRUCT_XrEventDataReferenceSpaceChangePending(_) \
    _(type)                                                      \
    _(next)                                                      \
    _(session)                                                   \
    _(referenceSpaceType)                                        \
    _(changeTime)                                                \
    _(poseValid)                                                 \
    _(poseInPreviousSpace)

/// Calls your macro with the name of each member of XrEventDataInteractionProfileChanged, in order.
#define XR_LIST_STRUCT_XrEventDataInteractionProfileChanged(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(session)

/// Calls your macro with the name of each member of XrHapticVibration, in order.
#define XR_LIST_STRUCT_XrHapticVibration(_) \
    _(type)                                 \
    _(next)                                 \
    _(duration)                             \
    _(frequency)                            \
    _(amplitude)

/// Calls your macro with the name of each member of XrOffset2Df, in order.
#define XR_LIST_STRUCT_XrOffset2Df(_) \
    _(x)                              \
    _(y)

/// Calls your macro with the name of each member of XrRect2Df, in order.
#define XR_LIST_STRUCT_XrRect2Df(_) \
    _(offset)                       \
    _(extent)

/// Calls your macro with the name of each member of XrVector4f, in order.
#define XR_LIST_STRUCT_XrVector4f(_) \
    _(x)                             \
    _(y)                             \
    _(z)                             \
    _(w)

/// Calls your macro with the name of each member of XrColor4f, in order.
#define XR_LIST_STRUCT_XrColor4f(_) \
    _(r)                            \
    _(g)                            \
    _(b)                            \
    _(a)

/// Calls your macro with the name of each member of XrApiLayerNextInfo, in order.
#define XR_LIST_STRUCT_XrApiLayerNextInfo(_) \
    _(structType)                            \
    _(structVersion)                         \
    _(structSize)                            \
    _(layerName)                             \
    _(nextGetInstanceProcAddr)               \
    _(nextCreateApiLayerInstance)            \
    _(next)

/// Calls your macro with the name of each member of XrApiLayerCreateInfo, in order.
#define XR_LIST_STRUCT_XrApiLayerCreateInfo(_) \
    _(structType)                              \
    _(structVersion)                           \
    _(structSize)                              \
    _(loaderInstance)                          \
    _(settings_file_location)                  \
    _(nextInfo)

/// Calls your macro with the name of each member of XrNegotiateLoaderInfo, in order.
#define XR_LIST_STRUCT_XrNegotiateLoaderInfo(_) \
    _(structType)                               \
    _(structVersion)                            \
    _(structSize)                               \
    _(minInterfaceVersion)                      \
    _(maxInterfaceVersion)                      \
    _(minApiVersion)                            \
    _(maxApiVersion)

/// Calls your macro with the name of each member of XrNegotiateRuntimeRequest, in order.
#define XR_LIST_STRUCT_XrNegotiateRuntimeRequest(_) \
    _(structType)                                   \
    _(structVersion)                                \
    _(structSize)                                   \
    _(runtimeInterfaceVersion)                      \
    _(runtimeApiVersion)                            \
    _(getInstanceProcAddr)

/// Calls your macro with the name of each member of XrNegotiateApiLayerRequest, in order.
#define XR_LIST_STRUCT_XrNegotiateApiLayerRequest(_) \
    _(structType)                                    \
    _(structVersion)                                 \
    _(structSize)                                    \
    _(layerInterfaceVersion)                         \
    _(layerApiVersion)                               \
    _(getInstanceProcAddr)                           \
    _(createApiLayerInstance)

/// Calls your macro with the name of each member of XrColor3f, in order.
#define XR_LIST_STRUCT_XrColor3f(_) \
    _(r)                            \
    _(g)                            \
    _(b)

/// Calls your macro with the name of each member of XrExtent3Df, in order.
#define XR_LIST_STRUCT_XrExtent3Df(_) \
    _(width)                          \
    _(height)                         \
    _(depth)

/// Calls your macro with the name of each member of XrSpheref, in order.
#define XR_LIST_STRUCT_XrSpheref(_) \
    _(center)                       \
    _(radius)

/// Calls your macro with the name of each member of XrBoxf, in order.
#define XR_LIST_STRUCT_XrBoxf(_) \
    _(center)                    \
    _(extents)

/// Calls your macro with the name of each member of XrFrustumf, in order.
#define XR_LIST_STRUCT_XrFrustumf(_) \
    _(pose)                          \
    _(fov)                           \
    _(nearZ)                         \
    _(farZ)

/// Calls your macro with the name of each member of XrUuid, in order.
#define XR_LIST_STRUCT_XrUuid(_) _(data)

/// Calls your macro with the name of each member of XrSpacesLocateInfo, in order.
#define XR_LIST_STRUCT_XrSpacesLocateInfo(_) \
    _(type)                                  \
    _(next)                                  \
    _(baseSpace)                             \
    _(time)                                  \
    _(spaceCount)                            \
    _(spaces)

/// Calls your macro with the name of each member of XrSpaceLocationData, in order.
#define XR_LIST_STRUCT_XrSpaceLocationData(_) \
    _(locationFlags)                          \
    _(pose)

/// Calls your macro with the name of each member of XrSpaceLocations, in order.
#define XR_LIST_STRUCT_XrSpaceLocations(_) \
    _(type)                                \
    _(next)                                \
    _(locationCount)                       \
    _(locations)

/// Calls your macro with the name of each member of XrSpaceVelocityData, in order.
#define XR_LIST_STRUCT_XrSpaceVelocityData(_) \
    _(velocityFlags)                          \
    _(linearVelocity)                         \
    _(angularVelocity)

/// Calls your macro with the name of each member of XrSpaceVelocities, in order.
#define XR_LIST_STRUCT_XrSpaceVelocities(_) \
    _(type)                                 \
    _(next)                                 \
    _(velocityCount)                        \
    _(velocities)

/// Calls your macro with the name of each member of XrCompositionLayerCubeKHR, in order.
#define XR_LIST_STRUCT_XrCompositionLayerCubeKHR(_) \
    _(type)                                         \
    _(next)                                         \
    _(layerFlags)                                   \
    _(space)                                        \
    _(eyeVisibility)                                \
    _(swapchain)                                    \
    _(imageArrayIndex)                              \
    _(orientation)

/// Calls your macro with the name of each member of XrInstanceCreateInfoAndroidKHR, in order.
#define XR_LIST_STRUCT_XrInstanceCreateInfoAndroidKHR(_) \
    _(type)                                              \
    _(next)                                              \
    _(applicationVM)                                     \
    _(applicationActivity)

/// Calls your macro with the name of each member of XrCompositionLayerDepthInfoKHR, in order.
#define XR_LIST_STRUCT_XrCompositionLayerDepthInfoKHR(_) \
    _(type)                                              \
    _(next)                                              \
    _(subImage)                                          \
    _(minDepth)                                          \
    _(maxDepth)                                          \
    _(nearZ)                                             \
    _(farZ)

/// Calls your macro with the name of each member of XrVulkanSwapchainFormatListCreateInfoKHR, in order.
#define XR_LIST_STRUCT_XrVulkanSwapchainFormatListCreateInfoKHR(_) \
    _(type)                                                        \
    _(next)                                                        \
    _(viewFormatCount)                                             \
    _(viewFormats)

/// Calls your macro with the name of each member of XrCompositionLayerCylinderKHR, in order.
#define XR_LIST_STRUCT_XrCompositionLayerCylinderKHR(_) \
    _(type)                                             \
    _(next)                                             \
    _(layerFlags)                                       \
    _(space)                                            \
    _(eyeVisibility)                                    \
    _(subImage)                                         \
    _(pose)                                             \
    _(radius)                                           \
    _(centralAngle)                                     \
    _(aspectRatio)

/// Calls your macro with the name of each member of XrCompositionLayerEquirectKHR, in order.
#define XR_LIST_STRUCT_XrCompositionLayerEquirectKHR(_) \
    _(type)                                             \
    _(next)                                             \
    _(layerFlags)                                       \
    _(space)                                            \
    _(eyeVisibility)                                    \
    _(subImage)                                         \
    _(pose)                                             \
    _(radius)                                           \
    _(scale)                                            \
    _(bias)

/// Calls your macro with the name of each member of XrGraphicsBindingOpenGLWin32KHR, in order.
#define XR_LIST_STRUCT_XrGraphicsBindingOpenGLWin32KHR(_) \
    _(type)                                               \
    _(next)                                               \
    _(hDC)                                                \
    _(hGLRC)

/// Calls your macro with the name of each member of XrGraphicsBindingOpenGLXlibKHR, in order.
#define XR_LIST_STRUCT_XrGraphicsBindingOpenGLXlibKHR(_) \
    _(type)                                              \
    _(next)                                              \
    _(xDisplay)                                          \
    _(visualid)                                          \
    _(glxFBConfig)                                       \
    _(glxDrawable)                                       \
    _(glxContext)

/// Calls your macro with the name of each member of XrGraphicsBindingOpenGLXcbKHR, in order.
#define XR_LIST_STRUCT_XrGraphicsBindingOpenGLXcbKHR(_) \
    _(type)                                             \
    _(next)                                             \
    _(connection)                                       \
    _(screenNumber)                                     \
    _(fbconfigid)                                       \
    _(visualid)                                         \
    _(glxDrawable)                                      \
    _(glxContext)

/// Calls your macro with the name of each member of XrGraphicsBindingOpenGLWaylandKHR, in order.
#define XR_LIST_STRUCT_XrGraphicsBindingOpenGLWaylandKHR(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(display)

/// Calls your macro with the name of each member of XrSwapchainImageOpenGLKHR, in order.
#define XR_LIST_STRUCT_XrSwapchainImageOpenGLKHR(_) \
    _(type)                                         \
    _(next)                                         \
    _(image)

/// Calls your macro with the name of each member of XrGraphicsRequirementsOpenGLKHR, in order.
#define XR_LIST_STRUCT_XrGraphicsRequirementsOpenGLKHR(_) \
    _(type)                                               \
    _(next)                                               \
    _(minApiVersionSupported)                             \
    _(maxApiVersionSupported)

/// Calls your macro with the name of each member of XrGraphicsBindingOpenGLESAndroidKHR, in order.
#define XR_LIST_STRUCT_XrGraphicsBindingOpenGLESAndroidKHR(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(display)                                                \
    _(config)                                                 \
    _(context)

/// Calls your macro with the name of each member of XrSwapchainImageOpenGLESKHR, in order.
#define XR_LIST_STRUCT_XrSwapchainImageOpenGLESKHR(_) \
    _(type)                                           \
    _(next)                                           \
    _(image)

/// Calls your macro with the name of each member of XrGraphicsRequirementsOpenGLESKHR, in order.
#define XR_LIST_STRUCT_XrGraphicsRequirementsOpenGLESKHR(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(minApiVersionSupported)                               \
    _(maxApiVersionSupported)

/// Calls your macro with the name of each member of XrGraphicsBindingVulkanKHR, in order.
#define XR_LIST_STRUCT_XrGraphicsBindingVulkanKHR(_) \
    _(type)                                          \
    _(next)                                          \
    _(instance)                                      \
    _(physicalDevice)                                \
    _(device)                                        \
    _(queueFamilyIndex)                              \
    _(queueIndex)

/// Calls your macro with the name of each member of XrSwapchainImageVulkanKHR, in order.
#define XR_LIST_STRUCT_XrSwapchainImageVulkanKHR(_) \
    _(type)                                         \
    _(next)                                         \
    _(image)

/// Calls your macro with the name of each member of XrGraphicsRequirementsVulkanKHR, in order.
#define XR_LIST_STRUCT_XrGraphicsRequirementsVulkanKHR(_) \
    _(type)                                               \
    _(next)                                               \
    _(minApiVersionSupported)                             \
    _(maxApiVersionSupported)

/// Calls your macro with the name of each member of XrGraphicsBindingD3D11KHR, in order.
#define XR_LIST_STRUCT_XrGraphicsBindingD3D11KHR(_) \
    _(type)                                         \
    _(next)                                         \
    _(device)

/// Calls your macro with the name of each member of XrSwapchainImageD3D11KHR, in order.
#define XR_LIST_STRUCT_XrSwapchainImageD3D11KHR(_) \
    _(type)                                        \
    _(next)                                        \
    _(texture)

/// Calls your macro with the name of each member of XrGraphicsRequirementsD3D11KHR, in order.
#define XR_LIST_STRUCT_XrGraphicsRequirementsD3D11KHR(_) \
    _(type)                                              \
    _(next)                                              \
    _(adapterLuid)                                       \
    _(minFeatureLevel)

/// Calls your macro with the name of each member of XrGraphicsBindingD3D12KHR, in order.
#define XR_LIST_STRUCT_XrGraphicsBindingD3D12KHR(_) \
    _(type)                                         \
    _(next)                                         \
    _(device)                                       \
    _(queue)

/// Calls your macro with the name of each member of XrSwapchainImageD3D12KHR, in order.
#define XR_LIST_STRUCT_XrSwapchainImageD3D12KHR(_) \
    _(type)                                        \
    _(next)                                        \
    _(texture)

/// Calls your macro with the name of each member of XrGraphicsRequirementsD3D12KHR, in order.
#define XR_LIST_STRUCT_XrGraphicsRequirementsD3D12KHR(_) \
    _(type)                                              \
    _(next)                                              \
    _(adapterLuid)                                       \
    _(minFeatureLevel)

/// Calls your macro with the name of each member of XrVisibilityMaskKHR, in order.
#define XR_LIST_STRUCT_XrVisibilityMaskKHR(_) \
    _(type)                                   \
    _(next)                                   \
    _(vertexCapacityInput)                    \
    _(vertexCountOutput)                      \
    _(vertices)                               \
    _(indexCapacityInput)                     \
    _(indexCountOutput)                       \
    _(indices)

/// Calls your macro with the name of each member of XrEventDataVisibilityMaskChangedKHR, in order.
#define XR_LIST_STRUCT_XrEventDataVisibilityMaskChangedKHR(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(session)                                                \
    _(viewConfigurationType)                                  \
    _(viewIndex)

/// Calls your macro with the name of each member of XrCompositionLayerColorScaleBiasKHR, in order.
#define XR_LIST_STRUCT_XrCompositionLayerColorScaleBiasKHR(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(colorScale)                                             \
    _(colorBias)

/// Calls your macro with the name of each member of XrLoaderInitInfoBaseHeaderKHR, in order.
#define XR_LIST_STRUCT_XrLoaderInitInfoBaseHeaderKHR(_) \
    _(type)                                             \
    _(next)

/// Calls your macro with the name of each member of XrLoaderInitInfoAndroidKHR, in order.
#define XR_LIST_STRUCT_XrLoaderInitInfoAndroidKHR(_) \
    _(type)                                          \
    _(next)                                          \
    _(applicationVM)                                 \
    _(applicationContext)

/// Calls your macro with the name of each member of XrVulkanInstanceCreateInfoKHR, in order.
#define XR_LIST_STRUCT_XrVulkanInstanceCreateInfoKHR(_) \
    _(type)                                             \
    _(next)                                             \
    _(systemId)                                         \
    _(createFlags)                                      \
    _(pfnGetInstanceProcAddr)                           \
    _(vulkanCreateInfo)                                 \
    _(vulkanAllocator)

/// Calls your macro with the name of each member of XrVulkanDeviceCreateInfoKHR, in order.
#define XR_LIST_STRUCT_XrVulkanDeviceCreateInfoKHR(_) \
    _(type)                                           \
    _(next)                                           \
    _(systemId)                                       \
    _(createFlags)                                    \
    _(pfnGetInstanceProcAddr)                         \
    _(vulkanPhysicalDevice)                           \
    _(vulkanCreateInfo)                               \
    _(vulkanAllocator)

/// Calls your macro with the name of each member of XrVulkanGraphicsDeviceGetInfoKHR, in order.
#define XR_LIST_STRUCT_XrVulkanGraphicsDeviceGetInfoKHR(_) \
    _(type)                                                \
    _(next)                                                \
    _(systemId)                                            \
    _(vulkanInstance)

/// Calls your macro with the name of each member of XrCompositionLayerEquirect2KHR, in order.
#define XR_LIST_STRUCT_XrCompositionLayerEquirect2KHR(_) \
    _(type)                                              \
    _(next)                                              \
    _(layerFlags)                                        \
    _(space)                                             \
    _(eyeVisibility)                                     \
    _(subImage)                                          \
    _(pose)                                              \
    _(radius)                                            \
    _(centralHorizontalAngle)                            \
    _(upperVerticalAngle)                                \
    _(lowerVerticalAngle)

/// Calls your macro with the name of each member of XrBindingModificationBaseHeaderKHR, in order.
#define XR_LIST_STRUCT_XrBindingModificationBaseHeaderKHR(_) \
    _(type)                                                  \
    _(next)

/// Calls your macro with the name of each member of XrBindingModificationsKHR, in order.
#define XR_LIST_STRUCT_XrBindingModificationsKHR(_) \
    _(type)                                         \
    _(next)                                         \
    _(bindingModificationCount)                     \
    _(bindingModifications)

/// Calls your macro with the name of each member of XrEventDataPerfSettingsEXT, in order.
#define XR_LIST_STRUCT_XrEventDataPerfSettingsEXT(_) \
    _(type)                                          \
    _(next)                                          \
    _(domain)                                        \
    _(subDomain)                                     \
    _(fromLevel)                                     \
    _(toLevel)

/// Calls your macro with the name of each member of XrDebugUtilsObjectNameInfoEXT, in order.
#define XR_LIST_STRUCT_XrDebugUtilsObjectNameInfoEXT(_) \
    _(type)                                             \
    _(next)                                             \
    _(objectType)                                       \
    _(objectHandle)                                     \
    _(objectName)

/// Calls your macro with the name of each member of XrDebugUtilsLabelEXT, in order.
#define XR_LIST_STRUCT_XrDebugUtilsLabelEXT(_) \
    _(type)                                    \
    _(next)                                    \
    _(labelName)

/// Calls your macro with the name of each member of XrDebugUtilsMessengerCallbackDataEXT, in order.
#define XR_LIST_STRUCT_XrDebugUtilsMessengerCallbackDataEXT(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(messageId)                                               \
    _(functionName)                                            \
    _(message)                                                 \
    _(objectCount)                                             \
    _(objects)                                                 \
    _(sessionLabelCount)                                       \
    _(sessionLabels)

/// Calls your macro with the name of each member of XrDebugUtilsMessengerCreateInfoEXT, in order.
#define XR_LIST_STRUCT_XrDebugUtilsMessengerCreateInfoEXT(_) \
    _(type)                                                  \
    _(next)                                                  \
    _(messageSeverities)                                     \
    _(messageTypes)                                          \
    _(userCallback)                                          \
    _(userData)

/// Calls your macro with the name of each member of XrSystemEyeGazeInteractionPropertiesEXT, in order.
#define XR_LIST_STRUCT_XrSystemEyeGazeInteractionPropertiesEXT(_) \
    _(type)                                                       \
    _(next)                                                       \
    _(supportsEyeGazeInteraction)

/// Calls your macro with the name of each member of XrEyeGazeSampleTimeEXT, in order.
#define XR_LIST_STRUCT_XrEyeGazeSampleTimeEXT(_) \
    _(type)                                      \
    _(next)                                      \
    _(time)

/// Calls your macro with the name of each member of XrSessionCreateInfoOverlayEXTX, in order.
#define XR_LIST_STRUCT_XrSessionCreateInfoOverlayEXTX(_) \
    _(type)                                              \
    _(next)                                              \
    _(createFlags)                                       \
    _(sessionLayersPlacement)

/// Calls your macro with the name of each member of XrEventDataMainSessionVisibilityChangedEXTX, in order.
#define XR_LIST_STRUCT_XrEventDataMainSessionVisibilityChangedEXTX(_) \
    _(type)                                                           \
    _(next)                                                           \
    _(visible)                                                        \
    _(flags)

/// Calls your macro with the name of each member of XrSpatialAnchorCreateInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSpatialAnchorCreateInfoMSFT(_) \
    _(type)                                             \
    _(next)                                             \
    _(space)                                            \
    _(pose)                                             \
    _(time)

/// Calls your macro with the name of each member of XrSpatialAnchorSpaceCreateInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSpatialAnchorSpaceCreateInfoMSFT(_) \
    _(type)                                                  \
    _(next)                                                  \
    _(anchor)                                                \
    _(poseInAnchorSpace)

/// Calls your macro with the name of each member of XrCompositionLayerImageLayoutFB, in order.
#define XR_LIST_STRUCT_XrCompositionLayerImageLayoutFB(_) \
    _(type)                                               \
    _(next)                                               \
    _(flags)

/// Calls your macro with the name of each member of XrCompositionLayerAlphaBlendFB, in order.
#define XR_LIST_STRUCT_XrCompositionLayerAlphaBlendFB(_) \
    _(type)                                              \
    _(next)                                              \
    _(srcFactorColor)                                    \
    _(dstFactorColor)                                    \
    _(srcFactorAlpha)                                    \
    _(dstFactorAlpha)

/// Calls your macro with the name of each member of XrViewConfigurationDepthRangeEXT, in order.
#define XR_LIST_STRUCT_XrViewConfigurationDepthRangeEXT(_) \
    _(type)                                                \
    _(next)                                                \
    _(recommendedNearZ)                                    \
    _(minNearZ)                                            \
    _(recommendedFarZ)                                     \
    _(maxFarZ)

/// Calls your macro with the name of each member of XrGraphicsBindingEGLMNDX, in order.
#define XR_LIST_STRUCT_XrGraphicsBindingEGLMNDX(_) \
    _(type)                                        \
    _(next)                                        \
    _(getProcAddress)                              \
    _(display)                                     \
    _(config)                                      \
    _(context)

/// Calls your macro with the name of each member of XrSpatialGraphNodeSpaceCreateInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSpatialGraphNodeSpaceCreateInfoMSFT(_) \
    _(type)                                                     \
    _(next)                                                     \
    _(nodeType)                                                 \
    _(nodeId)                                                   \
    _(pose)

/// Calls your macro with the name of each member of XrSpatialGraphStaticNodeBindingCreateInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSpatialGraphStaticNodeBindingCreateInfoMSFT(_) \
    _(type)                                                             \
    _(next)                                                             \
    _(space)                                                            \
    _(poseInSpace)                                                      \
    _(time)

/// Calls your macro with the name of each member of XrSpatialGraphNodeBindingPropertiesGetInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSpatialGraphNodeBindingPropertiesGetInfoMSFT(_) \
    _(type)                                                              \
    _(next)

/// Calls your macro with the name of each member of XrSpatialGraphNodeBindingPropertiesMSFT, in order.
#define XR_LIST_STRUCT_XrSpatialGraphNodeBindingPropertiesMSFT(_) \
    _(type)                                                       \
    _(next)                                                       \
    _(nodeId)                                                     \
    _(poseInNodeSpace)

/// Calls your macro with the name of each member of XrSystemHandTrackingPropertiesEXT, in order.
#define XR_LIST_STRUCT_XrSystemHandTrackingPropertiesEXT(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(supportsHandTracking)

/// Calls your macro with the name of each member of XrHandTrackerCreateInfoEXT, in order.
#define XR_LIST_STRUCT_XrHandTrackerCreateInfoEXT(_) \
    _(type)                                          \
    _(next)                                          \
    _(hand)                                          \
    _(handJointSet)

/// Calls your macro with the name of each member of XrHandJointsLocateInfoEXT, in order.
#define XR_LIST_STRUCT_XrHandJointsLocateInfoEXT(_) \
    _(type)                                         \
    _(next)                                         \
    _(baseSpace)                                    \
    _(time)

/// Calls your macro with the name of each member of XrHandJointLocationEXT, in order.
#define XR_LIST_STRUCT_XrHandJointLocationEXT(_) \
    _(locationFlags)                             \
    _(pose)                                      \
    _(radius)

/// Calls your macro with the name of each member of XrHandJointVelocityEXT, in order.
#define XR_LIST_STRUCT_XrHandJointVelocityEXT(_) \
    _(velocityFlags)                             \
    _(linearVelocity)                            \
    _(angularVelocity)

/// Calls your macro with the name of each member of XrHandJointLocationsEXT, in order.
#define XR_LIST_STRUCT_XrHandJointLocationsEXT(_) \
    _(type)                                       \
    _(next)                                       \
    _(isActive)                                   \
    _(jointCount)                                 \
    _(jointLocations)

/// Calls your macro with the name of each member of XrHandJointVelocitiesEXT, in order.
#define XR_LIST_STRUCT_XrHandJointVelocitiesEXT(_) \
    _(type)                                        \
    _(next)                                        \
    _(jointCount)                                  \
    _(jointVelocities)

/// Calls your macro with the name of each member of XrSystemHandTrackingMeshPropertiesMSFT, in order.
#define XR_LIST_STRUCT_XrSystemHandTrackingMeshPropertiesMSFT(_) \
    _(type)                                                      \
    _(next)                                                      \
    _(supportsHandTrackingMesh)                                  \
    _(maxHandMeshIndexCount)                                     \
    _(maxHandMeshVertexCount)

/// Calls your macro with the name of each member of XrHandMeshSpaceCreateInfoMSFT, in order.
#define XR_LIST_STRUCT_XrHandMeshSpaceCreateInfoMSFT(_) \
    _(type)                                             \
    _(next)                                             \
    _(handPoseType)                                     \
    _(poseInHandMeshSpace)

/// Calls your macro with the name of each member of XrHandMeshUpdateInfoMSFT, in order.
#define XR_LIST_STRUCT_XrHandMeshUpdateInfoMSFT(_) \
    _(type)                                        \
    _(next)                                        \
    _(time)                                        \
    _(handPoseType)

/// Calls your macro with the name of each member of XrHandMeshIndexBufferMSFT, in order.
#define XR_LIST_STRUCT_XrHandMeshIndexBufferMSFT(_) \
    _(indexBufferKey)                               \
    _(indexCapacityInput)                           \
    _(indexCountOutput)                             \
    _(indices)

/// Calls your macro with the name of each member of XrHandMeshVertexMSFT, in order.
#define XR_LIST_STRUCT_XrHandMeshVertexMSFT(_) \
    _(position)                                \
    _(normal)

/// Calls your macro with the name of each member of XrHandMeshVertexBufferMSFT, in order.
#define XR_LIST_STRUCT_XrHandMeshVertexBufferMSFT(_) \
    _(vertexUpdateTime)                              \
    _(vertexCapacityInput)                           \
    _(vertexCountOutput)                             \
    _(vertices)

/// Calls your macro with the name of each member of XrHandMeshMSFT, in order.
#define XR_LIST_STRUCT_XrHandMeshMSFT(_) \
    _(type)                              \
    _(next)                              \
    _(isActive)                          \
    _(indexBufferChanged)                \
    _(vertexBufferChanged)               \
    _(indexBuffer)                       \
    _(vertexBuffer)

/// Calls your macro with the name of each member of XrHandPoseTypeInfoMSFT, in order.
#define XR_LIST_STRUCT_XrHandPoseTypeInfoMSFT(_) \
    _(type)                                      \
    _(next)                                      \
    _(handPoseType)

/// Calls your macro with the name of each member of XrSecondaryViewConfigurationSessionBeginInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSecondaryViewConfigurationSessionBeginInfoMSFT(_) \
    _(type)                                                                \
    _(next)                                                                \
    _(viewConfigurationCount)                                              \
    _(enabledViewConfigurationTypes)

/// Calls your macro with the name of each member of XrSecondaryViewConfigurationStateMSFT, in order.
#define XR_LIST_STRUCT_XrSecondaryViewConfigurationStateMSFT(_) \
    _(type)                                                     \
    _(next)                                                     \
    _(viewConfigurationType)                                    \
    _(active)

/// Calls your macro with the name of each member of XrSecondaryViewConfigurationFrameStateMSFT, in order.
#define XR_LIST_STRUCT_XrSecondaryViewConfigurationFrameStateMSFT(_) \
    _(type)                                                          \
    _(next)                                                          \
    _(viewConfigurationCount)                                        \
    _(viewConfigurationStates)

/// Calls your macro with the name of each member of XrSecondaryViewConfigurationLayerInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSecondaryViewConfigurationLayerInfoMSFT(_) \
    _(type)                                                         \
    _(next)                                                         \
    _(viewConfigurationType)                                        \
    _(environmentBlendMode)                                         \
    _(layerCount)                                                   \
    _(layers)

/// Calls your macro with the name of each member of XrSecondaryViewConfigurationFrameEndInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSecondaryViewConfigurationFrameEndInfoMSFT(_) \
    _(type)                                                            \
    _(next)                                                            \
    _(viewConfigurationCount)                                          \
    _(viewConfigurationLayersInfo)

/// Calls your macro with the name of each member of XrSecondaryViewConfigurationSwapchainCreateInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSecondaryViewConfigurationSwapchainCreateInfoMSFT(_) \
    _(type)                                                                   \
    _(next)                                                                   \
    _(viewConfigurationType)

/// Calls your macro with the name of each member of XrControllerModelKeyStateMSFT, in order.
#define XR_LIST_STRUCT_XrControllerModelKeyStateMSFT(_) \
    _(type)                                             \
    _(next)                                             \
    _(modelKey)

/// Calls your macro with the name of each member of XrControllerModelNodePropertiesMSFT, in order.
#define XR_LIST_STRUCT_XrControllerModelNodePropertiesMSFT(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(parentNodeName)                                         \
    _(nodeName)

/// Calls your macro with the name of each member of XrControllerModelPropertiesMSFT, in order.
#define XR_LIST_STRUCT_XrControllerModelPropertiesMSFT(_) \
    _(type)                                               \
    _(next)                                               \
    _(nodeCapacityInput)                                  \
    _(nodeCountOutput)                                    \
    _(nodeProperties)

/// Calls your macro with the name of each member of XrControllerModelNodeStateMSFT, in order.
#define XR_LIST_STRUCT_XrControllerModelNodeStateMSFT(_) \
    _(type)                                              \
    _(next)                                              \
    _(nodePose)

/// Calls your macro with the name of each member of XrControllerModelStateMSFT, in order.
#define XR_LIST_STRUCT_XrControllerModelStateMSFT(_) \
    _(type)                                          \
    _(next)                                          \
    _(nodeCapacityInput)                             \
    _(nodeCountOutput)                               \
    _(nodeStates)

/// Calls your macro with the name of each member of XrViewConfigurationViewFovEPIC, in order.
#define XR_LIST_STRUCT_XrViewConfigurationViewFovEPIC(_) \
    _(type)                                              \
    _(next)                                              \
    _(recommendedFov)                                    \
    _(maxMutableFov)

/// Calls your macro with the name of each member of XrHolographicWindowAttachmentMSFT, in order.
#define XR_LIST_STRUCT_XrHolographicWindowAttachmentMSFT(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(holographicSpace)                                     \
    _(coreWindow)

/// Calls your macro with the name of each member of XrCompositionLayerReprojectionInfoMSFT, in order.
#define XR_LIST_STRUCT_XrCompositionLayerReprojectionInfoMSFT(_) \
    _(type)                                                      \
    _(next)                                                      \
    _(reprojectionMode)

/// Calls your macro with the name of each member of XrCompositionLayerReprojectionPlaneOverrideMSFT, in order.
#define XR_LIST_STRUCT_XrCompositionLayerReprojectionPlaneOverrideMSFT(_) \
    _(type)                                                               \
    _(next)                                                               \
    _(position)                                                           \
    _(normal)                                                             \
    _(velocity)

/// Calls your macro with the name of each member of XrAndroidSurfaceSwapchainCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrAndroidSurfaceSwapchainCreateInfoFB(_) \
    _(type)                                                     \
    _(next)                                                     \
    _(createFlags)

/// Calls your macro with the name of each member of XrSwapchainStateBaseHeaderFB, in order.
#define XR_LIST_STRUCT_XrSwapchainStateBaseHeaderFB(_) \
    _(type)                                            \
    _(next)

/// Calls your macro with the name of each member of XrCompositionLayerSecureContentFB, in order.
#define XR_LIST_STRUCT_XrCompositionLayerSecureContentFB(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(flags)

/// Calls your macro with the name of each member of XrBodyJointLocationFB, in order.
#define XR_LIST_STRUCT_XrBodyJointLocationFB(_) \
    _(locationFlags)                            \
    _(pose)

/// Calls your macro with the name of each member of XrSystemBodyTrackingPropertiesFB, in order.
#define XR_LIST_STRUCT_XrSystemBodyTrackingPropertiesFB(_) \
    _(type)                                                \
    _(next)                                                \
    _(supportsBodyTracking)

/// Calls your macro with the name of each member of XrBodyTrackerCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrBodyTrackerCreateInfoFB(_) \
    _(type)                                         \
    _(next)                                         \
    _(bodyJointSet)

/// Calls your macro with the name of each member of XrBodySkeletonJointFB, in order.
#define XR_LIST_STRUCT_XrBodySkeletonJointFB(_) \
    _(joint)                                    \
    _(parentJoint)                              \
    _(pose)

/// Calls your macro with the name of each member of XrBodySkeletonFB, in order.
#define XR_LIST_STRUCT_XrBodySkeletonFB(_) \
    _(type)                                \
    _(next)                                \
    _(jointCount)                          \
    _(joints)

/// Calls your macro with the name of each member of XrBodyJointsLocateInfoFB, in order.
#define XR_LIST_STRUCT_XrBodyJointsLocateInfoFB(_) \
    _(type)                                        \
    _(next)                                        \
    _(baseSpace)                                   \
    _(time)

/// Calls your macro with the name of each member of XrBodyJointLocationsFB, in order.
#define XR_LIST_STRUCT_XrBodyJointLocationsFB(_) \
    _(type)                                      \
    _(next)                                      \
    _(isActive)                                  \
    _(confidence)                                \
    _(jointCount)                                \
    _(jointLocations)                            \
    _(skeletonChangedCount)                      \
    _(time)

/// Calls your macro with the name of each member of XrInteractionProfileDpadBindingEXT, in order.
#define XR_LIST_STRUCT_XrInteractionProfileDpadBindingEXT(_) \
    _(type)                                                  \
    _(next)                                                  \
    _(binding)                                               \
    _(actionSet)                                             \
    _(forceThreshold)                                        \
    _(forceThresholdReleased)                                \
    _(centerRegion)                                          \
    _(wedgeAngle)                                            \
    _(isSticky)                                              \
    _(onHaptic)                                              \
    _(offHaptic)

/// Calls your macro with the name of each member of XrInteractionProfileAnalogThresholdVALVE, in order.
#define XR_LIST_STRUCT_XrInteractionProfileAnalogThresholdVALVE(_) \
    _(type)                                                        \
    _(next)                                                        \
    _(action)                                                      \
    _(binding)                                                     \
    _(onThreshold)                                                 \
    _(offThreshold)                                                \
    _(onHaptic)                                                    \
    _(offHaptic)

/// Calls your macro with the name of each member of XrHandJointsMotionRangeInfoEXT, in order.
#define XR_LIST_STRUCT_XrHandJointsMotionRangeInfoEXT(_) \
    _(type)                                              \
    _(next)                                              \
    _(handJointsMotionRange)

/// Calls your macro with the name of each member of XrUuidMSFT, in order.
#define XR_LIST_STRUCT_XrUuidMSFT(_) _(bytes)

/// Calls your macro with the name of each member of XrSceneObserverCreateInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSceneObserverCreateInfoMSFT(_) \
    _(type)                                             \
    _(next)

/// Calls your macro with the name of each member of XrSceneCreateInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSceneCreateInfoMSFT(_) \
    _(type)                                     \
    _(next)

/// Calls your macro with the name of each member of XrSceneSphereBoundMSFT, in order.
#define XR_LIST_STRUCT_XrSceneSphereBoundMSFT(_) \
    _(center)                                    \
    _(radius)

/// Calls your macro with the name of each member of XrSceneOrientedBoxBoundMSFT, in order.
#define XR_LIST_STRUCT_XrSceneOrientedBoxBoundMSFT(_) \
    _(pose)                                           \
    _(extents)

/// Calls your macro with the name of each member of XrSceneFrustumBoundMSFT, in order.
#define XR_LIST_STRUCT_XrSceneFrustumBoundMSFT(_) \
    _(pose)                                       \
    _(fov)                                        \
    _(farDistance)

/// Calls your macro with the name of each member of XrSceneBoundsMSFT, in order.
#define XR_LIST_STRUCT_XrSceneBoundsMSFT(_) \
    _(space)                                \
    _(time)                                 \
    _(sphereCount)                          \
    _(spheres)                              \
    _(boxCount)                             \
    _(boxes)                                \
    _(frustumCount)                         \
    _(frustums)

/// Calls your macro with the name of each member of XrNewSceneComputeInfoMSFT, in order.
#define XR_LIST_STRUCT_XrNewSceneComputeInfoMSFT(_) \
    _(type)                                         \
    _(next)                                         \
    _(requestedFeatureCount)                        \
    _(requestedFeatures)                            \
    _(consistency)                                  \
    _(bounds)

/// Calls your macro with the name of each member of XrVisualMeshComputeLodInfoMSFT, in order.
#define XR_LIST_STRUCT_XrVisualMeshComputeLodInfoMSFT(_) \
    _(type)                                              \
    _(next)                                              \
    _(lod)

/// Calls your macro with the name of each member of XrSceneComponentMSFT, in order.
#define XR_LIST_STRUCT_XrSceneComponentMSFT(_) \
    _(componentType)                           \
    _(id)                                      \
    _(parentId)                                \
    _(updateTime)

/// Calls your macro with the name of each member of XrSceneComponentsMSFT, in order.
#define XR_LIST_STRUCT_XrSceneComponentsMSFT(_) \
    _(type)                                     \
    _(next)                                     \
    _(componentCapacityInput)                   \
    _(componentCountOutput)                     \
    _(components)

/// Calls your macro with the name of each member of XrSceneComponentsGetInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSceneComponentsGetInfoMSFT(_) \
    _(type)                                            \
    _(next)                                            \
    _(componentType)

/// Calls your macro with the name of each member of XrSceneComponentLocationMSFT, in order.
#define XR_LIST_STRUCT_XrSceneComponentLocationMSFT(_) \
    _(flags)                                           \
    _(pose)

/// Calls your macro with the name of each member of XrSceneComponentLocationsMSFT, in order.
#define XR_LIST_STRUCT_XrSceneComponentLocationsMSFT(_) \
    _(type)                                             \
    _(next)                                             \
    _(locationCount)                                    \
    _(locations)

/// Calls your macro with the name of each member of XrSceneComponentsLocateInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSceneComponentsLocateInfoMSFT(_) \
    _(type)                                               \
    _(next)                                               \
    _(baseSpace)                                          \
    _(time)                                               \
    _(componentIdCount)                                   \
    _(componentIds)

/// Calls your macro with the name of each member of XrSceneObjectMSFT, in order.
#define XR_LIST_STRUCT_XrSceneObjectMSFT(_) _(objectType)

/// Calls your macro with the name of each member of XrSceneObjectsMSFT, in order.
#define XR_LIST_STRUCT_XrSceneObjectsMSFT(_) \
    _(type)                                  \
    _(next)                                  \
    _(sceneObjectCount)                      \
    _(sceneObjects)

/// Calls your macro with the name of each member of XrSceneComponentParentFilterInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSceneComponentParentFilterInfoMSFT(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(parentId)

/// Calls your macro with the name of each member of XrSceneObjectTypesFilterInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSceneObjectTypesFilterInfoMSFT(_) \
    _(type)                                                \
    _(next)                                                \
    _(objectTypeCount)                                     \
    _(objectTypes)

/// Calls your macro with the name of each member of XrScenePlaneMSFT, in order.
#define XR_LIST_STRUCT_XrScenePlaneMSFT(_) \
    _(alignment)                           \
    _(size)                                \
    _(meshBufferId)                        \
    _(supportsIndicesUint16)

/// Calls your macro with the name of each member of XrScenePlanesMSFT, in order.
#define XR_LIST_STRUCT_XrScenePlanesMSFT(_) \
    _(type)                                 \
    _(next)                                 \
    _(scenePlaneCount)                      \
    _(scenePlanes)

/// Calls your macro with the name of each member of XrScenePlaneAlignmentFilterInfoMSFT, in order.
#define XR_LIST_STRUCT_XrScenePlaneAlignmentFilterInfoMSFT(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(alignmentCount)                                         \
    _(alignments)

/// Calls your macro with the name of each member of XrSceneMeshMSFT, in order.
#define XR_LIST_STRUCT_XrSceneMeshMSFT(_) \
    _(meshBufferId)                       \
    _(supportsIndicesUint16)

/// Calls your macro with the name of each member of XrSceneMeshesMSFT, in order.
#define XR_LIST_STRUCT_XrSceneMeshesMSFT(_) \
    _(type)                                 \
    _(next)                                 \
    _(sceneMeshCount)                       \
    _(sceneMeshes)

/// Calls your macro with the name of each member of XrSceneMeshBuffersGetInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSceneMeshBuffersGetInfoMSFT(_) \
    _(type)                                             \
    _(next)                                             \
    _(meshBufferId)

/// Calls your macro with the name of each member of XrSceneMeshBuffersMSFT, in order.
#define XR_LIST_STRUCT_XrSceneMeshBuffersMSFT(_) \
    _(type)                                      \
    _(next)

/// Calls your macro with the name of each member of XrSceneMeshVertexBufferMSFT, in order.
#define XR_LIST_STRUCT_XrSceneMeshVertexBufferMSFT(_) \
    _(type)                                           \
    _(next)                                           \
    _(vertexCapacityInput)                            \
    _(vertexCountOutput)                              \
    _(vertices)

/// Calls your macro with the name of each member of XrSceneMeshIndicesUint32MSFT, in order.
#define XR_LIST_STRUCT_XrSceneMeshIndicesUint32MSFT(_) \
    _(type)                                            \
    _(next)                                            \
    _(indexCapacityInput)                              \
    _(indexCountOutput)                                \
    _(indices)

/// Calls your macro with the name of each member of XrSceneMeshIndicesUint16MSFT, in order.
#define XR_LIST_STRUCT_XrSceneMeshIndicesUint16MSFT(_) \
    _(type)                                            \
    _(next)                                            \
    _(indexCapacityInput)                              \
    _(indexCountOutput)                                \
    _(indices)

/// Calls your macro with the name of each member of XrSerializedSceneFragmentDataGetInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSerializedSceneFragmentDataGetInfoMSFT(_) \
    _(type)                                                        \
    _(next)                                                        \
    _(sceneFragmentId)

/// Calls your macro with the name of each member of XrDeserializeSceneFragmentMSFT, in order.
#define XR_LIST_STRUCT_XrDeserializeSceneFragmentMSFT(_) \
    _(bufferSize)                                        \
    _(buffer)

/// Calls your macro with the name of each member of XrSceneDeserializeInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSceneDeserializeInfoMSFT(_) \
    _(type)                                          \
    _(next)                                          \
    _(fragmentCount)                                 \
    _(fragments)

/// Calls your macro with the name of each member of XrEventDataDisplayRefreshRateChangedFB, in order.
#define XR_LIST_STRUCT_XrEventDataDisplayRefreshRateChangedFB(_) \
    _(type)                                                      \
    _(next)                                                      \
    _(fromDisplayRefreshRate)                                    \
    _(toDisplayRefreshRate)

/// Calls your macro with the name of each member of XrViveTrackerPathsHTCX, in order.
#define XR_LIST_STRUCT_XrViveTrackerPathsHTCX(_) \
    _(type)                                      \
    _(next)                                      \
    _(persistentPath)                            \
    _(rolePath)

/// Calls your macro with the name of each member of XrEventDataViveTrackerConnectedHTCX, in order.
#define XR_LIST_STRUCT_XrEventDataViveTrackerConnectedHTCX(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(paths)

/// Calls your macro with the name of each member of XrSystemFacialTrackingPropertiesHTC, in order.
#define XR_LIST_STRUCT_XrSystemFacialTrackingPropertiesHTC(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(supportEyeFacialTracking)                               \
    _(supportLipFacialTracking)

/// Calls your macro with the name of each member of XrFacialExpressionsHTC, in order.
#define XR_LIST_STRUCT_XrFacialExpressionsHTC(_) \
    _(type)                                      \
    _(next)                                      \
    _(isActive)                                  \
    _(sampleTime)                                \
    _(expressionCount)                           \
    _(expressionWeightings)

/// Calls your macro with the name of each member of XrFacialTrackerCreateInfoHTC, in order.
#define XR_LIST_STRUCT_XrFacialTrackerCreateInfoHTC(_) \
    _(type)                                            \
    _(next)                                            \
    _(facialTrackingType)

/// Calls your macro with the name of each member of XrSystemColorSpacePropertiesFB, in order.
#define XR_LIST_STRUCT_XrSystemColorSpacePropertiesFB(_) \
    _(type)                                              \
    _(next)                                              \
    _(colorSpace)

/// Calls your macro with the name of each member of XrVector4sFB, in order.
#define XR_LIST_STRUCT_XrVector4sFB(_) \
    _(x)                               \
    _(y)                               \
    _(z)                               \
    _(w)

/// Calls your macro with the name of each member of XrHandTrackingMeshFB, in order.
#define XR_LIST_STRUCT_XrHandTrackingMeshFB(_) \
    _(type)                                    \
    _(next)                                    \
    _(jointCapacityInput)                      \
    _(jointCountOutput)                        \
    _(jointBindPoses)                          \
    _(jointRadii)                              \
    _(jointParents)                            \
    _(vertexCapacityInput)                     \
    _(vertexCountOutput)                       \
    _(vertexPositions)                         \
    _(vertexNormals)                           \
    _(vertexUVs)                               \
    _(vertexBlendIndices)                      \
    _(vertexBlendWeights)                      \
    _(indexCapacityInput)                      \
    _(indexCountOutput)                        \
    _(indices)

/// Calls your macro with the name of each member of XrHandTrackingScaleFB, in order.
#define XR_LIST_STRUCT_XrHandTrackingScaleFB(_) \
    _(type)                                     \
    _(next)                                     \
    _(sensorOutput)                             \
    _(currentOutput)                            \
    _(overrideHandScale)                        \
    _(overrideValueInput)

/// Calls your macro with the name of each member of XrHandTrackingAimStateFB, in order.
#define XR_LIST_STRUCT_XrHandTrackingAimStateFB(_) \
    _(type)                                        \
    _(next)                                        \
    _(status)                                      \
    _(aimPose)                                     \
    _(pinchStrengthIndex)                          \
    _(pinchStrengthMiddle)                         \
    _(pinchStrengthRing)                           \
    _(pinchStrengthLittle)

/// Calls your macro with the name of each member of XrHandCapsuleFB, in order.
#define XR_LIST_STRUCT_XrHandCapsuleFB(_) \
    _(points)                             \
    _(radius)                             \
    _(joint)

/// Calls your macro with the name of each member of XrHandTrackingCapsulesStateFB, in order.
#define XR_LIST_STRUCT_XrHandTrackingCapsulesStateFB(_) \
    _(type)                                             \
    _(next)                                             \
    _(capsules)

/// Calls your macro with the name of each member of XrSystemSpatialEntityPropertiesFB, in order.
#define XR_LIST_STRUCT_XrSystemSpatialEntityPropertiesFB(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(supportsSpatialEntity)

/// Calls your macro with the name of each member of XrSpatialAnchorCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrSpatialAnchorCreateInfoFB(_) \
    _(type)                                           \
    _(next)                                           \
    _(space)                                          \
    _(poseInSpace)                                    \
    _(time)

/// Calls your macro with the name of each member of XrSpaceComponentStatusSetInfoFB, in order.
#define XR_LIST_STRUCT_XrSpaceComponentStatusSetInfoFB(_) \
    _(type)                                               \
    _(next)                                               \
    _(componentType)                                      \
    _(enabled)                                            \
    _(timeout)

/// Calls your macro with the name of each member of XrSpaceComponentStatusFB, in order.
#define XR_LIST_STRUCT_XrSpaceComponentStatusFB(_) \
    _(type)                                        \
    _(next)                                        \
    _(enabled)                                     \
    _(changePending)

/// Calls your macro with the name of each member of XrEventDataSpatialAnchorCreateCompleteFB, in order.
#define XR_LIST_STRUCT_XrEventDataSpatialAnchorCreateCompleteFB(_) \
    _(type)                                                        \
    _(next)                                                        \
    _(requestId)                                                   \
    _(result)                                                      \
    _(space)                                                       \
    _(uuid)

/// Calls your macro with the name of each member of XrEventDataSpaceSetStatusCompleteFB, in order.
#define XR_LIST_STRUCT_XrEventDataSpaceSetStatusCompleteFB(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(requestId)                                              \
    _(result)                                                 \
    _(space)                                                  \
    _(uuid)                                                   \
    _(componentType)                                          \
    _(enabled)

/// Calls your macro with the name of each member of XrFoveationProfileCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrFoveationProfileCreateInfoFB(_) \
    _(type)                                              \
    _(next)

/// Calls your macro with the name of each member of XrSwapchainCreateInfoFoveationFB, in order.
#define XR_LIST_STRUCT_XrSwapchainCreateInfoFoveationFB(_) \
    _(type)                                                \
    _(next)                                                \
    _(flags)

/// Calls your macro with the name of each member of XrSwapchainStateFoveationFB, in order.
#define XR_LIST_STRUCT_XrSwapchainStateFoveationFB(_) \
    _(type)                                           \
    _(next)                                           \
    _(flags)                                          \
    _(profile)

/// Calls your macro with the name of each member of XrFoveationLevelProfileCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrFoveationLevelProfileCreateInfoFB(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(level)                                                  \
    _(verticalOffset)                                         \
    _(dynamic)

/// Calls your macro with the name of each member of XrSystemKeyboardTrackingPropertiesFB, in order.
#define XR_LIST_STRUCT_XrSystemKeyboardTrackingPropertiesFB(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(supportsKeyboardTracking)

/// Calls your macro with the name of each member of XrKeyboardTrackingDescriptionFB, in order.
#define XR_LIST_STRUCT_XrKeyboardTrackingDescriptionFB(_) \
    _(trackedKeyboardId)                                  \
    _(size)                                               \
    _(flags)                                              \
    _(name)

/// Calls your macro with the name of each member of XrKeyboardSpaceCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrKeyboardSpaceCreateInfoFB(_) \
    _(type)                                           \
    _(next)                                           \
    _(trackedKeyboardId)

/// Calls your macro with the name of each member of XrKeyboardTrackingQueryFB, in order.
#define XR_LIST_STRUCT_XrKeyboardTrackingQueryFB(_) \
    _(type)                                         \
    _(next)                                         \
    _(flags)

/// Calls your macro with the name of each member of XrTriangleMeshCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrTriangleMeshCreateInfoFB(_) \
    _(type)                                          \
    _(next)                                          \
    _(flags)                                         \
    _(windingOrder)                                  \
    _(vertexCount)                                   \
    _(vertexBuffer)                                  \
    _(triangleCount)                                 \
    _(indexBuffer)

/// Calls your macro with the name of each member of XrSystemPassthroughPropertiesFB, in order.
#define XR_LIST_STRUCT_XrSystemPassthroughPropertiesFB(_) \
    _(type)                                               \
    _(next)                                               \
    _(supportsPassthrough)

/// Calls your macro with the name of each member of XrSystemPassthroughProperties2FB, in order.
#define XR_LIST_STRUCT_XrSystemPassthroughProperties2FB(_) \
    _(type)                                                \
    _(next)                                                \
    _(capabilities)

/// Calls your macro with the name of each member of XrPassthroughCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrPassthroughCreateInfoFB(_) \
    _(type)                                         \
    _(next)                                         \
    _(flags)

/// Calls your macro with the name of each member of XrPassthroughLayerCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrPassthroughLayerCreateInfoFB(_) \
    _(type)                                              \
    _(next)                                              \
    _(passthrough)                                       \
    _(flags)                                             \
    _(purpose)

/// Calls your macro with the name of each member of XrCompositionLayerPassthroughFB, in order.
#define XR_LIST_STRUCT_XrCompositionLayerPassthroughFB(_) \
    _(type)                                               \
    _(next)                                               \
    _(flags)                                              \
    _(space)                                              \
    _(layerHandle)

/// Calls your macro with the name of each member of XrGeometryInstanceCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrGeometryInstanceCreateInfoFB(_) \
    _(type)                                              \
    _(next)                                              \
    _(layer)                                             \
    _(mesh)                                              \
    _(baseSpace)                                         \
    _(pose)                                              \
    _(scale)

/// Calls your macro with the name of each member of XrGeometryInstanceTransformFB, in order.
#define XR_LIST_STRUCT_XrGeometryInstanceTransformFB(_) \
    _(type)                                             \
    _(next)                                             \
    _(baseSpace)                                        \
    _(time)                                             \
    _(pose)                                             \
    _(scale)

/// Calls your macro with the name of each member of XrPassthroughStyleFB, in order.
#define XR_LIST_STRUCT_XrPassthroughStyleFB(_) \
    _(type)                                    \
    _(next)                                    \
    _(textureOpacityFactor)                    \
    _(edgeColor)

/// Calls your macro with the name of each member of XrPassthroughColorMapMonoToRgbaFB, in order.
#define XR_LIST_STRUCT_XrPassthroughColorMapMonoToRgbaFB(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(textureColorMap)

/// Calls your macro with the name of each member of XrPassthroughColorMapMonoToMonoFB, in order.
#define XR_LIST_STRUCT_XrPassthroughColorMapMonoToMonoFB(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(textureColorMap)

/// Calls your macro with the name of each member of XrPassthroughBrightnessContrastSaturationFB, in order.
#define XR_LIST_STRUCT_XrPassthroughBrightnessContrastSaturationFB(_) \
    _(type)                                                           \
    _(next)                                                           \
    _(brightness)                                                     \
    _(contrast)                                                       \
    _(saturation)

/// Calls your macro with the name of each member of XrEventDataPassthroughStateChangedFB, in order.
#define XR_LIST_STRUCT_XrEventDataPassthroughStateChangedFB(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(flags)

/// Calls your macro with the name of each member of XrRenderModelPathInfoFB, in order.
#define XR_LIST_STRUCT_XrRenderModelPathInfoFB(_) \
    _(type)                                       \
    _(next)                                       \
    _(path)

/// Calls your macro with the name of each member of XrRenderModelPropertiesFB, in order.
#define XR_LIST_STRUCT_XrRenderModelPropertiesFB(_) \
    _(type)                                         \
    _(next)                                         \
    _(vendorId)                                     \
    _(modelName)                                    \
    _(modelKey)                                     \
    _(modelVersion)                                 \
    _(flags)

/// Calls your macro with the name of each member of XrRenderModelBufferFB, in order.
#define XR_LIST_STRUCT_XrRenderModelBufferFB(_) \
    _(type)                                     \
    _(next)                                     \
    _(bufferCapacityInput)                      \
    _(bufferCountOutput)                        \
    _(buffer)

/// Calls your macro with the name of each member of XrRenderModelLoadInfoFB, in order.
#define XR_LIST_STRUCT_XrRenderModelLoadInfoFB(_) \
    _(type)                                       \
    _(next)                                       \
    _(modelKey)

/// Calls your macro with the name of each member of XrSystemRenderModelPropertiesFB, in order.
#define XR_LIST_STRUCT_XrSystemRenderModelPropertiesFB(_) \
    _(type)                                               \
    _(next)                                               \
    _(supportsRenderModelLoading)

/// Calls your macro with the name of each member of XrRenderModelCapabilitiesRequestFB, in order.
#define XR_LIST_STRUCT_XrRenderModelCapabilitiesRequestFB(_) \
    _(type)                                                  \
    _(next)                                                  \
    _(flags)

/// Calls your macro with the name of each member of XrViewLocateFoveatedRenderingVARJO, in order.
#define XR_LIST_STRUCT_XrViewLocateFoveatedRenderingVARJO(_) \
    _(type)                                                  \
    _(next)                                                  \
    _(foveatedRenderingActive)

/// Calls your macro with the name of each member of XrFoveatedViewConfigurationViewVARJO, in order.
#define XR_LIST_STRUCT_XrFoveatedViewConfigurationViewVARJO(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(foveatedRenderingActive)

/// Calls your macro with the name of each member of XrSystemFoveatedRenderingPropertiesVARJO, in order.
#define XR_LIST_STRUCT_XrSystemFoveatedRenderingPropertiesVARJO(_) \
    _(type)                                                        \
    _(next)                                                        \
    _(supportsFoveatedRendering)

/// Calls your macro with the name of each member of XrCompositionLayerDepthTestVARJO, in order.
#define XR_LIST_STRUCT_XrCompositionLayerDepthTestVARJO(_) \
    _(type)                                                \
    _(next)                                                \
    _(depthTestRangeNearZ)                                 \
    _(depthTestRangeFarZ)

/// Calls your macro with the name of each member of XrSystemMarkerTrackingPropertiesVARJO, in order.
#define XR_LIST_STRUCT_XrSystemMarkerTrackingPropertiesVARJO(_) \
    _(type)                                                     \
    _(next)                                                     \
    _(supportsMarkerTracking)

/// Calls your macro with the name of each member of XrEventDataMarkerTrackingUpdateVARJO, in order.
#define XR_LIST_STRUCT_XrEventDataMarkerTrackingUpdateVARJO(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(markerId)                                                \
    _(isActive)                                                \
    _(isPredicted)                                             \
    _(time)

/// Calls your macro with the name of each member of XrMarkerSpaceCreateInfoVARJO, in order.
#define XR_LIST_STRUCT_XrMarkerSpaceCreateInfoVARJO(_) \
    _(type)                                            \
    _(next)                                            \
    _(markerId)                                        \
    _(poseInMarkerSpace)

/// Calls your macro with the name of each member of XrFrameEndInfoML, in order.
#define XR_LIST_STRUCT_XrFrameEndInfoML(_) \
    _(type)                                \
    _(next)                                \
    _(focusDistance)                       \
    _(flags)

/// Calls your macro with the name of each member of XrGlobalDimmerFrameEndInfoML, in order.
#define XR_LIST_STRUCT_XrGlobalDimmerFrameEndInfoML(_) \
    _(type)                                            \
    _(next)                                            \
    _(dimmerValue)                                     \
    _(flags)

/// Calls your macro with the name of each member of XrCoordinateSpaceCreateInfoML, in order.
#define XR_LIST_STRUCT_XrCoordinateSpaceCreateInfoML(_) \
    _(type)                                             \
    _(next)                                             \
    _(cfuid)                                            \
    _(poseInCoordinateSpace)

/// Calls your macro with the name of each member of XrSystemMarkerUnderstandingPropertiesML, in order.
#define XR_LIST_STRUCT_XrSystemMarkerUnderstandingPropertiesML(_) \
    _(type)                                                       \
    _(next)                                                       \
    _(supportsMarkerUnderstanding)

/// Calls your macro with the name of each member of XrMarkerDetectorCreateInfoML, in order.
#define XR_LIST_STRUCT_XrMarkerDetectorCreateInfoML(_) \
    _(type)                                            \
    _(next)                                            \
    _(profile)                                         \
    _(markerType)

/// Calls your macro with the name of each member of XrMarkerDetectorArucoInfoML, in order.
#define XR_LIST_STRUCT_XrMarkerDetectorArucoInfoML(_) \
    _(type)                                           \
    _(next)                                           \
    _(arucoDict)

/// Calls your macro with the name of each member of XrMarkerDetectorSizeInfoML, in order.
#define XR_LIST_STRUCT_XrMarkerDetectorSizeInfoML(_) \
    _(type)                                          \
    _(next)                                          \
    _(markerLength)

/// Calls your macro with the name of each member of XrMarkerDetectorAprilTagInfoML, in order.
#define XR_LIST_STRUCT_XrMarkerDetectorAprilTagInfoML(_) \
    _(type)                                              \
    _(next)                                              \
    _(aprilTagDict)

/// Calls your macro with the name of each member of XrMarkerDetectorCustomProfileInfoML, in order.
#define XR_LIST_STRUCT_XrMarkerDetectorCustomProfileInfoML(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(fpsHint)                                                \
    _(resolutionHint)                                         \
    _(cameraHint)                                             \
    _(cornerRefineMethod)                                     \
    _(useEdgeRefinement)                                      \
    _(fullAnalysisIntervalHint)

/// Calls your macro with the name of each member of XrMarkerDetectorSnapshotInfoML, in order.
#define XR_LIST_STRUCT_XrMarkerDetectorSnapshotInfoML(_) \
    _(type)                                              \
    _(next)

/// Calls your macro with the name of each member of XrMarkerDetectorStateML, in order.
#define XR_LIST_STRUCT_XrMarkerDetectorStateML(_) \
    _(type)                                       \
    _(next)                                       \
    _(state)

/// Calls your macro with the name of each member of XrMarkerSpaceCreateInfoML, in order.
#define XR_LIST_STRUCT_XrMarkerSpaceCreateInfoML(_) \
    _(type)                                         \
    _(next)                                         \
    _(markerDetector)                               \
    _(marker)                                       \
    _(poseInMarkerSpace)

/// Calls your macro with the name of each member of XrLocalizationMapML, in order.
#define XR_LIST_STRUCT_XrLocalizationMapML(_) \
    _(type)                                   \
    _(next)                                   \
    _(name)                                   \
    _(mapUuid)                                \
    _(mapType)

/// Calls your macro with the name of each member of XrEventDataLocalizationChangedML, in order.
#define XR_LIST_STRUCT_XrEventDataLocalizationChangedML(_) \
    _(type)                                                \
    _(next)                                                \
    _(session)                                             \
    _(state)                                               \
    _(map)                                                 \
    _(confidence)                                          \
    _(errorFlags)

/// Calls your macro with the name of each member of XrLocalizationMapQueryInfoBaseHeaderML, in order.
#define XR_LIST_STRUCT_XrLocalizationMapQueryInfoBaseHeaderML(_) \
    _(type)                                                      \
    _(next)

/// Calls your macro with the name of each member of XrMapLocalizationRequestInfoML, in order.
#define XR_LIST_STRUCT_XrMapLocalizationRequestInfoML(_) \
    _(type)                                              \
    _(next)                                              \
    _(mapUuid)

/// Calls your macro with the name of each member of XrLocalizationMapImportInfoML, in order.
#define XR_LIST_STRUCT_XrLocalizationMapImportInfoML(_) \
    _(type)                                             \
    _(next)                                             \
    _(size)                                             \
    _(data)

/// Calls your macro with the name of each member of XrLocalizationEnableEventsInfoML, in order.
#define XR_LIST_STRUCT_XrLocalizationEnableEventsInfoML(_) \
    _(type)                                                \
    _(next)                                                \
    _(enabled)

/// Calls your macro with the name of each member of XrSpatialAnchorPersistenceNameMSFT, in order.
#define XR_LIST_STRUCT_XrSpatialAnchorPersistenceNameMSFT(_) _(name)

/// Calls your macro with the name of each member of XrSpatialAnchorPersistenceInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSpatialAnchorPersistenceInfoMSFT(_) \
    _(type)                                                  \
    _(next)                                                  \
    _(spatialAnchorPersistenceName)                          \
    _(spatialAnchor)

/// Calls your macro with the name of each member of XrSpatialAnchorFromPersistedAnchorCreateInfoMSFT, in order.
#define XR_LIST_STRUCT_XrSpatialAnchorFromPersistedAnchorCreateInfoMSFT(_) \
    _(type)                                                                \
    _(next)                                                                \
    _(spatialAnchorStore)                                                  \
    _(spatialAnchorPersistenceName)

/// Calls your macro with the name of each member of XrSceneMarkerMSFT, in order.
#define XR_LIST_STRUCT_XrSceneMarkerMSFT(_) \
    _(markerType)                           \
    _(lastSeenTime)                         \
    _(center)                               \
    _(size)

/// Calls your macro with the name of each member of XrSceneMarkersMSFT, in order.
#define XR_LIST_STRUCT_XrSceneMarkersMSFT(_) \
    _(type)                                  \
    _(next)                                  \
    _(sceneMarkerCapacityInput)              \
    _(sceneMarkers)

/// Calls your macro with the name of each member of XrSceneMarkerTypeFilterMSFT, in order.
#define XR_LIST_STRUCT_XrSceneMarkerTypeFilterMSFT(_) \
    _(type)                                           \
    _(next)                                           \
    _(markerTypeCount)                                \
    _(markerTypes)

/// Calls your macro with the name of each member of XrSceneMarkerQRCodeMSFT, in order.
#define XR_LIST_STRUCT_XrSceneMarkerQRCodeMSFT(_) \
    _(symbolType)                                 \
    _(version)

/// Calls your macro with the name of each member of XrSceneMarkerQRCodesMSFT, in order.
#define XR_LIST_STRUCT_XrSceneMarkerQRCodesMSFT(_) \
    _(type)                                        \
    _(next)                                        \
    _(qrCodeCapacityInput)                         \
    _(qrCodes)

/// Calls your macro with the name of each member of XrSpaceQueryInfoBaseHeaderFB, in order.
#define XR_LIST_STRUCT_XrSpaceQueryInfoBaseHeaderFB(_) \
    _(type)                                            \
    _(next)

/// Calls your macro with the name of each member of XrSpaceFilterInfoBaseHeaderFB, in order.
#define XR_LIST_STRUCT_XrSpaceFilterInfoBaseHeaderFB(_) \
    _(type)                                             \
    _(next)

/// Calls your macro with the name of each member of XrSpaceQueryInfoFB, in order.
#define XR_LIST_STRUCT_XrSpaceQueryInfoFB(_) \
    _(type)                                  \
    _(next)                                  \
    _(queryAction)                           \
    _(maxResultCount)                        \
    _(timeout)                               \
    _(filter)                                \
    _(excludeFilter)

/// Calls your macro with the name of each member of XrSpaceStorageLocationFilterInfoFB, in order.
#define XR_LIST_STRUCT_XrSpaceStorageLocationFilterInfoFB(_) \
    _(type)                                                  \
    _(next)                                                  \
    _(location)

/// Calls your macro with the name of each member of XrSpaceUuidFilterInfoFB, in order.
#define XR_LIST_STRUCT_XrSpaceUuidFilterInfoFB(_) \
    _(type)                                       \
    _(next)                                       \
    _(uuidCount)                                  \
    _(uuids)

/// Calls your macro with the name of each member of XrSpaceComponentFilterInfoFB, in order.
#define XR_LIST_STRUCT_XrSpaceComponentFilterInfoFB(_) \
    _(type)                                            \
    _(next)                                            \
    _(componentType)

/// Calls your macro with the name of each member of XrSpaceQueryResultFB, in order.
#define XR_LIST_STRUCT_XrSpaceQueryResultFB(_) \
    _(space)                                   \
    _(uuid)

/// Calls your macro with the name of each member of XrSpaceQueryResultsFB, in order.
#define XR_LIST_STRUCT_XrSpaceQueryResultsFB(_) \
    _(type)                                     \
    _(next)                                     \
    _(resultCapacityInput)                      \
    _(resultCountOutput)                        \
    _(results)

/// Calls your macro with the name of each member of XrEventDataSpaceQueryResultsAvailableFB, in order.
#define XR_LIST_STRUCT_XrEventDataSpaceQueryResultsAvailableFB(_) \
    _(type)                                                       \
    _(next)                                                       \
    _(requestId)

/// Calls your macro with the name of each member of XrEventDataSpaceQueryCompleteFB, in order.
#define XR_LIST_STRUCT_XrEventDataSpaceQueryCompleteFB(_) \
    _(type)                                               \
    _(next)                                               \
    _(requestId)                                          \
    _(result)

/// Calls your macro with the name of each member of XrSpaceSaveInfoFB, in order.
#define XR_LIST_STRUCT_XrSpaceSaveInfoFB(_) \
    _(type)                                 \
    _(next)                                 \
    _(space)                                \
    _(location)                             \
    _(persistenceMode)

/// Calls your macro with the name of each member of XrSpaceEraseInfoFB, in order.
#define XR_LIST_STRUCT_XrSpaceEraseInfoFB(_) \
    _(type)                                  \
    _(next)                                  \
    _(space)                                 \
    _(location)

/// Calls your macro with the name of each member of XrEventDataSpaceSaveCompleteFB, in order.
#define XR_LIST_STRUCT_XrEventDataSpaceSaveCompleteFB(_) \
    _(type)                                              \
    _(next)                                              \
    _(requestId)                                         \
    _(result)                                            \
    _(space)                                             \
    _(uuid)                                              \
    _(location)

/// Calls your macro with the name of each member of XrEventDataSpaceEraseCompleteFB, in order.
#define XR_LIST_STRUCT_XrEventDataSpaceEraseCompleteFB(_) \
    _(type)                                               \
    _(next)                                               \
    _(requestId)                                          \
    _(result)                                             \
    _(space)                                              \
    _(uuid)                                               \
    _(location)

/// Calls your macro with the name of each member of XrSwapchainImageFoveationVulkanFB, in order.
#define XR_LIST_STRUCT_XrSwapchainImageFoveationVulkanFB(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(image)                                                \
    _(width)                                                \
    _(height)

/// Calls your macro with the name of each member of XrSwapchainStateAndroidSurfaceDimensionsFB, in order.
#define XR_LIST_STRUCT_XrSwapchainStateAndroidSurfaceDimensionsFB(_) \
    _(type)                                                          \
    _(next)                                                          \
    _(width)                                                         \
    _(height)

/// Calls your macro with the name of each member of XrSwapchainStateSamplerOpenGLESFB, in order.
#define XR_LIST_STRUCT_XrSwapchainStateSamplerOpenGLESFB(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(minFilter)                                            \
    _(magFilter)                                            \
    _(wrapModeS)                                            \
    _(wrapModeT)                                            \
    _(swizzleRed)                                           \
    _(swizzleGreen)                                         \
    _(swizzleBlue)                                          \
    _(swizzleAlpha)                                         \
    _(maxAnisotropy)                                        \
    _(borderColor)

/// Calls your macro with the name of each member of XrSwapchainStateSamplerVulkanFB, in order.
#define XR_LIST_STRUCT_XrSwapchainStateSamplerVulkanFB(_) \
    _(type)                                               \
    _(next)                                               \
    _(minFilter)                                          \
    _(magFilter)                                          \
    _(mipmapMode)                                         \
    _(wrapModeS)                                          \
    _(wrapModeT)                                          \
    _(swizzleRed)                                         \
    _(swizzleGreen)                                       \
    _(swizzleBlue)                                        \
    _(swizzleAlpha)                                       \
    _(maxAnisotropy)                                      \
    _(borderColor)

/// Calls your macro with the name of each member of XrSpaceShareInfoFB, in order.
#define XR_LIST_STRUCT_XrSpaceShareInfoFB(_) \
    _(type)                                  \
    _(next)                                  \
    _(spaceCount)                            \
    _(spaces)                                \
    _(userCount)                             \
    _(users)

/// Calls your macro with the name of each member of XrEventDataSpaceShareCompleteFB, in order.
#define XR_LIST_STRUCT_XrEventDataSpaceShareCompleteFB(_) \
    _(type)                                               \
    _(next)                                               \
    _(requestId)                                          \
    _(result)

/// Calls your macro with the name of each member of XrCompositionLayerSpaceWarpInfoFB, in order.
#define XR_LIST_STRUCT_XrCompositionLayerSpaceWarpInfoFB(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(layerFlags)                                           \
    _(motionVectorSubImage)                                 \
    _(appSpaceDeltaPose)                                    \
    _(depthSubImage)                                        \
    _(minDepth)                                             \
    _(maxDepth)                                             \
    _(nearZ)                                                \
    _(farZ)

/// Calls your macro with the name of each member of XrSystemSpaceWarpPropertiesFB, in order.
#define XR_LIST_STRUCT_XrSystemSpaceWarpPropertiesFB(_) \
    _(type)                                             \
    _(next)                                             \
    _(recommendedMotionVectorImageRectWidth)            \
    _(recommendedMotionVectorImageRectHeight)

/// Calls your macro with the name of each member of XrHapticAmplitudeEnvelopeVibrationFB, in order.
#define XR_LIST_STRUCT_XrHapticAmplitudeEnvelopeVibrationFB(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(duration)                                                \
    _(amplitudeCount)                                          \
    _(amplitudes)

/// Calls your macro with the name of each member of XrOffset3DfFB, in order.
#define XR_LIST_STRUCT_XrOffset3DfFB(_) \
    _(x)                                \
    _(y)                                \
    _(z)

/// Calls your macro with the name of each member of XrRect3DfFB, in order.
#define XR_LIST_STRUCT_XrRect3DfFB(_) \
    _(offset)                         \
    _(extent)

/// Calls your macro with the name of each member of XrSemanticLabelsFB, in order.
#define XR_LIST_STRUCT_XrSemanticLabelsFB(_) \
    _(type)                                  \
    _(next)                                  \
    _(bufferCapacityInput)                   \
    _(bufferCountOutput)                     \
    _(buffer)

/// Calls your macro with the name of each member of XrRoomLayoutFB, in order.
#define XR_LIST_STRUCT_XrRoomLayoutFB(_) \
    _(type)                              \
    _(next)                              \
    _(floorUuid)                         \
    _(ceilingUuid)                       \
    _(wallUuidCapacityInput)             \
    _(wallUuidCountOutput)               \
    _(wallUuids)

/// Calls your macro with the name of each member of XrBoundary2DFB, in order.
#define XR_LIST_STRUCT_XrBoundary2DFB(_) \
    _(type)                              \
    _(next)                              \
    _(vertexCapacityInput)               \
    _(vertexCountOutput)                 \
    _(vertices)

/// Calls your macro with the name of each member of XrSemanticLabelsSupportInfoFB, in order.
#define XR_LIST_STRUCT_XrSemanticLabelsSupportInfoFB(_) \
    _(type)                                             \
    _(next)                                             \
    _(flags)                                            \
    _(recognizedLabels)

/// Calls your macro with the name of each member of XrDigitalLensControlALMALENCE, in order.
#define XR_LIST_STRUCT_XrDigitalLensControlALMALENCE(_) \
    _(type)                                             \
    _(next)                                             \
    _(flags)

/// Calls your macro with the name of each member of XrEventDataSceneCaptureCompleteFB, in order.
#define XR_LIST_STRUCT_XrEventDataSceneCaptureCompleteFB(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(requestId)                                            \
    _(result)

/// Calls your macro with the name of each member of XrSceneCaptureRequestInfoFB, in order.
#define XR_LIST_STRUCT_XrSceneCaptureRequestInfoFB(_) \
    _(type)                                           \
    _(next)                                           \
    _(requestByteCount)                               \
    _(request)

/// Calls your macro with the name of each member of XrSpaceContainerFB, in order.
#define XR_LIST_STRUCT_XrSpaceContainerFB(_) \
    _(type)                                  \
    _(next)                                  \
    _(uuidCapacityInput)                     \
    _(uuidCountOutput)                       \
    _(uuids)

/// Calls your macro with the name of each member of XrFoveationEyeTrackedProfileCreateInfoMETA, in order.
#define XR_LIST_STRUCT_XrFoveationEyeTrackedProfileCreateInfoMETA(_) \
    _(type)                                                          \
    _(next)                                                          \
    _(flags)

/// Calls your macro with the name of each member of XrFoveationEyeTrackedStateMETA, in order.
#define XR_LIST_STRUCT_XrFoveationEyeTrackedStateMETA(_) \
    _(type)                                              \
    _(next)                                              \
    _(foveationCenter)                                   \
    _(flags)

/// Calls your macro with the name of each member of XrSystemFoveationEyeTrackedPropertiesMETA, in order.
#define XR_LIST_STRUCT_XrSystemFoveationEyeTrackedPropertiesMETA(_) \
    _(type)                                                         \
    _(next)                                                         \
    _(supportsFoveationEyeTracked)

/// Calls your macro with the name of each member of XrSystemFaceTrackingPropertiesFB, in order.
#define XR_LIST_STRUCT_XrSystemFaceTrackingPropertiesFB(_) \
    _(type)                                                \
    _(next)                                                \
    _(supportsFaceTracking)

/// Calls your macro with the name of each member of XrFaceTrackerCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrFaceTrackerCreateInfoFB(_) \
    _(type)                                         \
    _(next)                                         \
    _(faceExpressionSet)

/// Calls your macro with the name of each member of XrFaceExpressionInfoFB, in order.
#define XR_LIST_STRUCT_XrFaceExpressionInfoFB(_) \
    _(type)                                      \
    _(next)                                      \
    _(time)

/// Calls your macro with the name of each member of XrFaceExpressionStatusFB, in order.
#define XR_LIST_STRUCT_XrFaceExpressionStatusFB(_) \
    _(isValid)                                     \
    _(isEyeFollowingBlendshapesValid)

/// Calls your macro with the name of each member of XrFaceExpressionWeightsFB, in order.
#define XR_LIST_STRUCT_XrFaceExpressionWeightsFB(_) \
    _(type)                                         \
    _(next)                                         \
    _(weightCount)                                  \
    _(weights)                                      \
    _(confidenceCount)                              \
    _(confidences)                                  \
    _(status)                                       \
    _(time)

/// Calls your macro with the name of each member of XrEyeGazeFB, in order.
#define XR_LIST_STRUCT_XrEyeGazeFB(_) \
    _(isValid)                        \
    _(gazePose)                       \
    _(gazeConfidence)

/// Calls your macro with the name of each member of XrEyeTrackerCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrEyeTrackerCreateInfoFB(_) \
    _(type)                                        \
    _(next)

/// Calls your macro with the name of each member of XrEyeGazesInfoFB, in order.
#define XR_LIST_STRUCT_XrEyeGazesInfoFB(_) \
    _(type)                                \
    _(next)                                \
    _(baseSpace)                           \
    _(time)

/// Calls your macro with the name of each member of XrSystemEyeTrackingPropertiesFB, in order.
#define XR_LIST_STRUCT_XrSystemEyeTrackingPropertiesFB(_) \
    _(type)                                               \
    _(next)                                               \
    _(supportsEyeTracking)

/// Calls your macro with the name of each member of XrEyeGazesFB, in order.
#define XR_LIST_STRUCT_XrEyeGazesFB(_) \
    _(type)                            \
    _(next)                            \
    _(gaze)                            \
    _(time)

/// Calls your macro with the name of each member of XrPassthroughKeyboardHandsIntensityFB, in order.
#define XR_LIST_STRUCT_XrPassthroughKeyboardHandsIntensityFB(_) \
    _(type)                                                     \
    _(next)                                                     \
    _(leftHandIntensity)                                        \
    _(rightHandIntensity)

/// Calls your macro with the name of each member of XrCompositionLayerSettingsFB, in order.
#define XR_LIST_STRUCT_XrCompositionLayerSettingsFB(_) \
    _(type)                                            \
    _(next)                                            \
    _(layerFlags)

/// Calls your macro with the name of each member of XrHapticPcmVibrationFB, in order.
#define XR_LIST_STRUCT_XrHapticPcmVibrationFB(_) \
    _(type)                                      \
    _(next)                                      \
    _(bufferSize)                                \
    _(buffer)                                    \
    _(sampleRate)                                \
    _(append)                                    \
    _(samplesConsumed)

/// Calls your macro with the name of each member of XrDevicePcmSampleRateStateFB, in order.
#define XR_LIST_STRUCT_XrDevicePcmSampleRateStateFB(_) \
    _(type)                                            \
    _(next)                                            \
    _(sampleRate)

/// Calls your macro with the name of each member of XrCompositionLayerDepthTestFB, in order.
#define XR_LIST_STRUCT_XrCompositionLayerDepthTestFB(_) \
    _(type)                                             \
    _(next)                                             \
    _(depthMask)                                        \
    _(compareOp)

/// Calls your macro with the name of each member of XrLocalDimmingFrameEndInfoMETA, in order.
#define XR_LIST_STRUCT_XrLocalDimmingFrameEndInfoMETA(_) \
    _(type)                                              \
    _(next)                                              \
    _(localDimmingMode)

/// Calls your macro with the name of each member of XrPassthroughPreferencesMETA, in order.
#define XR_LIST_STRUCT_XrPassthroughPreferencesMETA(_) \
    _(type)                                            \
    _(next)                                            \
    _(flags)

/// Calls your macro with the name of each member of XrSystemVirtualKeyboardPropertiesMETA, in order.
#define XR_LIST_STRUCT_XrSystemVirtualKeyboardPropertiesMETA(_) \
    _(type)                                                     \
    _(next)                                                     \
    _(supportsVirtualKeyboard)

/// Calls your macro with the name of each member of XrVirtualKeyboardCreateInfoMETA, in order.
#define XR_LIST_STRUCT_XrVirtualKeyboardCreateInfoMETA(_) \
    _(type)                                               \
    _(next)

/// Calls your macro with the name of each member of XrVirtualKeyboardSpaceCreateInfoMETA, in order.
#define XR_LIST_STRUCT_XrVirtualKeyboardSpaceCreateInfoMETA(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(locationType)                                            \
    _(space)                                                   \
    _(poseInSpace)

/// Calls your macro with the name of each member of XrVirtualKeyboardLocationInfoMETA, in order.
#define XR_LIST_STRUCT_XrVirtualKeyboardLocationInfoMETA(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(locationType)                                         \
    _(space)                                                \
    _(poseInSpace)                                          \
    _(scale)

/// Calls your macro with the name of each member of XrVirtualKeyboardModelVisibilitySetInfoMETA, in order.
#define XR_LIST_STRUCT_XrVirtualKeyboardModelVisibilitySetInfoMETA(_) \
    _(type)                                                           \
    _(next)                                                           \
    _(visible)

/// Calls your macro with the name of each member of XrVirtualKeyboardAnimationStateMETA, in order.
#define XR_LIST_STRUCT_XrVirtualKeyboardAnimationStateMETA(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(animationIndex)                                         \
    _(fraction)

/// Calls your macro with the name of each member of XrVirtualKeyboardModelAnimationStatesMETA, in order.
#define XR_LIST_STRUCT_XrVirtualKeyboardModelAnimationStatesMETA(_) \
    _(type)                                                         \
    _(next)                                                         \
    _(stateCapacityInput)                                           \
    _(stateCountOutput)                                             \
    _(states)

/// Calls your macro with the name of each member of XrVirtualKeyboardTextureDataMETA, in order.
#define XR_LIST_STRUCT_XrVirtualKeyboardTextureDataMETA(_) \
    _(type)                                                \
    _(next)                                                \
    _(textureWidth)                                        \
    _(textureHeight)                                       \
    _(bufferCapacityInput)                                 \
    _(bufferCountOutput)                                   \
    _(buffer)

/// Calls your macro with the name of each member of XrVirtualKeyboardInputInfoMETA, in order.
#define XR_LIST_STRUCT_XrVirtualKeyboardInputInfoMETA(_) \
    _(type)                                              \
    _(next)                                              \
    _(inputSource)                                       \
    _(inputSpace)                                        \
    _(inputPoseInSpace)                                  \
    _(inputState)

/// Calls your macro with the name of each member of XrVirtualKeyboardTextContextChangeInfoMETA, in order.
#define XR_LIST_STRUCT_XrVirtualKeyboardTextContextChangeInfoMETA(_) \
    _(type)                                                          \
    _(next)                                                          \
    _(textContext)

/// Calls your macro with the name of each member of XrEventDataVirtualKeyboardCommitTextMETA, in order.
#define XR_LIST_STRUCT_XrEventDataVirtualKeyboardCommitTextMETA(_) \
    _(type)                                                        \
    _(next)                                                        \
    _(keyboard)                                                    \
    _(text)

/// Calls your macro with the name of each member of XrEventDataVirtualKeyboardBackspaceMETA, in order.
#define XR_LIST_STRUCT_XrEventDataVirtualKeyboardBackspaceMETA(_) \
    _(type)                                                       \
    _(next)                                                       \
    _(keyboard)

/// Calls your macro with the name of each member of XrEventDataVirtualKeyboardEnterMETA, in order.
#define XR_LIST_STRUCT_XrEventDataVirtualKeyboardEnterMETA(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(keyboard)

/// Calls your macro with the name of each member of XrEventDataVirtualKeyboardShownMETA, in order.
#define XR_LIST_STRUCT_XrEventDataVirtualKeyboardShownMETA(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(keyboard)

/// Calls your macro with the name of each member of XrEventDataVirtualKeyboardHiddenMETA, in order.
#define XR_LIST_STRUCT_XrEventDataVirtualKeyboardHiddenMETA(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(keyboard)

/// Calls your macro with the name of each member of XrExternalCameraIntrinsicsOCULUS, in order.
#define XR_LIST_STRUCT_XrExternalCameraIntrinsicsOCULUS(_) \
    _(lastChangeTime)                                      \
    _(fov)                                                 \
    _(virtualNearPlaneDistance)                            \
    _(virtualFarPlaneDistance)                             \
    _(imageSensorPixelResolution)

/// Calls your macro with the name of each member of XrExternalCameraExtrinsicsOCULUS, in order.
#define XR_LIST_STRUCT_XrExternalCameraExtrinsicsOCULUS(_) \
    _(lastChangeTime)                                      \
    _(cameraStatusFlags)                                   \
    _(attachedToDevice)                                    \
    _(relativePose)

/// Calls your macro with the name of each member of XrExternalCameraOCULUS, in order.
#define XR_LIST_STRUCT_XrExternalCameraOCULUS(_) \
    _(type)                                      \
    _(next)                                      \
    _(name)                                      \
    _(intrinsics)                                \
    _(extrinsics)

/// Calls your macro with the name of each member of XrVulkanSwapchainCreateInfoMETA, in order.
#define XR_LIST_STRUCT_XrVulkanSwapchainCreateInfoMETA(_) \
    _(type)                                               \
    _(next)                                               \
    _(additionalCreateFlags)                              \
    _(additionalUsageFlags)

/// Calls your macro with the name of each member of XrPerformanceMetricsStateMETA, in order.
#define XR_LIST_STRUCT_XrPerformanceMetricsStateMETA(_) \
    _(type)                                             \
    _(next)                                             \
    _(enabled)

/// Calls your macro with the name of each member of XrPerformanceMetricsCounterMETA, in order.
#define XR_LIST_STRUCT_XrPerformanceMetricsCounterMETA(_) \
    _(type)                                               \
    _(next)                                               \
    _(counterFlags)                                       \
    _(counterUnit)                                        \
    _(uintValue)                                          \
    _(floatValue)

/// Calls your macro with the name of each member of XrSpaceListSaveInfoFB, in order.
#define XR_LIST_STRUCT_XrSpaceListSaveInfoFB(_) \
    _(type)                                     \
    _(next)                                     \
    _(spaceCount)                               \
    _(spaces)                                   \
    _(location)

/// Calls your macro with the name of each member of XrEventDataSpaceListSaveCompleteFB, in order.
#define XR_LIST_STRUCT_XrEventDataSpaceListSaveCompleteFB(_) \
    _(type)                                                  \
    _(next)                                                  \
    _(requestId)                                             \
    _(result)

/// Calls your macro with the name of each member of XrSpaceUserCreateInfoFB, in order.
#define XR_LIST_STRUCT_XrSpaceUserCreateInfoFB(_) \
    _(type)                                       \
    _(next)                                       \
    _(userId)

/// Calls your macro with the name of each member of XrSystemHeadsetIdPropertiesMETA, in order.
#define XR_LIST_STRUCT_XrSystemHeadsetIdPropertiesMETA(_) \
    _(type)                                               \
    _(next)                                               \
    _(id)

/// Calls your macro with the name of each member of XrRecommendedLayerResolutionMETA, in order.
#define XR_LIST_STRUCT_XrRecommendedLayerResolutionMETA(_) \
    _(type)                                                \
    _(next)                                                \
    _(recommendedImageDimensions)                          \
    _(isValid)

/// Calls your macro with the name of each member of XrRecommendedLayerResolutionGetInfoMETA, in order.
#define XR_LIST_STRUCT_XrRecommendedLayerResolutionGetInfoMETA(_) \
    _(type)                                                       \
    _(next)                                                       \
    _(layer)                                                      \
    _(predictedDisplayTime)

/// Calls your macro with the name of each member of XrPassthroughColorLutDataMETA, in order.
#define XR_LIST_STRUCT_XrPassthroughColorLutDataMETA(_) \
    _(bufferSize)                                       \
    _(buffer)

/// Calls your macro with the name of each member of XrPassthroughColorLutCreateInfoMETA, in order.
#define XR_LIST_STRUCT_XrPassthroughColorLutCreateInfoMETA(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(channels)                                               \
    _(resolution)                                             \
    _(data)

/// Calls your macro with the name of each member of XrPassthroughColorLutUpdateInfoMETA, in order.
#define XR_LIST_STRUCT_XrPassthroughColorLutUpdateInfoMETA(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(data)

/// Calls your macro with the name of each member of XrPassthroughColorMapLutMETA, in order.
#define XR_LIST_STRUCT_XrPassthroughColorMapLutMETA(_) \
    _(type)                                            \
    _(next)                                            \
    _(colorLut)                                        \
    _(weight)

/// Calls your macro with the name of each member of XrPassthroughColorMapInterpolatedLutMETA, in order.
#define XR_LIST_STRUCT_XrPassthroughColorMapInterpolatedLutMETA(_) \
    _(type)                                                        \
    _(next)                                                        \
    _(sourceColorLut)                                              \
    _(targetColorLut)                                              \
    _(weight)

/// Calls your macro with the name of each member of XrSystemPassthroughColorLutPropertiesMETA, in order.
#define XR_LIST_STRUCT_XrSystemPassthroughColorLutPropertiesMETA(_) \
    _(type)                                                         \
    _(next)                                                         \
    _(maxColorLutResolution)

/// Calls your macro with the name of each member of XrSpaceTriangleMeshGetInfoMETA, in order.
#define XR_LIST_STRUCT_XrSpaceTriangleMeshGetInfoMETA(_) \
    _(type)                                              \
    _(next)

/// Calls your macro with the name of each member of XrSpaceTriangleMeshMETA, in order.
#define XR_LIST_STRUCT_XrSpaceTriangleMeshMETA(_) \
    _(type)                                       \
    _(next)                                       \
    _(vertexCapacityInput)                        \
    _(vertexCountOutput)                          \
    _(vertices)                                   \
    _(indexCapacityInput)                         \
    _(indexCountOutput)                           \
    _(indices)

/// Calls your macro with the name of each member of XrSystemFaceTrackingProperties2FB, in order.
#define XR_LIST_STRUCT_XrSystemFaceTrackingProperties2FB(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(supportsVisualFaceTracking)                           \
    _(supportsAudioFaceTracking)

/// Calls your macro with the name of each member of XrFaceTrackerCreateInfo2FB, in order.
#define XR_LIST_STRUCT_XrFaceTrackerCreateInfo2FB(_) \
    _(type)                                          \
    _(next)                                          \
    _(faceExpressionSet)                             \
    _(requestedDataSourceCount)                      \
    _(requestedDataSources)

/// Calls your macro with the name of each member of XrFaceExpressionInfo2FB, in order.
#define XR_LIST_STRUCT_XrFaceExpressionInfo2FB(_) \
    _(type)                                       \
    _(next)                                       \
    _(time)

/// Calls your macro with the name of each member of XrFaceExpressionWeights2FB, in order.
#define XR_LIST_STRUCT_XrFaceExpressionWeights2FB(_) \
    _(type)                                          \
    _(next)                                          \
    _(weightCount)                                   \
    _(weights)                                       \
    _(confidenceCount)                               \
    _(confidences)                                   \
    _(isValid)                                       \
    _(isEyeFollowingBlendshapesValid)                \
    _(dataSource)                                    \
    _(time)

/// Calls your macro with the name of each member of XrEnvironmentDepthProviderCreateInfoMETA, in order.
#define XR_LIST_STRUCT_XrEnvironmentDepthProviderCreateInfoMETA(_) \
    _(type)                                                        \
    _(next)                                                        \
    _(createFlags)

/// Calls your macro with the name of each member of XrEnvironmentDepthSwapchainCreateInfoMETA, in order.
#define XR_LIST_STRUCT_XrEnvironmentDepthSwapchainCreateInfoMETA(_) \
    _(type)                                                         \
    _(next)                                                         \
    _(createFlags)

/// Calls your macro with the name of each member of XrEnvironmentDepthSwapchainStateMETA, in order.
#define XR_LIST_STRUCT_XrEnvironmentDepthSwapchainStateMETA(_) \
    _(type)                                                    \
    _(next)                                                    \
    _(width)                                                   \
    _(height)

/// Calls your macro with the name of each member of XrEnvironmentDepthImageAcquireInfoMETA, in order.
#define XR_LIST_STRUCT_XrEnvironmentDepthImageAcquireInfoMETA(_) \
    _(type)                                                      \
    _(next)                                                      \
    _(space)                                                     \
    _(displayTime)

/// Calls your macro with the name of each member of XrEnvironmentDepthImageViewMETA, in order.
#define XR_LIST_STRUCT_XrEnvironmentDepthImageViewMETA(_) \
    _(type)                                               \
    _(next)                                               \
    _(fov)                                                \
    _(pose)

/// Calls your macro with the name of each member of XrEnvironmentDepthImageMETA, in order.
#define XR_LIST_STRUCT_XrEnvironmentDepthImageMETA(_) \
    _(type)                                           \
    _(next)                                           \
    _(swapchainIndex)                                 \
    _(nearZ)                                          \
    _(farZ)                                           \
    _(views)

/// Calls your macro with the name of each member of XrEnvironmentDepthHandRemovalSetInfoMETA, in order.
#define XR_LIST_STRUCT_XrEnvironmentDepthHandRemovalSetInfoMETA(_) \
    _(type)                                                        \
    _(next)                                                        \
    _(enabled)

/// Calls your macro with the name of each member of XrSystemEnvironmentDepthPropertiesMETA, in order.
#define XR_LIST_STRUCT_XrSystemEnvironmentDepthPropertiesMETA(_) \
    _(type)                                                      \
    _(next)                                                      \
    _(supportsEnvironmentDepth)                                  \
    _(supportsHandRemoval)

/// Calls your macro with the name of each member of XrPassthroughCreateInfoHTC, in order.
#define XR_LIST_STRUCT_XrPassthroughCreateInfoHTC(_) \
    _(type)                                          \
    _(next)                                          \
    _(form)

/// Calls your macro with the name of each member of XrPassthroughColorHTC, in order.
#define XR_LIST_STRUCT_XrPassthroughColorHTC(_) \
    _(type)                                     \
    _(next)                                     \
    _(alpha)

/// Calls your macro with the name of each member of XrPassthroughMeshTransformInfoHTC, in order.
#define XR_LIST_STRUCT_XrPassthroughMeshTransformInfoHTC(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(vertexCount)                                          \
    _(vertices)                                             \
    _(indexCount)                                           \
    _(indices)                                              \
    _(baseSpace)                                            \
    _(time)                                                 \
    _(pose)                                                 \
    _(scale)

/// Calls your macro with the name of each member of XrCompositionLayerPassthroughHTC, in order.
#define XR_LIST_STRUCT_XrCompositionLayerPassthroughHTC(_) \
    _(type)                                                \
    _(next)                                                \
    _(layerFlags)                                          \
    _(space)                                               \
    _(passthrough)                                         \
    _(color)

/// Calls your macro with the name of each member of XrFoveationApplyInfoHTC, in order.
#define XR_LIST_STRUCT_XrFoveationApplyInfoHTC(_) \
    _(type)                                       \
    _(next)                                       \
    _(mode)                                       \
    _(subImageCount)                              \
    _(subImages)

/// Calls your macro with the name of each member of XrFoveationConfigurationHTC, in order.
#define XR_LIST_STRUCT_XrFoveationConfigurationHTC(_) \
    _(level)                                          \
    _(clearFovDegree)                                 \
    _(focalCenterOffset)

/// Calls your macro with the name of each member of XrFoveationDynamicModeInfoHTC, in order.
#define XR_LIST_STRUCT_XrFoveationDynamicModeInfoHTC(_) \
    _(type)                                             \
    _(next)                                             \
    _(dynamicFlags)

/// Calls your macro with the name of each member of XrFoveationCustomModeInfoHTC, in order.
#define XR_LIST_STRUCT_XrFoveationCustomModeInfoHTC(_) \
    _(type)                                            \
    _(next)                                            \
    _(configCount)                                     \
    _(configs)

/// Calls your macro with the name of each member of XrSystemAnchorPropertiesHTC, in order.
#define XR_LIST_STRUCT_XrSystemAnchorPropertiesHTC(_) \
    _(type)                                           \
    _(next)                                           \
    _(supportsAnchor)

/// Calls your macro with the name of each member of XrSpatialAnchorNameHTC, in order.
#define XR_LIST_STRUCT_XrSpatialAnchorNameHTC(_) _(name)

/// Calls your macro with the name of each member of XrSpatialAnchorCreateInfoHTC, in order.
#define XR_LIST_STRUCT_XrSpatialAnchorCreateInfoHTC(_) \
    _(type)                                            \
    _(next)                                            \
    _(space)                                           \
    _(poseInSpace)                                     \
    _(name)

/// Calls your macro with the name of each member of XrActiveActionSetPriorityEXT, in order.
#define XR_LIST_STRUCT_XrActiveActionSetPriorityEXT(_) \
    _(actionSet)                                       \
    _(priorityOverride)

/// Calls your macro with the name of each member of XrActiveActionSetPrioritiesEXT, in order.
#define XR_LIST_STRUCT_XrActiveActionSetPrioritiesEXT(_) \
    _(type)                                              \
    _(next)                                              \
    _(actionSetPriorityCount)                            \
    _(actionSetPriorities)

/// Calls your macro with the name of each member of XrSystemForceFeedbackCurlPropertiesMNDX, in order.
#define XR_LIST_STRUCT_XrSystemForceFeedbackCurlPropertiesMNDX(_) \
    _(type)                                                       \
    _(next)                                                       \
    _(supportsForceFeedbackCurl)

/// Calls your macro with the name of each member of XrForceFeedbackCurlApplyLocationMNDX, in order.
#define XR_LIST_STRUCT_XrForceFeedbackCurlApplyLocationMNDX(_) \
    _(location)                                                \
    _(value)

/// Calls your macro with the name of each member of XrForceFeedbackCurlApplyLocationsMNDX, in order.
#define XR_LIST_STRUCT_XrForceFeedbackCurlApplyLocationsMNDX(_) \
    _(type)                                                     \
    _(next)                                                     \
    _(locationCount)                                            \
    _(locations)

/// Calls your macro with the name of each member of XrHandTrackingDataSourceInfoEXT, in order.
#define XR_LIST_STRUCT_XrHandTrackingDataSourceInfoEXT(_) \
    _(type)                                               \
    _(next)                                               \
    _(requestedDataSourceCount)                           \
    _(requestedDataSources)

/// Calls your macro with the name of each member of XrHandTrackingDataSourceStateEXT, in order.
#define XR_LIST_STRUCT_XrHandTrackingDataSourceStateEXT(_) \
    _(type)                                                \
    _(next)                                                \
    _(isActive)                                            \
    _(dataSource)

/// Calls your macro with the name of each member of XrSystemPlaneDetectionPropertiesEXT, in order.
#define XR_LIST_STRUCT_XrSystemPlaneDetectionPropertiesEXT(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(supportedFeatures)

/// Calls your macro with the name of each member of XrPlaneDetectorCreateInfoEXT, in order.
#define XR_LIST_STRUCT_XrPlaneDetectorCreateInfoEXT(_) \
    _(type)                                            \
    _(next)                                            \
    _(flags)

/// Calls your macro with the name of each member of XrPlaneDetectorBeginInfoEXT, in order.
#define XR_LIST_STRUCT_XrPlaneDetectorBeginInfoEXT(_) \
    _(type)                                           \
    _(next)                                           \
    _(baseSpace)                                      \
    _(time)                                           \
    _(orientationCount)                               \
    _(orientations)                                   \
    _(semanticTypeCount)                              \
    _(semanticTypes)                                  \
    _(maxPlanes)                                      \
    _(minArea)                                        \
    _(boundingBoxPose)                                \
    _(boundingBoxExtent)

/// Calls your macro with the name of each member of XrPlaneDetectorGetInfoEXT, in order.
#define XR_LIST_STRUCT_XrPlaneDetectorGetInfoEXT(_) \
    _(type)                                         \
    _(next)                                         \
    _(baseSpace)                                    \
    _(time)

/// Calls your macro with the name of each member of XrPlaneDetectorLocationEXT, in order.
#define XR_LIST_STRUCT_XrPlaneDetectorLocationEXT(_) \
    _(type)                                          \
    _(next)                                          \
    _(planeId)                                       \
    _(locationFlags)                                 \
    _(pose)                                          \
    _(extents)                                       \
    _(orientation)                                   \
    _(semanticType)                                  \
    _(polygonBufferCount)

/// Calls your macro with the name of each member of XrPlaneDetectorLocationsEXT, in order.
#define XR_LIST_STRUCT_XrPlaneDetectorLocationsEXT(_) \
    _(type)                                           \
    _(next)                                           \
    _(planeLocationCapacityInput)                     \
    _(planeLocationCountOutput)                       \
    _(planeLocations)

/// Calls your macro with the name of each member of XrPlaneDetectorPolygonBufferEXT, in order.
#define XR_LIST_STRUCT_XrPlaneDetectorPolygonBufferEXT(_) \
    _(type)                                               \
    _(next)                                               \
    _(vertexCapacityInput)                                \
    _(vertexCountOutput)                                  \
    _(vertices)

/// Calls your macro with the name of each member of XrFutureCancelInfoEXT, in order.
#define XR_LIST_STRUCT_XrFutureCancelInfoEXT(_) \
    _(type)                                     \
    _(next)                                     \
    _(future)

/// Calls your macro with the name of each member of XrFuturePollInfoEXT, in order.
#define XR_LIST_STRUCT_XrFuturePollInfoEXT(_) \
    _(type)                                   \
    _(next)                                   \
    _(future)

/// Calls your macro with the name of each member of XrFutureCompletionBaseHeaderEXT, in order.
#define XR_LIST_STRUCT_XrFutureCompletionBaseHeaderEXT(_) \
    _(type)                                               \
    _(next)                                               \
    _(futureResult)

/// Calls your macro with the name of each member of XrFutureCompletionEXT, in order.
#define XR_LIST_STRUCT_XrFutureCompletionEXT(_) \
    _(type)                                     \
    _(next)                                     \
    _(futureResult)

/// Calls your macro with the name of each member of XrFuturePollResultEXT, in order.
#define XR_LIST_STRUCT_XrFuturePollResultEXT(_) \
    _(type)                                     \
    _(next)                                     \
    _(state)

/// Calls your macro with the name of each member of XrEventDataUserPresenceChangedEXT, in order.
#define XR_LIST_STRUCT_XrEventDataUserPresenceChangedEXT(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(session)                                              \
    _(isUserPresent)

/// Calls your macro with the name of each member of XrSystemUserPresencePropertiesEXT, in order.
#define XR_LIST_STRUCT_XrSystemUserPresencePropertiesEXT(_) \
    _(type)                                                 \
    _(next)                                                 \
    _(supportsUserPresence)

/// Calls your macro with the name of each member of XrEventDataHeadsetFitChangedML, in order.
#define XR_LIST_STRUCT_XrEventDataHeadsetFitChangedML(_) \
    _(type)                                              \
    _(next)                                              \
    _(status)                                            \
    _(time)

/// Calls your macro with the name of each member of XrEventDataEyeCalibrationChangedML, in order.
#define XR_LIST_STRUCT_XrEventDataEyeCalibrationChangedML(_) \
    _(type)                                                  \
    _(next)                                                  \
    _(status)

/// Calls your macro with the name of each member of XrUserCalibrationEnableEventsInfoML, in order.
#define XR_LIST_STRUCT_XrUserCalibrationEnableEventsInfoML(_) \
    _(type)                                                   \
    _(next)                                                   \
    _(enabled)

/// Calls your macro with the structure type name and the XrStructureType constant for
/// each known/available structure type, excluding those unavailable due to preprocessor definitions.
#define XR_LIST_STRUCTURE_TYPES(_)                                                   \
    XR_LIST_STRUCTURE_TYPES_CORE(_)                                                  \
    XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D11(_)                             \
    XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D12(_)                             \
    XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL(_)                            \
    XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WAYLAND(_)    \
    XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WIN32(_)      \
    XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XCB(_)        \
    XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XLIB(_)       \
    XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES(_)                         \
    XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES_XR_USE_PLATFORM_ANDROID(_) \
    XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_VULKAN(_)                            \
    XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_ANDROID(_)                               \
    XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_EGL(_)                                   \
    XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_ML(_)                                    \
    XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_WIN32(_)

/// Implementation detail of XR_LIST_STRUCTURE_TYPES() - structure types available without any preprocessor definitions
#define XR_LIST_STRUCTURE_TYPES_CORE(_)                                                                                     \
    _(XrApiLayerProperties, XR_TYPE_API_LAYER_PROPERTIES)                                                                   \
    _(XrExtensionProperties, XR_TYPE_EXTENSION_PROPERTIES)                                                                  \
    _(XrInstanceCreateInfo, XR_TYPE_INSTANCE_CREATE_INFO)                                                                   \
    _(XrInstanceProperties, XR_TYPE_INSTANCE_PROPERTIES)                                                                    \
    _(XrEventDataBuffer, XR_TYPE_EVENT_DATA_BUFFER)                                                                         \
    _(XrSystemGetInfo, XR_TYPE_SYSTEM_GET_INFO)                                                                             \
    _(XrSystemProperties, XR_TYPE_SYSTEM_PROPERTIES)                                                                        \
    _(XrSessionCreateInfo, XR_TYPE_SESSION_CREATE_INFO)                                                                     \
    _(XrSpaceVelocity, XR_TYPE_SPACE_VELOCITY)                                                                              \
    _(XrReferenceSpaceCreateInfo, XR_TYPE_REFERENCE_SPACE_CREATE_INFO)                                                      \
    _(XrActionSpaceCreateInfo, XR_TYPE_ACTION_SPACE_CREATE_INFO)                                                            \
    _(XrSpaceLocation, XR_TYPE_SPACE_LOCATION)                                                                              \
    _(XrViewConfigurationProperties, XR_TYPE_VIEW_CONFIGURATION_PROPERTIES)                                                 \
    _(XrViewConfigurationView, XR_TYPE_VIEW_CONFIGURATION_VIEW)                                                             \
    _(XrSwapchainCreateInfo, XR_TYPE_SWAPCHAIN_CREATE_INFO)                                                                 \
    _(XrSwapchainImageAcquireInfo, XR_TYPE_SWAPCHAIN_IMAGE_ACQUIRE_INFO)                                                    \
    _(XrSwapchainImageWaitInfo, XR_TYPE_SWAPCHAIN_IMAGE_WAIT_INFO)                                                          \
    _(XrSwapchainImageReleaseInfo, XR_TYPE_SWAPCHAIN_IMAGE_RELEASE_INFO)                                                    \
    _(XrSessionBeginInfo, XR_TYPE_SESSION_BEGIN_INFO)                                                                       \
    _(XrFrameWaitInfo, XR_TYPE_FRAME_WAIT_INFO)                                                                             \
    _(XrFrameState, XR_TYPE_FRAME_STATE)                                                                                    \
    _(XrFrameBeginInfo, XR_TYPE_FRAME_BEGIN_INFO)                                                                           \
    _(XrFrameEndInfo, XR_TYPE_FRAME_END_INFO)                                                                               \
    _(XrViewLocateInfo, XR_TYPE_VIEW_LOCATE_INFO)                                                                           \
    _(XrViewState, XR_TYPE_VIEW_STATE)                                                                                      \
    _(XrView, XR_TYPE_VIEW)                                                                                                 \
    _(XrActionSetCreateInfo, XR_TYPE_ACTION_SET_CREATE_INFO)                                                                \
    _(XrActionCreateInfo, XR_TYPE_ACTION_CREATE_INFO)                                                                       \
    _(XrInteractionProfileSuggestedBinding, XR_TYPE_INTERACTION_PROFILE_SUGGESTED_BINDING)                                  \
    _(XrSessionActionSetsAttachInfo, XR_TYPE_SESSION_ACTION_SETS_ATTACH_INFO)                                               \
    _(XrInteractionProfileState, XR_TYPE_INTERACTION_PROFILE_STATE)                                                         \
    _(XrActionStateGetInfo, XR_TYPE_ACTION_STATE_GET_INFO)                                                                  \
    _(XrActionStateBoolean, XR_TYPE_ACTION_STATE_BOOLEAN)                                                                   \
    _(XrActionStateFloat, XR_TYPE_ACTION_STATE_FLOAT)                                                                       \
    _(XrActionStateVector2f, XR_TYPE_ACTION_STATE_VECTOR2F)                                                                 \
    _(XrActionStatePose, XR_TYPE_ACTION_STATE_POSE)                                                                         \
    _(XrActionsSyncInfo, XR_TYPE_ACTIONS_SYNC_INFO)                                                                         \
    _(XrBoundSourcesForActionEnumerateInfo, XR_TYPE_BOUND_SOURCES_FOR_ACTION_ENUMERATE_INFO)                                \
    _(XrInputSourceLocalizedNameGetInfo, XR_TYPE_INPUT_SOURCE_LOCALIZED_NAME_GET_INFO)                                      \
    _(XrHapticActionInfo, XR_TYPE_HAPTIC_ACTION_INFO)                                                                       \
    _(XrCompositionLayerProjectionView, XR_TYPE_COMPOSITION_LAYER_PROJECTION_VIEW)                                          \
    _(XrCompositionLayerProjection, XR_TYPE_COMPOSITION_LAYER_PROJECTION)                                                   \
    _(XrCompositionLayerQuad, XR_TYPE_COMPOSITION_LAYER_QUAD)                                                               \
    _(XrEventDataEventsLost, XR_TYPE_EVENT_DATA_EVENTS_LOST)                                                                \
    _(XrEventDataInstanceLossPending, XR_TYPE_EVENT_DATA_INSTANCE_LOSS_PENDING)                                             \
    _(XrEventDataSessionStateChanged, XR_TYPE_EVENT_DATA_SESSION_STATE_CHANGED)                                             \
    _(XrEventDataReferenceSpaceChangePending, XR_TYPE_EVENT_DATA_REFERENCE_SPACE_CHANGE_PENDING)                            \
    _(XrEventDataInteractionProfileChanged, XR_TYPE_EVENT_DATA_INTERACTION_PROFILE_CHANGED)                                 \
    _(XrHapticVibration, XR_TYPE_HAPTIC_VIBRATION)                                                                          \
    _(XrSpacesLocateInfo, XR_TYPE_SPACES_LOCATE_INFO)                                                                       \
    _(XrSpaceLocations, XR_TYPE_SPACE_LOCATIONS)                                                                            \
    _(XrSpaceVelocities, XR_TYPE_SPACE_VELOCITIES)                                                                          \
    _(XrCompositionLayerCubeKHR, XR_TYPE_COMPOSITION_LAYER_CUBE_KHR)                                                        \
    _(XrCompositionLayerDepthInfoKHR, XR_TYPE_COMPOSITION_LAYER_DEPTH_INFO_KHR)                                             \
    _(XrCompositionLayerCylinderKHR, XR_TYPE_COMPOSITION_LAYER_CYLINDER_KHR)                                                \
    _(XrCompositionLayerEquirectKHR, XR_TYPE_COMPOSITION_LAYER_EQUIRECT_KHR)                                                \
    _(XrVisibilityMaskKHR, XR_TYPE_VISIBILITY_MASK_KHR)                                                                     \
    _(XrEventDataVisibilityMaskChangedKHR, XR_TYPE_EVENT_DATA_VISIBILITY_MASK_CHANGED_KHR)                                  \
    _(XrCompositionLayerColorScaleBiasKHR, XR_TYPE_COMPOSITION_LAYER_COLOR_SCALE_BIAS_KHR)                                  \
    _(XrCompositionLayerEquirect2KHR, XR_TYPE_COMPOSITION_LAYER_EQUIRECT2_KHR)                                              \
    _(XrBindingModificationsKHR, XR_TYPE_BINDING_MODIFICATIONS_KHR)                                                         \
    _(XrEventDataPerfSettingsEXT, XR_TYPE_EVENT_DATA_PERF_SETTINGS_EXT)                                                     \
    _(XrDebugUtilsObjectNameInfoEXT, XR_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT)                                              \
    _(XrDebugUtilsLabelEXT, XR_TYPE_DEBUG_UTILS_LABEL_EXT)                                                                  \
    _(XrDebugUtilsMessengerCallbackDataEXT, XR_TYPE_DEBUG_UTILS_MESSENGER_CALLBACK_DATA_EXT)                                \
    _(XrDebugUtilsMessengerCreateInfoEXT, XR_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT)                                    \
    _(XrSystemEyeGazeInteractionPropertiesEXT, XR_TYPE_SYSTEM_EYE_GAZE_INTERACTION_PROPERTIES_EXT)                          \
    _(XrEyeGazeSampleTimeEXT, XR_TYPE_EYE_GAZE_SAMPLE_TIME_EXT)                                                             \
    _(XrSessionCreateInfoOverlayEXTX, XR_TYPE_SESSION_CREATE_INFO_OVERLAY_EXTX)                                             \
    _(XrEventDataMainSessionVisibilityChangedEXTX, XR_TYPE_EVENT_DATA_MAIN_SESSION_VISIBILITY_CHANGED_EXTX)                 \
    _(XrSpatialAnchorCreateInfoMSFT, XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_MSFT)                                               \
    _(XrSpatialAnchorSpaceCreateInfoMSFT, XR_TYPE_SPATIAL_ANCHOR_SPACE_CREATE_INFO_MSFT)                                    \
    _(XrCompositionLayerImageLayoutFB, XR_TYPE_COMPOSITION_LAYER_IMAGE_LAYOUT_FB)                                           \
    _(XrCompositionLayerAlphaBlendFB, XR_TYPE_COMPOSITION_LAYER_ALPHA_BLEND_FB)                                             \
    _(XrViewConfigurationDepthRangeEXT, XR_TYPE_VIEW_CONFIGURATION_DEPTH_RANGE_EXT)                                         \
    _(XrSpatialGraphNodeSpaceCreateInfoMSFT, XR_TYPE_SPATIAL_GRAPH_NODE_SPACE_CREATE_INFO_MSFT)                             \
    _(XrSpatialGraphStaticNodeBindingCreateInfoMSFT, XR_TYPE_SPATIAL_GRAPH_STATIC_NODE_BINDING_CREATE_INFO_MSFT)            \
    _(XrSpatialGraphNodeBindingPropertiesGetInfoMSFT, XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_GET_INFO_MSFT)          \
    _(XrSpatialGraphNodeBindingPropertiesMSFT, XR_TYPE_SPATIAL_GRAPH_NODE_BINDING_PROPERTIES_MSFT)                          \
    _(XrSystemHandTrackingPropertiesEXT, XR_TYPE_SYSTEM_HAND_TRACKING_PROPERTIES_EXT)                                       \
    _(XrHandTrackerCreateInfoEXT, XR_TYPE_HAND_TRACKER_CREATE_INFO_EXT)                                                     \
    _(XrHandJointsLocateInfoEXT, XR_TYPE_HAND_JOINTS_LOCATE_INFO_EXT)                                                       \
    _(XrHandJointLocationsEXT, XR_TYPE_HAND_JOINT_LOCATIONS_EXT)                                                            \
    _(XrHandJointVelocitiesEXT, XR_TYPE_HAND_JOINT_VELOCITIES_EXT)                                                          \
    _(XrSystemHandTrackingMeshPropertiesMSFT, XR_TYPE_SYSTEM_HAND_TRACKING_MESH_PROPERTIES_MSFT)                            \
    _(XrHandMeshSpaceCreateInfoMSFT, XR_TYPE_HAND_MESH_SPACE_CREATE_INFO_MSFT)                                              \
    _(XrHandMeshUpdateInfoMSFT, XR_TYPE_HAND_MESH_UPDATE_INFO_MSFT)                                                         \
    _(XrHandMeshMSFT, XR_TYPE_HAND_MESH_MSFT)                                                                               \
    _(XrHandPoseTypeInfoMSFT, XR_TYPE_HAND_POSE_TYPE_INFO_MSFT)                                                             \
    _(XrSecondaryViewConfigurationSessionBeginInfoMSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SESSION_BEGIN_INFO_MSFT)       \
    _(XrSecondaryViewConfigurationStateMSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_STATE_MSFT)                               \
    _(XrSecondaryViewConfigurationFrameStateMSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_STATE_MSFT)                    \
    _(XrSecondaryViewConfigurationLayerInfoMSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_LAYER_INFO_MSFT)                      \
    _(XrSecondaryViewConfigurationFrameEndInfoMSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_FRAME_END_INFO_MSFT)               \
    _(XrSecondaryViewConfigurationSwapchainCreateInfoMSFT, XR_TYPE_SECONDARY_VIEW_CONFIGURATION_SWAPCHAIN_CREATE_INFO_MSFT) \
    _(XrControllerModelKeyStateMSFT, XR_TYPE_CONTROLLER_MODEL_KEY_STATE_MSFT)                                               \
    _(XrControllerModelNodePropertiesMSFT, XR_TYPE_CONTROLLER_MODEL_NODE_PROPERTIES_MSFT)                                   \
    _(XrControllerModelPropertiesMSFT, XR_TYPE_CONTROLLER_MODEL_PROPERTIES_MSFT)                                            \
    _(XrControllerModelNodeStateMSFT, XR_TYPE_CONTROLLER_MODEL_NODE_STATE_MSFT)                                             \
    _(XrControllerModelStateMSFT, XR_TYPE_CONTROLLER_MODEL_STATE_MSFT)                                                      \
    _(XrViewConfigurationViewFovEPIC, XR_TYPE_VIEW_CONFIGURATION_VIEW_FOV_EPIC)                                             \
    _(XrCompositionLayerReprojectionInfoMSFT, XR_TYPE_COMPOSITION_LAYER_REPROJECTION_INFO_MSFT)                             \
    _(XrCompositionLayerReprojectionPlaneOverrideMSFT, XR_TYPE_COMPOSITION_LAYER_REPROJECTION_PLANE_OVERRIDE_MSFT)          \
    _(XrCompositionLayerSecureContentFB, XR_TYPE_COMPOSITION_LAYER_SECURE_CONTENT_FB)                                       \
    _(XrSystemBodyTrackingPropertiesFB, XR_TYPE_SYSTEM_BODY_TRACKING_PROPERTIES_FB)                                         \
    _(XrBodyTrackerCreateInfoFB, XR_TYPE_BODY_TRACKER_CREATE_INFO_FB)                                                       \
    _(XrBodySkeletonFB, XR_TYPE_BODY_SKELETON_FB)                                                                           \
    _(XrBodyJointsLocateInfoFB, XR_TYPE_BODY_JOINTS_LOCATE_INFO_FB)                                                         \
    _(XrBodyJointLocationsFB, XR_TYPE_BODY_JOINT_LOCATIONS_FB)                                                              \
    _(XrInteractionProfileDpadBindingEXT, XR_TYPE_INTERACTION_PROFILE_DPAD_BINDING_EXT)                                     \
    _(XrInteractionProfileAnalogThresholdVALVE, XR_TYPE_INTERACTION_PROFILE_ANALOG_THRESHOLD_VALVE)                         \
    _(XrHandJointsMotionRangeInfoEXT, XR_TYPE_HAND_JOINTS_MOTION_RANGE_INFO_EXT)                                            \
    _(XrSceneObserverCreateInfoMSFT, XR_TYPE_SCENE_OBSERVER_CREATE_INFO_MSFT)                                               \
    _(XrSceneCreateInfoMSFT, XR_TYPE_SCENE_CREATE_INFO_MSFT)                                                                \
    _(XrNewSceneComputeInfoMSFT, XR_TYPE_NEW_SCENE_COMPUTE_INFO_MSFT)                                                       \
    _(XrVisualMeshComputeLodInfoMSFT, XR_TYPE_VISUAL_MESH_COMPUTE_LOD_INFO_MSFT)                                            \
    _(XrSceneComponentsMSFT, XR_TYPE_SCENE_COMPONENTS_MSFT)                                                                 \
    _(XrSceneComponentsGetInfoMSFT, XR_TYPE_SCENE_COMPONENTS_GET_INFO_MSFT)                                                 \
    _(XrSceneComponentLocationsMSFT, XR_TYPE_SCENE_COMPONENT_LOCATIONS_MSFT)                                                \
    _(XrSceneComponentsLocateInfoMSFT, XR_TYPE_SCENE_COMPONENTS_LOCATE_INFO_MSFT)                                           \
    _(XrSceneObjectsMSFT, XR_TYPE_SCENE_OBJECTS_MSFT)                                                                       \
    _(XrSceneComponentParentFilterInfoMSFT, XR_TYPE_SCENE_COMPONENT_PARENT_FILTER_INFO_MSFT)                                \
    _(XrSceneObjectTypesFilterInfoMSFT, XR_TYPE_SCENE_OBJECT_TYPES_FILTER_INFO_MSFT)                                        \
    _(XrScenePlanesMSFT, XR_TYPE_SCENE_PLANES_MSFT)                                                                         \
    _(XrScenePlaneAlignmentFilterInfoMSFT, XR_TYPE_SCENE_PLANE_ALIGNMENT_FILTER_INFO_MSFT)                                  \
    _(XrSceneMeshesMSFT, XR_TYPE_SCENE_MESHES_MSFT)                                                                         \
    _(XrSceneMeshBuffersGetInfoMSFT, XR_TYPE_SCENE_MESH_BUFFERS_GET_INFO_MSFT)                                              \
    _(XrSceneMeshBuffersMSFT, XR_TYPE_SCENE_MESH_BUFFERS_MSFT)                                                              \
    _(XrSceneMeshVertexBufferMSFT, XR_TYPE_SCENE_MESH_VERTEX_BUFFER_MSFT)                                                   \
    _(XrSceneMeshIndicesUint32MSFT, XR_TYPE_SCENE_MESH_INDICES_UINT32_MSFT)                                                 \
    _(XrSceneMeshIndicesUint16MSFT, XR_TYPE_SCENE_MESH_INDICES_UINT16_MSFT)                                                 \
    _(XrSerializedSceneFragmentDataGetInfoMSFT, XR_TYPE_SERIALIZED_SCENE_FRAGMENT_DATA_GET_INFO_MSFT)                       \
    _(XrSceneDeserializeInfoMSFT, XR_TYPE_SCENE_DESERIALIZE_INFO_MSFT)                                                      \
    _(XrEventDataDisplayRefreshRateChangedFB, XR_TYPE_EVENT_DATA_DISPLAY_REFRESH_RATE_CHANGED_FB)                           \
    _(XrViveTrackerPathsHTCX, XR_TYPE_VIVE_TRACKER_PATHS_HTCX)                                                              \
    _(XrEventDataViveTrackerConnectedHTCX, XR_TYPE_EVENT_DATA_VIVE_TRACKER_CONNECTED_HTCX)                                  \
    _(XrSystemFacialTrackingPropertiesHTC, XR_TYPE_SYSTEM_FACIAL_TRACKING_PROPERTIES_HTC)                                   \
    _(XrFacialExpressionsHTC, XR_TYPE_FACIAL_EXPRESSIONS_HTC)                                                               \
    _(XrFacialTrackerCreateInfoHTC, XR_TYPE_FACIAL_TRACKER_CREATE_INFO_HTC)                                                 \
    _(XrSystemColorSpacePropertiesFB, XR_TYPE_SYSTEM_COLOR_SPACE_PROPERTIES_FB)                                             \
    _(XrHandTrackingMeshFB, XR_TYPE_HAND_TRACKING_MESH_FB)                                                                  \
    _(XrHandTrackingScaleFB, XR_TYPE_HAND_TRACKING_SCALE_FB)                                                                \
    _(XrHandTrackingAimStateFB, XR_TYPE_HAND_TRACKING_AIM_STATE_FB)                                                         \
    _(XrHandTrackingCapsulesStateFB, XR_TYPE_HAND_TRACKING_CAPSULES_STATE_FB)                                               \
    _(XrSystemSpatialEntityPropertiesFB, XR_TYPE_SYSTEM_SPATIAL_ENTITY_PROPERTIES_FB)                                       \
    _(XrSpatialAnchorCreateInfoFB, XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_FB)                                                   \
    _(XrSpaceComponentStatusSetInfoFB, XR_TYPE_SPACE_COMPONENT_STATUS_SET_INFO_FB)                                          \
    _(XrSpaceComponentStatusFB, XR_TYPE_SPACE_COMPONENT_STATUS_FB)                                                          \
    _(XrEventDataSpatialAnchorCreateCompleteFB, XR_TYPE_EVENT_DATA_SPATIAL_ANCHOR_CREATE_COMPLETE_FB)                       \
    _(XrEventDataSpaceSetStatusCompleteFB, XR_TYPE_EVENT_DATA_SPACE_SET_STATUS_COMPLETE_FB)                                 \
    _(XrFoveationProfileCreateInfoFB, XR_TYPE_FOVEATION_PROFILE_CREATE_INFO_FB)                                             \
    _(XrSwapchainCreateInfoFoveationFB, XR_TYPE_SWAPCHAIN_CREATE_INFO_FOVEATION_FB)                                         \
    _(XrSwapchainStateFoveationFB, XR_TYPE_SWAPCHAIN_STATE_FOVEATION_FB)                                                    \
    _(XrFoveationLevelProfileCreateInfoFB, XR_TYPE_FOVEATION_LEVEL_PROFILE_CREATE_INFO_FB)                                  \
    _(XrSystemKeyboardTrackingPropertiesFB, XR_TYPE_SYSTEM_KEYBOARD_TRACKING_PROPERTIES_FB)                                 \
    _(XrKeyboardSpaceCreateInfoFB, XR_TYPE_KEYBOARD_SPACE_CREATE_INFO_FB)                                                   \
    _(XrKeyboardTrackingQueryFB, XR_TYPE_KEYBOARD_TRACKING_QUERY_FB)                                                        \
    _(XrTriangleMeshCreateInfoFB, XR_TYPE_TRIANGLE_MESH_CREATE_INFO_FB)                                                     \
    _(XrSystemPassthroughPropertiesFB, XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES_FB)                                            \
    _(XrSystemPassthroughProperties2FB, XR_TYPE_SYSTEM_PASSTHROUGH_PROPERTIES2_FB)                                          \
    _(XrPassthroughCreateInfoFB, XR_TYPE_PASSTHROUGH_CREATE_INFO_FB)                                                        \
    _(XrPassthroughLayerCreateInfoFB, XR_TYPE_PASSTHROUGH_LAYER_CREATE_INFO_FB)                                             \
    _(XrCompositionLayerPassthroughFB, XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_FB)                                            \
    _(XrGeometryInstanceCreateInfoFB, XR_TYPE_GEOMETRY_INSTANCE_CREATE_INFO_FB)                                             \
    _(XrGeometryInstanceTransformFB, XR_TYPE_GEOMETRY_INSTANCE_TRANSFORM_FB)                                                \
    _(XrPassthroughStyleFB, XR_TYPE_PASSTHROUGH_STYLE_FB)                                                                   \
    _(XrPassthroughColorMapMonoToRgbaFB, XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_RGBA_FB)                                     \
    _(XrPassthroughColorMapMonoToMonoFB, XR_TYPE_PASSTHROUGH_COLOR_MAP_MONO_TO_MONO_FB)                                     \
    _(XrPassthroughBrightnessContrastSaturationFB, XR_TYPE_PASSTHROUGH_BRIGHTNESS_CONTRAST_SATURATION_FB)                   \
    _(XrEventDataPassthroughStateChangedFB, XR_TYPE_EVENT_DATA_PASSTHROUGH_STATE_CHANGED_FB)                                \
    _(XrRenderModelPathInfoFB, XR_TYPE_RENDER_MODEL_PATH_INFO_FB)                                                           \
    _(XrRenderModelPropertiesFB, XR_TYPE_RENDER_MODEL_PROPERTIES_FB)                                                        \
    _(XrRenderModelBufferFB, XR_TYPE_RENDER_MODEL_BUFFER_FB)                                                                \
    _(XrRenderModelLoadInfoFB, XR_TYPE_RENDER_MODEL_LOAD_INFO_FB)                                                           \
    _(XrSystemRenderModelPropertiesFB, XR_TYPE_SYSTEM_RENDER_MODEL_PROPERTIES_FB)                                           \
    _(XrRenderModelCapabilitiesRequestFB, XR_TYPE_RENDER_MODEL_CAPABILITIES_REQUEST_FB)                                     \
    _(XrViewLocateFoveatedRenderingVARJO, XR_TYPE_VIEW_LOCATE_FOVEATED_RENDERING_VARJO)                                     \
    _(XrFoveatedViewConfigurationViewVARJO, XR_TYPE_FOVEATED_VIEW_CONFIGURATION_VIEW_VARJO)                                 \
    _(XrSystemFoveatedRenderingPropertiesVARJO, XR_TYPE_SYSTEM_FOVEATED_RENDERING_PROPERTIES_VARJO)                         \
    _(XrCompositionLayerDepthTestVARJO, XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_VARJO)                                         \
    _(XrSystemMarkerTrackingPropertiesVARJO, XR_TYPE_SYSTEM_MARKER_TRACKING_PROPERTIES_VARJO)                               \
    _(XrEventDataMarkerTrackingUpdateVARJO, XR_TYPE_EVENT_DATA_MARKER_TRACKING_UPDATE_VARJO)                                \
    _(XrMarkerSpaceCreateInfoVARJO, XR_TYPE_MARKER_SPACE_CREATE_INFO_VARJO)                                                 \
    _(XrFrameEndInfoML, XR_TYPE_FRAME_END_INFO_ML)                                                                          \
    _(XrGlobalDimmerFrameEndInfoML, XR_TYPE_GLOBAL_DIMMER_FRAME_END_INFO_ML)                                                \
    _(XrSystemMarkerUnderstandingPropertiesML, XR_TYPE_SYSTEM_MARKER_UNDERSTANDING_PROPERTIES_ML)                           \
    _(XrMarkerDetectorCreateInfoML, XR_TYPE_MARKER_DETECTOR_CREATE_INFO_ML)                                                 \
    _(XrMarkerDetectorArucoInfoML, XR_TYPE_MARKER_DETECTOR_ARUCO_INFO_ML)                                                   \
    _(XrMarkerDetectorSizeInfoML, XR_TYPE_MARKER_DETECTOR_SIZE_INFO_ML)                                                     \
    _(XrMarkerDetectorAprilTagInfoML, XR_TYPE_MARKER_DETECTOR_APRIL_TAG_INFO_ML)                                            \
    _(XrMarkerDetectorCustomProfileInfoML, XR_TYPE_MARKER_DETECTOR_CUSTOM_PROFILE_INFO_ML)                                  \
    _(XrMarkerDetectorSnapshotInfoML, XR_TYPE_MARKER_DETECTOR_SNAPSHOT_INFO_ML)                                             \
    _(XrMarkerDetectorStateML, XR_TYPE_MARKER_DETECTOR_STATE_ML)                                                            \
    _(XrMarkerSpaceCreateInfoML, XR_TYPE_MARKER_SPACE_CREATE_INFO_ML)                                                       \
    _(XrLocalizationMapML, XR_TYPE_LOCALIZATION_MAP_ML)                                                                     \
    _(XrEventDataLocalizationChangedML, XR_TYPE_EVENT_DATA_LOCALIZATION_CHANGED_ML)                                         \
    _(XrMapLocalizationRequestInfoML, XR_TYPE_MAP_LOCALIZATION_REQUEST_INFO_ML)                                             \
    _(XrLocalizationMapImportInfoML, XR_TYPE_LOCALIZATION_MAP_IMPORT_INFO_ML)                                               \
    _(XrLocalizationEnableEventsInfoML, XR_TYPE_LOCALIZATION_ENABLE_EVENTS_INFO_ML)                                         \
    _(XrSpatialAnchorPersistenceInfoMSFT, XR_TYPE_SPATIAL_ANCHOR_PERSISTENCE_INFO_MSFT)                                     \
    _(XrSpatialAnchorFromPersistedAnchorCreateInfoMSFT, XR_TYPE_SPATIAL_ANCHOR_FROM_PERSISTED_ANCHOR_CREATE_INFO_MSFT)      \
    _(XrSceneMarkersMSFT, XR_TYPE_SCENE_MARKERS_MSFT)                                                                       \
    _(XrSceneMarkerTypeFilterMSFT, XR_TYPE_SCENE_MARKER_TYPE_FILTER_MSFT)                                                   \
    _(XrSceneMarkerQRCodesMSFT, XR_TYPE_SCENE_MARKER_QR_CODES_MSFT)                                                         \
    _(XrSpaceQueryInfoFB, XR_TYPE_SPACE_QUERY_INFO_FB)                                                                      \
    _(XrSpaceStorageLocationFilterInfoFB, XR_TYPE_SPACE_STORAGE_LOCATION_FILTER_INFO_FB)                                    \
    _(XrSpaceUuidFilterInfoFB, XR_TYPE_SPACE_UUID_FILTER_INFO_FB)                                                           \
    _(XrSpaceComponentFilterInfoFB, XR_TYPE_SPACE_COMPONENT_FILTER_INFO_FB)                                                 \
    _(XrSpaceQueryResultsFB, XR_TYPE_SPACE_QUERY_RESULTS_FB)                                                                \
    _(XrEventDataSpaceQueryResultsAvailableFB, XR_TYPE_EVENT_DATA_SPACE_QUERY_RESULTS_AVAILABLE_FB)                         \
    _(XrEventDataSpaceQueryCompleteFB, XR_TYPE_EVENT_DATA_SPACE_QUERY_COMPLETE_FB)                                          \
    _(XrSpaceSaveInfoFB, XR_TYPE_SPACE_SAVE_INFO_FB)                                                                        \
    _(XrSpaceEraseInfoFB, XR_TYPE_SPACE_ERASE_INFO_FB)                                                                      \
    _(XrEventDataSpaceSaveCompleteFB, XR_TYPE_EVENT_DATA_SPACE_SAVE_COMPLETE_FB)                                            \
    _(XrEventDataSpaceEraseCompleteFB, XR_TYPE_EVENT_DATA_SPACE_ERASE_COMPLETE_FB)                                          \
    _(XrSpaceShareInfoFB, XR_TYPE_SPACE_SHARE_INFO_FB)                                                                      \
    _(XrEventDataSpaceShareCompleteFB, XR_TYPE_EVENT_DATA_SPACE_SHARE_COMPLETE_FB)                                          \
    _(XrCompositionLayerSpaceWarpInfoFB, XR_TYPE_COMPOSITION_LAYER_SPACE_WARP_INFO_FB)                                      \
    _(XrSystemSpaceWarpPropertiesFB, XR_TYPE_SYSTEM_SPACE_WARP_PROPERTIES_FB)                                               \
    _(XrHapticAmplitudeEnvelopeVibrationFB, XR_TYPE_HAPTIC_AMPLITUDE_ENVELOPE_VIBRATION_FB)                                 \
    _(XrSemanticLabelsFB, XR_TYPE_SEMANTIC_LABELS_FB)                                                                       \
    _(XrRoomLayoutFB, XR_TYPE_ROOM_LAYOUT_FB)                                                                               \
    _(XrBoundary2DFB, XR_TYPE_BOUNDARY_2D_FB)                                                                               \
    _(XrSemanticLabelsSupportInfoFB, XR_TYPE_SEMANTIC_LABELS_SUPPORT_INFO_FB)                                               \
    _(XrDigitalLensControlALMALENCE, XR_TYPE_DIGITAL_LENS_CONTROL_ALMALENCE)                                                \
    _(XrEventDataSceneCaptureCompleteFB, XR_TYPE_EVENT_DATA_SCENE_CAPTURE_COMPLETE_FB)                                      \
    _(XrSceneCaptureRequestInfoFB, XR_TYPE_SCENE_CAPTURE_REQUEST_INFO_FB)                                                   \
    _(XrSpaceContainerFB, XR_TYPE_SPACE_CONTAINER_FB)                                                                       \
    _(XrFoveationEyeTrackedProfileCreateInfoMETA, XR_TYPE_FOVEATION_EYE_TRACKED_PROFILE_CREATE_INFO_META)                   \
    _(XrFoveationEyeTrackedStateMETA, XR_TYPE_FOVEATION_EYE_TRACKED_STATE_META)                                             \
    _(XrSystemFoveationEyeTrackedPropertiesMETA, XR_TYPE_SYSTEM_FOVEATION_EYE_TRACKED_PROPERTIES_META)                      \
    _(XrSystemFaceTrackingPropertiesFB, XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES_FB)                                         \
    _(XrFaceTrackerCreateInfoFB, XR_TYPE_FACE_TRACKER_CREATE_INFO_FB)                                                       \
    _(XrFaceExpressionInfoFB, XR_TYPE_FACE_EXPRESSION_INFO_FB)                                                              \
    _(XrFaceExpressionWeightsFB, XR_TYPE_FACE_EXPRESSION_WEIGHTS_FB)                                                        \
    _(XrEyeTrackerCreateInfoFB, XR_TYPE_EYE_TRACKER_CREATE_INFO_FB)                                                         \
    _(XrEyeGazesInfoFB, XR_TYPE_EYE_GAZES_INFO_FB)                                                                          \
    _(XrSystemEyeTrackingPropertiesFB, XR_TYPE_SYSTEM_EYE_TRACKING_PROPERTIES_FB)                                           \
    _(XrEyeGazesFB, XR_TYPE_EYE_GAZES_FB)                                                                                   \
    _(XrPassthroughKeyboardHandsIntensityFB, XR_TYPE_PASSTHROUGH_KEYBOARD_HANDS_INTENSITY_FB)                               \
    _(XrCompositionLayerSettingsFB, XR_TYPE_COMPOSITION_LAYER_SETTINGS_FB)                                                  \
    _(XrHapticPcmVibrationFB, XR_TYPE_HAPTIC_PCM_VIBRATION_FB)                                                              \
    _(XrDevicePcmSampleRateStateFB, XR_TYPE_DEVICE_PCM_SAMPLE_RATE_STATE_FB)                                                \
    _(XrCompositionLayerDepthTestFB, XR_TYPE_COMPOSITION_LAYER_DEPTH_TEST_FB)                                               \
    _(XrLocalDimmingFrameEndInfoMETA, XR_TYPE_LOCAL_DIMMING_FRAME_END_INFO_META)                                            \
    _(XrPassthroughPreferencesMETA, XR_TYPE_PASSTHROUGH_PREFERENCES_META)                                                   \
    _(XrSystemVirtualKeyboardPropertiesMETA, XR_TYPE_SYSTEM_VIRTUAL_KEYBOARD_PROPERTIES_META)                               \
    _(XrVirtualKeyboardCreateInfoMETA, XR_TYPE_VIRTUAL_KEYBOARD_CREATE_INFO_META)                                           \
    _(XrVirtualKeyboardSpaceCreateInfoMETA, XR_TYPE_VIRTUAL_KEYBOARD_SPACE_CREATE_INFO_META)                                \
    _(XrVirtualKeyboardLocationInfoMETA, XR_TYPE_VIRTUAL_KEYBOARD_LOCATION_INFO_META)                                       \
    _(XrVirtualKeyboardModelVisibilitySetInfoMETA, XR_TYPE_VIRTUAL_KEYBOARD_MODEL_VISIBILITY_SET_INFO_META)                 \
    _(XrVirtualKeyboardAnimationStateMETA, XR_TYPE_VIRTUAL_KEYBOARD_ANIMATION_STATE_META)                                   \
    _(XrVirtualKeyboardModelAnimationStatesMETA, XR_TYPE_VIRTUAL_KEYBOARD_MODEL_ANIMATION_STATES_META)                      \
    _(XrVirtualKeyboardTextureDataMETA, XR_TYPE_VIRTUAL_KEYBOARD_TEXTURE_DATA_META)                                         \
    _(XrVirtualKeyboardInputInfoMETA, XR_TYPE_VIRTUAL_KEYBOARD_INPUT_INFO_META)                                             \
    _(XrVirtualKeyboardTextContextChangeInfoMETA, XR_TYPE_VIRTUAL_KEYBOARD_TEXT_CONTEXT_CHANGE_INFO_META)                   \
    _(XrEventDataVirtualKeyboardCommitTextMETA, XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_COMMIT_TEXT_META)                       \
    _(XrEventDataVirtualKeyboardBackspaceMETA, XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_BACKSPACE_META)                          \
    _(XrEventDataVirtualKeyboardEnterMETA, XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_ENTER_META)                                  \
    _(XrEventDataVirtualKeyboardShownMETA, XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_SHOWN_META)                                  \
    _(XrEventDataVirtualKeyboardHiddenMETA, XR_TYPE_EVENT_DATA_VIRTUAL_KEYBOARD_HIDDEN_META)                                \
    _(XrExternalCameraOCULUS, XR_TYPE_EXTERNAL_CAMERA_OCULUS)                                                               \
    _(XrPerformanceMetricsStateMETA, XR_TYPE_PERFORMANCE_METRICS_STATE_META)                                                \
    _(XrPerformanceMetricsCounterMETA, XR_TYPE_PERFORMANCE_METRICS_COUNTER_META)                                            \
    _(XrSpaceListSaveInfoFB, XR_TYPE_SPACE_LIST_SAVE_INFO_FB)                                                               \
    _(XrEventDataSpaceListSaveCompleteFB, XR_TYPE_EVENT_DATA_SPACE_LIST_SAVE_COMPLETE_FB)                                   \
    _(XrSpaceUserCreateInfoFB, XR_TYPE_SPACE_USER_CREATE_INFO_FB)                                                           \
    _(XrSystemHeadsetIdPropertiesMETA, XR_TYPE_SYSTEM_HEADSET_ID_PROPERTIES_META)                                           \
    _(XrRecommendedLayerResolutionMETA, XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_META)                                          \
    _(XrRecommendedLayerResolutionGetInfoMETA, XR_TYPE_RECOMMENDED_LAYER_RESOLUTION_GET_INFO_META)                          \
    _(XrPassthroughColorLutCreateInfoMETA, XR_TYPE_PASSTHROUGH_COLOR_LUT_CREATE_INFO_META)                                  \
    _(XrPassthroughColorLutUpdateInfoMETA, XR_TYPE_PASSTHROUGH_COLOR_LUT_UPDATE_INFO_META)                                  \
    _(XrPassthroughColorMapLutMETA, XR_TYPE_PASSTHROUGH_COLOR_MAP_LUT_META)                                                 \
    _(XrPassthroughColorMapInterpolatedLutMETA, XR_TYPE_PASSTHROUGH_COLOR_MAP_INTERPOLATED_LUT_META)                        \
    _(XrSystemPassthroughColorLutPropertiesMETA, XR_TYPE_SYSTEM_PASSTHROUGH_COLOR_LUT_PROPERTIES_META)                      \
    _(XrSpaceTriangleMeshGetInfoMETA, XR_TYPE_SPACE_TRIANGLE_MESH_GET_INFO_META)                                            \
    _(XrSpaceTriangleMeshMETA, XR_TYPE_SPACE_TRIANGLE_MESH_META)                                                            \
    _(XrSystemFaceTrackingProperties2FB, XR_TYPE_SYSTEM_FACE_TRACKING_PROPERTIES2_FB)                                       \
    _(XrFaceTrackerCreateInfo2FB, XR_TYPE_FACE_TRACKER_CREATE_INFO2_FB)                                                     \
    _(XrFaceExpressionInfo2FB, XR_TYPE_FACE_EXPRESSION_INFO2_FB)                                                            \
    _(XrFaceExpressionWeights2FB, XR_TYPE_FACE_EXPRESSION_WEIGHTS2_FB)                                                      \
    _(XrEnvironmentDepthProviderCreateInfoMETA, XR_TYPE_ENVIRONMENT_DEPTH_PROVIDER_CREATE_INFO_META)                        \
    _(XrEnvironmentDepthSwapchainCreateInfoMETA, XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_CREATE_INFO_META)                      \
    _(XrEnvironmentDepthSwapchainStateMETA, XR_TYPE_ENVIRONMENT_DEPTH_SWAPCHAIN_STATE_META)                                 \
    _(XrEnvironmentDepthImageAcquireInfoMETA, XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_ACQUIRE_INFO_META)                            \
    _(XrEnvironmentDepthImageViewMETA, XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_VIEW_META)                                           \
    _(XrEnvironmentDepthImageMETA, XR_TYPE_ENVIRONMENT_DEPTH_IMAGE_META)                                                    \
    _(XrEnvironmentDepthHandRemovalSetInfoMETA, XR_TYPE_ENVIRONMENT_DEPTH_HAND_REMOVAL_SET_INFO_META)                       \
    _(XrSystemEnvironmentDepthPropertiesMETA, XR_TYPE_SYSTEM_ENVIRONMENT_DEPTH_PROPERTIES_META)                             \
    _(XrPassthroughCreateInfoHTC, XR_TYPE_PASSTHROUGH_CREATE_INFO_HTC)                                                      \
    _(XrPassthroughColorHTC, XR_TYPE_PASSTHROUGH_COLOR_HTC)                                                                 \
    _(XrPassthroughMeshTransformInfoHTC, XR_TYPE_PASSTHROUGH_MESH_TRANSFORM_INFO_HTC)                                       \
    _(XrCompositionLayerPassthroughHTC, XR_TYPE_COMPOSITION_LAYER_PASSTHROUGH_HTC)                                          \
    _(XrFoveationApplyInfoHTC, XR_TYPE_FOVEATION_APPLY_INFO_HTC)                                                            \
    _(XrFoveationDynamicModeInfoHTC, XR_TYPE_FOVEATION_DYNAMIC_MODE_INFO_HTC)                                               \
    _(XrFoveationCustomModeInfoHTC, XR_TYPE_FOVEATION_CUSTOM_MODE_INFO_HTC)                                                 \
    _(XrSystemAnchorPropertiesHTC, XR_TYPE_SYSTEM_ANCHOR_PROPERTIES_HTC)                                                    \
    _(XrSpatialAnchorCreateInfoHTC, XR_TYPE_SPATIAL_ANCHOR_CREATE_INFO_HTC)                                                 \
    _(XrActiveActionSetPrioritiesEXT, XR_TYPE_ACTIVE_ACTION_SET_PRIORITIES_EXT)                                             \
    _(XrSystemForceFeedbackCurlPropertiesMNDX, XR_TYPE_SYSTEM_FORCE_FEEDBACK_CURL_PROPERTIES_MNDX)                          \
    _(XrForceFeedbackCurlApplyLocationsMNDX, XR_TYPE_FORCE_FEEDBACK_CURL_APPLY_LOCATIONS_MNDX)                              \
    _(XrHandTrackingDataSourceInfoEXT, XR_TYPE_HAND_TRACKING_DATA_SOURCE_INFO_EXT)                                          \
    _(XrHandTrackingDataSourceStateEXT, XR_TYPE_HAND_TRACKING_DATA_SOURCE_STATE_EXT)                                        \
    _(XrSystemPlaneDetectionPropertiesEXT, XR_TYPE_SYSTEM_PLANE_DETECTION_PROPERTIES_EXT)                                   \
    _(XrPlaneDetectorCreateInfoEXT, XR_TYPE_PLANE_DETECTOR_CREATE_INFO_EXT)                                                 \
    _(XrPlaneDetectorBeginInfoEXT, XR_TYPE_PLANE_DETECTOR_BEGIN_INFO_EXT)                                                   \
    _(XrPlaneDetectorGetInfoEXT, XR_TYPE_PLANE_DETECTOR_GET_INFO_EXT)                                                       \
    _(XrPlaneDetectorLocationEXT, XR_TYPE_PLANE_DETECTOR_LOCATION_EXT)                                                      \
    _(XrPlaneDetectorLocationsEXT, XR_TYPE_PLANE_DETECTOR_LOCATIONS_EXT)                                                    \
    _(XrPlaneDetectorPolygonBufferEXT, XR_TYPE_PLANE_DETECTOR_POLYGON_BUFFER_EXT)                                           \
    _(XrFutureCancelInfoEXT, XR_TYPE_FUTURE_CANCEL_INFO_EXT)                                                                \
    _(XrFuturePollInfoEXT, XR_TYPE_FUTURE_POLL_INFO_EXT)                                                                    \
    _(XrFutureCompletionEXT, XR_TYPE_FUTURE_COMPLETION_EXT)                                                                 \
    _(XrFuturePollResultEXT, XR_TYPE_FUTURE_POLL_RESULT_EXT)                                                                \
    _(XrEventDataUserPresenceChangedEXT, XR_TYPE_EVENT_DATA_USER_PRESENCE_CHANGED_EXT)                                      \
    _(XrSystemUserPresencePropertiesEXT, XR_TYPE_SYSTEM_USER_PRESENCE_PROPERTIES_EXT)                                       \
    _(XrEventDataHeadsetFitChangedML, XR_TYPE_EVENT_DATA_HEADSET_FIT_CHANGED_ML)                                            \
    _(XrEventDataEyeCalibrationChangedML, XR_TYPE_EVENT_DATA_EYE_CALIBRATION_CHANGED_ML)                                    \
    _(XrUserCalibrationEnableEventsInfoML, XR_TYPE_USER_CALIBRATION_ENABLE_EVENTS_INFO_ML)

#if defined(XR_USE_GRAPHICS_API_D3D11)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_GRAPHICS_API_D3D11 is defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D11(_)         \
        _(XrGraphicsBindingD3D11KHR, XR_TYPE_GRAPHICS_BINDING_D3D11_KHR) \
        _(XrSwapchainImageD3D11KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR)   \
        _(XrGraphicsRequirementsD3D11KHR, XR_TYPE_GRAPHICS_REQUIREMENTS_D3D11_KHR)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D11(_)
#endif

#if defined(XR_USE_GRAPHICS_API_D3D12)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_GRAPHICS_API_D3D12 is defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D12(_)         \
        _(XrGraphicsBindingD3D12KHR, XR_TYPE_GRAPHICS_BINDING_D3D12_KHR) \
        _(XrSwapchainImageD3D12KHR, XR_TYPE_SWAPCHAIN_IMAGE_D3D12_KHR)   \
        _(XrGraphicsRequirementsD3D12KHR, XR_TYPE_GRAPHICS_REQUIREMENTS_D3D12_KHR)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_D3D12(_)
#endif

#if defined(XR_USE_GRAPHICS_API_OPENGL)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_GRAPHICS_API_OPENGL is defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL(_)        \
        _(XrSwapchainImageOpenGLKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR) \
        _(XrGraphicsRequirementsOpenGLKHR, XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL(_)
#endif

#if defined(XR_USE_GRAPHICS_API_OPENGL) && defined(XR_USE_PLATFORM_WAYLAND)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_GRAPHICS_API_OPENGL and XR_USE_PLATFORM_WAYLAND are defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WAYLAND(_) \
        _(XrGraphicsBindingOpenGLWaylandKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_WAYLAND_KHR)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WAYLAND(_)
#endif

#if defined(XR_USE_GRAPHICS_API_OPENGL) && defined(XR_USE_PLATFORM_WIN32)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_GRAPHICS_API_OPENGL and XR_USE_PLATFORM_WIN32 are defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WIN32(_) \
        _(XrGraphicsBindingOpenGLWin32KHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_WIN32_KHR)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_WIN32(_)
#endif

#if defined(XR_USE_GRAPHICS_API_OPENGL) && defined(XR_USE_PLATFORM_XCB)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_GRAPHICS_API_OPENGL and XR_USE_PLATFORM_XCB are defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XCB(_) \
        _(XrGraphicsBindingOpenGLXcbKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_XCB_KHR)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XCB(_)
#endif

#if defined(XR_USE_GRAPHICS_API_OPENGL) && defined(XR_USE_PLATFORM_XLIB)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_GRAPHICS_API_OPENGL and XR_USE_PLATFORM_XLIB are defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XLIB(_) \
        _(XrGraphicsBindingOpenGLXlibKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_XR_USE_PLATFORM_XLIB(_)
#endif

#if defined(XR_USE_GRAPHICS_API_OPENGL_ES)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_GRAPHICS_API_OPENGL_ES is defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES(_)                      \
        _(XrSwapchainImageOpenGLESKHR, XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_ES_KHR)             \
        _(XrGraphicsRequirementsOpenGLESKHR, XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_ES_KHR) \
        _(XrSwapchainStateSamplerOpenGLESFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_OPENGL_ES_FB)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES(_)
#endif

#if defined(XR_USE_GRAPHICS_API_OPENGL_ES) && defined(XR_USE_PLATFORM_ANDROID)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_GRAPHICS_API_OPENGL_ES and XR_USE_PLATFORM_ANDROID are defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES_XR_USE_PLATFORM_ANDROID(_) \
        _(XrGraphicsBindingOpenGLESAndroidKHR, XR_TYPE_GRAPHICS_BINDING_OPENGL_ES_ANDROID_KHR)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_OPENGL_ES_XR_USE_PLATFORM_ANDROID(_)
#endif

#if defined(XR_USE_GRAPHICS_API_VULKAN)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_GRAPHICS_API_VULKAN is defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_VULKAN(_)                                         \
        _(XrVulkanSwapchainFormatListCreateInfoKHR, XR_TYPE_VULKAN_SWAPCHAIN_FORMAT_LIST_CREATE_INFO_KHR) \
        _(XrGraphicsBindingVulkanKHR, XR_TYPE_GRAPHICS_BINDING_VULKAN_KHR)                                \
        _(XrSwapchainImageVulkanKHR, XR_TYPE_SWAPCHAIN_IMAGE_VULKAN_KHR)                                  \
        _(XrGraphicsRequirementsVulkanKHR, XR_TYPE_GRAPHICS_REQUIREMENTS_VULKAN_KHR)                      \
        _(XrVulkanInstanceCreateInfoKHR, XR_TYPE_VULKAN_INSTANCE_CREATE_INFO_KHR)                         \
        _(XrVulkanDeviceCreateInfoKHR, XR_TYPE_VULKAN_DEVICE_CREATE_INFO_KHR)                             \
        _(XrVulkanGraphicsDeviceGetInfoKHR, XR_TYPE_VULKAN_GRAPHICS_DEVICE_GET_INFO_KHR)                  \
        _(XrSwapchainImageFoveationVulkanFB, XR_TYPE_SWAPCHAIN_IMAGE_FOVEATION_VULKAN_FB)                 \
        _(XrSwapchainStateSamplerVulkanFB, XR_TYPE_SWAPCHAIN_STATE_SAMPLER_VULKAN_FB)                     \
        _(XrVulkanSwapchainCreateInfoMETA, XR_TYPE_VULKAN_SWAPCHAIN_CREATE_INFO_META)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_GRAPHICS_API_VULKAN(_)
#endif

#if defined(XR_USE_PLATFORM_ANDROID)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_PLATFORM_ANDROID is defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_ANDROID(_)                                     \
        _(XrInstanceCreateInfoAndroidKHR, XR_TYPE_INSTANCE_CREATE_INFO_ANDROID_KHR)                \
        _(XrLoaderInitInfoAndroidKHR, XR_TYPE_LOADER_INIT_INFO_ANDROID_KHR)                        \
        _(XrAndroidSurfaceSwapchainCreateInfoFB, XR_TYPE_ANDROID_SURFACE_SWAPCHAIN_CREATE_INFO_FB) \
        _(XrSwapchainStateAndroidSurfaceDimensionsFB, XR_TYPE_SWAPCHAIN_STATE_ANDROID_SURFACE_DIMENSIONS_FB)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_ANDROID(_)
#endif

#if defined(XR_USE_PLATFORM_EGL)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_PLATFORM_EGL is defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_EGL(_) _(XrGraphicsBindingEGLMNDX, XR_TYPE_GRAPHICS_BINDING_EGL_MNDX)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_EGL(_)
#endif

#if defined(XR_USE_PLATFORM_ML)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_PLATFORM_ML is defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_ML(_) \
        _(XrCoordinateSpaceCreateInfoML, XR_TYPE_COORDINATE_SPACE_CREATE_INFO_ML)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_ML(_)
#endif

#if defined(XR_USE_PLATFORM_WIN32)
    /// Implementation detail of XR_LIST_STRUCTURE_TYPES()
    /// Structure types available only when XR_USE_PLATFORM_WIN32 is defined
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_WIN32(_) \
        _(XrHolographicWindowAttachmentMSFT, XR_TYPE_HOLOGRAPHIC_WINDOW_ATTACHMENT_MSFT)

#else
    #define XR_LIST_STRUCTURE_TYPES_XR_USE_PLATFORM_WIN32(_)
#endif

/// Calls your macro with the name and extension number of all known
/// extensions in this version of the spec.
#define XR_LIST_EXTENSIONS(_)                            \
    _(XR_KHR_android_thread_settings, 4)                 \
    _(XR_KHR_android_surface_swapchain, 5)               \
    _(XR_KHR_composition_layer_cube, 7)                  \
    _(XR_KHR_android_create_instance, 9)                 \
    _(XR_KHR_composition_layer_depth, 11)                \
    _(XR_KHR_vulkan_swapchain_format_list, 15)           \
    _(XR_EXT_performance_settings, 16)                   \
    _(XR_EXT_thermal_query, 17)                          \
    _(XR_KHR_composition_layer_cylinder, 18)             \
    _(XR_KHR_composition_layer_equirect, 19)             \
    _(XR_EXT_debug_utils, 20)                            \
    _(XR_KHR_opengl_enable, 24)                          \
    _(XR_KHR_opengl_es_enable, 25)                       \
    _(XR_KHR_vulkan_enable, 26)                          \
    _(XR_KHR_D3D11_enable, 28)                           \
    _(XR_KHR_D3D12_enable, 29)                           \
    _(XR_EXT_eye_gaze_interaction, 31)                   \
    _(XR_KHR_visibility_mask, 32)                        \
    _(XR_EXTX_overlay, 34)                               \
    _(XR_KHR_composition_layer_color_scale_bias, 35)     \
    _(XR_KHR_win32_convert_performance_counter_time, 36) \
    _(XR_KHR_convert_timespec_time, 37)                  \
    _(XR_VARJO_quad_views, 38)                           \
    _(XR_MSFT_unbounded_reference_space, 39)             \
    _(XR_MSFT_spatial_anchor, 40)                        \
    _(XR_FB_composition_layer_image_layout, 41)          \
    _(XR_FB_composition_layer_alpha_blend, 42)           \
    _(XR_MND_headless, 43)                               \
    _(XR_OCULUS_android_session_state_enable, 45)        \
    _(XR_EXT_view_configuration_depth_range, 47)         \
    _(XR_EXT_conformance_automation, 48)                 \
    _(XR_MNDX_egl_enable, 49)                            \
    _(XR_MSFT_spatial_graph_bridge, 50)                  \
    _(XR_MSFT_hand_interaction, 51)                      \
    _(XR_EXT_hand_tracking, 52)                          \
    _(XR_MSFT_hand_tracking_mesh, 53)                    \
    _(XR_MSFT_secondary_view_configuration, 54)          \
    _(XR_MSFT_first_person_observer, 55)                 \
    _(XR_MSFT_controller_model, 56)                      \
    _(XR_MSFT_perception_anchor_interop, 57)             \
    _(XR_EXT_win32_appcontainer_compatible, 58)          \
    _(XR_EPIC_view_configuration_fov, 60)                \
    _(XR_MSFT_holographic_window_attachment, 64)         \
    _(XR_MSFT_composition_layer_reprojection, 67)        \
    _(XR_HUAWEI_controller_interaction, 70)              \
    _(XR_FB_android_surface_swapchain_create, 71)        \
    _(XR_FB_swapchain_update_state, 72)                  \
    _(XR_FB_composition_layer_secure_content, 73)        \
    _(XR_FB_body_tracking, 77)                           \
    _(XR_EXT_dpad_binding, 79)                           \
    _(XR_VALVE_analog_threshold, 80)                     \
    _(XR_EXT_hand_joints_motion_range, 81)               \
    _(XR_KHR_loader_init, 89)                            \
    _(XR_KHR_loader_init_android, 90)                    \
    _(XR_KHR_vulkan_enable2, 91)                         \
    _(XR_KHR_composition_layer_equirect2, 92)            \
    _(XR_EXT_samsung_odyssey_controller, 95)             \
    _(XR_EXT_hp_mixed_reality_controller, 96)            \
    _(XR_MND_swapchain_usage_input_attachment_bit, 97)   \
    _(XR_MSFT_scene_understanding, 98)                   \
    _(XR_MSFT_scene_understanding_serialization, 99)     \
    _(XR_FB_display_refresh_rate, 102)                   \
    _(XR_HTC_vive_cosmos_controller_interaction, 103)    \
    _(XR_HTCX_vive_tracker_interaction, 104)             \
    _(XR_HTC_facial_tracking, 105)                       \
    _(XR_HTC_vive_focus3_controller_interaction, 106)    \
    _(XR_HTC_hand_interaction, 107)                      \
    _(XR_HTC_vive_wrist_tracker_interaction, 108)        \
    _(XR_FB_color_space, 109)                            \
    _(XR_FB_hand_tracking_mesh, 111)                     \
    _(XR_FB_hand_tracking_aim, 112)                      \
    _(XR_FB_hand_tracking_capsules, 113)                 \
    _(XR_FB_spatial_entity, 114)                         \
    _(XR_FB_foveation, 115)                              \
    _(XR_FB_foveation_configuration, 116)                \
    _(XR_FB_keyboard_tracking, 117)                      \
    _(XR_FB_triangle_mesh, 118)                          \
    _(XR_FB_passthrough, 119)                            \
    _(XR_FB_render_model, 120)                           \
    _(XR_KHR_binding_modification, 121)                  \
    _(XR_VARJO_foveated_rendering, 122)                  \
    _(XR_VARJO_composition_layer_depth_test, 123)        \
    _(XR_VARJO_environment_depth_estimation, 124)        \
    _(XR_VARJO_marker_tracking, 125)                     \
    _(XR_VARJO_view_offset, 126)                         \
    _(XR_VARJO_xr4_controller_interaction, 130)          \
    _(XR_ML_ml2_controller_interaction, 135)             \
    _(XR_ML_frame_end_info, 136)                         \
    _(XR_ML_global_dimmer, 137)                          \
    _(XR_ML_compat, 138)                                 \
    _(XR_ML_marker_understanding, 139)                   \
    _(XR_ML_localization_map, 140)                       \
    _(XR_MSFT_spatial_anchor_persistence, 143)           \
    _(XR_MSFT_scene_marker, 148)                         \
    _(XR_ULTRALEAP_hand_tracking_forearm, 150)           \
    _(XR_FB_spatial_entity_query, 157)                   \
    _(XR_FB_spatial_entity_storage, 159)                 \
    _(XR_OCULUS_audio_device_guid, 160)                  \
    _(XR_FB_foveation_vulkan, 161)                       \
    _(XR_FB_swapchain_update_state_android_surface, 162) \
    _(XR_FB_swapchain_update_state_opengl_es, 163)       \
    _(XR_FB_swapchain_update_state_vulkan, 164)          \
    _(XR_KHR_swapchain_usage_input_attachment_bit, 166)  \
    _(XR_FB_touch_controller_pro, 168)                   \
    _(XR_FB_spatial_entity_sharing, 170)                 \
    _(XR_FB_space_warp, 172)                             \
    _(XR_FB_haptic_amplitude_envelope, 174)              \
    _(XR_FB_scene, 176)                                  \
    _(XR_EXT_palm_pose, 177)                             \
    _(XR_ALMALENCE_digital_lens_control, 197)            \
    _(XR_FB_scene_capture, 199)                          \
    _(XR_FB_spatial_entity_container, 200)               \
    _(XR_META_foveation_eye_tracked, 201)                \
    _(XR_FB_face_tracking, 202)                          \
    _(XR_FB_eye_tracking_social, 203)                    \
    _(XR_FB_passthrough_keyboard_hands, 204)             \
    _(XR_FB_composition_layer_settings, 205)             \
    _(XR_FB_touch_controller_proximity, 207)             \
    _(XR_FB_haptic_pcm, 210)                             \
    _(XR_FB_composition_layer_depth_test, 213)           \
    _(XR_META_local_dimming, 217)                        \
    _(XR_META_passthrough_preferences, 218)              \
    _(XR_META_virtual_keyboard, 220)                     \
    _(XR_OCULUS_external_camera, 227)                    \
    _(XR_META_vulkan_swapchain_create_info, 228)         \
    _(XR_META_performance_metrics, 233)                  \
    _(XR_FB_spatial_entity_storage_batch, 239)           \
    _(XR_FB_spatial_entity_user, 242)                    \
    _(XR_META_headset_id, 246)                           \
    _(XR_META_recommended_layer_resolution, 255)         \
    _(XR_META_passthrough_color_lut, 267)                \
    _(XR_META_spatial_entity_mesh, 270)                  \
    _(XR_META_automatic_layer_filter, 272)               \
    _(XR_META_touch_controller_plus, 280)                \
    _(XR_FB_face_tracking2, 288)                         \
    _(XR_META_environment_depth, 292)                    \
    _(XR_EXT_uuid, 300)                                  \
    _(XR_EXT_hand_interaction, 303)                      \
    _(XR_QCOM_tracking_optimization_settings, 307)       \
    _(XR_HTC_passthrough, 318)                           \
    _(XR_HTC_foveation, 319)                             \
    _(XR_HTC_anchor, 320)                                \
    _(XR_EXT_active_action_set_priority, 374)            \
    _(XR_MNDX_force_feedback_curl, 376)                  \
    _(XR_BD_controller_interaction, 385)                 \
    _(XR_EXT_local_floor, 427)                           \
    _(XR_EXT_hand_tracking_data_source, 429)             \
    _(XR_EXT_plane_detection, 430)                       \
    _(XR_OPPO_controller_interaction, 454)               \
    _(XR_EXT_future, 470)                                \
    _(XR_EXT_user_presence, 471)                         \
    _(XR_KHR_locate_spaces, 472)                         \
    _(XR_ML_user_calibration, 473)                       \
    _(XR_YVR_controller_interaction, 498)                \
    _(XR_KHR_maintenance1, 711)

/// For every function defined by XR_VERSION_1_0 in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_VERSION_1_0(_)              \
    _(GetInstanceProcAddr, VERSION_1_0)                  \
    _(EnumerateApiLayerProperties, VERSION_1_0)          \
    _(EnumerateInstanceExtensionProperties, VERSION_1_0) \
    _(CreateInstance, VERSION_1_0)                       \
    _(DestroyInstance, VERSION_1_0)                      \
    _(GetInstanceProperties, VERSION_1_0)                \
    _(PollEvent, VERSION_1_0)                            \
    _(ResultToString, VERSION_1_0)                       \
    _(StructureTypeToString, VERSION_1_0)                \
    _(GetSystem, VERSION_1_0)                            \
    _(GetSystemProperties, VERSION_1_0)                  \
    _(EnumerateEnvironmentBlendModes, VERSION_1_0)       \
    _(CreateSession, VERSION_1_0)                        \
    _(DestroySession, VERSION_1_0)                       \
    _(EnumerateReferenceSpaces, VERSION_1_0)             \
    _(CreateReferenceSpace, VERSION_1_0)                 \
    _(GetReferenceSpaceBoundsRect, VERSION_1_0)          \
    _(CreateActionSpace, VERSION_1_0)                    \
    _(LocateSpace, VERSION_1_0)                          \
    _(DestroySpace, VERSION_1_0)                         \
    _(EnumerateViewConfigurations, VERSION_1_0)          \
    _(GetViewConfigurationProperties, VERSION_1_0)       \
    _(EnumerateViewConfigurationViews, VERSION_1_0)      \
    _(EnumerateSwapchainFormats, VERSION_1_0)            \
    _(CreateSwapchain, VERSION_1_0)                      \
    _(DestroySwapchain, VERSION_1_0)                     \
    _(EnumerateSwapchainImages, VERSION_1_0)             \
    _(AcquireSwapchainImage, VERSION_1_0)                \
    _(WaitSwapchainImage, VERSION_1_0)                   \
    _(ReleaseSwapchainImage, VERSION_1_0)                \
    _(BeginSession, VERSION_1_0)                         \
    _(EndSession, VERSION_1_0)                           \
    _(RequestExitSession, VERSION_1_0)                   \
    _(WaitFrame, VERSION_1_0)                            \
    _(BeginFrame, VERSION_1_0)                           \
    _(EndFrame, VERSION_1_0)                             \
    _(LocateViews, VERSION_1_0)                          \
    _(StringToPath, VERSION_1_0)                         \
    _(PathToString, VERSION_1_0)                         \
    _(CreateActionSet, VERSION_1_0)                      \
    _(DestroyActionSet, VERSION_1_0)                     \
    _(CreateAction, VERSION_1_0)                         \
    _(DestroyAction, VERSION_1_0)                        \
    _(SuggestInteractionProfileBindings, VERSION_1_0)    \
    _(AttachSessionActionSets, VERSION_1_0)              \
    _(GetCurrentInteractionProfile, VERSION_1_0)         \
    _(GetActionStateBoolean, VERSION_1_0)                \
    _(GetActionStateFloat, VERSION_1_0)                  \
    _(GetActionStateVector2f, VERSION_1_0)               \
    _(GetActionStatePose, VERSION_1_0)                   \
    _(SyncActions, VERSION_1_0)                          \
    _(EnumerateBoundSourcesForAction, VERSION_1_0)       \
    _(GetInputSourceLocalizedName, VERSION_1_0)          \
    _(ApplyHapticFeedback, VERSION_1_0)                  \
    _(StopHapticFeedback, VERSION_1_0)

/// For every function defined by XR_LOADER_VERSION_1_0 in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_LOADER_VERSION_1_0(_)         \
    _(CreateApiLayerInstance, LOADER_VERSION_1_0)          \
    _(NegotiateLoaderRuntimeInterface, LOADER_VERSION_1_0) \
    _(NegotiateLoaderApiLayerInterface, LOADER_VERSION_1_0)

/// For every function defined by XR_VERSION_1_1 in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_VERSION_1_1(_) _(LocateSpaces, VERSION_1_1)

/// For every function defined by XR_KHR_android_thread_settings in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_android_thread_settings(_) _(SetAndroidApplicationThreadKHR, KHR_android_thread_settings)

/// For every function defined by XR_KHR_android_surface_swapchain in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_android_surface_swapchain(_) _(CreateSwapchainAndroidSurfaceKHR, KHR_android_surface_swapchain)

/// For every function defined by XR_KHR_opengl_enable in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_opengl_enable(_) _(GetOpenGLGraphicsRequirementsKHR, KHR_opengl_enable)

/// For every function defined by XR_KHR_opengl_es_enable in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_opengl_es_enable(_) _(GetOpenGLESGraphicsRequirementsKHR, KHR_opengl_es_enable)

/// For every function defined by XR_KHR_vulkan_enable in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_vulkan_enable(_)        \
    _(GetVulkanInstanceExtensionsKHR, KHR_vulkan_enable) \
    _(GetVulkanDeviceExtensionsKHR, KHR_vulkan_enable)   \
    _(GetVulkanGraphicsDeviceKHR, KHR_vulkan_enable)     \
    _(GetVulkanGraphicsRequirementsKHR, KHR_vulkan_enable)

/// For every function defined by XR_KHR_D3D11_enable in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_D3D11_enable(_) _(GetD3D11GraphicsRequirementsKHR, KHR_D3D11_enable)

/// For every function defined by XR_KHR_D3D12_enable in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_D3D12_enable(_) _(GetD3D12GraphicsRequirementsKHR, KHR_D3D12_enable)

/// For every function defined by XR_KHR_visibility_mask in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_visibility_mask(_) _(GetVisibilityMaskKHR, KHR_visibility_mask)

/// For every function defined by XR_KHR_win32_convert_performance_counter_time in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_win32_convert_performance_counter_time(_)                 \
    _(ConvertWin32PerformanceCounterToTimeKHR, KHR_win32_convert_performance_counter_time) \
    _(ConvertTimeToWin32PerformanceCounterKHR, KHR_win32_convert_performance_counter_time)

/// For every function defined by XR_KHR_convert_timespec_time in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_convert_timespec_time(_)      \
    _(ConvertTimespecTimeToTimeKHR, KHR_convert_timespec_time) \
    _(ConvertTimeToTimespecTimeKHR, KHR_convert_timespec_time)

/// For every function defined by XR_KHR_loader_init in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_loader_init(_) _(InitializeLoaderKHR, KHR_loader_init)

/// For every function defined by XR_KHR_vulkan_enable2 in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_KHR_vulkan_enable2(_) \
    _(CreateVulkanInstanceKHR, KHR_vulkan_enable2) \
    _(CreateVulkanDeviceKHR, KHR_vulkan_enable2)   \
    _(GetVulkanGraphicsDevice2KHR, KHR_vulkan_enable2)

/// For every function defined by XR_EXT_performance_settings in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_EXT_performance_settings(_) _(PerfSettingsSetPerformanceLevelEXT, EXT_performance_settings)

/// For every function defined by XR_EXT_thermal_query in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_EXT_thermal_query(_) _(ThermalGetTemperatureTrendEXT, EXT_thermal_query)

/// For every function defined by XR_EXT_debug_utils in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_EXT_debug_utils(_)              \
    _(SetDebugUtilsObjectNameEXT, EXT_debug_utils)           \
    _(CreateDebugUtilsMessengerEXT, EXT_debug_utils)         \
    _(DestroyDebugUtilsMessengerEXT, EXT_debug_utils)        \
    _(SubmitDebugUtilsMessageEXT, EXT_debug_utils)           \
    _(SessionBeginDebugUtilsLabelRegionEXT, EXT_debug_utils) \
    _(SessionEndDebugUtilsLabelRegionEXT, EXT_debug_utils)   \
    _(SessionInsertDebugUtilsLabelEXT, EXT_debug_utils)

/// For every function defined by XR_MSFT_spatial_anchor in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_MSFT_spatial_anchor(_)      \
    _(CreateSpatialAnchorMSFT, MSFT_spatial_anchor)      \
    _(CreateSpatialAnchorSpaceMSFT, MSFT_spatial_anchor) \
    _(DestroySpatialAnchorMSFT, MSFT_spatial_anchor)

/// For every function defined by XR_EXT_conformance_automation in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_EXT_conformance_automation(_)        \
    _(SetInputDeviceActiveEXT, EXT_conformance_automation)        \
    _(SetInputDeviceStateBoolEXT, EXT_conformance_automation)     \
    _(SetInputDeviceStateFloatEXT, EXT_conformance_automation)    \
    _(SetInputDeviceStateVector2fEXT, EXT_conformance_automation) \
    _(SetInputDeviceLocationEXT, EXT_conformance_automation)

/// For every function defined by XR_MSFT_spatial_graph_bridge in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_MSFT_spatial_graph_bridge(_)                    \
    _(CreateSpatialGraphNodeSpaceMSFT, MSFT_spatial_graph_bridge)            \
    _(TryCreateSpatialGraphStaticNodeBindingMSFT, MSFT_spatial_graph_bridge) \
    _(DestroySpatialGraphNodeBindingMSFT, MSFT_spatial_graph_bridge)         \
    _(GetSpatialGraphNodeBindingPropertiesMSFT, MSFT_spatial_graph_bridge)

/// For every function defined by XR_EXT_hand_tracking in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_EXT_hand_tracking(_) \
    _(CreateHandTrackerEXT, EXT_hand_tracking)    \
    _(DestroyHandTrackerEXT, EXT_hand_tracking)   \
    _(LocateHandJointsEXT, EXT_hand_tracking)

/// For every function defined by XR_MSFT_hand_tracking_mesh in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_MSFT_hand_tracking_mesh(_) \
    _(CreateHandMeshSpaceMSFT, MSFT_hand_tracking_mesh) \
    _(UpdateHandMeshMSFT, MSFT_hand_tracking_mesh)

/// For every function defined by XR_MSFT_controller_model in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_MSFT_controller_model(_)          \
    _(GetControllerModelKeyMSFT, MSFT_controller_model)        \
    _(LoadControllerModelMSFT, MSFT_controller_model)          \
    _(GetControllerModelPropertiesMSFT, MSFT_controller_model) \
    _(GetControllerModelStateMSFT, MSFT_controller_model)

/// For every function defined by XR_MSFT_perception_anchor_interop in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_MSFT_perception_anchor_interop(_)                     \
    _(CreateSpatialAnchorFromPerceptionAnchorMSFT, MSFT_perception_anchor_interop) \
    _(TryGetPerceptionAnchorFromSpatialAnchorMSFT, MSFT_perception_anchor_interop)

/// For every function defined by XR_MSFT_composition_layer_reprojection in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_MSFT_composition_layer_reprojection(_) \
    _(EnumerateReprojectionModesMSFT, MSFT_composition_layer_reprojection)

/// For every function defined by XR_FB_swapchain_update_state in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_swapchain_update_state(_) \
    _(UpdateSwapchainFB, FB_swapchain_update_state)       \
    _(GetSwapchainStateFB, FB_swapchain_update_state)

/// For every function defined by XR_FB_body_tracking in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_body_tracking(_) \
    _(CreateBodyTrackerFB, FB_body_tracking)     \
    _(DestroyBodyTrackerFB, FB_body_tracking)    \
    _(LocateBodyJointsFB, FB_body_tracking)      \
    _(GetBodySkeletonFB, FB_body_tracking)

/// For every function defined by XR_MSFT_scene_understanding in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_MSFT_scene_understanding(_)           \
    _(EnumerateSceneComputeFeaturesMSFT, MSFT_scene_understanding) \
    _(CreateSceneObserverMSFT, MSFT_scene_understanding)           \
    _(DestroySceneObserverMSFT, MSFT_scene_understanding)          \
    _(CreateSceneMSFT, MSFT_scene_understanding)                   \
    _(DestroySceneMSFT, MSFT_scene_understanding)                  \
    _(ComputeNewSceneMSFT, MSFT_scene_understanding)               \
    _(GetSceneComputeStateMSFT, MSFT_scene_understanding)          \
    _(GetSceneComponentsMSFT, MSFT_scene_understanding)            \
    _(LocateSceneComponentsMSFT, MSFT_scene_understanding)         \
    _(GetSceneMeshBuffersMSFT, MSFT_scene_understanding)

/// For every function defined by XR_MSFT_scene_understanding_serialization in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_MSFT_scene_understanding_serialization(_) \
    _(DeserializeSceneMSFT, MSFT_scene_understanding_serialization)    \
    _(GetSerializedSceneFragmentDataMSFT, MSFT_scene_understanding_serialization)

/// For every function defined by XR_FB_display_refresh_rate in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_display_refresh_rate(_)        \
    _(EnumerateDisplayRefreshRatesFB, FB_display_refresh_rate) \
    _(GetDisplayRefreshRateFB, FB_display_refresh_rate)        \
    _(RequestDisplayRefreshRateFB, FB_display_refresh_rate)

/// For every function defined by XR_HTCX_vive_tracker_interaction in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_HTCX_vive_tracker_interaction(_) _(EnumerateViveTrackerPathsHTCX, HTCX_vive_tracker_interaction)

/// For every function defined by XR_HTC_facial_tracking in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_HTC_facial_tracking(_) \
    _(CreateFacialTrackerHTC, HTC_facial_tracking)  \
    _(DestroyFacialTrackerHTC, HTC_facial_tracking) \
    _(GetFacialExpressionsHTC, HTC_facial_tracking)

/// For every function defined by XR_FB_color_space in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_color_space(_) \
    _(EnumerateColorSpacesFB, FB_color_space)  \
    _(SetColorSpaceFB, FB_color_space)

/// For every function defined by XR_FB_hand_tracking_mesh in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_hand_tracking_mesh(_) _(GetHandMeshFB, FB_hand_tracking_mesh)

/// For every function defined by XR_FB_spatial_entity in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_spatial_entity(_)             \
    _(CreateSpatialAnchorFB, FB_spatial_entity)               \
    _(GetSpaceUuidFB, FB_spatial_entity)                      \
    _(EnumerateSpaceSupportedComponentsFB, FB_spatial_entity) \
    _(SetSpaceComponentStatusFB, FB_spatial_entity)           \
    _(GetSpaceComponentStatusFB, FB_spatial_entity)

/// For every function defined by XR_FB_foveation in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_foveation(_)  \
    _(CreateFoveationProfileFB, FB_foveation) \
    _(DestroyFoveationProfileFB, FB_foveation)

/// For every function defined by XR_FB_keyboard_tracking in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_keyboard_tracking(_)      \
    _(QuerySystemTrackedKeyboardFB, FB_keyboard_tracking) \
    _(CreateKeyboardSpaceFB, FB_keyboard_tracking)

/// For every function defined by XR_FB_triangle_mesh in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_triangle_mesh(_)               \
    _(CreateTriangleMeshFB, FB_triangle_mesh)                  \
    _(DestroyTriangleMeshFB, FB_triangle_mesh)                 \
    _(TriangleMeshGetVertexBufferFB, FB_triangle_mesh)         \
    _(TriangleMeshGetIndexBufferFB, FB_triangle_mesh)          \
    _(TriangleMeshBeginUpdateFB, FB_triangle_mesh)             \
    _(TriangleMeshEndUpdateFB, FB_triangle_mesh)               \
    _(TriangleMeshBeginVertexBufferUpdateFB, FB_triangle_mesh) \
    _(TriangleMeshEndVertexBufferUpdateFB, FB_triangle_mesh)

/// For every function defined by XR_FB_passthrough in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_passthrough(_)    \
    _(CreatePassthroughFB, FB_passthrough)        \
    _(DestroyPassthroughFB, FB_passthrough)       \
    _(PassthroughStartFB, FB_passthrough)         \
    _(PassthroughPauseFB, FB_passthrough)         \
    _(CreatePassthroughLayerFB, FB_passthrough)   \
    _(DestroyPassthroughLayerFB, FB_passthrough)  \
    _(PassthroughLayerPauseFB, FB_passthrough)    \
    _(PassthroughLayerResumeFB, FB_passthrough)   \
    _(PassthroughLayerSetStyleFB, FB_passthrough) \
    _(CreateGeometryInstanceFB, FB_passthrough)   \
    _(DestroyGeometryInstanceFB, FB_passthrough)  \
    _(GeometryInstanceSetTransformFB, FB_passthrough)

/// For every function defined by XR_FB_render_model in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_render_model(_)     \
    _(EnumerateRenderModelPathsFB, FB_render_model) \
    _(GetRenderModelPropertiesFB, FB_render_model)  \
    _(LoadRenderModelFB, FB_render_model)

/// For every function defined by XR_VARJO_environment_depth_estimation in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_VARJO_environment_depth_estimation(_) \
    _(SetEnvironmentDepthEstimationVARJO, VARJO_environment_depth_estimation)

/// For every function defined by XR_VARJO_marker_tracking in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_VARJO_marker_tracking(_)          \
    _(SetMarkerTrackingVARJO, VARJO_marker_tracking)           \
    _(SetMarkerTrackingTimeoutVARJO, VARJO_marker_tracking)    \
    _(SetMarkerTrackingPredictionVARJO, VARJO_marker_tracking) \
    _(GetMarkerSizeVARJO, VARJO_marker_tracking)               \
    _(CreateMarkerSpaceVARJO, VARJO_marker_tracking)

/// For every function defined by XR_VARJO_view_offset in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_VARJO_view_offset(_) _(SetViewOffsetVARJO, VARJO_view_offset)

/// For every function defined by XR_ML_compat in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_ML_compat(_) _(CreateSpaceFromCoordinateFrameUIDML, ML_compat)

/// For every function defined by XR_ML_marker_understanding in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_ML_marker_understanding(_)      \
    _(CreateMarkerDetectorML, ML_marker_understanding)       \
    _(DestroyMarkerDetectorML, ML_marker_understanding)      \
    _(SnapshotMarkerDetectorML, ML_marker_understanding)     \
    _(GetMarkerDetectorStateML, ML_marker_understanding)     \
    _(GetMarkersML, ML_marker_understanding)                 \
    _(GetMarkerReprojectionErrorML, ML_marker_understanding) \
    _(GetMarkerLengthML, ML_marker_understanding)            \
    _(GetMarkerNumberML, ML_marker_understanding)            \
    _(GetMarkerStringML, ML_marker_understanding)            \
    _(CreateMarkerSpaceML, ML_marker_understanding)

/// For every function defined by XR_ML_localization_map in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_ML_localization_map(_)          \
    _(EnableLocalizationEventsML, ML_localization_map)       \
    _(QueryLocalizationMapsML, ML_localization_map)          \
    _(RequestMapLocalizationML, ML_localization_map)         \
    _(ImportLocalizationMapML, ML_localization_map)          \
    _(CreateExportedLocalizationMapML, ML_localization_map)  \
    _(DestroyExportedLocalizationMapML, ML_localization_map) \
    _(GetExportedLocalizationMapDataML, ML_localization_map)

/// For every function defined by XR_MSFT_spatial_anchor_persistence in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_MSFT_spatial_anchor_persistence(_)                  \
    _(CreateSpatialAnchorStoreConnectionMSFT, MSFT_spatial_anchor_persistence)   \
    _(DestroySpatialAnchorStoreConnectionMSFT, MSFT_spatial_anchor_persistence)  \
    _(PersistSpatialAnchorMSFT, MSFT_spatial_anchor_persistence)                 \
    _(EnumeratePersistedSpatialAnchorNamesMSFT, MSFT_spatial_anchor_persistence) \
    _(CreateSpatialAnchorFromPersistedNameMSFT, MSFT_spatial_anchor_persistence) \
    _(UnpersistSpatialAnchorMSFT, MSFT_spatial_anchor_persistence)               \
    _(ClearSpatialAnchorStoreMSFT, MSFT_spatial_anchor_persistence)

/// For every function defined by XR_MSFT_scene_marker in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_MSFT_scene_marker(_)   \
    _(GetSceneMarkerRawDataMSFT, MSFT_scene_marker) \
    _(GetSceneMarkerDecodedStringMSFT, MSFT_scene_marker)

/// For every function defined by XR_FB_spatial_entity_query in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_spatial_entity_query(_) \
    _(QuerySpacesFB, FB_spatial_entity_query)           \
    _(RetrieveSpaceQueryResultsFB, FB_spatial_entity_query)

/// For every function defined by XR_FB_spatial_entity_storage in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_spatial_entity_storage(_) \
    _(SaveSpaceFB, FB_spatial_entity_storage)             \
    _(EraseSpaceFB, FB_spatial_entity_storage)

/// For every function defined by XR_OCULUS_audio_device_guid in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_OCULUS_audio_device_guid(_)        \
    _(GetAudioOutputDeviceGuidOculus, OCULUS_audio_device_guid) \
    _(GetAudioInputDeviceGuidOculus, OCULUS_audio_device_guid)

/// For every function defined by XR_FB_spatial_entity_sharing in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_spatial_entity_sharing(_) _(ShareSpacesFB, FB_spatial_entity_sharing)

/// For every function defined by XR_FB_scene in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_scene(_)  \
    _(GetSpaceBoundingBox2DFB, FB_scene)  \
    _(GetSpaceBoundingBox3DFB, FB_scene)  \
    _(GetSpaceSemanticLabelsFB, FB_scene) \
    _(GetSpaceBoundary2DFB, FB_scene)     \
    _(GetSpaceRoomLayoutFB, FB_scene)

/// For every function defined by XR_ALMALENCE_digital_lens_control in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_ALMALENCE_digital_lens_control(_) _(SetDigitalLensControlALMALENCE, ALMALENCE_digital_lens_control)

/// For every function defined by XR_FB_scene_capture in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_scene_capture(_) _(RequestSceneCaptureFB, FB_scene_capture)

/// For every function defined by XR_FB_spatial_entity_container in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_spatial_entity_container(_) _(GetSpaceContainerFB, FB_spatial_entity_container)

/// For every function defined by XR_META_foveation_eye_tracked in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_META_foveation_eye_tracked(_) _(GetFoveationEyeTrackedStateMETA, META_foveation_eye_tracked)

/// For every function defined by XR_FB_face_tracking in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_face_tracking(_) \
    _(CreateFaceTrackerFB, FB_face_tracking)     \
    _(DestroyFaceTrackerFB, FB_face_tracking)    \
    _(GetFaceExpressionWeightsFB, FB_face_tracking)

/// For every function defined by XR_FB_eye_tracking_social in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_eye_tracking_social(_) \
    _(CreateEyeTrackerFB, FB_eye_tracking_social)      \
    _(DestroyEyeTrackerFB, FB_eye_tracking_social)     \
    _(GetEyeGazesFB, FB_eye_tracking_social)

/// For every function defined by XR_FB_passthrough_keyboard_hands in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_passthrough_keyboard_hands(_) \
    _(PassthroughLayerSetKeyboardHandsIntensityFB, FB_passthrough_keyboard_hands)

/// For every function defined by XR_FB_haptic_pcm in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_haptic_pcm(_) _(GetDeviceSampleRateFB, FB_haptic_pcm)

/// For every function defined by XR_META_passthrough_preferences in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_META_passthrough_preferences(_) _(GetPassthroughPreferencesMETA, META_passthrough_preferences)

/// For every function defined by XR_META_virtual_keyboard in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_META_virtual_keyboard(_)                    \
    _(CreateVirtualKeyboardMETA, META_virtual_keyboard)                  \
    _(DestroyVirtualKeyboardMETA, META_virtual_keyboard)                 \
    _(CreateVirtualKeyboardSpaceMETA, META_virtual_keyboard)             \
    _(SuggestVirtualKeyboardLocationMETA, META_virtual_keyboard)         \
    _(GetVirtualKeyboardScaleMETA, META_virtual_keyboard)                \
    _(SetVirtualKeyboardModelVisibilityMETA, META_virtual_keyboard)      \
    _(GetVirtualKeyboardModelAnimationStatesMETA, META_virtual_keyboard) \
    _(GetVirtualKeyboardDirtyTexturesMETA, META_virtual_keyboard)        \
    _(GetVirtualKeyboardTextureDataMETA, META_virtual_keyboard)          \
    _(SendVirtualKeyboardInputMETA, META_virtual_keyboard)               \
    _(ChangeVirtualKeyboardTextContextMETA, META_virtual_keyboard)

/// For every function defined by XR_OCULUS_external_camera in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_OCULUS_external_camera(_) _(EnumerateExternalCamerasOCULUS, OCULUS_external_camera)

/// For every function defined by XR_META_performance_metrics in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_META_performance_metrics(_)                     \
    _(EnumeratePerformanceMetricsCounterPathsMETA, META_performance_metrics) \
    _(SetPerformanceMetricsStateMETA, META_performance_metrics)              \
    _(GetPerformanceMetricsStateMETA, META_performance_metrics)              \
    _(QueryPerformanceMetricsCounterMETA, META_performance_metrics)

/// For every function defined by XR_FB_spatial_entity_storage_batch in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_spatial_entity_storage_batch(_) _(SaveSpaceListFB, FB_spatial_entity_storage_batch)

/// For every function defined by XR_FB_spatial_entity_user in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_spatial_entity_user(_) \
    _(CreateSpaceUserFB, FB_spatial_entity_user)       \
    _(GetSpaceUserIdFB, FB_spatial_entity_user)        \
    _(DestroySpaceUserFB, FB_spatial_entity_user)

/// For every function defined by XR_META_recommended_layer_resolution in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_META_recommended_layer_resolution(_) \
    _(GetRecommendedLayerResolutionMETA, META_recommended_layer_resolution)

/// For every function defined by XR_META_passthrough_color_lut in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_META_passthrough_color_lut(_)        \
    _(CreatePassthroughColorLutMETA, META_passthrough_color_lut)  \
    _(DestroyPassthroughColorLutMETA, META_passthrough_color_lut) \
    _(UpdatePassthroughColorLutMETA, META_passthrough_color_lut)

/// For every function defined by XR_META_spatial_entity_mesh in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_META_spatial_entity_mesh(_) _(GetSpaceTriangleMeshMETA, META_spatial_entity_mesh)

/// For every function defined by XR_FB_face_tracking2 in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_FB_face_tracking2(_) \
    _(CreateFaceTracker2FB, FB_face_tracking2)    \
    _(DestroyFaceTracker2FB, FB_face_tracking2)   \
    _(GetFaceExpressionWeights2FB, FB_face_tracking2)

/// For every function defined by XR_META_environment_depth in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_META_environment_depth(_)                      \
    _(CreateEnvironmentDepthProviderMETA, META_environment_depth)           \
    _(DestroyEnvironmentDepthProviderMETA, META_environment_depth)          \
    _(StartEnvironmentDepthProviderMETA, META_environment_depth)            \
    _(StopEnvironmentDepthProviderMETA, META_environment_depth)             \
    _(CreateEnvironmentDepthSwapchainMETA, META_environment_depth)          \
    _(DestroyEnvironmentDepthSwapchainMETA, META_environment_depth)         \
    _(EnumerateEnvironmentDepthSwapchainImagesMETA, META_environment_depth) \
    _(GetEnvironmentDepthSwapchainStateMETA, META_environment_depth)        \
    _(AcquireEnvironmentDepthImageMETA, META_environment_depth)             \
    _(SetEnvironmentDepthHandRemovalMETA, META_environment_depth)

/// For every function defined by XR_QCOM_tracking_optimization_settings in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_QCOM_tracking_optimization_settings(_) \
    _(SetTrackingOptimizationSettingsHintQCOM, QCOM_tracking_optimization_settings)

/// For every function defined by XR_HTC_passthrough in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_HTC_passthrough(_) \
    _(CreatePassthroughHTC, HTC_passthrough)    \
    _(DestroyPassthroughHTC, HTC_passthrough)

/// For every function defined by XR_HTC_foveation in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_HTC_foveation(_) _(ApplyFoveationHTC, HTC_foveation)

/// For every function defined by XR_HTC_anchor in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_HTC_anchor(_) \
    _(CreateSpatialAnchorHTC, HTC_anchor)  \
    _(GetSpatialAnchorNameHTC, HTC_anchor)

/// For every function defined by XR_MNDX_force_feedback_curl in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_MNDX_force_feedback_curl(_) _(ApplyForceFeedbackCurlMNDX, MNDX_force_feedback_curl)

/// For every function defined by XR_EXT_plane_detection in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_EXT_plane_detection(_)   \
    _(CreatePlaneDetectorEXT, EXT_plane_detection)    \
    _(DestroyPlaneDetectorEXT, EXT_plane_detection)   \
    _(BeginPlaneDetectionEXT, EXT_plane_detection)    \
    _(GetPlaneDetectionStateEXT, EXT_plane_detection) \
    _(GetPlaneDetectionsEXT, EXT_plane_detection)     \
    _(GetPlanePolygonBufferEXT, EXT_plane_detection)

/// For every function defined by XR_EXT_future in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_EXT_future(_) \
    _(PollFutureEXT, EXT_future)           \
    _(CancelFutureEXT, EXT_future)

/// For every function defined by XR_ML_user_calibration in this version of the spec,
/// calls your macro with the function name and extension name.
/// Trims the leading `xr` from the function name and the leading `XR_` from the feature name,
/// because it is easy to add back but impossible to remove with the preprocessor.
#define XR_LIST_FUNCTIONS_XR_ML_user_calibration(_) _(EnableUserCalibrationEventsML, ML_user_calibration)

#endif
