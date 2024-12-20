include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

protobuf_generate_obj(PROTO_PATH gpu OBJ_NAME gl_context_options)
protobuf_generate_obj(PROTO_PATH gpu OBJ_NAME gpu_origin)
