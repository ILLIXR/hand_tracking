cmake_minimum_required(VERSION 3.16)

project(illixr_oxr_test LANGUAGES C)

include(ExternalProject)

externalproject_add(
        monado
        GIT_REPOSITORY https://gitlab.freedesktop.org/monado/monado.git
        GIT_TAG 529aa5b092b592714812b4685aa0454a3cfb120e
        PREFIX ${CMAKE_BINARY_DIR}/_deps/monado
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX} -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF -DXRT_HAVE_LIBUDEV=ON -DXRT_HAVE_LIBUSB=ON -DXRT_HAVE_LIBUVC=ON -DXRT_HAVE_V4L2=ON -DXRT_FEATURE_SERVICE=ON
)

externalproject_add(
        test_data
        GIT_REPOSITORY https://github.com/ILLIXR/zed_test_data_public.git
        GIT_TAG main
        PREFIX ${CMAKE_BINARY_DIR}/_deps/data
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ln -fs ${CMAKE_BINARY_DIR}/_deps/data/src/test_data/fps30_dur10 ${CMAKE_INSTALL_PREFIX}/share/fps30_dur10
)
find_package(X11 REQUIRED)

pkg_check_modules(gl REQUIRED gl)

if (POLICY CMP0072)
    cmake_policy (SET CMP0072 NEW)
endif(POLICY CMP0072)

find_package(OpenGL REQUIRED)

add_executable(illixr_oxr_test
               struct.h
               test.c
               macro.h
               macro.c
               gl.h
               gl.c
               func.h
               func.c
)

target_compile_definitions(illixr_oxr_test PUBLIC -DXR_USE_GRAPHICS_API_OPENGL -DXR_USE_PLATFORM_XLIB)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

find_package(X11 REQUIRED)
set(LINUX_LIBS "Xrandr ${X11_LIBRARIES}" m)


pkg_search_module(OPENXR openxr)
if (OPENXR_FOUND)
    MESSAGE("OpenXR found with pkg-config")
    target_link_libraries(illixr_oxr_test PRIVATE ${OPENXR_LIBRARIES})
else()
    MESSAGE("OpenXR not found with pkg-config, trying cmake script")
    # current issue in upstream OpenXR cmake files requires us to find Threads on our own
    find_package(Threads REQUIRED)
    find_package(OpenXR REQUIRED)
    if (NOT OpenXR_FOUND)
        MESSAGE(FATAL_ERROR "OpenXR not found!")
    endif()

    target_include_directories(illixr-oxr-test PRIVATE ${OpenXR_INCLUDE_DIR})
    target_link_libraries(illixr-oxr-test PRIVATE OpenXR::openxr_loader)
endif()

target_link_libraries(illixr_oxr_test PRIVATE ${LINUX_LIBS} ${X11_LIBRARIES} ${SDL2_LIBRARIES} OpenGL::GL fmt)
target_include_directories(illixr_oxr_test PRIVATE ${X11_INCLUDE_DIR} ${SDL2_INCLUDE_DIRS} ${gl_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/external/openxr_headers ${ILLIXR_HDR_PATH})

target_compile_options(illixr_oxr_test PRIVATE -pedantic -Wall -Wextra -Wno-unused-parameter)

install(TARGETS illixr_oxr_test RUNTIME DESTINATION bin)
