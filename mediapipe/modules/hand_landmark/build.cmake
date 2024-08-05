include(${CMAKE_SOURCE_DIR}/cmake/make_pb_binary.cmake)

set(HLLR_LIBRARIES
    $<TARGET_OBJECTS:calculators.internal.callback_packet_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.rect_transformation_calculator_proto>
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
    $<TARGET_OBJECTS:framework.formats.landmark_proto>
    $<TARGET_OBJECTS:framework.formats.rect_proto>
    $<TARGET_OBJECTS:framework.stream_handler.default_input_stream_handler_proto>
    $<TARGET_OBJECTS:framework.tool.calculator_graph_template_proto>
    $<TARGET_OBJECTS:framework.tool.field_data_proto>
    $<TARGET_OBJECTS:framework.tool.packet_generator_wrapper_calculator_proto>

)

make_proto_binary(BINARY_NAME hand_landmark_landmarks_to_roi_graph_text_to_binary_graph
                  FILE_ROOT modules/hand_landmark
                  FILE_BASE_NAME hand_landmark_landmarks_to_roi
                  CLASS_NAME HandLandmarkLandmarksToRoi
                  PROTO_LIBRARIES ${HLLR_LIBRARIES}
)

set(HLGT_LIBRARIES
    $<TARGET_OBJECTS:calculators.core.constant_side_packet_calculator_proto>
    $<TARGET_OBJECTS:calculators.core.gate_calculator_proto>
    $<TARGET_OBJECTS:calculators.core.split_vector_calculator_proto>
    $<TARGET_OBJECTS:calculators.internal.callback_packet_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.image_to_tensor_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.inference_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.tensors_to_classification_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.tensors_to_floats_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.tensors_to_landmarks_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.landmark_projection_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.local_file_contents_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.thresholding_calculator_proto>
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
    $<TARGET_OBJECTS:framework.formats.time_series_header_proto>
    $<TARGET_OBJECTS:framework.formats.annotation.locus_proto>
    $<TARGET_OBJECTS:framework.formats.annotation.rasterization_proto>
    $<TARGET_OBJECTS:framework.stream_handler.default_input_stream_handler_proto>
    $<TARGET_OBJECTS:framework.stream_handler.fixed_size_input_stream_handler_proto>
    $<TARGET_OBJECTS:framework.tool.calculator_graph_template_proto>
    $<TARGET_OBJECTS:framework.tool.field_data_proto>
    $<TARGET_OBJECTS:framework.tool.packet_generator_wrapper_calculator_proto>
    $<TARGET_OBJECTS:framework.tool.switch_container_proto>
    $<TARGET_OBJECTS:gpu.gpu_origin_proto>
    $<TARGET_OBJECTS:util.color_proto>
    $<TARGET_OBJECTS:util.label_map_proto>
    $<TARGET_OBJECTS:util.render_data_proto>

)

if(HT_ENABLE_GPU)
    set(NAME_POST gpu)
    set(CLASS_POST Gpu)
else()
    set(NAME_POST cpu)
    set(CLASS_POST Cpu)
endif()

make_proto_binary(BINARY_NAME hand_landmark_graph_text_to_binary_graph
                  FILE_ROOT modules/hand_landmark
                  FILE_BASE_NAME hand_landmark_${NAME_POST}
                  CLASS_NAME HandLandmark${CLASS_POST}
                  PROTO_LIBRARIES ${HLGT_LIBRARIES})

set(HLML_LIBRARIES
    $<TARGET_OBJECTS:calculators.core.constant_side_packet_calculator_proto>
    $<TARGET_OBJECTS:calculators.internal.callback_packet_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.local_file_contents_calculator_proto>
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
    $<TARGET_OBJECTS:framework.formats.image_format_proto>
    $<TARGET_OBJECTS:framework.formats.landmark_proto>
    $<TARGET_OBJECTS:framework.formats.matrix_data_proto>
    $<TARGET_OBJECTS:framework.formats.time_series_header_proto>
    $<TARGET_OBJECTS:framework.stream_handler.default_input_stream_handler_proto>
    $<TARGET_OBJECTS:framework.tool.calculator_graph_template_proto>
    $<TARGET_OBJECTS:framework.tool.field_data_proto>
    $<TARGET_OBJECTS:framework.tool.packet_generator_wrapper_calculator_proto>
    $<TARGET_OBJECTS:framework.tool.switch_container_proto>

)

make_proto_binary(BINARY_NAME hand_landmark_model_loader_graph_text_to_binary_graph
                  FILE_ROOT modules/hand_landmark
                  FILE_BASE_NAME hand_landmark_model_loader
                  CLASS_NAME HandLandmarkModelLoader
                  PROTO_LIBRARIES ${HLML_LIBRARIES})

set(HLTG_LIBRARIES
    $<TARGET_OBJECTS:calculators.core.clip_vector_size_calculator_proto>
    $<TARGET_OBJECTS:calculators.core.constant_side_packet_calculator_proto>
    $<TARGET_OBJECTS:calculators.core.flow_limiter_calculator_proto>
    $<TARGET_OBJECTS:calculators.core.gate_calculator_proto>
    $<TARGET_OBJECTS:calculators.core.split_vector_calculator_proto>
    $<TARGET_OBJECTS:calculators.internal.callback_packet_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.image_to_tensor_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.inference_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.tensors_to_classification_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.tensors_to_detections_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.tensors_to_floats_calculator_proto>
    $<TARGET_OBJECTS:calculators.tensor.tensors_to_landmarks_calculator_proto>
    $<TARGET_OBJECTS:calculators.tflite.ssd_anchors_calculator_proto>
    $<TARGET_OBJECTS:calculators.tflite.tflite_custom_op_resolver_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.association_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.collection_has_min_size_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.detections_to_rects_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.landmark_projection_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.local_file_contents_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.non_max_suppression_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.rect_transformation_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.thresholding_calculator_proto>
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
    $<TARGET_OBJECTS:framework.formats.time_series_header_proto>
    $<TARGET_OBJECTS:framework.formats.annotation.locus_proto>
    $<TARGET_OBJECTS:framework.formats.annotation.rasterization_proto>
    $<TARGET_OBJECTS:framework.formats.object_detection.anchor_proto>
    $<TARGET_OBJECTS:framework.stream_handler.default_input_stream_handler_proto>
    $<TARGET_OBJECTS:framework.stream_handler.fixed_size_input_stream_handler_proto>
    $<TARGET_OBJECTS:framework.tool.calculator_graph_template_proto>
    $<TARGET_OBJECTS:framework.tool.field_data_proto>
    $<TARGET_OBJECTS:framework.tool.packet_generator_wrapper_calculator_proto>
    $<TARGET_OBJECTS:framework.tool.switch_container_proto>
    $<TARGET_OBJECTS:gpu.gpu_origin_proto>
    $<TARGET_OBJECTS:util.color_proto>
    $<TARGET_OBJECTS:util.label_map_proto>
    $<TARGET_OBJECTS:util.render_data_proto>
)

make_proto_binary(BINARY_NAME hand_landmark_tracking_graph_text_to_binary_graph
                  FILE_ROOT modules/hand_landmark
                  FILE_BASE_NAME hand_landmark_tracking_${NAME_POST}
                  CLASS_NAME HandLandmarkTracking${CLASS_POST}
                  PROTO_LIBRARIES ${HLTG_LIBRARIES})

set(PDDR_LIBRARIES
    $<TARGET_OBJECTS:calculators.internal.callback_packet_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.detections_to_rects_calculator_proto>
    $<TARGET_OBJECTS:calculators.util.rect_transformation_calculator_proto>
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
    $<TARGET_OBJECTS:framework.formats.detection_proto>
    $<TARGET_OBJECTS:framework.formats.location_data_proto>
    $<TARGET_OBJECTS:framework.formats.rect_proto>
    $<TARGET_OBJECTS:framework.formats.annotation.rasterization_proto>
    $<TARGET_OBJECTS:framework.stream_handler.default_input_stream_handler_proto>
    $<TARGET_OBJECTS:framework.tool.calculator_graph_template_proto>
    $<TARGET_OBJECTS:framework.tool.field_data_proto>
    $<TARGET_OBJECTS:framework.tool.packet_generator_wrapper_calculator_proto>
)

make_proto_binary(BINARY_NAME palm_detection_detection_to_roi_graph_text_to_binary_graph
                  FILE_ROOT modules/hand_landmark
                  FILE_BASE_NAME palm_detection_detection_to_roi
                  CLASS_NAME PalmDetectionDetectionToRoi
                  PROTO_LIBRARIES ${PDDR_LIBRARIES})

include(${CMAKE_CURRENT_LIST_DIR}/calculators/build.cmake)
