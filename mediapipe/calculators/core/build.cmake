set(CORE_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/begin_loop_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/clip_vector_size_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/constant_side_packet_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/end_loop_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/flow_limiter_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/gate_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/immediate_mux_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/merge_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/packet_inner_join_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/packet_sequencer_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/previous_loopback_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/split_vector_calculator.cc
)

set(CORE_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/begin_loop_calculator.h
    ${CMAKE_CURRENT_LIST_DIR}/clip_vector_size_calculator.h
    ${CMAKE_CURRENT_LIST_DIR}/end_loop_calculator.h
    ${CMAKE_CURRENT_LIST_DIR}/split_vector_calculator.h
)

target_sources(${PLUGIN_NAME} PRIVATE
               ${CORE_SOURCES}
               ${CORE_HEADERS}
)
