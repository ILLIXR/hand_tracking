set(UTIL_SOURCES
    util/annotation_renderer.cc
    util/cpu_util.cc
    util/header_util.cc
    util/rectangle_util.cc
    util/resource_util.cc
    util/resource_util_internal.cc
)

set(UTIL_HEADERS
    util/annotation_renderer.h
    util/cpu_util.h
    util/header_util.h
    util/rectangle_util.h
    util/resource_cache.h
    util/resource_util.h
    util/resource_util_custom.h
    util/resource_util_internal.h
)

target_sources(${PLUGIN_NAME} PUBLIC
               ${UTIL_SOURCES}
               ${UTIL_HEADERS}
)

include(tflite/build.cmake)
