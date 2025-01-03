#pragma once
#ifdef BUILD_OXR
#include <openxr/openxr.h>

#define XRT_MAX_HANDLE_CHILDREN 256
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * Call this, passing a macro taking two parameters, to
 * generate tables, code, etc. related to OpenXR extensions.
 * Upon including invoking OXR_EXTENSION_SUPPORT_GENERATE() with some
 * MY_HANDLE_EXTENSION(mixed_case, all_caps), MY_HANDLE_EXTENSION will be called
 * for each extension implemented in Monado and supported in this build:
 *
 * - The first parameter is the name of the extension without the leading XR_
 *   prefix: e.g. `KHR_opengl_enable`
 * - The second parameter is the same text as the first, but in all uppercase,
 *   since this transform cannot be done in the C preprocessor, and some
 *   extension-related entities use this instead of the exact extension name.
 *
 * Implementation note: This macro calls another macro for each extension: that
 * macro is either defined to call your provided macro, or defined to nothing,
 * depending on if the extension is supported in this build.
 *
 * @note Do not edit anything between `clang-format off` and `clang-format on` -
 * it will be replaced next time this file is generated!
 */

/*!
* A wrapper around a native mutex.
*/
struct os_mutex
{
    pthread_mutex_t mutex;

#ifndef NDEBUG
    bool initialized;
    bool recursive;
#endif
};

/*!
 * Internal enum for the type of space, lets us reason about action spaces.
 *
 * @ingroup oxr_main
 */
enum oxr_space_type
{
    OXR_SPACE_TYPE_REFERENCE_VIEW,
    OXR_SPACE_TYPE_REFERENCE_LOCAL,
    OXR_SPACE_TYPE_REFERENCE_LOCAL_FLOOR,
    OXR_SPACE_TYPE_REFERENCE_STAGE,
    OXR_SPACE_TYPE_REFERENCE_UNBOUNDED_MSFT,
    OXR_SPACE_TYPE_REFERENCE_COMBINED_EYE_VARJO,
    OXR_SPACE_TYPE_REFERENCE_LOCALIZATION_MAP_ML,

    OXR_SPACE_TYPE_ACTION,
    OXR_SPACE_TYPE_XDEV_POSE,
};

static inline bool
oxr_space_type_is_reference(enum oxr_space_type space_type)
{
    switch (space_type) {
        case OXR_SPACE_TYPE_REFERENCE_VIEW:
        case OXR_SPACE_TYPE_REFERENCE_LOCAL:
        case OXR_SPACE_TYPE_REFERENCE_LOCAL_FLOOR:
        case OXR_SPACE_TYPE_REFERENCE_STAGE:
        case OXR_SPACE_TYPE_REFERENCE_UNBOUNDED_MSFT:
        case OXR_SPACE_TYPE_REFERENCE_COMBINED_EYE_VARJO:
        case OXR_SPACE_TYPE_REFERENCE_LOCALIZATION_MAP_ML:
            // These are reference spaces.
            return true;

        case OXR_SPACE_TYPE_ACTION:
        case OXR_SPACE_TYPE_XDEV_POSE:
            // These are not reference spaces.
            return false;
    }

    // Handles invalid value.
    return false;
}

/*!
 * The number of bits reserved for the input type in @ref xrt_input_name
 *
 * @see xrt_input_name
 * @ingroup xrt_iface
 */
#define XRT_INPUT_TYPE_BITWIDTH 8u

/*!
 * @brief Create an enum value for xrt_input_name that packs an ID and input
 * type.
 *
 * @param id an integer
 * @param type The suffix of an xrt_input_type value name: `XRT_INPUT_TYPE_` is
 * prepended automatically.
 *
 * @see xrt_input_name
 * @ingroup xrt_iface
 */
#define XRT_INPUT_NAME(id, type) ((UINT32_C(id) << XRT_INPUT_TYPE_BITWIDTH) | (uint32_t)XRT_INPUT_TYPE_##type)


/*!
 * Base type of this inputs.
 *
 * @ingroup xrt_iface
 */
enum xrt_input_type
{
    // clang-format off
    //! Float input in [0, 1]
    XRT_INPUT_TYPE_VEC1_ZERO_TO_ONE      = 0x00,
    //! Float input in [-1, 1]
    XRT_INPUT_TYPE_VEC1_MINUS_ONE_TO_ONE = 0x01,
    //! Vec2 input, components in [-1, 1]
    XRT_INPUT_TYPE_VEC2_MINUS_ONE_TO_ONE = 0x02,
    //! Vec3 input, components in [-1, 1]
    XRT_INPUT_TYPE_VEC3_MINUS_ONE_TO_ONE = 0x03,
    //! Boolean (digital, binary) input
    XRT_INPUT_TYPE_BOOLEAN               = 0x04,
    //! A tracked pose
    XRT_INPUT_TYPE_POSE                  = 0x05,
    //! A tracked hand
    XRT_INPUT_TYPE_HAND_TRACKING         = 0x06,
    //! A tracked face
    XRT_INPUT_TYPE_FACE_TRACKING         = 0x07,
    //! A tracked body
    XRT_INPUT_TYPE_BODY_TRACKING         = 0x08,
    // clang-format on
};

/*!
 * Every internal input source known to monado with a baked in type.
 *
 * @see xrt_input_type
 * @ingroup xrt_iface
 */
enum xrt_input_name
{
    // clang-format off
    //! Standard pose used for rendering
    XRT_INPUT_GENERIC_HEAD_POSE                       = XRT_INPUT_NAME(0x0000, POSE),
    XRT_INPUT_GENERIC_HEAD_DETECT                     = XRT_INPUT_NAME(0x0001, BOOLEAN),
    XRT_INPUT_GENERIC_HAND_TRACKING_LEFT              = XRT_INPUT_NAME(0x0002, HAND_TRACKING),
    XRT_INPUT_GENERIC_HAND_TRACKING_RIGHT             = XRT_INPUT_NAME(0x0004, HAND_TRACKING),
    XRT_INPUT_GENERIC_TRACKER_POSE                    = XRT_INPUT_NAME(0x0005, POSE),
    XRT_INPUT_GENERIC_STAGE_SPACE_POSE                = XRT_INPUT_NAME(0x0006, POSE),
    XRT_INPUT_GENERIC_LOCAL_SPACE_POSE                = XRT_INPUT_NAME(0x0007, POSE),
    XRT_INPUT_GENERIC_EYE_GAZE_POSE                   = XRT_INPUT_NAME(0x0008, POSE)
    // clang-format on
};


/*!
 * A quaternion with single floats.
 *
 * @ingroup xrt_iface math
 */
struct xrt_quat
{
    float x;
    float y;
    float z;
    float w;
};
/*!
 * A 3 element vector with single floats.
 *
 * @ingroup xrt_iface math
 */
struct xrt_vec3
{
    float x;
    float y;
    float z;
};

/*!
 * A pose composed of a position and orientation.
 *
 * @see xrt_qaut
 * @see xrt_vec3
 * @ingroup xrt_iface math
 */
struct xrt_pose
{
    struct xrt_quat orientation;
    struct xrt_vec3 position;
};

/*!
 * State of a handle base, to reduce likelihood of going "boom" on
 * out-of-order destruction or other unsavory behavior.
 *
 * @ingroup oxr_main
 */
enum oxr_handle_state
{
    /*! State during/before oxr_handle_init, or after failure */
    OXR_HANDLE_STATE_UNINITIALIZED = 0,

    /*! State after successful oxr_handle_init */
    OXR_HANDLE_STATE_LIVE,

    /*! State after successful oxr_handle_destroy */
    OXR_HANDLE_STATE_DESTROYED,
};

/*!
 * Function pointer type for a handle destruction function.
 *
 * @relates oxr_handle_base
 */
typedef XrResult (*oxr_handle_destroyer)(struct oxr_logger *log, struct oxr_handle_base *hb);


/*!
 * Used to hold diverse child handles and ensure orderly destruction.
 *
 * Each object referenced by an OpenXR handle should have one of these as its
 * first element, thus "extending" this class.
 */
struct oxr_handle_base
{
    //! Magic (per-handle-type) value for debugging.
    uint64_t debug;

    /*!
     * Pointer to this object's parent handle holder, if any.
     */
    struct oxr_handle_base *parent;

    /*!
     * Array of children, if any.
     */
    struct oxr_handle_base *children[XRT_MAX_HANDLE_CHILDREN];

    /*!
     * Current handle state.
     */
    enum oxr_handle_state state;

    /*!
     * Destroy the object this handle refers to.
     */
    oxr_handle_destroyer destroy;
};

/*!
 * Expansion macro (x-macro) that calls the macro you pass with the shorthand
 * name of each valid subaction path.
 *
 * Use to generate code that checks each subaction path in sequence, etc.
 *
 * If you also want the bogus subaction path of just plain `/user`, then see
 * OXR_FOR_EACH_SUBACTION_PATH()
 *
 * @note Keep this synchronized with OXR_ACTION_GET_FILLER!
 */
#define OXR_FOR_EACH_VALID_SUBACTION_PATH(_)                                                                           \
	_(left)                                                                                                        \
	_(right)                                                                                                       \
	_(head)                                                                                                        \
	_(gamepad)                                                                                                     \
	_(eyes)

/*!
 * Expansion macro (x-macro) that calls the macro you pass with the shorthand
 * name of each subaction path, including just bare `user`.
 *
 * Use to generate code that checks each subaction path in sequence, etc.
 *
 * @note Keep this synchronized with OXR_ACTION_GET_FILLER!
 */
#define OXR_FOR_EACH_SUBACTION_PATH(_)                                                                                 \
	OXR_FOR_EACH_VALID_SUBACTION_PATH(_)                                                                           \
	_(user)

/*!
 * A parsed equivalent of a list of sub-action paths.
 *
 * If @p any is true, then no paths were provided, which typically means any
 * input is acceptable.
 *
 * @ingroup oxr_main
 * @ingroup oxr_input
 */
struct oxr_subaction_paths
{
    bool any;
#define OXR_SUBPATH_MEMBER(X) bool X;
    OXR_FOR_EACH_SUBACTION_PATH(OXR_SUBPATH_MEMBER)
#undef OXR_SUBPATH_MEMBER
};

/*!
 * Can be one of several reference space types, or a space that is bound to an
 * action.
 *
 * Parent type/handle is @ref oxr_session
 *
 * @obj{XrSpace}
 * @extends oxr_handle_base
 */
struct oxr_space
{
    //! Common structure for things referred to by OpenXR handles.
    struct oxr_handle_base handle;

    //! Owner of this space.
    struct oxr_session *sess;

    //! Pose that was given during creation.
    struct xrt_pose pose;

    //! Action key from which action this space was created from.
    uint32_t act_key;

    //! What kind of space is this?
    enum oxr_space_type space_type;

    //! Which sub action path is this?
    struct oxr_subaction_paths subaction_paths;

    struct
    {
        struct xrt_space *xs;
        struct xrt_device *xdev;
        enum xrt_input_name name;
    } action;

    struct
    {
        struct xrt_space *xs;
    } xdev_pose;
};



/*!
 * A enum that is used to name devices so that the
 * state trackers can reason about the devices easier.
 */
enum xrt_device_name
{
    XRT_DEVICE_INVALID = 0,

    XRT_DEVICE_GENERIC_HMD = 1,

    // Vive stuff.
    XRT_DEVICE_VIVE_PRO,
    XRT_DEVICE_VIVE_WAND,
    XRT_DEVICE_VIVE_TRACKER, // Generic, only used for bindings.
    XRT_DEVICE_VIVE_TRACKER_GEN1,
    XRT_DEVICE_VIVE_TRACKER_GEN2,
    XRT_DEVICE_VIVE_TRACKER_GEN3,
    XRT_DEVICE_VIVE_TRACKER_TUNDRA,

    // "Controllers" somewhat sorted as listed in spec.
    XRT_DEVICE_SIMPLE_CONTROLLER,
    XRT_DEVICE_DAYDREAM,
    XRT_DEVICE_WMR_CONTROLLER,
    XRT_DEVICE_XBOX_CONTROLLER,
    XRT_DEVICE_GO_CONTROLLER,
    XRT_DEVICE_TOUCH_CONTROLLER,
    XRT_DEVICE_INDEX_CONTROLLER,

    XRT_DEVICE_HP_REVERB_G2_CONTROLLER,
    XRT_DEVICE_SAMSUNG_ODYSSEY_CONTROLLER,
    XRT_DEVICE_ML2_CONTROLLER,
    XRT_DEVICE_OPPO_MR_CONTROLLER,

    XRT_DEVICE_HAND_INTERACTION,

    XRT_DEVICE_EYE_GAZE_INTERACTION,

    XRT_DEVICE_PSMV,
    XRT_DEVICE_PSSENSE,
    XRT_DEVICE_HYDRA,

    // Other misc stuff.
    XRT_DEVICE_HAND_TRACKER,
    XRT_DEVICE_REALSENSE,
    XRT_DEVICE_DEPTHAI,

    //! XR_EXT_hand_interaction
    XRT_DEVICE_EXT_HAND_INTERACTION,

    //! XR_HTC_facial_tracking
    XRT_DEVICE_HTC_FACE_TRACKING,

    //! XR_FB_body_tracking
    XRT_DEVICE_FB_BODY_TRACKING,

    //! XR_FB_face_tracking2
    XRT_DEVICE_FB_FACE_TRACKING2,

    // added in OpenXR 1.1
    XRT_DEVICE_PICO_NEO3_CONTROLLER,
    XRT_DEVICE_PICO4_CONTROLLER,
    XRT_DEVICE_PICO_G3_CONTROLLER,

    XRT_DEVICE_VIVE_COSMOS_CONTROLLER,
    XRT_DEVICE_VIVE_FOCUS3_CONTROLLER,

    XRT_DEVICE_TOUCH_PRO_CONTROLLER,
    XRT_DEVICE_TOUCH_PLUS_CONTROLLER,
};

/*!
 * Data associating a device index (in @ref xrt_system_devices::xdevs) with a
 * given "role" for dynamic role switching.
 *
 * For each of the named roles, a negative value means unpopulated/not available.
 *
 * Populated by a call from the @ref xrt_system_devices interface.
 *
 * When the caller of @ref xrt_system_devices_get_roles sees a change (based on
 * comparing @ref generation_id) the caller must do the needed actions to handle
 * device changes. For example, for the OpenXR state tracker this may include
 * rebinding, queuing a change to the current interaction profile, and queuing
 * the events associated with such a change.
 *
 * @see xrt_system_devices
 * @ingroup xrt_iface
 */
struct xrt_system_roles
{
    /*!
     * Monotonically increasing generation counter for the association
     * between role and index.
     *
     * Increment whenever the roles are changed.
     *
     * All valid values are greater then zero; this is to
     * make init easier where any cache can start at zero and be guaranteed
     * to be replaced with a new @ref xrt_system_roles.
     */
    uint64_t generation_id;

    /*!
     * Index in @ref xrt_system_devices::xdevs for the user's left
     * controller/hand, or negative if none available.
     */
    int32_t left;

    /*!
     * Index in @ref xrt_system_devices::xdevs for the user's right
     * controller/hand, or negative if none available.
     */
    int32_t right;

    /*!
     * Index in @ref xrt_system_devices::xdevs for the user's gamepad
     * device, or negative if none available.
     */
    int32_t gamepad;

    enum xrt_device_name left_profile;

    enum xrt_device_name right_profile;

    enum xrt_device_name gamepad_profile;
};


#define MAKE_EXT_STATUS(mixed_case, all_caps) bool mixed_case;
/*!
 * Structure tracking which extensions are enabled for a given instance.
 *
 * Names are systematic: the extension name with the XR_ prefix removed.
 */
struct oxr_extension_status
{
    bool KHR_binding_modification;
    bool KHR_composition_layer_cylinder;
    bool KHR_composition_layer_depth;
    bool KHR_composition_layer_equirect2;
    bool KHR_convert_timespec_time;
    bool KHR_locate_spaces;
    bool KHR_maintenance1;
    bool KHR_opengl_enable;
    bool KHR_opengl_es_enable;
    bool KHR_swapchain_usage_input_attachment_bit;
    bool KHR_visibility_mask;
    bool KHR_vulkan_enable;
    bool KHR_vulkan_enable2;
    bool KHR_vulkan_swapchain_format_list;
    bool EXT_dpad_binding;
    bool EXT_eye_gaze_interaction;
    bool EXT_hand_interaction;
    bool EXT_hand_tracking;
    bool EXT_hp_mixed_reality_controller;
    bool EXT_local_floor;
    bool EXT_samsung_odyssey_controller;
    bool BD_controller_interaction;
    bool FB_display_refresh_rate;
    bool FB_touch_controller_pro;
    bool FB_touch_controller_proximity;
    bool META_touch_controller_plus;
    bool ML_ml2_controller_interaction;
    bool MND_headless;
    bool MND_swapchain_usage_input_attachment_bit;
    bool MSFT_unbounded_reference_space;
    bool OPPO_controller_interaction;
    bool EXTX_overlay;
    bool HTC_vive_cosmos_controller_interaction;
    bool HTC_vive_focus3_controller_interaction;
    bool MNDX_ball_on_a_stick_controller;
    bool MNDX_egl_enable;
    bool MNDX_force_feedback_curl;
    bool MNDX_hydra;
    bool MNDX_system_buttons;
    bool MNDX_xdev_space;
};
#undef MAKE_EXT_STATUS



/*!
 * Single or multiple devices grouped together to form a system that sessions
 * can be created from. Might need to open devices to get all
 * properties from it, but shouldn't.
 *
 * Not strictly an object, but an atom.
 *
 * Valid only within an XrInstance (@ref oxr_instance)
 *
 * @obj{XrSystemId}
 */
struct oxr_system
{
    struct oxr_instance *inst;

    //! The @ref xrt_iface level system.
    struct xrt_system *xsys;

    //! System devices used in all session types.
    struct xrt_system_devices *xsysd;

    //! Space overseer used in all session types.
    struct xrt_space_overseer *xso;

    //! System compositor, used to create session compositors.
    struct xrt_system_compositor *xsysc;

    XrSystemId systemId;

    //! Have the client application called the gfx api requirements func?
    bool gotten_requirements;

    XrFormFactor form_factor;
    XrViewConfigurationType view_config_type;
    XrViewConfigurationView views[2];
    uint32_t blend_mode_count;
    XrEnvironmentBlendMode blend_modes[3];

    XrReferenceSpaceType reference_spaces[5];
    uint32_t reference_space_count;

    //! Cache of the last known system roles, see @ref xrt_system_roles::generation_id
    struct xrt_system_roles dynamic_roles_cache;
    struct os_mutex sync_actions_mutex;

    struct xrt_visibility_mask *visibility_mask[2];

#ifdef OXR_HAVE_MNDX_xdev_space
    bool supports_xdev_space;
#endif

#ifdef XR_USE_GRAPHICS_API_VULKAN
    //! The instance/device we create when vulkan_enable2 is used
	VkInstance vulkan_enable2_instance;
	//! The device returned with the last xrGetVulkanGraphicsDeviceKHR or xrGetVulkanGraphicsDevice2KHR call.
	//! XR_NULL_HANDLE if neither has been called.
	VkPhysicalDevice suggested_vulkan_physical_device;

	struct
	{
		// No better place to keep this state.
		bool external_fence_fd_enabled;
		bool external_semaphore_fd_enabled;
		bool timeline_semaphore_enabled;
		bool debug_utils_enabled;
		bool image_format_list_enabled;
	} vk;

#endif
};

/*!
 * Main object that ties everything together.
 *
 * No parent type/handle: this is the root handle.
 *
 * @obj{XrInstance}
 * @extends oxr_handle_base
 */
struct oxr_instance
{
    //! Common structure for things referred to by OpenXR handles.
    struct oxr_handle_base handle;

    struct u_debug_gui *debug_ui;

    struct xrt_instance *xinst;

    //! Enabled extensions
    struct oxr_extension_status extensions;

    //! The OpenXR version requested in the app info. It determines the instance's OpenXR version.
    struct
    {
        //! Stores only major.minor version. Simplifies comparisons for e.g. "at least OpenXR 1.1".
        XrVersion major_minor;
    } openxr_version;

    // Hardcoded single system.
    struct oxr_system system;

    struct time_state *timekeeping;

    struct
    {
        struct u_hashset *name_store;
        struct u_hashset *loc_store;
    } action_sets;

    //! Path store, for looking up paths.
    struct u_hashset *path_store;
    //! Mapping from ID to path.
    struct oxr_path **path_array;
    //! Total length of path array.
    size_t path_array_length;
    //! Number of paths in the array (0 is always null).
    size_t path_num;

    // Event queue.
    struct
    {
        struct os_mutex mutex;
        struct oxr_event *last;
        struct oxr_event *next;
    } event;

    //! Interaction profile bindings that have been suggested by the client.
    struct oxr_interaction_profile **profiles;
    size_t profile_count;

    struct oxr_session *sessions;

    struct
    {

#define SUBACTION_PATH_MEMBER(X) XrPath X;
        OXR_FOR_EACH_SUBACTION_PATH(SUBACTION_PATH_MEMBER)

#undef SUBACTION_PATH_MEMBER
    } path_cache;

    struct
    {
        struct
        {
            struct
            {
                uint32_t major;
                uint32_t minor;
                uint32_t patch;
                const char *name; //< Engine name, not freed.
            } engine;
        } detected;
    } appinfo;

    struct
    {
        //! Unreal has a bug in the VulkanRHI backend.
        bool disable_vulkan_format_depth_stencil;
        //! Unreal 4 has a bug calling xrEndSession; the function should just exit
        bool skip_end_session;

        /*!
         * Return XR_ERROR_REFERENCE_SPACE_UNSUPPORTED instead of
         * XR_ERROR_VALIDATION_FAILURE in xrCreateReferenceSpace.
         */
        bool no_validation_error_in_create_ref_space;

        //! For applications that rely on views being parallel, notably some OpenVR games with OpenComposite.
        bool parallel_views;
    } quirks;

    //! Debug messengers
    struct oxr_debug_messenger *messengers[XRT_MAX_HANDLE_CHILDREN];

    bool lifecycle_verbose;
    bool debug_views;
    bool debug_spaces;
    bool debug_bindings;

};

static const XrExtensionProperties extension_props = {XR_TYPE_EXTENSION_PROPERTIES, ((void *) 0), "XR_EXT_hand_tracking", 4};


#ifdef __cplusplus
}
#endif

#endif  // BUILD_OXR
