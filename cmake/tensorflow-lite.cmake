# based on tensorflow::absl
if(TARGET tensorflow-lite_base OR tensorflow-lite_POPULATED)
    return()
endif()

cmake_policy(SET CMP0135 NEW)
include(FetchContent)

FetchContent_Declare(
        tensorflow-lite
        GIT_REPOSITORY https://github.com/ILLIXR/tensorflow-lite.git
        GIT_TAG 421b551e76de7b837394801d1c3b246457bb5742
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        PREFIX "${CMAKE_BINARY_DIR}"
        SOURCE_DIR "${CMAKE_BINARY_DIR}/tensorflow-lite"
)
FetchContent_GetProperties(tensorflow-lite)
if(NOT tensorflow-lite_POPULATED)
    FetchContent_Populate(tensorflow-lite)
endif()

set(ABSL_ENABLE_INSTALL ON CACHE BOOL "")
set(TFLITE_ENABLE_INSTALL ON CACHE BOOL "")
set(SYSTEM_FARMHASH ON CACHE BOOL "")
set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
set(TFLITE_ENABLE_GPU ${HT_ENABLE_GPU} CACHE BOOL "")
add_subdirectory(
        "${tensorflow-lite_SOURCE_DIR}"
        "${tensorflow-lite_BINARY_DIR}"
)

