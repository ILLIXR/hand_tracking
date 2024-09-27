include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME annotation_overlay_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME collection_has_min_size_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME detections_to_render_data_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME labels_to_render_data_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME landmarks_to_render_data_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME rect_to_render_data_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME local_file_contents_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME rect_transformation_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME detections_to_rects_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME association_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME non_max_suppression_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME thresholding_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME landmark_projection_calculator)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME illixr_data)
protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME render_and_points)
if (HT_ENABLE_GPU)
    protobuf_generate_obj(PROTO_PATH calculators/util OBJ_NAME image_data)
endif()

