include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

protobuf_generate_obj(PROTO_PATH calculators/tensor OBJ_NAME image_to_tensor_calculator)
protobuf_generate_obj(PROTO_PATH calculators/tensor OBJ_NAME inference_calculator DESCRIPTORS)
protobuf_generate_obj(PROTO_PATH calculators/tensor OBJ_NAME tensors_to_classification_calculator)
protobuf_generate_obj(PROTO_PATH calculators/tensor OBJ_NAME tensors_to_floats_calculator)
protobuf_generate_obj(PROTO_PATH calculators/tensor OBJ_NAME tensors_to_landmarks_calculator)
protobuf_generate_obj(PROTO_PATH calculators/tensor OBJ_NAME tensors_to_detections_calculator)
