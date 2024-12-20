set(FRAMEWORK_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/calculator_base.cc
    ${CMAKE_CURRENT_LIST_DIR}/calculator_context.cc
    ${CMAKE_CURRENT_LIST_DIR}/calculator_context_manager.cc
    ${CMAKE_CURRENT_LIST_DIR}/calculator_contract.cc
    ${CMAKE_CURRENT_LIST_DIR}/calculator_graph.cc
    ${CMAKE_CURRENT_LIST_DIR}/calculator_node.cc
    ${CMAKE_CURRENT_LIST_DIR}/calculator_state.cc
    ${CMAKE_CURRENT_LIST_DIR}/collection_item_id.cc
    ${CMAKE_CURRENT_LIST_DIR}/counter_factory.cc
    ${CMAKE_CURRENT_LIST_DIR}/collection_item_id.cc
    ${CMAKE_CURRENT_LIST_DIR}/delegating_executor.cc
    ${CMAKE_CURRENT_LIST_DIR}/executor.cc
    ${CMAKE_CURRENT_LIST_DIR}/graph_output_stream.cc
    ${CMAKE_CURRENT_LIST_DIR}/graph_service_manager.cc
    ${CMAKE_CURRENT_LIST_DIR}/input_side_packet_handler.cc
    ${CMAKE_CURRENT_LIST_DIR}/input_stream_handler.cc
    ${CMAKE_CURRENT_LIST_DIR}/input_stream_manager.cc
    ${CMAKE_CURRENT_LIST_DIR}/input_stream_shard.cc
    ${CMAKE_CURRENT_LIST_DIR}/legacy_calculator_support.cc
    ${CMAKE_CURRENT_LIST_DIR}/output_side_packet_impl.cc
    ${CMAKE_CURRENT_LIST_DIR}/output_stream_handler.cc
    ${CMAKE_CURRENT_LIST_DIR}/output_stream_manager.cc
    ${CMAKE_CURRENT_LIST_DIR}/output_stream_shard.cc
    ${CMAKE_CURRENT_LIST_DIR}/packet.cc
    ${CMAKE_CURRENT_LIST_DIR}/packet_generator_graph.cc
    ${CMAKE_CURRENT_LIST_DIR}/packet_type.cc
    ${CMAKE_CURRENT_LIST_DIR}/scheduler.cc
    ${CMAKE_CURRENT_LIST_DIR}/scheduler_queue.cc
    ${CMAKE_CURRENT_LIST_DIR}/subgraph.cc
    ${CMAKE_CURRENT_LIST_DIR}/thread_pool_executor.cc
    ${CMAKE_CURRENT_LIST_DIR}/timestamp.cc
    ${CMAKE_CURRENT_LIST_DIR}/validated_graph_config.cc
)

set(FRAMEWORK_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/calculator_base.h
    ${CMAKE_CURRENT_LIST_DIR}/calculator_context.h
    ${CMAKE_CURRENT_LIST_DIR}/calculator_context_manager.h
    ${CMAKE_CURRENT_LIST_DIR}/calculator_contract.h
    ${CMAKE_CURRENT_LIST_DIR}/calculator_framework.h
    ${CMAKE_CURRENT_LIST_DIR}/calculator_graph.h
    ${CMAKE_CURRENT_LIST_DIR}/calculator_node.h
    ${CMAKE_CURRENT_LIST_DIR}/calculator_registry.h
    ${CMAKE_CURRENT_LIST_DIR}/calculator_state.h
    ${CMAKE_CURRENT_LIST_DIR}/collection.h
    ${CMAKE_CURRENT_LIST_DIR}/collection_item_id.h
    ${CMAKE_CURRENT_LIST_DIR}/counter.h
    ${CMAKE_CURRENT_LIST_DIR}/counter_factory.h
    ${CMAKE_CURRENT_LIST_DIR}/delegating_executor.h
    ${CMAKE_CURRENT_LIST_DIR}/demangle.h
    ${CMAKE_CURRENT_LIST_DIR}/executor.h
    ${CMAKE_CURRENT_LIST_DIR}/graph_output_stream.h
    ${CMAKE_CURRENT_LIST_DIR}/graph_service.h
    ${CMAKE_CURRENT_LIST_DIR}/graph_service_manager.h
    ${CMAKE_CURRENT_LIST_DIR}/input_side_packet_handler.h
    ${CMAKE_CURRENT_LIST_DIR}/input_stream.h
    ${CMAKE_CURRENT_LIST_DIR}/input_stream_handler.h
    ${CMAKE_CURRENT_LIST_DIR}/input_stream_manager.h
    ${CMAKE_CURRENT_LIST_DIR}/input_stream_shard.h
    ${CMAKE_CURRENT_LIST_DIR}/legacy_calculator_support.h
    ${CMAKE_CURRENT_LIST_DIR}/mediapipe_profiling.h
    ${CMAKE_CURRENT_LIST_DIR}/memory_manager.h
    ${CMAKE_CURRENT_LIST_DIR}/output_side_packet.h
    ${CMAKE_CURRENT_LIST_DIR}/output_side_packet_impl.h
    ${CMAKE_CURRENT_LIST_DIR}/output_stream.h
    ${CMAKE_CURRENT_LIST_DIR}/output_stream_handler.h
    ${CMAKE_CURRENT_LIST_DIR}/output_stream_manager.h
    ${CMAKE_CURRENT_LIST_DIR}/output_stream_poller.h
    ${CMAKE_CURRENT_LIST_DIR}/output_stream_shard.h
    ${CMAKE_CURRENT_LIST_DIR}/packet.h
    ${CMAKE_CURRENT_LIST_DIR}/packet_generator.h
    ${CMAKE_CURRENT_LIST_DIR}/packet_generator_graph.h
    ${CMAKE_CURRENT_LIST_DIR}/packet_set.h
    ${CMAKE_CURRENT_LIST_DIR}/packet_type.h
    ${CMAKE_CURRENT_LIST_DIR}/platform_specific_profiling.h
    ${CMAKE_CURRENT_LIST_DIR}/port.h
    ${CMAKE_CURRENT_LIST_DIR}/scheduler.h
    ${CMAKE_CURRENT_LIST_DIR}/scheduler_queue.h
    ${CMAKE_CURRENT_LIST_DIR}/scheduler_shared.h
    ${CMAKE_CURRENT_LIST_DIR}/status_handler.h
    ${CMAKE_CURRENT_LIST_DIR}/subgraph.h
    ${CMAKE_CURRENT_LIST_DIR}/thread_pool_executor.h
    ${CMAKE_CURRENT_LIST_DIR}/timestamp.h
    ${CMAKE_CURRENT_LIST_DIR}/type_map.h
    ${CMAKE_CURRENT_LIST_DIR}/validated_graph_config.h
)
###"//mediapipe/framework/port:disable_opencv": ["MEDIAPIPE_DISABLE_OPENCV=1"]
###"//mediapipe/gpu:disable_gpu": ["MEDIAPIPE_DISABLE_GPU=1"],
###//mediapipe/framework:disable_rtti_and_exceptions": [
###            "MEDIAPIPE_HAS_RTTI=0"

# When --copt=-fno-rtti is set, MEDIAPIPE_HAS_RTTI is cleared in port.h.
# To explicitly clear MEDIAPIPE_HAS_RTTI, compile with:
#   bazel build --define=disable_rtti_and_exceptions=true
#config_setting(
#        name = "disable_rtti_and_exceptions",
#        define_values = {"disable_rtti_and_exceptions": "true"},
#)

target_sources(${PLUGIN_NAME} PRIVATE
               ${FRAMEWORK_SOURCES}
               ${FRAMEWORK_HEADERS}
)
include(${CMAKE_CURRENT_LIST_DIR}/api/build.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/deps/build.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/formats/build.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/port/build.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/profiler/build.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/stream_handler/build.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/tool/build.cmake)
