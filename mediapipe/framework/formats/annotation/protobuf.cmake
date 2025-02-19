include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

protobuf_generate_obj(PROTO_PATH framework/formats/annotation OBJ_NAME rasterization)
protobuf_generate_obj(PROTO_PATH framework/formats/annotation OBJ_NAME locus)
