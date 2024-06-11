#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Create imported target flatbuffers::flatbuffers
add_library(flatbuffers::flatbuffers STATIC IMPORTED)

set_target_properties(flatbuffers::flatbuffers PROPERTIES
                      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/include"
                      INTERFACE_LINK_LIBRARIES "\$<LINK_ONLY:>"
)


#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "flatbuffers::flatbuffers" for configuration "Release"
set_property(TARGET flatbuffers::flatbuffers APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(flatbuffers::flatbuffers PROPERTIES
                      IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/lib/libflatbuffers.a"
)

list(APPEND _cmake_import_check_targets flatbuffers::flatbuffers )
list(APPEND _cmake_import_check_files_for_flatbuffers::flatbuffers "${CMAKE_INSTALL_PREFIX}/lib/libflatbuffers.a" )


#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Create imported target flatbuffers::flatc
add_executable(flatbuffers::flatc IMPORTED)

# Import target "flatbuffers::flatc" for configuration "Release"
set_property(TARGET flatbuffers::flatc APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(flatbuffers::flatc PROPERTIES
                      IMPORTED_LOCATION_RELEASE "${CMAKE_INSTALL_PREFIX}/bin/flatc"
)

list(APPEND _cmake_import_check_targets flatbuffers::flatc )
list(APPEND _cmake_import_check_files_for_flatbuffers::flatc "${CMAKE_INSTALL_PREFIX}/bin/flatc" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
