#pragma once

#include "struct.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

bool init_sdl_window(Display** xDisplay, GLXDrawable* glxDrawable, GLXContext* glxContext, int w, int h);

int init_gl(uint32_t view_count, uint32_t* swapchain_lengths, struct gl_renderer_t* gl_renderer);

bool check_opengl_version(XrGraphicsRequirementsOpenGLKHR* opengl_reqs);

// returns the preferred swapchain format if it is supported
// else:
// - if fallback is true, return the first supported format
// - if fallback is false, return -1
int64_t get_swapchain_format(XrInstance instance, XrSession session, int64_t preferred_format, bool fallback);

XrResult init_opengl_fp(XrInstance instance, struct base_extension_t* base);

bool init_opengl_t(struct base_extension_t** out_base);

XrResult init_refresh_rate_fp(XrInstance instance, struct base_extension_t* base);

bool init_refresh_rate_t(struct base_extension_t** out_base);

// --- Create swapchain
bool create_swapchain(XrInstance instance, XrSession session, struct swapchain_t* swapchain, int num_swapchain, int64_t format,
                      uint32_t sample_count, uint32_t w, uint32_t h, XrSwapchainUsageFlags usage_flags);

bool create_one_swapchain(XrInstance instance, XrSession session, struct swapchain_t* swapchain, int64_t format,
                          uint32_t sample_count, uint32_t w, uint32_t h, XrSwapchainUsageFlags usage_flags);

bool create_swapchain_from_views(XrInstance instance, XrSession session, struct swapchain_t* swapchain, uint32_t view_count,
                                 int64_t format, XrViewConfigurationView* viewconfig_views, XrSwapchainUsageFlags usage_flags);

void destroy_swapchain(struct swapchain_t* swapchain);

// =============================================================================
// OpenGL rendering code
// =============================================================================

static SDL_Window*   desktop_window;
static SDL_GLContext gl_context;

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
                     const void* userParam);
