
if(HT_ENABLE_GRAPH_PROFILER)
    target_sources(${PLUGIN_NAME} PRIVATE
                   ${CMAKE_CURRENT_LIST_DIR}/graph_profiler.cc
                   ${CMAKE_CURRENT_LIST_DIR}/graph_profiler.h
                   ${CMAKE_CURRENT_LIST_DIR}/graph_tracer.cc
                   ${CMAKE_CURRENT_LIST_DIR}/graph_tracer.h
                   ${CMAKE_CURRENT_LIST_DIR}/trace_builder.cc
                   ${CMAKE_CURRENT_LIST_DIR}/trace_builder.h
                   ${CMAKE_CURRENT_LIST_DIR}/trace_buffer.h
                   ${CMAKE_CURRENT_LIST_DIR}/circular_buffer.h
                   ${CMAKE_CURRENT_LIST_DIR}/profiler_resource_util_common.cc
                   ${CMAKE_CURRENT_LIST_DIR}/profiler_resource_util.cc
                   ${CMAKE_CURRENT_LIST_DIR}/profiler_resource_util.h
                   ${CMAKE_CURRENT_LIST_DIR}/sharded_map.h
                   ${CMAKE_CURRENT_LIST_DIR}/web_performance_profiling.h
    )
    if(HT_ENABLE_GPU)
        target_sources(${PLUGIN_NAME} PRIVATE
                       ${CMAKE_CURRENT_LIST_DIR}/gl_context_profiler.cc
        )
    endif()

else()
    target_sources(${PLUGIN_NAME} PRIVATE
                   ${CMAKE_CURRENT_LIST_DIR}/graph_profiler_stub.h
    )
endif()
