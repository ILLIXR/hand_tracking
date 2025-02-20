#pragma once

#include <stdbool.h>
#include "external/openxr_headers/openxr.h"

#include "struct.h"

bool xr_check(XrInstance instance,
              XrResult result,
              const char* format, ...);

void print_system_properties(XrSystemProperties* system_properties);

void print_supported_view_configs(XrInstance instance,
                                  XrSystemId system_id);

void print_viewconfig_view_info(uint32_t view_count,
                                XrViewConfigurationView* viewconfig_views);

void print_reference_spaces(XrInstance instance,
                            XrSession session);

XrResult init_hand_tracking_fp(XrInstance instance,
                               struct base_extension_t* base);

bool init_hand_tracking_t(struct base_extension_t** out_base);

XrResult init_xdev_space_fp(XrInstance instance,
                            struct base_extension_t* base);

bool init_xdev_space_t(struct base_extension_t** out_base);

struct base_extension_t* get_ext(struct ApplicationState* app,
                                 char* ext_name_string);

bool check_extension_support(struct base_extension_t* e,
                             XrExtensionProperties* extension_props,
                             uint32_t ext_count);

bool alloc_extensions(struct ApplicationState* app);

XrResult check_extensions(struct ApplicationState* app);

XrResult init_extensions(struct ApplicationState* app);

bool create_hand_trackers(XrInstance instance,
                          XrSession session,
                          struct hand_tracking_t* hand_tracking);

bool get_hand_tracking(XrInstance instance,
                       XrSpace space,
                       XrTime time,
                       bool query_joint_velocities,
                       struct hand_tracking_t* hand_tracking,
                       int hand);
