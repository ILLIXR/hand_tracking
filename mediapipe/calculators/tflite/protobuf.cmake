include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

protobuf_generate_obj(PROTO_PATH calculators/tflite OBJ_NAME ssd_anchors_calculator)
protobuf_generate_obj(PROTO_PATH calculators/tflite OBJ_NAME tflite_custom_op_resolver_calculator)
