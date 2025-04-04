cmake_minimum_required(VERSION 3.17)
project(ILLIXR_hand_tracking)
set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/lib/cmake")
set(ENV{PKG_CONFIG_PATH} "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")

include(CMakeDependentOption)

cmake_policy(SET CMP0153 OLD)
cmake_policy(SET CMP0146 OLD)

set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -Wall -Wextra -rdynamic -Wno-attributes -Wno-unused-function -Wno-unknown-pragmas -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG -Wall -Wextra -Wno-attributes -Wno-unused-function -Wno-unknown-pragmas -fPIC")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-ggdb -O3 -Wall -Wextra -Wno-attributes -Wno-unused-function -Wno-unknown-pragmas -fPIC")

option(HT_ENABLE_GPU "Whether to enable GPU based codes vs CPU based" OFF)
option(HT_ENABLE_GRAPH_PROFILER "Whether to enable the graph profiler" OFF)
option(BUILD_OXR_INTERFACE "Whether to build the OpenXR interface library" OFF)
cmake_dependent_option(BUILD_OXR_TEST "Whether to build the OpenXR test" OFF BUILD_OXR_INTERFACE OFF)
option(TFLIBRARY_POSTFIX "Postfix to attach to XNNPACK and tensorflow libraries to identify the specuific version needed" OFF)
cmake_dependent_option(HT_ENABLE_WEB_PROFILING "Whether to enable web profiling" ON HT_ENABLE_GRAPH_PROFILER OFF)
option(BUILD_DOCS "Build the documentation" OFF)

if(BUILD_OXR_INTERFACE)
    add_definitions(-DENABLE_OXR)
endif()

if(BUILD_OXR_TEST)
    add_definitions(-DENABLE_OXR_TEST)
endif()


if(TFLIBRARY_POSTFIX)
    if(NOT ((TFLIBRARY_POSTFIX MATCHES "^-") OR (TFLIBRARY_POSTFIX MATCHES "^_")))
        set(TFLIBRARY_POSTFIX "-${TFLIBRARY_POSTFIX}")
    endif()
else()
    set(TFLIBRARY_POSTFIX "")
endif()
if(HT_ENABLE_GPU)
    add_definitions(-DMEDIAPIPE_DISABLE_GPU=0 -DMESA_EGL_NO_X11_HEADERS -DEGL_NO_X11)
    set(TF_POSTFIX "${TFLIBRARY_POSTFIX}-gpu")
else()
    add_definitions(-DMEDIAPIPE_DISABLE_GPU=1)
    set(TF_POSTFIX ${TFLIBRARY_POSTFIX})
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
add_custom_target(docs_dummy_target
                  COMMAND ${CMAKE_COMMAND} -E echo ""
)
find_package(PkgConfig)

if(ILLIXR_ROOT)
    set(ILLIXR_HDR_PATH "${ILLIXR_ROOT}/include" CACHE PATH "Location of ILLIXR headers")
else()
    message(FATAL_ERROR "ILLIXR_ROOT must be specified")
endif()

set(protobuf_MODULE_COMPATIBLE ON)
find_package(ZLIB REQUIRED)
find_package(ZED 3 QUIET)
if(ZED_FOUND)
    find_package(CUDAToolkit ${ZED_CUDA_VERSION} EXACT QUIET)
    if(NOT CUDAToolkit_FOUND)
        set(ZED_FOUND NO)
    else()
        add_definitions(-DHAVE_ZED)
    endif()
endif()
find_package(Protobuf 3.19 REQUIRED CONFIG)
pkg_check_modules(glog REQUIRED libglog)
pkg_check_modules(egl REQUIRED egl)
pkg_check_modules(glesv2 REQUIRED glesv2)
find_package(Eigen3 REQUIRED)
find_package(OpenCV 4 REQUIRED)
set(ENABLE_OPENCV ON)

set(PROTOBUF_DESCRIPTORS "" CACHE INTERNAL "")
pkg_check_modules(cpuinfo REQUIRED libcpuinfo)

find_package(gemmlowp REQUIRED CONFIG)
find_package(tfl-XNNPACK${TFLIBRARY_POSTFIX} REQUIRED CONFIG)
find_package(pthreadpool REQUIRED CONFIG)
find_package(tensorflow-lite${TF_POSTFIX} REQUIRED CONFIG)

if(tfl-XNNPACK${TFLIBRARY_POSTFIX}_BINARY_DIR)
    add_link_options(-L${tfl-XNNPACK${TFLIBRARY_POSTFIX}_BINARY_DIR})
endif()

include(mediapipe/protobuf.cmake)
include(cmake/encoder.cmake)
set(CURRENT_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}" CACHE INTERNAL "")
file(MAKE_DIRECTORY ${CURRENT_BUILD_DIR}/mediapipe/calculators/tensor)
foreach(ITEM ${PROTOBUF_DESCRIPTORS})
    get_filename_component(_FILE ${ITEM} NAME_WE)
    add_custom_target(${_FILE}_desc
                      ALL
                      COMMAND cat ${ITEM} >> ${CURRENT_BUILD_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin_temp
                      DEPENDS encode_as_c_string ${ITEM}
    )
    list(APPEND FILE_DEPS ${_FILE}_desc)
endforeach()
add_custom_target(move_temp_bin ALL
                  COMMAND mv ${CURRENT_BUILD_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin_temp ${CURRENT_BUILD_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin
                  DEPENDS ${FILE_DEPS}
                  BYPRODUCTS ${CURRENT_BUILD_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin
)

add_custom_target(encode_descriptor_sets ALL
                  COMMAND ${CMAKE_COMMAND} -E env "LD_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib" ${CURRENT_BUILD_DIR}/encode_as_c_string
                  ${CURRENT_BUILD_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin > ${CURRENT_BUILD_DIR}/mediapipe/calculators/tensor/inference_calculator_proto_descriptors.inc
                  DEPENDS encode_as_c_string move_temp_bin
                  BYPRODUCTS ${CURRENT_BUILD_DIR}/mediapipe/calculators/tensor/inference_calculator_proto_descriptors.inc
)

include(cmake/message_util.cmake)
add_custom_target(make_message_type
                  COMMAND message_type_util
                  --input_path=${CURRENT_BUILD_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin --root_type_macro_output_path=${CURRENT_BUILD_DIR}/mediapipe/calculators/tensor/inference_calculator_options_lib_type_name.h
                  DEPENDS message_type_util
                  BYPRODUCTS ${CURRENT_BUILD_DIR}/mediapipe/calculators/tensor/inference_calculator_options_lib_type_name.h
)
#add_custom_target(encode_cleanup ALL
#                  COMMAND rm ${CURRENT_BUILD_DIR}/inference_calculator_proto_transitive-transitive-descriptor-set.proto.bin
#                  DEPENDS encode_descriptor_sets make_message_type
#)

set(HT_PROCESSOR "")
if(HT_ENABLE_GPU)
    set(HT_PROCESSOR "_gpu")
endif()
set(PLUGIN_NAME plugin.hand_tracking${HT_PROCESSOR}${ILLIXR_BUILD_SUFFIX})
add_library(${PLUGIN_NAME} SHARED
            plugin.cpp
            plugin.hpp
            hand_tracking_publisher.cpp
            hand_tracking_publisher.hpp
            ${ILLIXR_HDR_PATH}/illixr/data_format/misc.hpp
            ${ILLIXR_HDR_PATH}/illixr/data_format/zed_cam.hpp
            ${ILLIXR_HDR_PATH}/illixr/threadloop.hpp
            ${ILLIXR_HDR_PATH}/illixr/data_format/camera_data.hpp
            ${ILLIXR_HDR_PATH}/illixr/data_format/hand_tracking_data.hpp
            ${ILLIXR_HDR_PATH}/illixr/data_format/pose.hpp
            ${ILLIXR_HDR_PATH}/illixr/plugin.hpp
            ${ILLIXR_HDR_PATH}/illixr/phonebook.hpp
            ${ILLIXR_HDR_PATH}/illixr/switchboard.hpp
            ${ILLIXR_HDR_PATH}/illixr/record_logger.hpp
            ${ILLIXR_HDR_PATH}/illixr/stoplight.hpp
            ${ILLIXR_HDR_PATH}/illixr/cpu_timer.hpp
            ${ILLIXR_HDR_PATH}/illixr/error_util.hpp
)
add_subdirectory(mediapipe)

target_link_libraries(${PLUGIN_NAME} PUBLIC
                      ${OpenCV_LIBRARIES}
                      absl::base
                      absl::flags_parse
                      fmt
)

target_include_directories(${PLUGIN_NAME} PUBLIC
                           ${ILLIXR_HDR_PATH}
                           ${ILLIXR_ROOT}
                           ${OpenCV_INCLUDE_DIRS}
                           ${CURRENT_BUILD_DIR}
                           ${CMAKE_SOURCE_DIR}
)

if(BUILD_OXR_INTERFACE)
    add_subdirectory(openxr)
    target_link_libraries(${PLUGIN_NAME} PUBLIC
                          OXR_HEADERS
    )
    if(BUILD_OXR_TEST)
        include(openxr/test/cmake/scripts.cmake)
    endif()
endif()

install(TARGETS ${PLUGIN_NAME} DESTINATION lib)

if(BUILD_DOCS)
    add_subdirectory(docs)
endif()
