include(${CMAKE_SOURCE_DIR}/cmake/make_pb_binary.cmake)

set(PDML_PROTO_LIBRARIES
    $<TARGET_OBJECTS:calculators.util.local_file_contents_calculator_proto>
    $<TARGET_OBJECTS:calculators.core.constant_side_packet_calculator_proto>
    $<TARGET_OBJECTS:framework.deps.proto_descriptor_proto>
    $<TARGET_OBJECTS:framework.formats.classification_proto>
    $<TARGET_OBJECTS:framework.formats.image_format_proto>
    $<TARGET_OBJECTS:framework.formats.landmark_proto>
    $<TARGET_OBJECTS:framework.formats.matrix_data_proto>
    $<TARGET_OBJECTS:framework.formats.time_series_header_proto>
    $<TARGET_OBJECTS:framework.calculator_proto>
    $<TARGET_OBJECTS:framework.calculator_options_proto>
    $<TARGET_OBJECTS:framework.calculator_profile_proto>
    $<TARGET_OBJECTS:framework.mediapipe_options_proto>
    $<TARGET_OBJECTS:framework.packet_factory_proto>
    $<TARGET_OBJECTS:framework.packet_generator_proto>
    $<TARGET_OBJECTS:framework.status_handler_proto>
    $<TARGET_OBJECTS:framework.stream_handler_proto>
    $<TARGET_OBJECTS:framework.thread_pool_executor_proto>
    $<TARGET_OBJECTS:calculators.internal.callback_packet_calculator_proto>
    $<TARGET_OBJECTS:framework.stream_handler.default_input_stream_handler_proto>
    $<TARGET_OBJECTS:framework.tool.calculator_graph_template_proto>
    $<TARGET_OBJECTS:framework.tool.field_data_proto>
    $<TARGET_OBJECTS:framework.tool.packet_generator_wrapper_calculator_proto>
    $<TARGET_OBJECTS:framework.tool.switch_container_proto>
)

make_proto_binary(BINARY_NAME palm_detection_model_loader_graph_text_to_binary_graph
                  FILE_ROOT modules/palm_detection
                  FILE_BASE_NAME palm_detection_model_loader
                  CLASS_NAME PalmDetectionModelLoader
                  PROTO_LIBRARIES ${PDML_PROTO_LIBRARIES})

set(PDGT_LIBRARIES
    $<TARGET_OBJECTS:calculators.tensor.image_to_tensor_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.inference_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.tensors_to_detections_calculator_proto>
    $<TARGET_OBJECTS:calculators.tflite.ssd_anchors_calculator_proto>
    $<TARGET_OBJECTS:calculators.tflite.tflite_custom_op_resolver_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.non_max_suppression_calculator_proto>
    $<TARGET_OBJECTS:framework.calculator_proto>
    $<TARGET_OBJECTS:framework.calculator_options_proto>
    $<TARGET_OBJECTS:gpu.gpu_origin_proto>
    $<TARGET_OBJECTS:framework.formats.object_detection.anchor_proto>
    $<TARGET_OBJECTS:framework.packet_generator_proto>
    $<TARGET_OBJECTS:framework.status_handler_proto>
    $<TARGET_OBJECTS:framework.mediapipe_options_proto>
    $<TARGET_OBJECTS:framework.stream_handler_proto>
    $<TARGET_OBJECTS:framework.packet_factory_proto>
)

if(HT_ENABLE_GPU)
    set(NAME_POST gpu)
    set(CLASS_POST Gpu)
else()
    set(NAME_POST cpu)
    set(CLASS_POST Cpu)
endif()

make_proto_binary(BINARY_NAME palm_detection_graph_text_to_binary_graph
                  FILE_ROOT modules/palm_detection
                  FILE_BASE_NAME palm_detection_${NAME_POST}
                  CLASS_NAME PalmDetection${CLASS_POST}
                  PROTO_LIBRARIES ${PDGT_LIBRARIES})
