set(UTIL_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/annotation_renderer.cc
    ${CMAKE_CURRENT_LIST_DIR}/cpu_util.cc
    ${CMAKE_CURRENT_LIST_DIR}/header_util.cc
    ${CMAKE_CURRENT_LIST_DIR}/rectangle_util.cc
    ${CMAKE_CURRENT_LIST_DIR}/resource_util.cc
    ${CMAKE_CURRENT_LIST_DIR}/resource_util_default.cc
)

set(UTIL_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/annotation_renderer.h
    ${CMAKE_CURRENT_LIST_DIR}/cpu_util.h
    ${CMAKE_CURRENT_LIST_DIR}/header_util.h
    ${CMAKE_CURRENT_LIST_DIR}/rectangle_util.h
    ${CMAKE_CURRENT_LIST_DIR}/resource_cache.h
    ${CMAKE_CURRENT_LIST_DIR}/resource_util.h
    ${CMAKE_CURRENT_LIST_DIR}/resource_util_custom.h
    ${CMAKE_CURRENT_LIST_DIR}/resource_util_internal.h
)

target_sources(${PLUGIN_NAME} PRIVATE
               ${UTIL_SOURCES}
               ${UTIL_HEADERS}
)

include(${CMAKE_CURRENT_LIST_DIR}/tflite/build.cmake)
