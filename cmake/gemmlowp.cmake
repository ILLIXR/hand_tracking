#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Create imported target gemmlowp::gemmlowp
add_library(gemmlowp::gemmlowp INTERFACE IMPORTED)

set_target_properties(gemmlowp::gemmlowp PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include/gemmlowp"
                      INTERFACE_LINK_LIBRARIES "gemmlowp::eight_bit_int_gemm"
)

# Create imported target gemmlowp::eight_bit_int_gemm
add_library(gemmlowp::eight_bit_int_gemm STATIC IMPORTED)

set_target_properties(gemmlowp::eight_bit_int_gemm PROPERTIES
                      INTERFACE_LINK_LIBRARIES "Threads::Threads"
)


#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Import target "gemmlowp::eight_bit_int_gemm" for configuration "Release"
set_property(TARGET gemmlowp::eight_bit_int_gemm APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(gemmlowp::eight_bit_int_gemm PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libeight_bit_int_gemm.a"
)

list(APPEND _cmake_import_check_targets gemmlowp::eight_bit_int_gemm )
list(APPEND _cmake_import_check_files_for_gemmlowp::eight_bit_int_gemm "${CMAKE_INSTALL_PREFIX}/lib/libeight_bit_int_gemm.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
