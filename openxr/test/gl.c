// Required headers for OpenGL rendering, as well as for including openxr_platform
#include "GL/glcorearb.h"

#include "gl.h"
#include "func.h"

#define GL_DECL(TYPE, FUNC) TYPE FUNC = NULL;

#define LOAD_GL_FUNC(TYPE, FUNC) FUNC = (TYPE)SDL_GL_GetProcAddress(#FUNC);

#define FOR_EACH_GL_FUNC(_)                                        \
	_(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers)           \
	_(PFNGLDEBUGMESSAGECALLBACKPROC, glDebugMessageCallback)       \
	_(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers)                 \
	_(PFNGLCREATESHADERPROC, glCreateShader)                       \
	_(PFNGLSHADERSOURCEPROC, glShaderSource)                       \
	_(PFNGLCOMPILESHADERPROC, glCompileShader)                     \
	_(PFNGLGETSHADERIVPROC, glGetShaderiv)                         \
	_(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog)               \
	_(PFNGLCREATEPROGRAMPROC, glCreateProgram)                     \
	_(PFNGLATTACHSHADERPROC, glAttachShader)                       \
	_(PFNGLLINKPROGRAMPROC, glLinkProgram)                         \
	_(PFNGLGETPROGRAMIVPROC, glGetProgramiv)                       \
	_(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog)             \
	_(PFNGLDELETESHADERPROC, glDeleteShader)                       \
	_(PFNGLGENBUFFERSPROC, glGenBuffers)                           \
	_(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays)                 \
	_(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray)                 \
	_(PFNGLBINDBUFFERPROC, glBindBuffer)                           \
	_(PFNGLBUFFERDATAPROC, glBufferData)                           \
	_(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer)         \
	_(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray) \
	_(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation)           \
	_(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer)                 \
	_(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D)       \
	_(PFNGLUSEPROGRAMPROC, glUseProgram)                           \
	_(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv)               \
	_(PFNGLBLITNAMEDFRAMEBUFFERPROC, glBlitNamedFramebuffer)       \
	_(PFNGLUNIFORM4FPROC, glUniform4f)                             \
	_(PFNGLACTIVETEXTUREPROC, glActiveTextureARB)                  \
	_(PFNGLUNIFORM1IPROC, glUniform1i)


// HACK: Use the ARB extension version because on windows glActiveTexture is not declared and on
// linux glx.h pulls in system gl.h that declares it.

// creates a global declaration for each gl fun listed in FOR_EACH_GL_FUNC
FOR_EACH_GL_FUNC(GL_DECL)

bool check_opengl_version(XrGraphicsRequirementsOpenGLKHR* opengl_reqs) {
    XrVersion desired_opengl_version = XR_MAKE_VERSION(3, 3, 0);
    if (desired_opengl_version > opengl_reqs->maxApiVersionSupported ||
        desired_opengl_version < opengl_reqs->minApiVersionSupported) {
        printf(
                "We want OpenGL %d.%d.%d, but runtime only supports OpenGL "
                "%d.%d.%d - %d.%d.%d!\n",
                XR_VERSION_MAJOR(desired_opengl_version), XR_VERSION_MINOR(desired_opengl_version),
                XR_VERSION_PATCH(desired_opengl_version),
                XR_VERSION_MAJOR(opengl_reqs->minApiVersionSupported),
                XR_VERSION_MINOR(opengl_reqs->minApiVersionSupported),
                XR_VERSION_PATCH(opengl_reqs->minApiVersionSupported),
                XR_VERSION_MAJOR(opengl_reqs->maxApiVersionSupported),
                XR_VERSION_MINOR(opengl_reqs->maxApiVersionSupported),
                XR_VERSION_PATCH(opengl_reqs->maxApiVersionSupported));
        return false;
    }
    return true;
}

int64_t get_swapchain_format(XrInstance instance,
                             XrSession session,
                             int64_t preferred_format,
                             bool fallback) {
    XrResult result;

    uint32_t swapchain_format_count;
    result = xrEnumerateSwapchainFormats(session, 0, &swapchain_format_count, NULL);
    if (!xr_check(instance, result, "Failed to get number of supported swapchain formats"))
        return -1;

    printf("Runtime supports %d swapchain formats\n", swapchain_format_count);
    int64_t* swapchain_formats = malloc(sizeof(int64_t) * swapchain_format_count);
    result = xrEnumerateSwapchainFormats(session, swapchain_format_count, &swapchain_format_count,
                                         swapchain_formats);
    if (!xr_check(instance, result, "Failed to enumerate swapchain formats"))
        return -1;

    int64_t chosen_format = fallback ? swapchain_formats[0] : -1;

    for (uint32_t i = 0; i < swapchain_format_count; i++) {
        printf("Supported GL format: %#lx\n", swapchain_formats[i]);
        if (swapchain_formats[i] == preferred_format) {
            chosen_format = swapchain_formats[i];
            printf("Using preferred swapchain format %#lx\n", chosen_format);
            break;
        }
    }
    if (fallback && chosen_format != preferred_format) {
        printf("Falling back to non preferred swapchain format %#lx\n", chosen_format);
    }

    free(swapchain_formats);

    return chosen_format;
}

XrResult init_opengl_fp(XrInstance instance,
                        struct base_extension_t* base) {
    struct opengl_t* opengl = (struct opengl_t*)base;
    LOAD_OR_RETURN(xrGetOpenGLGraphicsRequirementsKHR, opengl)
    return XR_SUCCESS;
}
bool init_opengl_t(struct base_extension_t** out_base) {
    *out_base = malloc(sizeof(struct opengl_t));
    (*out_base)->ext_name_string = XR_KHR_OPENGL_ENABLE_EXTENSION_NAME;
    (*out_base)->init_fp = &init_opengl_fp;
    return true;
}

XrResult init_refresh_rate_fp(XrInstance instance,
                              struct base_extension_t* base) {
    struct refresh_rate_t* refresh_rate = (struct refresh_rate_t*)base;
    LOAD_OR_RETURN(xrEnumerateDisplayRefreshRatesFB, refresh_rate)
    LOAD_OR_RETURN(xrGetDisplayRefreshRateFB, refresh_rate)
    LOAD_OR_RETURN(xrRequestDisplayRefreshRateFB, refresh_rate)
    return XR_SUCCESS;
}

bool init_refresh_rate_t(struct base_extension_t** out_base) {
    *out_base = malloc(sizeof(struct refresh_rate_t));

    (*out_base)->ext_name_string = XR_FB_DISPLAY_REFRESH_RATE_EXTENSION_NAME;
    (*out_base)->init_fp = &init_refresh_rate_fp;
    return true;
}


bool create_swapchain(XrInstance instance,
                      XrSession session,
                      struct swapchain_t* swapchain,
                      int num_swapchain,
                      int64_t format,
                      uint32_t sample_count,
                      uint32_t w,
                      uint32_t h,
                      XrSwapchainUsageFlags usage_flags) {
    XrSwapchainCreateInfo swapchain_create_info = {
            .type = XR_TYPE_SWAPCHAIN_CREATE_INFO,
            .usageFlags = usage_flags,
            .createFlags = 0,
            .format = format,
            .sampleCount = sample_count,
            .width = w,
            .height = h,
            .faceCount = 1,
            .arraySize = 1,
            .mipCount = 1,
            .next = NULL,
    };

    XrResult result;

    result =
            xrCreateSwapchain(session, &swapchain_create_info, &swapchain->swapchains[num_swapchain]);
    if (!xr_check(instance, result, "Failed to create swapchain!"))
        return false;

    // The runtime controls how many textures we have to be able to render to
    // (e.g. "triple buffering")
    result = xrEnumerateSwapchainImages(swapchain->swapchains[num_swapchain], 0,
                                        &swapchain->swapchain_lengths[num_swapchain], NULL);
    if (!xr_check(instance, result, "Failed to enumerate swapchains"))
        return false;

    swapchain->images[num_swapchain] =
            malloc(sizeof(XrSwapchainImageOpenGLKHR) * swapchain->swapchain_lengths[num_swapchain]);
    for (uint32_t j = 0; j < swapchain->swapchain_lengths[num_swapchain]; j++) {
        swapchain->images[num_swapchain][j].type = XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR;
        swapchain->images[num_swapchain][j].next = NULL;
    }
    result = xrEnumerateSwapchainImages(
            swapchain->swapchains[num_swapchain], swapchain->swapchain_lengths[num_swapchain],
            &swapchain->swapchain_lengths[num_swapchain],
            (XrSwapchainImageBaseHeader*)swapchain->images[num_swapchain]);
    if (!xr_check(instance, result, "Failed to enumerate swapchain images"))
        return false;

    return true;
}

bool create_one_swapchain(XrInstance instance,
                          XrSession session,
                          struct swapchain_t* swapchain,
                          int64_t format,
                          uint32_t sample_count,
                          uint32_t w,
                          uint32_t h,
                          XrSwapchainUsageFlags usage_flags) {
    swapchain->swapchains = malloc(sizeof(XrSwapchain));
    swapchain->swapchain_lengths = malloc(sizeof(uint32_t));
    swapchain->images = malloc(sizeof(XrSwapchainImageOpenGLKHR*));
    swapchain->swapchain_count = 1;

    return create_swapchain(instance, session, swapchain, 0, format, sample_count, w, h,
                            usage_flags);
}

bool create_swapchain_from_views(XrInstance instance,
                                 XrSession session,
                                 struct swapchain_t* swapchain,
                                 uint32_t view_count,
                                 int64_t format,
                                 XrViewConfigurationView* viewconfig_views,
                                 XrSwapchainUsageFlags usage_flags) {
    swapchain->swapchains = malloc(sizeof(XrSwapchain) * view_count);
    swapchain->swapchain_lengths = malloc(sizeof(uint32_t) * view_count);
    swapchain->images = malloc(sizeof(XrSwapchainImageOpenGLKHR*) * view_count);
    swapchain->swapchain_count = view_count;

    for (uint32_t i = 0; i < view_count; i++) {
        uint32_t sample_count = viewconfig_views[i].recommendedSwapchainSampleCount;
        uint32_t w = viewconfig_views[i].recommendedImageRectWidth;
        uint32_t h = viewconfig_views[i].recommendedImageRectHeight;

        if (!create_swapchain(instance, session, swapchain, (int)i, format, sample_count, w, h,
                              usage_flags))
            return false;
    }

    return true;
}

void destroy_swapchain(struct swapchain_t* swapchain) {
    free(swapchain->swapchains);
    free(swapchain->images);
    free(swapchain->swapchain_lengths);
}

void MessageCallback(GLenum source,
                     GLenum type,
                     GLuint id,
                     GLenum severity,
                     GLsizei length,
                     const GLchar* message,
                     const void* userParam) {
    (void)source;
    (void)id;
    (void)length;
    (void)userParam;
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        return;
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}


bool init_sdl_window(Display** xDisplay,
                     GLXDrawable* glxDrawable,
                     GLXContext* glxContext,
                     int w,
                     int h) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Unable to initialize SDL");
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);


    /* Create our window centered at half the VR resolution */
    desktop_window =
            SDL_CreateWindow("OpenXR Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w / 2,
                             h / 2, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!desktop_window) {
        printf("Unable to create window");
        return false;
    }

    gl_context = SDL_GL_CreateContext(desktop_window);

    FOR_EACH_GL_FUNC(LOAD_GL_FUNC)

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    SDL_GL_SetSwapInterval(0);

    // HACK? OpenXR wants us to report these values, so "work around" SDL a
    // bit and get the underlying glx stuff. Does this still work when e.g.
    // SDL switches to xcb?
    *xDisplay = XOpenDisplay(NULL);
    *glxContext = glXGetCurrentContext();
    *glxDrawable = glXGetCurrentDrawable();
    return true;
}

int init_gl(uint32_t view_count,
            uint32_t* swapchain_lengths,
            struct gl_renderer_t* gl_renderer) {

    /* Allocate resources that we use for our own rendering.
     * We will bind framebuffers to the runtime provided textures for rendering.
     * For this, we create one framebuffer per OpenGL texture.
     * This is not mandated by OpenXR, other ways to render to textures will work too.
     */
    gl_renderer->framebuffers = malloc(sizeof(GLuint*) * view_count);
    for (uint32_t i = 0; i < view_count; i++) {
        gl_renderer->framebuffers[i] = malloc(sizeof(GLuint) * swapchain_lengths[i]);
        glGenFramebuffers((GLsizei)swapchain_lengths[i], gl_renderer->framebuffers[i]);
    }

    gl_renderer->shader_program_id = glCreateProgram();


    GLuint VBOs[1];
    glGenBuffers(1, VBOs);


    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

    glEnable(GL_DEPTH_TEST);

    return 0;
}
