# based on tensorflow-liteTargets.cmake

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Create imported target tensorflow-lite::fft2d_fftsg
add_library(tensorflow-lite::fft2d_fftsg STATIC IMPORTED)

set_target_properties(tensorflow-lite::fft2d_fftsg PROPERTIES
                      INTERFACE_LINK_LIBRARIES "m"
)

# Create imported target tensorflow-lite::fft2d_fftsg2d
add_library(tensorflow-lite::fft2d_fftsg2d STATIC IMPORTED)

set_target_properties(tensorflow-lite::fft2d_fftsg2d PROPERTIES
                      INTERFACE_LINK_LIBRARIES "tensorflow-lite::fft2d_fftsg"
)

# Create imported target tensorflow-lite::ml_dtypes
add_library(tensorflow-lite::ml_dtypes INTERFACE IMPORTED)

set_target_properties(tensorflow-lite::ml_dtypes PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include/ml_dtypes"
)

# Create imported target tensorflow-lite::tensorflow-lite
add_library(tensorflow-lite::tensorflow-lite STATIC IMPORTED)

set_target_properties(tensorflow-lite::tensorflow-lite PROPERTIES
                      INTERFACE_COMPILE_OPTIONS "-DEIGEN_NEON_GEBP_NR=4;-DCL_DELEGATE_NO_GL;-DEGL_NO_X11;-DTFLITE_BUILD_WITH_XNNPACK_DELEGATE;-DXNNPACK_DELEGATE_ENABLE_QS8;-DXNNPACK_DELEGATE_ENABLE_QU8;-DXNNPACK_DELEGATE_USE_LATEST_OPS;-DXNNPACK_DELEGATE_ENABLE_SUBGRAPH_RESHAPING;-DTFL_STATIC_LIBRARY_BUILD"
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "Eigen3::Eigen;absl::flags;absl::hash;absl::status;absl::strings;absl::synchronization;absl::variant;farmhash;tensorflow-lite::fft2d_fftsg2d;flatbuffers::flatbuffers;gemmlowp::gemmlowp;tensorflow-lite::ml_dtypes;ruy::ruy;PTHREADLIB;dl;NEON_2_SSE::NEON_2_SSE;absl::any;absl::flat_hash_map;XNNPACKLIB"
)


#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Import target "tensorflow-lite::fft2d_fftsg" for configuration "Release"
set_property(TARGET tensorflow-lite::fft2d_fftsg APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(tensorflow-lite::fft2d_fftsg PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libfft2d_fftsg.a"
)

list(APPEND _cmake_import_check_targets tensorflow-lite::fft2d_fftsg )
list(APPEND _cmake_import_check_files_for_tensorflow-lite::fft2d_fftsg "${CMAKE_INSTALL_PREFIX}/lib/libfft2d_fftsg.a" )

# Import target "tensorflow-lite::fft2d_fftsg2d" for configuration "Release"
set_property(TARGET tensorflow-lite::fft2d_fftsg2d APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(tensorflow-lite::fft2d_fftsg2d PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libfft2d_fftsg2d.a"
)

list(APPEND _cmake_import_check_targets tensorflow-lite::fft2d_fftsg2d )
list(APPEND _cmake_import_check_files_for_tensorflow-lite::fft2d_fftsg2d "${CMAKE_INSTALL_PREFIX}/lib/libfft2d_fftsg2d.a" )

# Import target "tensorflow-lite::tensorflow-lite" for configuration "Release"
set_property(TARGET tensorflow-lite::tensorflow-lite APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(tensorflow-lite::tensorflow-lite PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libtensorflow-lite.a"
)

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
