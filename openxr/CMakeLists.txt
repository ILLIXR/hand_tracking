cmake_minimum_required(VERSION 3.17)
project(htand_tracking_oxr C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/lib/cmake")
set(ENV{PKG_CONFIG_PATH} "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")

find_package(OpenXR REQUIRED CONFIG)
find_package(Boost REQUIRED CONFIG)
find_package(OpenCV 4 REQUIRED)
find_package(spdlog REQUIRED)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/openxr/external/OpenXR-SDK-release-1.0.34")
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/openxr/external/oxr_sdk.zip")
        file(DOWNLOAD https://github.com/KhronosGroup/OpenXR-SDK/archive/refs/tags/release-1.0.34.zip ${CMAKE_SOURCE_DIR}/openxr/external/oxr_sdk.zip SHOW_PROGRESS)
    endif()
    if(${CMAKE_MINOR_VERSION} LESS 18)
        execute_process(COMMAND unzip -d ${CMAKE_SOURCE_DIR}/openxr/external ${CMAKE_SOURCE_DIR}/openxr/external/oxr_sdk.zip)
    else()
        file(ARCHIVE_EXTRACT INPUT ${CMAKE_SOURCE_DIR}/openxr/external/oxr_sdk.zip DESTINATION ${CMAKE_SOURCE_DIR}/openxr/external)
    endif()
endif()


add_library(openxr_illixr_ht SHARED
            openxr.cpp
            interface.h
            oxr_objects.h
            ../hand_tracking_publisher.hpp
            interface.cpp
            ixr_openxr.hpp
)
target_link_libraries(openxr_illixr_ht PUBLIC
                      absl::base
                      spdlog::spdlog
                      ${glog_LIBRARIES}
)

target_include_directories(openxr_illixr_ht PUBLIC
                           ${ILLIXR_HDR_PATH}
                           ${OpenXR_INCLUDE_DIR}
                           ${Boost_INCLUDE_DIRS}
                           ${OpenCV_INCLUDE_DIRS}
                           ${CMAKE_SOURCE_DIR}
                           ${CMAKE_BINARY_DIR}
                           ${CMAKE_SOURCE_DIR}/openxr/external/OpenXR-SDK-release-1.0.34/include
)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/illixr_ht.json.in ${CMAKE_BINARY_DIR}/illixr_ht.json)
install(FILES ${CMAKE_BINARY_DIR}/illixr_ht.json
        DESTINATION $ENV{HOME}/.local/share/openxr/1/api_layers/implicit.d)

if(BUILD_OXR_TEST)
    add_subdirectory(test)
endif()

install(TARGETS openxr_illixr_ht DESTINATION lib)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
