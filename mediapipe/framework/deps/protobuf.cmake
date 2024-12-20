include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

protobuf_generate_obj(PROTO_PATH framework/deps OBJ_NAME proto_descriptor)
