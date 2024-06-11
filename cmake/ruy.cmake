#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Create imported target NEON_2_SSE::NEON_2_SSE
add_library(NEON_2_SSE::NEON_2_SSE INTERFACE IMPORTED)

set_target_properties(NEON_2_SSE::NEON_2_SSE PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
)


#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ruy::ruy_wait" for configuration "Release"
set_property(TARGET ruy::ruy_wait APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_wait PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_wait.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_wait )
list(APPEND _cmake_import_check_files_for_ruy::ruy_wait "${CMAKE_INSTALL_PREFIX}/lib/libruy_wait.a" )

# Import target "ruy::ruy_tune" for configuration "Release"
set_property(TARGET ruy::ruy_tune APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_tune PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_tune.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_tune )
list(APPEND _cmake_import_check_files_for_ruy::ruy_tune "${CMAKE_INSTALL_PREFIX}/lib/libruy_tune.a" )

# Import target "ruy::ruy_system_aligned_alloc" for configuration "Release"
set_property(TARGET ruy::ruy_system_aligned_alloc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_system_aligned_alloc PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_system_aligned_alloc.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_system_aligned_alloc )
list(APPEND _cmake_import_check_files_for_ruy::ruy_system_aligned_alloc "${CMAKE_INSTALL_PREFIX}/lib/libruy_system_aligned_alloc.a" )

# Import target "ruy::ruy_prepacked_cache" for configuration "Release"
set_property(TARGET ruy::ruy_prepacked_cache APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_prepacked_cache PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_prepacked_cache.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_prepacked_cache )
list(APPEND _cmake_import_check_files_for_ruy::ruy_prepacked_cache "${CMAKE_INSTALL_PREFIX}/lib/libruy_prepacked_cache.a" )

# Import target "ruy::ruy_allocator" for configuration "Release"
set_property(TARGET ruy::ruy_allocator APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_allocator PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_allocator.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_allocator )
list(APPEND _cmake_import_check_files_for_ruy::ruy_allocator "${CMAKE_INSTALL_PREFIX}/lib/libruy_allocator.a" )

# Import target "ruy::ruy_block_map" for configuration "Release"
set_property(TARGET ruy::ruy_block_map APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_block_map PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_block_map.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_block_map )
list(APPEND _cmake_import_check_files_for_ruy::ruy_block_map "${CMAKE_INSTALL_PREFIX}/lib/libruy_block_map.a" )

# Import target "ruy::ruy_blocking_counter" for configuration "Release"
set_property(TARGET ruy::ruy_blocking_counter APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_blocking_counter PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_blocking_counter.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_blocking_counter )
list(APPEND _cmake_import_check_files_for_ruy::ruy_blocking_counter "${CMAKE_INSTALL_PREFIX}/lib/libruy_blocking_counter.a" )

# Import target "ruy::ruy_thread_pool" for configuration "Release"
set_property(TARGET ruy::ruy_thread_pool APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_thread_pool PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_thread_pool.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_thread_pool )
list(APPEND _cmake_import_check_files_for_ruy::ruy_thread_pool "${CMAKE_INSTALL_PREFIX}/lib/libruy_thread_pool.a" )

# Import target "ruy::ruy_cpuinfo" for configuration "Release"
set_property(TARGET ruy::ruy_cpuinfo APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_cpuinfo PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_cpuinfo.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_cpuinfo )
list(APPEND _cmake_import_check_files_for_ruy::ruy_cpuinfo "${CMAKE_INSTALL_PREFIX}/lib/libruy_cpuinfo.a" )

# Import target "ruy::ruy_denormal" for configuration "Release"
set_property(TARGET ruy::ruy_denormal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_denormal PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_denormal.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_denormal )
list(APPEND _cmake_import_check_files_for_ruy::ruy_denormal "${CMAKE_INSTALL_PREFIX}/lib/libruy_denormal.a" )

# Import target "ruy::ruy_apply_multiplier" for configuration "Release"
set_property(TARGET ruy::ruy_apply_multiplier APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_apply_multiplier PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_apply_multiplier.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_apply_multiplier )
list(APPEND _cmake_import_check_files_for_ruy::ruy_apply_multiplier "${CMAKE_INSTALL_PREFIX}/lib/libruy_apply_multiplier.a" )

# Import target "ruy::ruy_kernel_arm" for configuration "Release"
set_property(TARGET ruy::ruy_kernel_arm APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_kernel_arm PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_kernel_arm.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_kernel_arm )
list(APPEND _cmake_import_check_files_for_ruy::ruy_kernel_arm "${CMAKE_INSTALL_PREFIX}/lib/libruy_kernel_arm.a" )

# Import target "ruy::ruy_pack_arm" for configuration "Release"
set_property(TARGET ruy::ruy_pack_arm APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_pack_arm PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_pack_arm.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_pack_arm )
list(APPEND _cmake_import_check_files_for_ruy::ruy_pack_arm "${CMAKE_INSTALL_PREFIX}/lib/libruy_pack_arm.a" )

# Import target "ruy::ruy_kernel_avx512" for configuration "Release"
set_property(TARGET ruy::ruy_kernel_avx512 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_kernel_avx512 PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_kernel_avx512.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_kernel_avx512 )
list(APPEND _cmake_import_check_files_for_ruy::ruy_kernel_avx512 "${CMAKE_INSTALL_PREFIX}/lib/libruy_kernel_avx512.a" )

# Import target "ruy::ruy_pack_avx512" for configuration "Release"
set_property(TARGET ruy::ruy_pack_avx512 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_pack_avx512 PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_pack_avx512.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_pack_avx512 )
list(APPEND _cmake_import_check_files_for_ruy::ruy_pack_avx512 "${CMAKE_INSTALL_PREFIX}/lib/libruy_pack_avx512.a" )

# Import target "ruy::ruy_have_built_path_for_avx512" for configuration "Release"
set_property(TARGET ruy::ruy_have_built_path_for_avx512 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_have_built_path_for_avx512 PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_have_built_path_for_avx512.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_have_built_path_for_avx512 )
list(APPEND _cmake_import_check_files_for_ruy::ruy_have_built_path_for_avx512 "${CMAKE_INSTALL_PREFIX}/lib/libruy_have_built_path_for_avx512.a" )

# Import target "ruy::ruy_kernel_avx2_fma" for configuration "Release"
set_property(TARGET ruy::ruy_kernel_avx2_fma APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_kernel_avx2_fma PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_kernel_avx2_fma.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_kernel_avx2_fma )
list(APPEND _cmake_import_check_files_for_ruy::ruy_kernel_avx2_fma "${CMAKE_INSTALL_PREFIX}/lib/libruy_kernel_avx2_fma.a" )

# Import target "ruy::ruy_pack_avx2_fma" for configuration "Release"
set_property(TARGET ruy::ruy_pack_avx2_fma APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_pack_avx2_fma PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_pack_avx2_fma.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_pack_avx2_fma )
list(APPEND _cmake_import_check_files_for_ruy::ruy_pack_avx2_fma "${CMAKE_INSTALL_PREFIX}/lib/libruy_pack_avx2_fma.a" )

# Import target "ruy::ruy_have_built_path_for_avx2_fma" for configuration "Release"
set_property(TARGET ruy::ruy_have_built_path_for_avx2_fma APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_have_built_path_for_avx2_fma PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_have_built_path_for_avx2_fma.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_have_built_path_for_avx2_fma )
list(APPEND _cmake_import_check_files_for_ruy::ruy_have_built_path_for_avx2_fma "${CMAKE_INSTALL_PREFIX}/lib/libruy_have_built_path_for_avx2_fma.a" )

# Import target "ruy::ruy_kernel_avx" for configuration "Release"
set_property(TARGET ruy::ruy_kernel_avx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_kernel_avx PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_kernel_avx.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_kernel_avx )
list(APPEND _cmake_import_check_files_for_ruy::ruy_kernel_avx "${CMAKE_INSTALL_PREFIX}/lib/libruy_kernel_avx.a" )

# Import target "ruy::ruy_pack_avx" for configuration "Release"
set_property(TARGET ruy::ruy_pack_avx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_pack_avx PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_pack_avx.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_pack_avx )
list(APPEND _cmake_import_check_files_for_ruy::ruy_pack_avx "${CMAKE_INSTALL_PREFIX}/lib/libruy_pack_avx.a" )

# Import target "ruy::ruy_have_built_path_for_avx" for configuration "Release"
set_property(TARGET ruy::ruy_have_built_path_for_avx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_have_built_path_for_avx PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_have_built_path_for_avx.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_have_built_path_for_avx )
list(APPEND _cmake_import_check_files_for_ruy::ruy_have_built_path_for_avx "${CMAKE_INSTALL_PREFIX}/lib/libruy_have_built_path_for_avx.a" )

# Import target "ruy::ruy_context" for configuration "Release"
set_property(TARGET ruy::ruy_context APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_context PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_context.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_context )
list(APPEND _cmake_import_check_files_for_ruy::ruy_context "${CMAKE_INSTALL_PREFIX}/lib/libruy_context.a" )

# Import target "ruy::ruy_ctx" for configuration "Release"
set_property(TARGET ruy::ruy_ctx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_ctx PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_ctx.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_ctx )
list(APPEND _cmake_import_check_files_for_ruy::ruy_ctx "${CMAKE_INSTALL_PREFIX}/lib/libruy_ctx.a" )

# Import target "ruy::ruy_context_get_ctx" for configuration "Release"
set_property(TARGET ruy::ruy_context_get_ctx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_context_get_ctx PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_context_get_ctx.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_context_get_ctx )
list(APPEND _cmake_import_check_files_for_ruy::ruy_context_get_ctx "${CMAKE_INSTALL_PREFIX}/lib/libruy_context_get_ctx.a" )

# Import target "ruy::ruy_trmul" for configuration "Release"
set_property(TARGET ruy::ruy_trmul APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_trmul PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_trmul.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_trmul )
list(APPEND _cmake_import_check_files_for_ruy::ruy_trmul "${CMAKE_INSTALL_PREFIX}/lib/libruy_trmul.a" )

# Import target "ruy::ruy_prepare_packed_matrices" for configuration "Release"
set_property(TARGET ruy::ruy_prepare_packed_matrices APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_prepare_packed_matrices PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_prepare_packed_matrices.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_prepare_packed_matrices )
list(APPEND _cmake_import_check_files_for_ruy::ruy_prepare_packed_matrices "${CMAKE_INSTALL_PREFIX}/lib/libruy_prepare_packed_matrices.a" )

# Import target "ruy::ruy_frontend" for configuration "Release"
set_property(TARGET ruy::ruy_frontend APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_frontend PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_frontend.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_frontend )
list(APPEND _cmake_import_check_files_for_ruy::ruy_frontend "${CMAKE_INSTALL_PREFIX}/lib/libruy_frontend.a" )

# Import target "ruy::ruy_profiler_instrumentation" for configuration "Release"
set_property(TARGET ruy::ruy_profiler_instrumentation APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_profiler_instrumentation PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_profiler_instrumentation.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_profiler_instrumentation )
list(APPEND _cmake_import_check_files_for_ruy::ruy_profiler_instrumentation "${CMAKE_INSTALL_PREFIX}/lib/libruy_profiler_instrumentation.a" )

# Import target "ruy::ruy_profiler_profiler" for configuration "Release"
set_property(TARGET ruy::ruy_profiler_profiler APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ruy::ruy_profiler_profiler PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libruy_profiler_profiler.a"
)

list(APPEND _cmake_import_check_targets ruy::ruy_profiler_profiler )
list(APPEND _cmake_import_check_files_for_ruy::ruy_profiler_profiler "${CMAKE_INSTALL_PREFIX}/lib/libruy_profiler_profiler.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
