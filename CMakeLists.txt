cmake_minimum_required(VERSION 3.17)
project(ILLIXR_hand_tracking)
set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
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
add_compile_options(-Wno-deprecated-declarations)
if(HT_ENABLE_GRAPH_PROFILER)
    add_definitions(-DMEDIAPIPE_PROFILER_AVAILABLE=1)
    if(HT_ENABLE_WEB_PROFILING)
        add_definitions(-DMEDIAPIPE_WEB_PROFILING_ENABLED=1)
    endif()
endif()
set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH}
    ${CMAKE_INSTALL_PREFIX}/lib/cmake
)

find_package(PkgConfig)

if(ILLIXR_ROOT)
    set(ILLIXR_HDR_PATH ${ILLIXR_ROOT} CACHE PATH "Location of ILLIXR headers")
    #add_definitions(-DBUILD_ILLIXR)
else()
    message(FATAL_ERROR "ILLIXR_ROOT must be specified")
endif()

set(protobuf_MODULE_COMPATIBLE ON)
find_package(ZLIB REQUIRED)
find_package(Protobuf 3.19 REQUIRED CONFIG)
pkg_check_modules(glog REQUIRED libglog)
pkg_check_modules(egl REQUIRED egl)
pkg_check_modules(glesv2 REQUIRED glesv2)
find_package(Eigen3 REQUIRED)
find_package(OpenCV 4 REQUIRED)
set(ENABLE_OPENCV ON)

set(PROTOBUF_DESCRIPTORS "" CACHE INTERNAL "")
pkg_check_modules(cpuinfo REQUIRED libcpuinfo)

find_package(tfl-XNNPACK REQUIRED CONFIG)
find_package(pthreadpool REQUIRED CONFIG)
find_package(tensorflow-lite REQUIRED CONFIG)

if(tfl-XNNPACK_BINARY_DIR)
    add_link_options(-L${tfl-XNNPACK_BINARY_DIR})
endif()

include(mediapipe/protobuf.cmake)
include(cmake/encoder.cmake)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/mediapipe/calculators/tensor)
foreach(ITEM ${PROTOBUF_DESCRIPTORS})
    get_filename_component(_FILE ${ITEM} NAME_WE)
    add_custom_target(${_FILE}_desc
                      ALL
                      COMMAND cat ${ITEM} >> ${CMAKE_BINARY_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin_temp
                      DEPENDS encode_as_c_string ${ITEM}
    )
    list(APPEND FILE_DEPS ${_FILE}_desc)
endforeach()
add_custom_target(move_temp_bin ALL
                  COMMAND mv ${CMAKE_BINARY_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin_temp ${CMAKE_BINARY_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin
                  DEPENDS ${FILE_DEPS}
                  BYPRODUCTS ${CMAKE_BINARY_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin
)

add_custom_target(encode_descriptor_sets ALL
                  COMMAND ${CMAKE_COMMAND} -E env "LD_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib" ${CMAKE_BINARY_DIR}/encode_as_c_string
                  ${CMAKE_BINARY_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin > ${CMAKE_BINARY_DIR}/mediapipe/calculators/tensor/inference_calculator_proto_descriptors.inc
                  DEPENDS encode_as_c_string move_temp_bin
                  BYPRODUCTS ${CMAKE_BINARY_DIR}/mediapipe/calculators/tensor/inference_calculator_proto_descriptors.inc
)

include(cmake/message_util.cmake)
add_custom_target(make_message_type
                  COMMAND message_type_util
                  --input_path=${CMAKE_BINARY_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin --root_type_macro_output_path=${CMAKE_BINARY_DIR}/mediapipe/calculators/tensor/inference_calculator_options_lib_type_name.h
                  DEPENDS message_type_util
                  BYPRODUCTS ${CMAKE_BINARY_DIR}/mediapipe/calculators/tensor/inference_calculator_options_lib_type_name.h
)
#add_custom_target(encode_cleanup ALL
#                  COMMAND rm ${CMAKE_BINARY_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin
#                  DEPENDS encode_descriptor_sets make_message_type
#)


set(PLUGIN_NAME plugin.hand_tracking${ILLIXR_BUILD_SUFFIX})
add_library(${PLUGIN_NAME} SHARED plugin.cpp)

add_subdirectory(mediapipe)

target_link_libraries(${PLUGIN_NAME} PUBLIC
                      ${OpenCV_LIBRARIES}
                      absl::base
                      absl::flags_parse
                      fmt
)

target_include_directories(${PLUGIN_NAME} PRIVATE
                           ${ILLIXR_HDR_PATH}
                           ${OpenCV_INCLUDE_DIRS}
                           ${CMAKE_BINARY_DIR}
                           ${CMAKE_SOURCE_DIR}
)
install(TARGETS ${PLUGIN_NAME} DESTINATION lib)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
