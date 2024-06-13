cmake_minimum_required(VERSION 3.17)
project(ILLIXRHandTracking)
set(CMAKE_VERBOSE_MAKEFILE True)

set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/lib/cmake")
set(ENV{PKG_CONFIG_PATH} "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")

include(CMakeDependentOption)

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
find_package(PkgConfig)

find_package(ZLIB REQUIRED)
find_package(Protobuf REQUIRED)
pkg_check_modules(glog REQUIRED libglog)
pkg_check_modules(egl REQUIRED egl)
pkg_check_modules(glesv2 REQUIRED glesv2)
find_package(Eigen3 REQUIRED)
find_package(OpenCV 4 REQUIRED)

set(PROTOBUF_DESCRIPTORS "" CACHE INTERNAL "")
pkg_check_modules(cpuinfo REQUIRED libcpuinfo)

find_package(tensorflow-lite QUIET)
find_package(absl QUIET)

if(NOT tensorflow-lite_FOUND)
    include(ExternalProject)
    if(NOT tensorflow-lite)
        ExternalProject_Add(TF_ext
                            GIT_REPOSITORY https://github.com/ILLIXR/tensorflow-lite.git
                            GIT_TAG d13d80b79c3d2f6436b14354c52ad160f4d256ed
                            PREFIX ${CMAKE_BINARY_DIR}/_deps/tensorflow-lite
                            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DABSL_ENABLE_INSTALL=ON -DTFLITE_ENABLE_INSTALL=ON -DSYSTEM_FARMHASH=ON -DBUILD_SHARED_LIBS=OFF -DTFLITE_ENABLE_GPU=${HT_ENABLE_GPU}
        )
        include(cmake/gemmlowp.cmake)
        include(cmake/NEON_2_SSE.cmake)
        include(cmake/ruy.cmake)
        include(cmake/flatbuffer.cmake)
        if(NOT absl_FOUND)
            include(cmake/absl.cmake)
        endif()
        include(cmake/tensorflow-lite.cmake)
    endif()
endif()

include(mediapipe/protobuf.cmake)
include(cmake/encoder.cmake)

#foreach(ITEM IN LISTS PROTOBUF_DESCRIPTORS)
#    file(READ ${ITEM} CONTENTS)
#    file(APPEND inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin "${CONTENTS}")
#endforeach()

#add_custom_target(encode_descriptor_sets
#                  COMMAND encode_as_c_string
#                  "inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin > ${CMAKE_BINARY_DIR}src/calculators/tensor/inference_calculator_proto_descriptors.inc"
#                  DEPENDS encode_as_c_string
#                  BYPRODUCTS ${CMAKE_BINARY_DIR}src/calculators/tensor/inference_calculator_proto_descriptors.inc
#)
#include(cmake/message_util.cmake)
#add_custom_target(make_message_type
#                  COMMAND message_type_util
#                  "--input_path=inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin --root_type_macro_output_path=${CMAKE_BINARY_DIR}/src/calculators/tensor/inference_calculator_options_lib_type_name.h"
#)
#add_subdirectory(src/util/tflite)



#message_type_util --input_path=bazel-out/k8-opt/bin/mediapipe/calculators/tensor/inference_calculator_proto_direct-direct-descriptor-set.proto.bin --root_type_macro_output_path=bazel-out/k8-opt/bin/mediapipe/calculators/tensor/inference_calculator_options_lib_type_name.h ')


#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
