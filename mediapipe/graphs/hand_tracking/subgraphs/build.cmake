include(${CMAKE_SOURCE_DIR}/cmake/make_pb_binary.cmake)

set(HRGT_LIBRARIES
    $<TARGET_OBJECTS:calculators.core.gate_calculator_proto>
    $<TARGET_OBJECTS:calculators.core.split_vector_calculator_proto>
    $<TARGET_OBJECTS:calculators.internal.callback_packet_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.annotation_overlay_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.collection_has_min_size_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.detections_to_render_data_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.labels_to_render_data_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.landmarks_to_render_data_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.rect_to_render_data_calculator_proto>
    $<TARGET_OBJECTS:framework.calculator_proto>
    $<TARGET_OBJECTS:framework.calculator_options_proto>
    $<TARGET_OBJECTS:framework.calculator_profile_proto>
    $<TARGET_OBJECTS:framework.mediapipe_options_proto>
    $<TARGET_OBJECTS:framework.packet_factory_proto>
    $<TARGET_OBJECTS:framework.packet_generator_proto>
    $<TARGET_OBJECTS:framework.status_handler_proto>
    $<TARGET_OBJECTS:framework.stream_handler_proto>
    $<TARGET_OBJECTS:framework.thread_pool_executor_proto>
    $<TARGET_OBJECTS:framework.deps.proto_descriptor_proto>
    $<TARGET_OBJECTS:framework.formats.classification_proto>
    $<TARGET_OBJECTS:framework.formats.detection_proto>
    $<TARGET_OBJECTS:framework.formats.image_format_proto>
    $<TARGET_OBJECTS:framework.formats.landmark_proto>
    $<TARGET_OBJECTS:framework.formats.location_data_proto>
    $<TARGET_OBJECTS:framework.formats.matrix_data_proto>
    $<TARGET_OBJECTS:framework.formats.rect_proto>
    $<TARGET_OBJECTS:framework.formats.annotation.rasterization_proto>
    $<TARGET_OBJECTS:framework.stream_handler.default_input_stream_handler_proto>
    $<TARGET_OBJECTS:framework.tool.calculator_graph_template_proto>
    $<TARGET_OBJECTS:framework.tool.field_data_proto>
    $<TARGET_OBJECTS:framework.tool.packet_generator_wrapper_calculator_proto>
    $<TARGET_OBJECTS:util.color_proto>
    $<TARGET_OBJECTS:util.render_data_proto>)

if(HT_ENABLE_GPU)
    set(NAME_POST gpu)
    set(CLASS_POST Gpu)
else()
    set(NAME_POST cpu)
    set(CLASS_POST Cpu)
endif()


make_proto_binary(BINARY_NAME hand_renderer_graph_text_to_binary_graph
                  FILE_ROOT graphs/hand_tracking/subgraphs
                  FILE_BASE_NAME hand_renderer_${NAME_POST}
                  CLASS_NAME HandRendererSubgraph
                  PROTO_LIBRARIES ${HRGT_LIBRARIES})
