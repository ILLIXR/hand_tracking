set(SH_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/default_input_stream_handler.h
    ${CMAKE_CURRENT_LIST_DIR}/default_input_stream_handler.cc
    ${CMAKE_CURRENT_LIST_DIR}/fixed_size_input_stream_handler.h
    ${CMAKE_CURRENT_LIST_DIR}/fixed_size_input_stream_handler.cc
    ${CMAKE_CURRENT_LIST_DIR}/immediate_input_stream_handler.h
    ${CMAKE_CURRENT_LIST_DIR}/immediate_input_stream_handler.cc
    ${CMAKE_CURRENT_LIST_DIR}/in_order_output_stream_handler.h
    ${CMAKE_CURRENT_LIST_DIR}/in_order_output_stream_handler.cc
)

target_sources(${PLUGIN_NAME} PRIVATE
               ${SH_SOURCES}
)