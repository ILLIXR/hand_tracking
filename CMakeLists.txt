cmake_minimum_required(VERSION 3.17)
project(ILLIXRHandTracking)
set(CMAKE_VERBOSE_MAKEFILE True)

option(HT_ENABLE_GPU "Whether to enable GPU based codes vs CPU based" OFF)
option(HT_ENABLE_GRAPH_PROFILER "Whether to enable the graph profiler" OFF)
cmake_dependent_option(HT_ENABLE_WEB_PROFILING "Whether to enable web profiling" ON HT_ENABLE_GRAPH_PROFILER OFF)

if(HT_ENABLE_GPU)
    add_definitions(-DMEDIAPIPE_DISABLE_GPU=0)
else()
    add_definitions(-DMEDIAPIPE_DISABLE_GPU=1)
endif()

if(HT_ENABLE_GRAPH_PROFILER)
    add_definitions(-DMEDIAPIPE_PROFILER_AVAILABLE=1)
    if(HT_ENABLE_WEB_PROFILING)
        add_definitions(-DMEDIAPIPE_WEB_PROFILING_ENABLED=1)
    endif()
endif()

find_package(zlib REQUIRED)
find_package(Protobuf REQUIRED)
find_package(glog REQUIRED)
message("${CMAKE_INSTALL_PREFIX}")
set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/lib/cmake")
#set(ENV{PKG_CONFIG_PATH} "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")
set(PROTOBUF_DESCRIPTORS "" CACHE INTERNAL "")
find_package(PkgConfig)
pkg_check_modules(cpuinfo REQUIRED libcpuinfo)
find_package(tensorflow-lite REQUIRED)

include_directories(${tensorflow-lite_INCLUDE_DIR})
message("TFL ${tensorflow-lite_INCLUDE_DIR}")

include(src/protobuf.cmake)
include(cmake/encoder.cmake)

foreach(ITEM IN LISTS PROTOBUF_DESCRIPTORS)
    file(READ ${ITEM} CONTENTS)
    file(APPEND inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin "${CONTENTS}")
endforeach()

add_custom_target(encode_descriptor_sets
                  COMMAND encode_as_c_string
                  "inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin > ${CMAKE_BINARY_DIR}src/calculators/tensor/inference_calculator_proto_descriptors.inc"
                  DEPENDS encode_as_c_string
                  BYPRODUCTS ${CMAKE_BINARY_DIR}src/calculators/tensor/inference_calculator_proto_descriptors.inc
)
include(cmake/message_util.cmake)
add_custom_target(make_message_type
                  COMMAND message_type_util
                  "--input_path=inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin --root_type_macro_output_path=${CMAKE_BINARY_DIR}/src/calculators/tensor/inference_calculator_options_lib_type_name.h"
)
add_subdirectory(src/util/tflite)



message_type_util --input_path=bazel-out/k8-opt/bin/mediapipe/calculators/tensor/inference_calculator_proto_direct-direct-descriptor-set.proto.bin --root_type_macro_output_path=bazel-out/k8-opt/bin/mediapipe/calculators/tensor/inference_calculator_options_lib_type_name.h ')


#####-DMEDIAPIPE_DISABLE_GPU=1


#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
