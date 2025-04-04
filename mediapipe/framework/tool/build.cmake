set(TOOL_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/container_util.cc
    ${CMAKE_CURRENT_LIST_DIR}/fill_packet_set.cc
    ${CMAKE_CURRENT_LIST_DIR}/name_util.cc
    ${CMAKE_CURRENT_LIST_DIR}/options_field_util.cc
    ${CMAKE_CURRENT_LIST_DIR}/options_registry.cc
    ${CMAKE_CURRENT_LIST_DIR}/options_syntax_util.cc
    ${CMAKE_CURRENT_LIST_DIR}/options_util.cc
    ${CMAKE_CURRENT_LIST_DIR}/packet_generator_wrapper_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/proto_util_lite.cc
    ${CMAKE_CURRENT_LIST_DIR}/sink.cc
    ${CMAKE_CURRENT_LIST_DIR}/status_util.cc
    ${CMAKE_CURRENT_LIST_DIR}/switch_container.cc
    ${CMAKE_CURRENT_LIST_DIR}/subgraph_expansion.cc
    ${CMAKE_CURRENT_LIST_DIR}/switch_demux_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/switch_mux_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/tag_map.cc
    ${CMAKE_CURRENT_LIST_DIR}/tag_map_helper.cc
    ${CMAKE_CURRENT_LIST_DIR}/template_expander.cc
    ${CMAKE_CURRENT_LIST_DIR}/validate.cc
    ${CMAKE_CURRENT_LIST_DIR}/validate_name.cc
)

set(TOOL_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/container_util.h
    ${CMAKE_CURRENT_LIST_DIR}/fill_packet_set.h
    ${CMAKE_CURRENT_LIST_DIR}/name_util.h
    ${CMAKE_CURRENT_LIST_DIR}/options_map.h
    ${CMAKE_CURRENT_LIST_DIR}/options_field_util.h
    ${CMAKE_CURRENT_LIST_DIR}/options_registry.h
    ${CMAKE_CURRENT_LIST_DIR}/options_syntax_util.h
    ${CMAKE_CURRENT_LIST_DIR}/options_util.h
    ${CMAKE_CURRENT_LIST_DIR}/packet_generator_wrapper_calculator.h
    ${CMAKE_CURRENT_LIST_DIR}/proto_util_lite.h
    ${CMAKE_CURRENT_LIST_DIR}/sink.h
    ${CMAKE_CURRENT_LIST_DIR}/status_util.h
    ${CMAKE_CURRENT_LIST_DIR}/subgraph_expansion.h
    ${CMAKE_CURRENT_LIST_DIR}/tag_map.h
    ${CMAKE_CURRENT_LIST_DIR}/tag_map_helper.h
    ${CMAKE_CURRENT_LIST_DIR}/template_expander.h
    ${CMAKE_CURRENT_LIST_DIR}/type_util.h
    ${CMAKE_CURRENT_LIST_DIR}/validate.h
    ${CMAKE_CURRENT_LIST_DIR}/validate_name.h
)

target_sources(${PLUGIN_NAME} PRIVATE
               ${TOOL_SOURCES}
               ${TOOL_HEADERS}
)