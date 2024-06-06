set(PLUGIN_NAME illixr_hand_tracking)
add_library(${PLUGIN_NAME} SHARED)

include(calculators/build.cmake)
include(framework/build.cmake)
include(gpu/build.cmake)
include(graphs/build.cmake)
include(modules/build.cmake)
include(util/build.cmake)

# protobuf
target_link_libraries(${PLUGIN_NAME} PUBLIC
                      calc_utils.annotation_overlay_calculator_proto
                      calc_utils.association_calculator_proto
                      calc_utils.collection_has_min_size_calculator_proto
                      calc_utils.detections_to_rects_calculator_proto
                      calc_utils.detections_to_render_data_calculator_proto
                      calc_utils.labels_to_render_data_calculator
                      calc_utils.landmarks_to_render_data_calculator_proto
                      calc_utils.local_file_contents_calculator_proto
                      calc_utils.non_max_suppression_calculator_proto
                      calc_utils.rect_to_render_data_calculator_proto
                      calc_utils.rect_transformation_calculator_proto
                      calc_utils.thresholding_calculator_proto
                      core.clip_vector_size_calculator_proto
                      core.constant_side_packet_calculator_proto
                      core.flow_limiter_calculator_proto
                      core.gate_calculator_proto
                      core.split_vector_calculator_proto
                      formats.classification_proto
                      formats.classification_proto
                      formats.detection_proto
                      formats.landmark_proto
                      formats.landmark_proto
                      formats.location_data_proto
                      formats.rect_proto
                      framework.calculator_options_proto
                      framework.calculator_proto
                      gpu.gpu_origin_proto
                      internal.callback_packet_calculator_proto
                      tensor.image_to_tensor_calculator_proto
                      tensor.inference_calculator_proto
                      tensor.tensors_to_classification_calculator_proto
                      tensor.tensors_to_detections_calculator_proto
                      tensor.tensors_to_floats_calculator_proto
                      tensor.tensors_to_landmarks_calculator_proto
                      tflite.ssd_anchors_calculator_proto
                      tflite.tflite_custom_op_resolver_calculator_proto
                      util.color_proto
                      util.label_map_proto
                      util.render_data_proto
                      video.opencv_video_encoder_calculator_proto
                      framework.calculator_proto
                      framework.mediapipe_options_proto
                      framework.packet_generator_proto
                      framework.status_handler_proto
                      framework.stream_handler_proto
                      framework.threadpool_executor_proto
                      framework.packet_factory_proto
                      internal.callback_packet_calculator_proto
                      framework.calculator_options_proto
                      tool.field_data_proto
                      tool.packet_generator_wrapper_calculator_proto
                      tool.switch_container_proto
                      formats.image_format_proto
                      formats.matrix_data_proto
                      formats.location_data_proto
                      stream_handler.default_input_stream_handler_proto
                      stream_handler.fixed_size_input_stream_handler_proto


)

if(HT_ENABLE_GPU)
    target_link_libraries(${PLUGIN_NAME} PUBLIC
                          gpu.gl_context_options??
                          GLESv2
                          EGL
    )
    add_compile_options(-layering_check)
endif()
# third party
target_include_directories(${PLUGIN_NAME} PUBLIC

)
target_link_libraries(${PLUGIN_NAME} PUBLIC
                      protobuf::libprotobuf
                      ${absl-cpp_LIBRARIES}
                      tensorflow-lite::tensorflow-lite
                      eigen
                      glog
                      opencv

)