cmake_minimum_required(VERSION 3.17)
project(htand_tracking_oxr C CXX)
set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/lib/cmake")
set(ENV{PKG_CONFIG_PATH} "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")

find_package(OpenXR REQUIRED CONFIG)
find_package(Boost REQUIRED CONFIG COMPONENTS interprocess)

if(NOT EXISTS "./oxr_sdk.zip" AND NOT EXISTS "OpenXR-SDK-release-1.0.34")
    file(DOWNLOAD https://github.com/KhronosGroup/OpenXR-SDK/archive/refs/tags/release-1.0.34.zip ./oxr_sdk.zip SHOW_PROGRESS)
    if(${CMAKE_MINOR_VERSION} LESS 18)
        execute_process(COMMAND unzip -d ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/oxr_sdk.zip)
    else()
        file(ARCHIVE_EXTRACT INPUT ./oxr_sdk.zip DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
    endif()
endif()

add_library(openxr_illixr_api SHARED
            ../hand_tracking_publisher.hpp
            interface.h
            interface.cpp
)

target_link_libraries(openxr_illixr_api PUBLIC
                      ${PLUGIN_NAME}
)

target_include_directories(openxr_illixr_api PUBLIC
                           ${ILLIXR_HDR_PATH}
                           ${OpenXR_INCLUDE_DIR}
                           OpenXR-SDK-release-1.0.34/include
)

add_library(openxr_illixr_ht SHARED
            openxr.c
            interface.h
)
target_link_libraries(openxr_illixr_ht PUBLIC
                      openxr_illixr_api
)
#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
