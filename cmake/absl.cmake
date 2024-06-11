# based on absl-Targets.cmake

# Create imported target absl::atomic_hook
add_library(absl::atomic_hook INTERFACE IMPORTED)

set_target_properties(absl::atomic_hook PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers"
)

# Create imported target absl::errno_saver
add_library(absl::errno_saver INTERFACE IMPORTED)

set_target_properties(absl::errno_saver PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::log_severity
add_library(absl::log_severity STATIC IMPORTED)

set_target_properties(absl::log_severity PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers"
)

# Create imported target absl::nullability
add_library(absl::nullability INTERFACE IMPORTED)

set_target_properties(absl::nullability PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers;absl::type_traits"
)

# Create imported target absl::raw_logging_internal
add_library(absl::raw_logging_internal STATIC IMPORTED)

set_target_properties(absl::raw_logging_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::atomic_hook;absl::config;absl::core_headers;absl::errno_saver;absl::log_severity"
)

# Create imported target absl::spinlock_wait
add_library(absl::spinlock_wait STATIC IMPORTED)

set_target_properties(absl::spinlock_wait PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base_internal;absl::core_headers;absl::errno_saver"
)

# Create imported target absl::config
add_library(absl::config INTERFACE IMPORTED)

set_target_properties(absl::config PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
)

# Create imported target absl::dynamic_annotations
add_library(absl::dynamic_annotations INTERFACE IMPORTED)

set_target_properties(absl::dynamic_annotations PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::core_headers
add_library(absl::core_headers INTERFACE IMPORTED)

set_target_properties(absl::core_headers PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::malloc_internal
add_library(absl::malloc_internal STATIC IMPORTED)

set_target_properties(absl::malloc_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::base_internal;absl::config;absl::core_headers;absl::dynamic_annotations;absl::raw_logging_internal;Threads::Threads"
)

# Create imported target absl::base_internal
add_library(absl::base_internal INTERFACE IMPORTED)

set_target_properties(absl::base_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::type_traits"
)

# Create imported target absl::base
add_library(absl::base STATIC IMPORTED)

set_target_properties(absl::base PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::atomic_hook;absl::base_internal;absl::config;absl::core_headers;absl::dynamic_annotations;absl::log_severity;absl::raw_logging_internal;absl::spinlock_wait;absl::type_traits;Threads::Threads;\$<LINK_ONLY:\$<\$<BOOL:/usr/lib/x86_64-linux-gnu/librt.a>:-lrt>>;\$<LINK_ONLY:\$<\$<BOOL:>:-ladvapi32>>"
)

# Create imported target absl::throw_delegate
add_library(absl::throw_delegate STATIC IMPORTED)

set_target_properties(absl::throw_delegate PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::raw_logging_internal"
)

# Create imported target absl::pretty_function
add_library(absl::pretty_function INTERFACE IMPORTED)

set_target_properties(absl::pretty_function PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
)

# Create imported target absl::endian
add_library(absl::endian INTERFACE IMPORTED)

set_target_properties(absl::endian PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::core_headers"
)

# Create imported target absl::scoped_set_env
add_library(absl::scoped_set_env STATIC IMPORTED)

set_target_properties(absl::scoped_set_env PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::raw_logging_internal"
)

# Create imported target absl::strerror
add_library(absl::strerror STATIC IMPORTED)

set_target_properties(absl::strerror PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::errno_saver"
)

# Create imported target absl::fast_type_id
add_library(absl::fast_type_id INTERFACE IMPORTED)

set_target_properties(absl::fast_type_id PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::prefetch
add_library(absl::prefetch INTERFACE IMPORTED)

set_target_properties(absl::prefetch PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers"
)

# Create imported target absl::algorithm
add_library(absl::algorithm INTERFACE IMPORTED)

set_target_properties(absl::algorithm PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::algorithm_container
add_library(absl::algorithm_container INTERFACE IMPORTED)

set_target_properties(absl::algorithm_container PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::algorithm;absl::core_headers;absl::meta"
)

# Create imported target absl::cleanup_internal
add_library(absl::cleanup_internal INTERFACE IMPORTED)

set_target_properties(absl::cleanup_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base_internal;absl::core_headers;absl::utility"
)

# Create imported target absl::cleanup
add_library(absl::cleanup INTERFACE IMPORTED)

set_target_properties(absl::cleanup PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::cleanup_internal;absl::config;absl::core_headers"
)

# Create imported target absl::btree
add_library(absl::btree INTERFACE IMPORTED)

set_target_properties(absl::btree PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::container_common;absl::common_policy_traits;absl::compare;absl::compressed_tuple;absl::container_memory;absl::cord;absl::core_headers;absl::layout;absl::memory;absl::raw_logging_internal;absl::strings;absl::throw_delegate;absl::type_traits;absl::utility"
)

# Create imported target absl::compressed_tuple
add_library(absl::compressed_tuple INTERFACE IMPORTED)

set_target_properties(absl::compressed_tuple PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::utility"
)

# Create imported target absl::fixed_array
add_library(absl::fixed_array INTERFACE IMPORTED)

set_target_properties(absl::fixed_array PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::compressed_tuple;absl::algorithm;absl::config;absl::core_headers;absl::dynamic_annotations;absl::throw_delegate;absl::memory"
)

# Create imported target absl::inlined_vector_internal
add_library(absl::inlined_vector_internal INTERFACE IMPORTED)

set_target_properties(absl::inlined_vector_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::compressed_tuple;absl::core_headers;absl::memory;absl::span;absl::type_traits"
)

# Create imported target absl::inlined_vector
add_library(absl::inlined_vector INTERFACE IMPORTED)

set_target_properties(absl::inlined_vector PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::algorithm;absl::core_headers;absl::inlined_vector_internal;absl::throw_delegate;absl::memory;absl::type_traits"
)

# Create imported target absl::counting_allocator
add_library(absl::counting_allocator INTERFACE IMPORTED)

set_target_properties(absl::counting_allocator PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::flat_hash_map
add_library(absl::flat_hash_map INTERFACE IMPORTED)

set_target_properties(absl::flat_hash_map PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::container_memory;absl::core_headers;absl::hash_function_defaults;absl::raw_hash_map;absl::algorithm_container;absl::memory"
)

# Create imported target absl::flat_hash_set
add_library(absl::flat_hash_set INTERFACE IMPORTED)

set_target_properties(absl::flat_hash_set PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::container_memory;absl::hash_function_defaults;absl::raw_hash_set;absl::algorithm_container;absl::core_headers;absl::memory"
)

# Create imported target absl::node_hash_map
add_library(absl::node_hash_map INTERFACE IMPORTED)

set_target_properties(absl::node_hash_map PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::container_memory;absl::core_headers;absl::hash_function_defaults;absl::node_slot_policy;absl::raw_hash_map;absl::algorithm_container;absl::memory"
)

# Create imported target absl::node_hash_set
add_library(absl::node_hash_set INTERFACE IMPORTED)

set_target_properties(absl::node_hash_set PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers;absl::hash_function_defaults;absl::node_slot_policy;absl::raw_hash_set;absl::algorithm_container;absl::memory"
)

# Create imported target absl::container_memory
add_library(absl::container_memory INTERFACE IMPORTED)

set_target_properties(absl::container_memory PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::memory;absl::type_traits;absl::utility"
)

# Create imported target absl::hash_function_defaults
add_library(absl::hash_function_defaults INTERFACE IMPORTED)

set_target_properties(absl::hash_function_defaults PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::cord;absl::hash;absl::strings"
)

# Create imported target absl::hash_policy_traits
add_library(absl::hash_policy_traits INTERFACE IMPORTED)

set_target_properties(absl::hash_policy_traits PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::common_policy_traits;absl::meta"
)

# Create imported target absl::common_policy_traits
add_library(absl::common_policy_traits INTERFACE IMPORTED)

set_target_properties(absl::common_policy_traits PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::meta"
)

# Create imported target absl::hashtablez_sampler
add_library(absl::hashtablez_sampler STATIC IMPORTED)

set_target_properties(absl::hashtablez_sampler PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::exponential_biased;absl::raw_logging_internal;absl::sample_recorder;absl::synchronization;absl::time"
)

# Create imported target absl::hashtable_debug
add_library(absl::hashtable_debug INTERFACE IMPORTED)

set_target_properties(absl::hashtable_debug PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::hashtable_debug_hooks"
)

# Create imported target absl::hashtable_debug_hooks
add_library(absl::hashtable_debug_hooks INTERFACE IMPORTED)

set_target_properties(absl::hashtable_debug_hooks PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::node_slot_policy
add_library(absl::node_slot_policy INTERFACE IMPORTED)

set_target_properties(absl::node_slot_policy PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::raw_hash_map
add_library(absl::raw_hash_map INTERFACE IMPORTED)

set_target_properties(absl::raw_hash_map PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::container_memory;absl::raw_hash_set;absl::throw_delegate"
)

# Create imported target absl::container_common
add_library(absl::container_common INTERFACE IMPORTED)

set_target_properties(absl::container_common PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::type_traits"
)

# Create imported target absl::raw_hash_set
add_library(absl::raw_hash_set STATIC IMPORTED)

set_target_properties(absl::raw_hash_set PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::bits;absl::compressed_tuple;absl::config;absl::container_common;absl::container_memory;absl::core_headers;absl::dynamic_annotations;absl::endian;absl::hash;absl::hash_policy_traits;absl::hashtable_debug_hooks;absl::hashtablez_sampler;absl::memory;absl::meta;absl::optional;absl::prefetch;absl::raw_logging_internal;absl::utility"
)

# Create imported target absl::layout
add_library(absl::layout INTERFACE IMPORTED)

set_target_properties(absl::layout PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::meta;absl::strings;absl::span;absl::utility"
)

# Create imported target absl::crc_cpu_detect
add_library(absl::crc_cpu_detect STATIC IMPORTED)

set_target_properties(absl::crc_cpu_detect PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config"
)

# Create imported target absl::crc_internal
add_library(absl::crc_internal STATIC IMPORTED)

set_target_properties(absl::crc_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::crc_cpu_detect;absl::base;absl::config;absl::core_headers;absl::dynamic_annotations;absl::endian;absl::prefetch;absl::raw_logging_internal;absl::memory;absl::bits"
)

# Create imported target absl::crc32c
add_library(absl::crc32c STATIC IMPORTED)

set_target_properties(absl::crc32c PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::crc_cpu_detect;absl::crc_internal;absl::non_temporal_memcpy;absl::config;absl::core_headers;absl::dynamic_annotations;absl::endian;absl::prefetch;absl::str_format;absl::strings"
)

# Create imported target absl::non_temporal_arm_intrinsics
add_library(absl::non_temporal_arm_intrinsics INTERFACE IMPORTED)

set_target_properties(absl::non_temporal_arm_intrinsics PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::non_temporal_memcpy
add_library(absl::non_temporal_memcpy INTERFACE IMPORTED)

set_target_properties(absl::non_temporal_memcpy PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::non_temporal_arm_intrinsics;absl::config;absl::core_headers"
)

# Create imported target absl::crc_cord_state
add_library(absl::crc_cord_state STATIC IMPORTED)

set_target_properties(absl::crc_cord_state PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::crc32c;absl::config;absl::strings"
)

# Create imported target absl::stacktrace
add_library(absl::stacktrace STATIC IMPORTED)

set_target_properties(absl::stacktrace PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::debugging_internal;absl::config;absl::core_headers;absl::dynamic_annotations;absl::raw_logging_internal;\$<LINK_ONLY:\$<\$<BOOL:EXECINFO_LIBRARY-NOTFOUND>:EXECINFO_LIBRARY-NOTFOUND>>"
)

# Create imported target absl::symbolize
add_library(absl::symbolize STATIC IMPORTED)

set_target_properties(absl::symbolize PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::debugging_internal;absl::demangle_internal;absl::base;absl::config;absl::core_headers;absl::dynamic_annotations;absl::malloc_internal;absl::raw_logging_internal;absl::strings;\$<LINK_ONLY:\$<\$<BOOL:>:-ldbghelp>>"
)

# Create imported target absl::examine_stack
add_library(absl::examine_stack STATIC IMPORTED)

set_target_properties(absl::examine_stack PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::stacktrace;absl::symbolize;absl::config;absl::core_headers;absl::raw_logging_internal"
)

# Create imported target absl::failure_signal_handler
add_library(absl::failure_signal_handler STATIC IMPORTED)

set_target_properties(absl::failure_signal_handler PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::examine_stack;absl::stacktrace;absl::base;absl::config;absl::core_headers;absl::raw_logging_internal"
)

# Create imported target absl::debugging_internal
add_library(absl::debugging_internal STATIC IMPORTED)

set_target_properties(absl::debugging_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers;absl::config;absl::dynamic_annotations;absl::errno_saver;absl::raw_logging_internal"
)

# Create imported target absl::demangle_internal
add_library(absl::demangle_internal STATIC IMPORTED)

set_target_properties(absl::demangle_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::core_headers"
)

# Create imported target absl::leak_check
add_library(absl::leak_check STATIC IMPORTED)

set_target_properties(absl::leak_check PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers"
)

# Create imported target absl::debugging
add_library(absl::debugging INTERFACE IMPORTED)

set_target_properties(absl::debugging PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::stacktrace;absl::leak_check"
)

# Create imported target absl::flags_path_util
add_library(absl::flags_path_util INTERFACE IMPORTED)

set_target_properties(absl::flags_path_util PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::strings"
)

# Create imported target absl::flags_program_name
add_library(absl::flags_program_name STATIC IMPORTED)

set_target_properties(absl::flags_program_name PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::flags_path_util;absl::strings;absl::synchronization"
)

# Create imported target absl::flags_config
add_library(absl::flags_config STATIC IMPORTED)

set_target_properties(absl::flags_config PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::flags_path_util;absl::flags_program_name;absl::core_headers;absl::strings;absl::synchronization"
)

# Create imported target absl::flags_marshalling
add_library(absl::flags_marshalling STATIC IMPORTED)

set_target_properties(absl::flags_marshalling PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::log_severity;absl::int128;absl::optional;absl::strings;absl::str_format"
)

# Create imported target absl::flags_commandlineflag_internal
add_library(absl::flags_commandlineflag_internal STATIC IMPORTED)

set_target_properties(absl::flags_commandlineflag_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::dynamic_annotations;absl::fast_type_id"
)

# Create imported target absl::flags_commandlineflag
add_library(absl::flags_commandlineflag STATIC IMPORTED)

set_target_properties(absl::flags_commandlineflag PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::fast_type_id;absl::flags_commandlineflag_internal;absl::optional;absl::strings"
)

# Create imported target absl::flags_private_handle_accessor
add_library(absl::flags_private_handle_accessor STATIC IMPORTED)

set_target_properties(absl::flags_private_handle_accessor PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::flags_commandlineflag;absl::flags_commandlineflag_internal;absl::strings"
)

# Create imported target absl::flags_reflection
add_library(absl::flags_reflection STATIC IMPORTED)

set_target_properties(absl::flags_reflection PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::flags_commandlineflag;absl::flags_private_handle_accessor;absl::flags_config;absl::strings;absl::synchronization;absl::flat_hash_map"
)

# Create imported target absl::flags_internal
add_library(absl::flags_internal STATIC IMPORTED)

set_target_properties(absl::flags_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::flags_commandlineflag;absl::flags_commandlineflag_internal;absl::flags_config;absl::flags_marshalling;absl::synchronization;absl::meta;absl::utility"
)

# Create imported target absl::flags
add_library(absl::flags STATIC IMPORTED)

set_target_properties(absl::flags PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::flags_commandlineflag;absl::flags_config;absl::flags_internal;absl::flags_reflection;absl::base;absl::core_headers;absl::strings"
)

# Create imported target absl::flags_usage_internal
add_library(absl::flags_usage_internal STATIC IMPORTED)

set_target_properties(absl::flags_usage_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::flags_config;absl::flags;absl::flags_commandlineflag;absl::flags_internal;absl::flags_path_util;absl::flags_private_handle_accessor;absl::flags_program_name;absl::flags_reflection;absl::flat_hash_map;absl::strings;absl::synchronization"
)

# Create imported target absl::flags_usage
add_library(absl::flags_usage STATIC IMPORTED)

set_target_properties(absl::flags_usage PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::flags_usage_internal;absl::raw_logging_internal;absl::strings;absl::synchronization"
)

# Create imported target absl::flags_parse
add_library(absl::flags_parse STATIC IMPORTED)

set_target_properties(absl::flags_parse PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::algorithm_container;absl::config;absl::core_headers;absl::flags_config;absl::flags;absl::flags_commandlineflag;absl::flags_commandlineflag_internal;absl::flags_internal;absl::flags_private_handle_accessor;absl::flags_program_name;absl::flags_reflection;absl::flags_usage;absl::strings;absl::synchronization"
)

# Create imported target absl::any_invocable
add_library(absl::any_invocable INTERFACE IMPORTED)

set_target_properties(absl::any_invocable PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base_internal;absl::config;absl::core_headers;absl::type_traits;absl::utility"
)

# Create imported target absl::bind_front
add_library(absl::bind_front INTERFACE IMPORTED)

set_target_properties(absl::bind_front PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base_internal;absl::compressed_tuple"
)

# Create imported target absl::function_ref
add_library(absl::function_ref INTERFACE IMPORTED)

set_target_properties(absl::function_ref PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base_internal;absl::core_headers;absl::any_invocable;absl::meta"
)

# Create imported target absl::hash
add_library(absl::hash STATIC IMPORTED)

set_target_properties(absl::hash PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::bits;absl::city;absl::config;absl::core_headers;absl::endian;absl::fixed_array;absl::function_ref;absl::meta;absl::int128;absl::strings;absl::optional;absl::variant;absl::utility;absl::low_level_hash"
)

# Create imported target absl::city
add_library(absl::city STATIC IMPORTED)

set_target_properties(absl::city PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::endian"
)

# Create imported target absl::low_level_hash
add_library(absl::low_level_hash STATIC IMPORTED)

set_target_properties(absl::low_level_hash PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::endian;absl::int128;absl::prefetch"
)

# Create imported target absl::log_internal_check_impl
add_library(absl::log_internal_check_impl INTERFACE IMPORTED)

set_target_properties(absl::log_internal_check_impl PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers;absl::log_internal_check_op;absl::log_internal_conditions;absl::log_internal_message;absl::log_internal_strip"
)

# Create imported target absl::log_internal_check_op
add_library(absl::log_internal_check_op STATIC IMPORTED)

set_target_properties(absl::log_internal_check_op PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::log_internal_nullguard;absl::log_internal_nullstream;absl::log_internal_strip;absl::strings"
)

# Create imported target absl::log_internal_conditions
add_library(absl::log_internal_conditions STATIC IMPORTED)

set_target_properties(absl::log_internal_conditions PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::core_headers;absl::log_internal_voidify"
)

# Create imported target absl::log_internal_config
add_library(absl::log_internal_config INTERFACE IMPORTED)

set_target_properties(absl::log_internal_config PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers"
)

# Create imported target absl::log_internal_flags
add_library(absl::log_internal_flags INTERFACE IMPORTED)

set_target_properties(absl::log_internal_flags PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::flags"
)

# Create imported target absl::log_internal_format
add_library(absl::log_internal_format STATIC IMPORTED)

set_target_properties(absl::log_internal_format PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::log_internal_append_truncated;absl::log_internal_config;absl::log_internal_globals;absl::log_severity;absl::strings;absl::str_format;absl::time;absl::span"
)

# Create imported target absl::log_internal_globals
add_library(absl::log_internal_globals STATIC IMPORTED)

set_target_properties(absl::log_internal_globals PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::log_severity;absl::raw_logging_internal;absl::strings;absl::time"
)

# Create imported target absl::log_internal_log_impl
add_library(absl::log_internal_log_impl INTERFACE IMPORTED)

set_target_properties(absl::log_internal_log_impl PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::log_internal_conditions;absl::log_internal_message;absl::log_internal_strip"
)

# Create imported target absl::log_internal_proto
add_library(absl::log_internal_proto STATIC IMPORTED)

set_target_properties(absl::log_internal_proto PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::core_headers;absl::strings;absl::span"
)

# Create imported target absl::log_internal_message
add_library(absl::log_internal_message STATIC IMPORTED)

set_target_properties(absl::log_internal_message PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::core_headers;absl::errno_saver;absl::inlined_vector;absl::examine_stack;absl::log_internal_append_truncated;absl::log_internal_format;absl::log_internal_globals;absl::log_internal_proto;absl::log_internal_log_sink_set;absl::log_internal_nullguard;absl::log_globals;absl::log_entry;absl::log_severity;absl::log_sink;absl::log_sink_registry;absl::memory;absl::raw_logging_internal;absl::strings;absl::strerror;absl::time;absl::span"
)

# Create imported target absl::log_internal_log_sink_set
add_library(absl::log_internal_log_sink_set STATIC IMPORTED)

set_target_properties(absl::log_internal_log_sink_set PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::cleanup;absl::config;absl::core_headers;absl::log_internal_config;absl::log_internal_globals;absl::log_globals;absl::log_entry;absl::log_severity;absl::log_sink;absl::raw_logging_internal;absl::synchronization;absl::span;absl::strings;\$<LINK_ONLY:\$<\$<BOOL:>:-llog>>"
)

# Create imported target absl::log_internal_nullguard
add_library(absl::log_internal_nullguard STATIC IMPORTED)

set_target_properties(absl::log_internal_nullguard PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers"
)

# Create imported target absl::log_internal_nullstream
add_library(absl::log_internal_nullstream INTERFACE IMPORTED)

set_target_properties(absl::log_internal_nullstream PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::log_severity;absl::strings"
)

# Create imported target absl::log_internal_strip
add_library(absl::log_internal_strip INTERFACE IMPORTED)

set_target_properties(absl::log_internal_strip PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::log_internal_message;absl::log_internal_nullstream;absl::log_severity"
)

# Create imported target absl::log_internal_voidify
add_library(absl::log_internal_voidify INTERFACE IMPORTED)

set_target_properties(absl::log_internal_voidify PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::log_internal_append_truncated
add_library(absl::log_internal_append_truncated INTERFACE IMPORTED)

set_target_properties(absl::log_internal_append_truncated PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::strings;absl::span"
)

# Create imported target absl::absl_check
add_library(absl::absl_check INTERFACE IMPORTED)

set_target_properties(absl::absl_check PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::log_internal_check_impl"
)

# Create imported target absl::absl_log
add_library(absl::absl_log INTERFACE IMPORTED)

set_target_properties(absl::absl_log PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::log_internal_log_impl"
)

# Create imported target absl::check
add_library(absl::check INTERFACE IMPORTED)

set_target_properties(absl::check PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::log_internal_check_impl;absl::core_headers;absl::log_internal_check_op;absl::log_internal_conditions;absl::log_internal_message;absl::log_internal_strip"
)

# Create imported target absl::die_if_null
add_library(absl::die_if_null STATIC IMPORTED)

set_target_properties(absl::die_if_null PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::log;absl::strings"
)

# Create imported target absl::log_flags
add_library(absl::log_flags STATIC IMPORTED)

set_target_properties(absl::log_flags PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::log_globals;absl::log_severity;absl::log_internal_config;absl::log_internal_flags;absl::flags;absl::flags_marshalling;absl::strings"
)

# Create imported target absl::log_globals
add_library(absl::log_globals STATIC IMPORTED)

set_target_properties(absl::log_globals PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::atomic_hook;absl::config;absl::core_headers;absl::hash;absl::log_severity;absl::raw_logging_internal;absl::strings"
)

# Create imported target absl::log_initialize
add_library(absl::log_initialize STATIC IMPORTED)

set_target_properties(absl::log_initialize PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::log_globals;absl::log_internal_globals;absl::time"
)

# Create imported target absl::log
add_library(absl::log INTERFACE IMPORTED)

set_target_properties(absl::log PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::log_internal_log_impl"
)

# Create imported target absl::log_entry
add_library(absl::log_entry STATIC IMPORTED)

set_target_properties(absl::log_entry PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::log_internal_config;absl::log_severity;absl::span;absl::strings;absl::time"
)

# Create imported target absl::log_sink
add_library(absl::log_sink STATIC IMPORTED)

set_target_properties(absl::log_sink PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::log_entry"
)

# Create imported target absl::log_sink_registry
add_library(absl::log_sink_registry INTERFACE IMPORTED)

set_target_properties(absl::log_sink_registry PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::log_sink;absl::log_internal_log_sink_set"
)

# Create imported target absl::log_streamer
add_library(absl::log_streamer INTERFACE IMPORTED)

set_target_properties(absl::log_streamer PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::absl_log;absl::log_severity;absl::optional;absl::strings;absl::strings_internal;absl::utility"
)

# Create imported target absl::log_internal_structured
add_library(absl::log_internal_structured INTERFACE IMPORTED)

set_target_properties(absl::log_internal_structured PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::log_internal_message;absl::strings"
)

# Create imported target absl::log_structured
add_library(absl::log_structured INTERFACE IMPORTED)

set_target_properties(absl::log_structured PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::log_internal_structured;absl::strings"
)

# Create imported target absl::memory
add_library(absl::memory INTERFACE IMPORTED)

set_target_properties(absl::memory PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers;absl::meta"
)

# Create imported target absl::type_traits
add_library(absl::type_traits INTERFACE IMPORTED)

set_target_properties(absl::type_traits PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers"
)

# Create imported target absl::meta
add_library(absl::meta INTERFACE IMPORTED)

set_target_properties(absl::meta PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::type_traits"
)

# Create imported target absl::bits
add_library(absl::bits INTERFACE IMPORTED)

set_target_properties(absl::bits PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers"
)

# Create imported target absl::int128
add_library(absl::int128 STATIC IMPORTED)

set_target_properties(absl::int128 PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::bits"
)

# Create imported target absl::numeric
add_library(absl::numeric INTERFACE IMPORTED)

set_target_properties(absl::numeric PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::int128"
)

# Create imported target absl::numeric_representation
add_library(absl::numeric_representation INTERFACE IMPORTED)

set_target_properties(absl::numeric_representation PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::sample_recorder
add_library(absl::sample_recorder INTERFACE IMPORTED)

set_target_properties(absl::sample_recorder PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::synchronization"
)

# Create imported target absl::exponential_biased
add_library(absl::exponential_biased STATIC IMPORTED)

set_target_properties(absl::exponential_biased PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers"
)

# Create imported target absl::periodic_sampler
add_library(absl::periodic_sampler STATIC IMPORTED)

set_target_properties(absl::periodic_sampler PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers;absl::exponential_biased"
)

# Create imported target absl::random_random
add_library(absl::random_random INTERFACE IMPORTED)

set_target_properties(absl::random_random PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::random_distributions;absl::random_internal_nonsecure_base;absl::random_internal_pcg_engine;absl::random_internal_pool_urbg;absl::random_internal_randen_engine;absl::random_seed_sequences"
)

# Create imported target absl::random_bit_gen_ref
add_library(absl::random_bit_gen_ref INTERFACE IMPORTED)

set_target_properties(absl::random_bit_gen_ref PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers;absl::random_internal_distribution_caller;absl::random_internal_fast_uniform_bits;absl::type_traits"
)

# Create imported target absl::random_internal_mock_helpers
add_library(absl::random_internal_mock_helpers INTERFACE IMPORTED)

set_target_properties(absl::random_internal_mock_helpers PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::fast_type_id;absl::optional"
)

# Create imported target absl::random_distributions
add_library(absl::random_distributions STATIC IMPORTED)

set_target_properties(absl::random_distributions PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base_internal;absl::config;absl::core_headers;absl::random_internal_generate_real;absl::random_internal_distribution_caller;absl::random_internal_fast_uniform_bits;absl::random_internal_fastmath;absl::random_internal_iostream_state_saver;absl::random_internal_traits;absl::random_internal_uniform_helper;absl::random_internal_wide_multiply;absl::strings;absl::type_traits"
)

# Create imported target absl::random_seed_gen_exception
add_library(absl::random_seed_gen_exception STATIC IMPORTED)

set_target_properties(absl::random_seed_gen_exception PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::random_seed_sequences
add_library(absl::random_seed_sequences STATIC IMPORTED)

set_target_properties(absl::random_seed_sequences PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::inlined_vector;absl::random_internal_pool_urbg;absl::random_internal_salted_seed_seq;absl::random_internal_seed_material;absl::random_seed_gen_exception;absl::span"
)

# Create imported target absl::random_internal_traits
add_library(absl::random_internal_traits INTERFACE IMPORTED)

set_target_properties(absl::random_internal_traits PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::random_internal_distribution_caller
add_library(absl::random_internal_distribution_caller INTERFACE IMPORTED)

set_target_properties(absl::random_internal_distribution_caller PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::utility;absl::fast_type_id"
)

# Create imported target absl::random_internal_fast_uniform_bits
add_library(absl::random_internal_fast_uniform_bits INTERFACE IMPORTED)

set_target_properties(absl::random_internal_fast_uniform_bits PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::random_internal_seed_material
add_library(absl::random_internal_seed_material STATIC IMPORTED)

set_target_properties(absl::random_internal_seed_material PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers;absl::optional;absl::random_internal_fast_uniform_bits;absl::raw_logging_internal;absl::span;absl::strings;\$<LINK_ONLY:\$<\$<BOOL:>:-lbcrypt>>"
)

# Create imported target absl::random_internal_pool_urbg
add_library(absl::random_internal_pool_urbg STATIC IMPORTED)

set_target_properties(absl::random_internal_pool_urbg PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::core_headers;absl::endian;absl::random_internal_randen;absl::random_internal_seed_material;absl::random_internal_traits;absl::random_seed_gen_exception;absl::raw_logging_internal;absl::span"
)

# Create imported target absl::random_internal_salted_seed_seq
add_library(absl::random_internal_salted_seed_seq INTERFACE IMPORTED)

set_target_properties(absl::random_internal_salted_seed_seq PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::inlined_vector;absl::optional;absl::span;absl::random_internal_seed_material;absl::type_traits"
)

# Create imported target absl::random_internal_iostream_state_saver
add_library(absl::random_internal_iostream_state_saver INTERFACE IMPORTED)

set_target_properties(absl::random_internal_iostream_state_saver PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::int128;absl::type_traits"
)

# Create imported target absl::random_internal_generate_real
add_library(absl::random_internal_generate_real INTERFACE IMPORTED)

set_target_properties(absl::random_internal_generate_real PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::bits;absl::random_internal_fastmath;absl::random_internal_traits;absl::type_traits"
)

# Create imported target absl::random_internal_wide_multiply
add_library(absl::random_internal_wide_multiply INTERFACE IMPORTED)

set_target_properties(absl::random_internal_wide_multiply PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::bits;absl::config;absl::int128"
)

# Create imported target absl::random_internal_fastmath
add_library(absl::random_internal_fastmath INTERFACE IMPORTED)

set_target_properties(absl::random_internal_fastmath PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::bits"
)

# Create imported target absl::random_internal_nonsecure_base
add_library(absl::random_internal_nonsecure_base INTERFACE IMPORTED)

set_target_properties(absl::random_internal_nonsecure_base PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers;absl::inlined_vector;absl::random_internal_pool_urbg;absl::random_internal_salted_seed_seq;absl::random_internal_seed_material;absl::span;absl::type_traits"
)

# Create imported target absl::random_internal_pcg_engine
add_library(absl::random_internal_pcg_engine INTERFACE IMPORTED)

set_target_properties(absl::random_internal_pcg_engine PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::int128;absl::random_internal_fastmath;absl::random_internal_iostream_state_saver;absl::type_traits"
)

# Create imported target absl::random_internal_randen_engine
add_library(absl::random_internal_randen_engine INTERFACE IMPORTED)

set_target_properties(absl::random_internal_randen_engine PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::endian;absl::random_internal_iostream_state_saver;absl::random_internal_randen;absl::raw_logging_internal;absl::type_traits"
)

# Create imported target absl::random_internal_platform
add_library(absl::random_internal_platform STATIC IMPORTED)

set_target_properties(absl::random_internal_platform PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::random_internal_randen
add_library(absl::random_internal_randen STATIC IMPORTED)

set_target_properties(absl::random_internal_randen PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::random_internal_platform;absl::random_internal_randen_hwaes;absl::random_internal_randen_slow"
)

# Create imported target absl::random_internal_randen_slow
add_library(absl::random_internal_randen_slow STATIC IMPORTED)

set_target_properties(absl::random_internal_randen_slow PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::random_internal_platform;absl::config"
)

# Create imported target absl::random_internal_randen_hwaes
add_library(absl::random_internal_randen_hwaes STATIC IMPORTED)

set_target_properties(absl::random_internal_randen_hwaes PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::random_internal_platform;absl::random_internal_randen_hwaes_impl;absl::config"
)

# Create imported target absl::random_internal_randen_hwaes_impl
add_library(absl::random_internal_randen_hwaes_impl STATIC IMPORTED)

set_target_properties(absl::random_internal_randen_hwaes_impl PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::random_internal_platform;absl::config"
)

# Create imported target absl::random_internal_distribution_test_util
add_library(absl::random_internal_distribution_test_util STATIC IMPORTED)

set_target_properties(absl::random_internal_distribution_test_util PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::raw_logging_internal;absl::strings;absl::str_format;absl::span"
)

# Create imported target absl::random_internal_uniform_helper
add_library(absl::random_internal_uniform_helper INTERFACE IMPORTED)

set_target_properties(absl::random_internal_uniform_helper PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::random_internal_traits;absl::type_traits"
)

# Create imported target absl::status
add_library(absl::status STATIC IMPORTED)

set_target_properties(absl::status PROPERTIES
                      INTERFACE_COMPILE_DEFINITIONS "\$<\$<PLATFORM_ID:AIX>:_LINUX_SOURCE_COMPAT>"
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::atomic_hook;absl::config;absl::cord;absl::core_headers;absl::function_ref;absl::inlined_vector;absl::optional;absl::raw_logging_internal;absl::stacktrace;absl::str_format;absl::strerror;absl::strings;absl::symbolize"
)

# Create imported target absl::statusor
add_library(absl::statusor STATIC IMPORTED)

set_target_properties(absl::statusor PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::status;absl::core_headers;absl::raw_logging_internal;absl::type_traits;absl::strings;absl::utility;absl::variant"
)

# Create imported target absl::string_view
add_library(absl::string_view STATIC IMPORTED)

set_target_properties(absl::string_view PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::core_headers;absl::throw_delegate"
)

# Create imported target absl::strings
add_library(absl::strings STATIC IMPORTED)

set_target_properties(absl::strings PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::string_view;absl::strings_internal;absl::base;absl::bits;absl::config;absl::core_headers;absl::endian;absl::int128;absl::memory;absl::raw_logging_internal;absl::throw_delegate;absl::type_traits"
)

# Create imported target absl::strings_internal
add_library(absl::strings_internal STATIC IMPORTED)

set_target_properties(absl::strings_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::endian;absl::raw_logging_internal;absl::type_traits"
)

# Create imported target absl::str_format
add_library(absl::str_format INTERFACE IMPORTED)

set_target_properties(absl::str_format PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::str_format_internal"
)

# Create imported target absl::str_format_internal
add_library(absl::str_format_internal STATIC IMPORTED)

set_target_properties(absl::str_format_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::bits;absl::strings;absl::config;absl::core_headers;absl::inlined_vector;absl::numeric_representation;absl::type_traits;absl::utility;absl::int128;absl::span"
)

# Create imported target absl::cord_internal
add_library(absl::cord_internal STATIC IMPORTED)

set_target_properties(absl::cord_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base_internal;absl::compressed_tuple;absl::config;absl::container_memory;absl::core_headers;absl::crc_cord_state;absl::endian;absl::inlined_vector;absl::layout;absl::raw_logging_internal;absl::strings;absl::throw_delegate;absl::type_traits"
)

# Create imported target absl::cordz_update_tracker
add_library(absl::cordz_update_tracker INTERFACE IMPORTED)

set_target_properties(absl::cordz_update_tracker PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

# Create imported target absl::cordz_functions
add_library(absl::cordz_functions STATIC IMPORTED)

set_target_properties(absl::cordz_functions PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::exponential_biased;absl::raw_logging_internal"
)

# Create imported target absl::cordz_statistics
add_library(absl::cordz_statistics INTERFACE IMPORTED)

set_target_properties(absl::cordz_statistics PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::core_headers;absl::cordz_update_tracker;absl::synchronization"
)

# Create imported target absl::cordz_handle
add_library(absl::cordz_handle STATIC IMPORTED)

set_target_properties(absl::cordz_handle PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::raw_logging_internal;absl::synchronization"
)

# Create imported target absl::cordz_info
add_library(absl::cordz_info STATIC IMPORTED)

set_target_properties(absl::cordz_info PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::cord_internal;absl::cordz_functions;absl::cordz_handle;absl::cordz_statistics;absl::cordz_update_tracker;absl::core_headers;absl::inlined_vector;absl::span;absl::raw_logging_internal;absl::stacktrace;absl::synchronization;absl::time"
)

# Create imported target absl::cordz_sample_token
add_library(absl::cordz_sample_token STATIC IMPORTED)

set_target_properties(absl::cordz_sample_token PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::cordz_handle;absl::cordz_info"
)

# Create imported target absl::cordz_update_scope
add_library(absl::cordz_update_scope INTERFACE IMPORTED)

set_target_properties(absl::cordz_update_scope PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::cord_internal;absl::cordz_info;absl::cordz_update_tracker;absl::core_headers"
)

# Create imported target absl::cord
add_library(absl::cord STATIC IMPORTED)

set_target_properties(absl::cord PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::cord_internal;absl::cordz_functions;absl::cordz_info;absl::cordz_update_scope;absl::cordz_update_tracker;absl::core_headers;absl::crc_cord_state;absl::endian;absl::fixed_array;absl::function_ref;absl::inlined_vector;absl::optional;absl::raw_logging_internal;absl::span;absl::strings;absl::type_traits"
)

# Create imported target absl::graphcycles_internal
add_library(absl::graphcycles_internal STATIC IMPORTED)

set_target_properties(absl::graphcycles_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::base_internal;absl::config;absl::core_headers;absl::malloc_internal;absl::raw_logging_internal"
)

# Create imported target absl::kernel_timeout_internal
add_library(absl::kernel_timeout_internal STATIC IMPORTED)

set_target_properties(absl::kernel_timeout_internal PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::config;absl::core_headers;absl::raw_logging_internal;absl::time"
)

# Create imported target absl::synchronization
add_library(absl::synchronization STATIC IMPORTED)

set_target_properties(absl::synchronization PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::graphcycles_internal;absl::kernel_timeout_internal;absl::atomic_hook;absl::base;absl::base_internal;absl::config;absl::core_headers;absl::dynamic_annotations;absl::malloc_internal;absl::raw_logging_internal;absl::stacktrace;absl::symbolize;absl::time;Threads::Threads"
)

# Create imported target absl::time
add_library(absl::time STATIC IMPORTED)

set_target_properties(absl::time PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base;absl::civil_time;absl::core_headers;absl::int128;absl::raw_logging_internal;absl::strings;absl::time_zone"
)

# Create imported target absl::civil_time
add_library(absl::civil_time STATIC IMPORTED)

set_target_properties(absl::civil_time PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
)

# Create imported target absl::time_zone
add_library(absl::time_zone STATIC IMPORTED)

set_target_properties(absl::time_zone PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "Threads::Threads;\$<\$<PLATFORM_ID:Darwin>:-Wl,-framework,CoreFoundation>"
)

# Create imported target absl::any
add_library(absl::any INTERFACE IMPORTED)

set_target_properties(absl::any PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::bad_any_cast;absl::config;absl::core_headers;absl::fast_type_id;absl::type_traits;absl::utility"
)

# Create imported target absl::bad_any_cast
add_library(absl::bad_any_cast INTERFACE IMPORTED)

set_target_properties(absl::bad_any_cast PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::bad_any_cast_impl;absl::config"
)

# Create imported target absl::bad_any_cast_impl
add_library(absl::bad_any_cast_impl STATIC IMPORTED)

set_target_properties(absl::bad_any_cast_impl PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::raw_logging_internal"
)

# Create imported target absl::span
add_library(absl::span INTERFACE IMPORTED)

set_target_properties(absl::span PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::algorithm;absl::core_headers;absl::throw_delegate;absl::type_traits"
)

# Create imported target absl::optional
add_library(absl::optional INTERFACE IMPORTED)

set_target_properties(absl::optional PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::bad_optional_access;absl::base_internal;absl::config;absl::core_headers;absl::memory;absl::type_traits;absl::utility"
)

# Create imported target absl::bad_optional_access
add_library(absl::bad_optional_access STATIC IMPORTED)

set_target_properties(absl::bad_optional_access PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::raw_logging_internal"
)

# Create imported target absl::bad_variant_access
add_library(absl::bad_variant_access STATIC IMPORTED)

set_target_properties(absl::bad_variant_access PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config;absl::raw_logging_internal"
)

# Create imported target absl::variant
add_library(absl::variant INTERFACE IMPORTED)

set_target_properties(absl::variant PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::bad_variant_access;absl::base_internal;absl::config;absl::core_headers;absl::type_traits;absl::utility"
)

# Create imported target absl::compare
add_library(absl::compare INTERFACE IMPORTED)

set_target_properties(absl::compare PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::core_headers;absl::type_traits"
)

# Create imported target absl::utility
add_library(absl::utility INTERFACE IMPORTED)

set_target_properties(absl::utility PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::base_internal;absl::config;absl::type_traits"
)

# Create imported target absl::if_constexpr
add_library(absl::if_constexpr INTERFACE IMPORTED)

set_target_properties(absl::if_constexpr PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "absl::config"
)

#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "absl::log_severity" for configuration "Release"
set_property(TARGET absl::log_severity APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_severity PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_severity.a"
)

list(APPEND _cmake_import_check_targets absl::log_severity )
list(APPEND _cmake_import_check_files_for_absl::log_severity "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_severity.a" )

# Import target "absl::raw_logging_internal" for configuration "Release"
set_property(TARGET absl::raw_logging_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::raw_logging_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_raw_logging_internal.a"
)

list(APPEND _cmake_import_check_targets absl::raw_logging_internal )
list(APPEND _cmake_import_check_files_for_absl::raw_logging_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_raw_logging_internal.a" )

# Import target "absl::spinlock_wait" for configuration "Release"
set_property(TARGET absl::spinlock_wait APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::spinlock_wait PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_spinlock_wait.a"
)

list(APPEND _cmake_import_check_targets absl::spinlock_wait )
list(APPEND _cmake_import_check_files_for_absl::spinlock_wait "${CMAKE_INSTALL_PREFIX}/lib/libabsl_spinlock_wait.a" )

# Import target "absl::malloc_internal" for configuration "Release"
set_property(TARGET absl::malloc_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::malloc_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_malloc_internal.a"
)

list(APPEND _cmake_import_check_targets absl::malloc_internal )
list(APPEND _cmake_import_check_files_for_absl::malloc_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_malloc_internal.a" )

# Import target "absl::base" for configuration "Release"
set_property(TARGET absl::base APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::base PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_base.a"
)

list(APPEND _cmake_import_check_targets absl::base )
list(APPEND _cmake_import_check_files_for_absl::base "${CMAKE_INSTALL_PREFIX}/lib/libabsl_base.a" )

# Import target "absl::throw_delegate" for configuration "Release"
set_property(TARGET absl::throw_delegate APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::throw_delegate PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_throw_delegate.a"
)

list(APPEND _cmake_import_check_targets absl::throw_delegate )
list(APPEND _cmake_import_check_files_for_absl::throw_delegate "${CMAKE_INSTALL_PREFIX}/lib/libabsl_throw_delegate.a" )

# Import target "absl::scoped_set_env" for configuration "Release"
set_property(TARGET absl::scoped_set_env APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::scoped_set_env PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_scoped_set_env.a"
)

list(APPEND _cmake_import_check_targets absl::scoped_set_env )
list(APPEND _cmake_import_check_files_for_absl::scoped_set_env "${CMAKE_INSTALL_PREFIX}/lib/libabsl_scoped_set_env.a" )

# Import target "absl::strerror" for configuration "Release"
set_property(TARGET absl::strerror APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::strerror PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_strerror.a"
)

list(APPEND _cmake_import_check_targets absl::strerror )
list(APPEND _cmake_import_check_files_for_absl::strerror "${CMAKE_INSTALL_PREFIX}/lib/libabsl_strerror.a" )

# Import target "absl::hashtablez_sampler" for configuration "Release"
set_property(TARGET absl::hashtablez_sampler APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::hashtablez_sampler PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_hashtablez_sampler.a"
)

list(APPEND _cmake_import_check_targets absl::hashtablez_sampler )
list(APPEND _cmake_import_check_files_for_absl::hashtablez_sampler "${CMAKE_INSTALL_PREFIX}/lib/libabsl_hashtablez_sampler.a" )

# Import target "absl::raw_hash_set" for configuration "Release"
set_property(TARGET absl::raw_hash_set APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::raw_hash_set PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_raw_hash_set.a"
)

list(APPEND _cmake_import_check_targets absl::raw_hash_set )
list(APPEND _cmake_import_check_files_for_absl::raw_hash_set "${CMAKE_INSTALL_PREFIX}/lib/libabsl_raw_hash_set.a" )

# Import target "absl::crc_cpu_detect" for configuration "Release"
set_property(TARGET absl::crc_cpu_detect APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::crc_cpu_detect PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_crc_cpu_detect.a"
)

list(APPEND _cmake_import_check_targets absl::crc_cpu_detect )
list(APPEND _cmake_import_check_files_for_absl::crc_cpu_detect "${CMAKE_INSTALL_PREFIX}/lib/libabsl_crc_cpu_detect.a" )

# Import target "absl::crc_internal" for configuration "Release"
set_property(TARGET absl::crc_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::crc_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_crc_internal.a"
)

list(APPEND _cmake_import_check_targets absl::crc_internal )
list(APPEND _cmake_import_check_files_for_absl::crc_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_crc_internal.a" )

# Import target "absl::crc32c" for configuration "Release"
set_property(TARGET absl::crc32c APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::crc32c PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_crc32c.a"
)

list(APPEND _cmake_import_check_targets absl::crc32c )
list(APPEND _cmake_import_check_files_for_absl::crc32c "${CMAKE_INSTALL_PREFIX}/lib/libabsl_crc32c.a" )

# Import target "absl::crc_cord_state" for configuration "Release"
set_property(TARGET absl::crc_cord_state APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::crc_cord_state PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_crc_cord_state.a"
)

list(APPEND _cmake_import_check_targets absl::crc_cord_state )
list(APPEND _cmake_import_check_files_for_absl::crc_cord_state "${CMAKE_INSTALL_PREFIX}/lib/libabsl_crc_cord_state.a" )

# Import target "absl::stacktrace" for configuration "Release"
set_property(TARGET absl::stacktrace APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::stacktrace PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_stacktrace.a"
)

list(APPEND _cmake_import_check_targets absl::stacktrace )
list(APPEND _cmake_import_check_files_for_absl::stacktrace "${CMAKE_INSTALL_PREFIX}/lib/libabsl_stacktrace.a" )

# Import target "absl::symbolize" for configuration "Release"
set_property(TARGET absl::symbolize APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::symbolize PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_symbolize.a"
)

list(APPEND _cmake_import_check_targets absl::symbolize )
list(APPEND _cmake_import_check_files_for_absl::symbolize "${CMAKE_INSTALL_PREFIX}/lib/libabsl_symbolize.a" )

# Import target "absl::examine_stack" for configuration "Release"
set_property(TARGET absl::examine_stack APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::examine_stack PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_examine_stack.a"
)

list(APPEND _cmake_import_check_targets absl::examine_stack )
list(APPEND _cmake_import_check_files_for_absl::examine_stack "${CMAKE_INSTALL_PREFIX}/lib/libabsl_examine_stack.a" )

# Import target "absl::failure_signal_handler" for configuration "Release"
set_property(TARGET absl::failure_signal_handler APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::failure_signal_handler PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_failure_signal_handler.a"
)

list(APPEND _cmake_import_check_targets absl::failure_signal_handler )
list(APPEND _cmake_import_check_files_for_absl::failure_signal_handler "${CMAKE_INSTALL_PREFIX}/lib/libabsl_failure_signal_handler.a" )

# Import target "absl::debugging_internal" for configuration "Release"
set_property(TARGET absl::debugging_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::debugging_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_debugging_internal.a"
)

list(APPEND _cmake_import_check_targets absl::debugging_internal )
list(APPEND _cmake_import_check_files_for_absl::debugging_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_debugging_internal.a" )

# Import target "absl::demangle_internal" for configuration "Release"
set_property(TARGET absl::demangle_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::demangle_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_demangle_internal.a"
)

list(APPEND _cmake_import_check_targets absl::demangle_internal )
list(APPEND _cmake_import_check_files_for_absl::demangle_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_demangle_internal.a" )

# Import target "absl::leak_check" for configuration "Release"
set_property(TARGET absl::leak_check APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::leak_check PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_leak_check.a"
)

list(APPEND _cmake_import_check_targets absl::leak_check )
list(APPEND _cmake_import_check_files_for_absl::leak_check "${CMAKE_INSTALL_PREFIX}/lib/libabsl_leak_check.a" )

# Import target "absl::flags_program_name" for configuration "Release"
set_property(TARGET absl::flags_program_name APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags_program_name PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_program_name.a"
)

list(APPEND _cmake_import_check_targets absl::flags_program_name )
list(APPEND _cmake_import_check_files_for_absl::flags_program_name "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_program_name.a" )

# Import target "absl::flags_config" for configuration "Release"
set_property(TARGET absl::flags_config APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags_config PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_config.a"
)

list(APPEND _cmake_import_check_targets absl::flags_config )
list(APPEND _cmake_import_check_files_for_absl::flags_config "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_config.a" )

# Import target "absl::flags_marshalling" for configuration "Release"
set_property(TARGET absl::flags_marshalling APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags_marshalling PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_marshalling.a"
)

list(APPEND _cmake_import_check_targets absl::flags_marshalling )
list(APPEND _cmake_import_check_files_for_absl::flags_marshalling "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_marshalling.a" )

# Import target "absl::flags_commandlineflag_internal" for configuration "Release"
set_property(TARGET absl::flags_commandlineflag_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags_commandlineflag_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_commandlineflag_internal.a"
)

list(APPEND _cmake_import_check_targets absl::flags_commandlineflag_internal )
list(APPEND _cmake_import_check_files_for_absl::flags_commandlineflag_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_commandlineflag_internal.a" )

# Import target "absl::flags_commandlineflag" for configuration "Release"
set_property(TARGET absl::flags_commandlineflag APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags_commandlineflag PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_commandlineflag.a"
)

list(APPEND _cmake_import_check_targets absl::flags_commandlineflag )
list(APPEND _cmake_import_check_files_for_absl::flags_commandlineflag "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_commandlineflag.a" )

# Import target "absl::flags_private_handle_accessor" for configuration "Release"
set_property(TARGET absl::flags_private_handle_accessor APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags_private_handle_accessor PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_private_handle_accessor.a"
)

list(APPEND _cmake_import_check_targets absl::flags_private_handle_accessor )
list(APPEND _cmake_import_check_files_for_absl::flags_private_handle_accessor "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_private_handle_accessor.a" )

# Import target "absl::flags_reflection" for configuration "Release"
set_property(TARGET absl::flags_reflection APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags_reflection PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_reflection.a"
)

list(APPEND _cmake_import_check_targets absl::flags_reflection )
list(APPEND _cmake_import_check_files_for_absl::flags_reflection "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_reflection.a" )

# Import target "absl::flags_internal" for configuration "Release"
set_property(TARGET absl::flags_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_internal.a"
)

list(APPEND _cmake_import_check_targets absl::flags_internal )
list(APPEND _cmake_import_check_files_for_absl::flags_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_internal.a" )

# Import target "absl::flags" for configuration "Release"
set_property(TARGET absl::flags APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags.a"
)

list(APPEND _cmake_import_check_targets absl::flags )
list(APPEND _cmake_import_check_files_for_absl::flags "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags.a" )

# Import target "absl::flags_usage_internal" for configuration "Release"
set_property(TARGET absl::flags_usage_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags_usage_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_usage_internal.a"
)

list(APPEND _cmake_import_check_targets absl::flags_usage_internal )
list(APPEND _cmake_import_check_files_for_absl::flags_usage_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_usage_internal.a" )

# Import target "absl::flags_usage" for configuration "Release"
set_property(TARGET absl::flags_usage APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags_usage PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_usage.a"
)

list(APPEND _cmake_import_check_targets absl::flags_usage )
list(APPEND _cmake_import_check_files_for_absl::flags_usage "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_usage.a" )

# Import target "absl::flags_parse" for configuration "Release"
set_property(TARGET absl::flags_parse APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::flags_parse PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_parse.a"
)

list(APPEND _cmake_import_check_targets absl::flags_parse )
list(APPEND _cmake_import_check_files_for_absl::flags_parse "${CMAKE_INSTALL_PREFIX}/lib/libabsl_flags_parse.a" )

# Import target "absl::hash" for configuration "Release"
set_property(TARGET absl::hash APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::hash PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_hash.a"
)

list(APPEND _cmake_import_check_targets absl::hash )
list(APPEND _cmake_import_check_files_for_absl::hash "${CMAKE_INSTALL_PREFIX}/lib/libabsl_hash.a" )

# Import target "absl::city" for configuration "Release"
set_property(TARGET absl::city APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::city PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_city.a"
)

list(APPEND _cmake_import_check_targets absl::city )
list(APPEND _cmake_import_check_files_for_absl::city "${CMAKE_INSTALL_PREFIX}/lib/libabsl_city.a" )

# Import target "absl::low_level_hash" for configuration "Release"
set_property(TARGET absl::low_level_hash APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::low_level_hash PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_low_level_hash.a"
)

list(APPEND _cmake_import_check_targets absl::low_level_hash )
list(APPEND _cmake_import_check_files_for_absl::low_level_hash "${CMAKE_INSTALL_PREFIX}/lib/libabsl_low_level_hash.a" )

# Import target "absl::log_internal_check_op" for configuration "Release"
set_property(TARGET absl::log_internal_check_op APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_internal_check_op PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_check_op.a"
)

list(APPEND _cmake_import_check_targets absl::log_internal_check_op )
list(APPEND _cmake_import_check_files_for_absl::log_internal_check_op "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_check_op.a" )

# Import target "absl::log_internal_conditions" for configuration "Release"
set_property(TARGET absl::log_internal_conditions APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_internal_conditions PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_conditions.a"
)

list(APPEND _cmake_import_check_targets absl::log_internal_conditions )
list(APPEND _cmake_import_check_files_for_absl::log_internal_conditions "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_conditions.a" )

# Import target "absl::log_internal_format" for configuration "Release"
set_property(TARGET absl::log_internal_format APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_internal_format PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_format.a"
)

list(APPEND _cmake_import_check_targets absl::log_internal_format )
list(APPEND _cmake_import_check_files_for_absl::log_internal_format "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_format.a" )

# Import target "absl::log_internal_globals" for configuration "Release"
set_property(TARGET absl::log_internal_globals APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_internal_globals PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_globals.a"
)

list(APPEND _cmake_import_check_targets absl::log_internal_globals )
list(APPEND _cmake_import_check_files_for_absl::log_internal_globals "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_globals.a" )

# Import target "absl::log_internal_proto" for configuration "Release"
set_property(TARGET absl::log_internal_proto APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_internal_proto PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_proto.a"
)

list(APPEND _cmake_import_check_targets absl::log_internal_proto )
list(APPEND _cmake_import_check_files_for_absl::log_internal_proto "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_proto.a" )

# Import target "absl::log_internal_message" for configuration "Release"
set_property(TARGET absl::log_internal_message APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_internal_message PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_message.a"
)

list(APPEND _cmake_import_check_targets absl::log_internal_message )
list(APPEND _cmake_import_check_files_for_absl::log_internal_message "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_message.a" )

# Import target "absl::log_internal_log_sink_set" for configuration "Release"
set_property(TARGET absl::log_internal_log_sink_set APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_internal_log_sink_set PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_log_sink_set.a"
)

list(APPEND _cmake_import_check_targets absl::log_internal_log_sink_set )
list(APPEND _cmake_import_check_files_for_absl::log_internal_log_sink_set "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_log_sink_set.a" )

# Import target "absl::log_internal_nullguard" for configuration "Release"
set_property(TARGET absl::log_internal_nullguard APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_internal_nullguard PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_nullguard.a"
)

list(APPEND _cmake_import_check_targets absl::log_internal_nullguard )
list(APPEND _cmake_import_check_files_for_absl::log_internal_nullguard "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_internal_nullguard.a" )

# Import target "absl::die_if_null" for configuration "Release"
set_property(TARGET absl::die_if_null APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::die_if_null PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_die_if_null.a"
)

list(APPEND _cmake_import_check_targets absl::die_if_null )
list(APPEND _cmake_import_check_files_for_absl::die_if_null "${CMAKE_INSTALL_PREFIX}/lib/libabsl_die_if_null.a" )

# Import target "absl::log_flags" for configuration "Release"
set_property(TARGET absl::log_flags APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_flags PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_flags.a"
)

list(APPEND _cmake_import_check_targets absl::log_flags )
list(APPEND _cmake_import_check_files_for_absl::log_flags "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_flags.a" )

# Import target "absl::log_globals" for configuration "Release"
set_property(TARGET absl::log_globals APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_globals PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_globals.a"
)

list(APPEND _cmake_import_check_targets absl::log_globals )
list(APPEND _cmake_import_check_files_for_absl::log_globals "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_globals.a" )

# Import target "absl::log_initialize" for configuration "Release"
set_property(TARGET absl::log_initialize APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_initialize PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_initialize.a"
)

list(APPEND _cmake_import_check_targets absl::log_initialize )
list(APPEND _cmake_import_check_files_for_absl::log_initialize "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_initialize.a" )

# Import target "absl::log_entry" for configuration "Release"
set_property(TARGET absl::log_entry APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_entry PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_entry.a"
)

list(APPEND _cmake_import_check_targets absl::log_entry )
list(APPEND _cmake_import_check_files_for_absl::log_entry "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_entry.a" )

# Import target "absl::log_sink" for configuration "Release"
set_property(TARGET absl::log_sink APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::log_sink PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_sink.a"
)

list(APPEND _cmake_import_check_targets absl::log_sink )
list(APPEND _cmake_import_check_files_for_absl::log_sink "${CMAKE_INSTALL_PREFIX}/lib/libabsl_log_sink.a" )

# Import target "absl::int128" for configuration "Release"
set_property(TARGET absl::int128 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::int128 PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_int128.a"
)

list(APPEND _cmake_import_check_targets absl::int128 )
list(APPEND _cmake_import_check_files_for_absl::int128 "${CMAKE_INSTALL_PREFIX}/lib/libabsl_int128.a" )

# Import target "absl::exponential_biased" for configuration "Release"
set_property(TARGET absl::exponential_biased APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::exponential_biased PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_exponential_biased.a"
)

list(APPEND _cmake_import_check_targets absl::exponential_biased )
list(APPEND _cmake_import_check_files_for_absl::exponential_biased "${CMAKE_INSTALL_PREFIX}/lib/libabsl_exponential_biased.a" )

# Import target "absl::periodic_sampler" for configuration "Release"
set_property(TARGET absl::periodic_sampler APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::periodic_sampler PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_periodic_sampler.a"
)

list(APPEND _cmake_import_check_targets absl::periodic_sampler )
list(APPEND _cmake_import_check_files_for_absl::periodic_sampler "${CMAKE_INSTALL_PREFIX}/lib/libabsl_periodic_sampler.a" )

# Import target "absl::random_distributions" for configuration "Release"
set_property(TARGET absl::random_distributions APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::random_distributions PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_distributions.a"
)

list(APPEND _cmake_import_check_targets absl::random_distributions )
list(APPEND _cmake_import_check_files_for_absl::random_distributions "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_distributions.a" )

# Import target "absl::random_seed_gen_exception" for configuration "Release"
set_property(TARGET absl::random_seed_gen_exception APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::random_seed_gen_exception PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_seed_gen_exception.a"
)

list(APPEND _cmake_import_check_targets absl::random_seed_gen_exception )
list(APPEND _cmake_import_check_files_for_absl::random_seed_gen_exception "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_seed_gen_exception.a" )

# Import target "absl::random_seed_sequences" for configuration "Release"
set_property(TARGET absl::random_seed_sequences APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::random_seed_sequences PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_seed_sequences.a"
)

list(APPEND _cmake_import_check_targets absl::random_seed_sequences )
list(APPEND _cmake_import_check_files_for_absl::random_seed_sequences "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_seed_sequences.a" )

# Import target "absl::random_internal_seed_material" for configuration "Release"
set_property(TARGET absl::random_internal_seed_material APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::random_internal_seed_material PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_seed_material.a"
)

list(APPEND _cmake_import_check_targets absl::random_internal_seed_material )
list(APPEND _cmake_import_check_files_for_absl::random_internal_seed_material "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_seed_material.a" )

# Import target "absl::random_internal_pool_urbg" for configuration "Release"
set_property(TARGET absl::random_internal_pool_urbg APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::random_internal_pool_urbg PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_pool_urbg.a"
)

list(APPEND _cmake_import_check_targets absl::random_internal_pool_urbg )
list(APPEND _cmake_import_check_files_for_absl::random_internal_pool_urbg "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_pool_urbg.a" )

# Import target "absl::random_internal_platform" for configuration "Release"
set_property(TARGET absl::random_internal_platform APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::random_internal_platform PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_platform.a"
)

list(APPEND _cmake_import_check_targets absl::random_internal_platform )
list(APPEND _cmake_import_check_files_for_absl::random_internal_platform "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_platform.a" )

# Import target "absl::random_internal_randen" for configuration "Release"
set_property(TARGET absl::random_internal_randen APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::random_internal_randen PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_randen.a"
)

list(APPEND _cmake_import_check_targets absl::random_internal_randen )
list(APPEND _cmake_import_check_files_for_absl::random_internal_randen "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_randen.a" )

# Import target "absl::random_internal_randen_slow" for configuration "Release"
set_property(TARGET absl::random_internal_randen_slow APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::random_internal_randen_slow PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_randen_slow.a"
)

list(APPEND _cmake_import_check_targets absl::random_internal_randen_slow )
list(APPEND _cmake_import_check_files_for_absl::random_internal_randen_slow "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_randen_slow.a" )

# Import target "absl::random_internal_randen_hwaes" for configuration "Release"
set_property(TARGET absl::random_internal_randen_hwaes APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::random_internal_randen_hwaes PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_randen_hwaes.a"
)

list(APPEND _cmake_import_check_targets absl::random_internal_randen_hwaes )
list(APPEND _cmake_import_check_files_for_absl::random_internal_randen_hwaes "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_randen_hwaes.a" )

# Import target "absl::random_internal_randen_hwaes_impl" for configuration "Release"
set_property(TARGET absl::random_internal_randen_hwaes_impl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::random_internal_randen_hwaes_impl PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_randen_hwaes_impl.a"
)

list(APPEND _cmake_import_check_targets absl::random_internal_randen_hwaes_impl )
list(APPEND _cmake_import_check_files_for_absl::random_internal_randen_hwaes_impl "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_randen_hwaes_impl.a" )

# Import target "absl::random_internal_distribution_test_util" for configuration "Release"
set_property(TARGET absl::random_internal_distribution_test_util APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::random_internal_distribution_test_util PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_distribution_test_util.a"
)

list(APPEND _cmake_import_check_targets absl::random_internal_distribution_test_util )
list(APPEND _cmake_import_check_files_for_absl::random_internal_distribution_test_util "${CMAKE_INSTALL_PREFIX}/lib/libabsl_random_internal_distribution_test_util.a" )

# Import target "absl::status" for configuration "Release"
set_property(TARGET absl::status APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::status PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_status.a"
)

list(APPEND _cmake_import_check_targets absl::status )
list(APPEND _cmake_import_check_files_for_absl::status "${CMAKE_INSTALL_PREFIX}/lib/libabsl_status.a" )

# Import target "absl::statusor" for configuration "Release"
set_property(TARGET absl::statusor APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::statusor PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_statusor.a"
)

list(APPEND _cmake_import_check_targets absl::statusor )
list(APPEND _cmake_import_check_files_for_absl::statusor "${CMAKE_INSTALL_PREFIX}/lib/libabsl_statusor.a" )

# Import target "absl::string_view" for configuration "Release"
set_property(TARGET absl::string_view APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::string_view PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_string_view.a"
)

list(APPEND _cmake_import_check_targets absl::string_view )
list(APPEND _cmake_import_check_files_for_absl::string_view "${CMAKE_INSTALL_PREFIX}/lib/libabsl_string_view.a" )

# Import target "absl::strings" for configuration "Release"
set_property(TARGET absl::strings APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::strings PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_strings.a"
)

list(APPEND _cmake_import_check_targets absl::strings )
list(APPEND _cmake_import_check_files_for_absl::strings "${CMAKE_INSTALL_PREFIX}/lib/libabsl_strings.a" )

# Import target "absl::strings_internal" for configuration "Release"
set_property(TARGET absl::strings_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::strings_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_strings_internal.a"
)

list(APPEND _cmake_import_check_targets absl::strings_internal )
list(APPEND _cmake_import_check_files_for_absl::strings_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_strings_internal.a" )

# Import target "absl::str_format_internal" for configuration "Release"
set_property(TARGET absl::str_format_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::str_format_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_str_format_internal.a"
)

list(APPEND _cmake_import_check_targets absl::str_format_internal )
list(APPEND _cmake_import_check_files_for_absl::str_format_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_str_format_internal.a" )

# Import target "absl::cord_internal" for configuration "Release"
set_property(TARGET absl::cord_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::cord_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cord_internal.a"
)

list(APPEND _cmake_import_check_targets absl::cord_internal )
list(APPEND _cmake_import_check_files_for_absl::cord_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cord_internal.a" )

# Import target "absl::cordz_functions" for configuration "Release"
set_property(TARGET absl::cordz_functions APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::cordz_functions PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cordz_functions.a"
)

list(APPEND _cmake_import_check_targets absl::cordz_functions )
list(APPEND _cmake_import_check_files_for_absl::cordz_functions "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cordz_functions.a" )

# Import target "absl::cordz_handle" for configuration "Release"
set_property(TARGET absl::cordz_handle APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::cordz_handle PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cordz_handle.a"
)

list(APPEND _cmake_import_check_targets absl::cordz_handle )
list(APPEND _cmake_import_check_files_for_absl::cordz_handle "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cordz_handle.a" )

# Import target "absl::cordz_info" for configuration "Release"
set_property(TARGET absl::cordz_info APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::cordz_info PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cordz_info.a"
)

list(APPEND _cmake_import_check_targets absl::cordz_info )
list(APPEND _cmake_import_check_files_for_absl::cordz_info "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cordz_info.a" )

# Import target "absl::cordz_sample_token" for configuration "Release"
set_property(TARGET absl::cordz_sample_token APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::cordz_sample_token PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cordz_sample_token.a"
)

list(APPEND _cmake_import_check_targets absl::cordz_sample_token )
list(APPEND _cmake_import_check_files_for_absl::cordz_sample_token "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cordz_sample_token.a" )

# Import target "absl::cord" for configuration "Release"
set_property(TARGET absl::cord APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::cord PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cord.a"
)

list(APPEND _cmake_import_check_targets absl::cord )
list(APPEND _cmake_import_check_files_for_absl::cord "${CMAKE_INSTALL_PREFIX}/lib/libabsl_cord.a" )

# Import target "absl::graphcycles_internal" for configuration "Release"
set_property(TARGET absl::graphcycles_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::graphcycles_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_graphcycles_internal.a"
)

list(APPEND _cmake_import_check_targets absl::graphcycles_internal )
list(APPEND _cmake_import_check_files_for_absl::graphcycles_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_graphcycles_internal.a" )

# Import target "absl::kernel_timeout_internal" for configuration "Release"
set_property(TARGET absl::kernel_timeout_internal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::kernel_timeout_internal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_kernel_timeout_internal.a"
)

list(APPEND _cmake_import_check_targets absl::kernel_timeout_internal )
list(APPEND _cmake_import_check_files_for_absl::kernel_timeout_internal "${CMAKE_INSTALL_PREFIX}/lib/libabsl_kernel_timeout_internal.a" )

# Import target "absl::synchronization" for configuration "Release"
set_property(TARGET absl::synchronization APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::synchronization PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_synchronization.a"
)

list(APPEND _cmake_import_check_targets absl::synchronization )
list(APPEND _cmake_import_check_files_for_absl::synchronization "${CMAKE_INSTALL_PREFIX}/lib/libabsl_synchronization.a" )

# Import target "absl::time" for configuration "Release"
set_property(TARGET absl::time APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::time PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_time.a"
)

list(APPEND _cmake_import_check_targets absl::time )
list(APPEND _cmake_import_check_files_for_absl::time "${CMAKE_INSTALL_PREFIX}/lib/libabsl_time.a" )

# Import target "absl::civil_time" for configuration "Release"
set_property(TARGET absl::civil_time APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::civil_time PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_civil_time.a"
)

list(APPEND _cmake_import_check_targets absl::civil_time )
list(APPEND _cmake_import_check_files_for_absl::civil_time "${CMAKE_INSTALL_PREFIX}/lib/libabsl_civil_time.a" )

# Import target "absl::time_zone" for configuration "Release"
set_property(TARGET absl::time_zone APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::time_zone PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_time_zone.a"
)

list(APPEND _cmake_import_check_targets absl::time_zone )
list(APPEND _cmake_import_check_files_for_absl::time_zone "${CMAKE_INSTALL_PREFIX}/lib/libabsl_time_zone.a" )

# Import target "absl::bad_any_cast_impl" for configuration "Release"
set_property(TARGET absl::bad_any_cast_impl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::bad_any_cast_impl PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_bad_any_cast_impl.a"
)

list(APPEND _cmake_import_check_targets absl::bad_any_cast_impl )
list(APPEND _cmake_import_check_files_for_absl::bad_any_cast_impl "${CMAKE_INSTALL_PREFIX}/lib/libabsl_bad_any_cast_impl.a" )

# Import target "absl::bad_optional_access" for configuration "Release"
set_property(TARGET absl::bad_optional_access APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::bad_optional_access PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_bad_optional_access.a"
)

list(APPEND _cmake_import_check_targets absl::bad_optional_access )
list(APPEND _cmake_import_check_files_for_absl::bad_optional_access "${CMAKE_INSTALL_PREFIX}/lib/libabsl_bad_optional_access.a" )

# Import target "absl::bad_variant_access" for configuration "Release"
set_property(TARGET absl::bad_variant_access APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(absl::bad_variant_access PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libabsl_bad_variant_access.a"
)

list(APPEND _cmake_import_check_targets absl::bad_variant_access )
list(APPEND _cmake_import_check_files_for_absl::bad_variant_access "${CMAKE_INSTALL_PREFIX}/lib/libabsl_bad_variant_access.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
