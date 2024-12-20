include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

protobuf_generate_obj(PROTO_PATH util OBJ_NAME color)
protobuf_generate_obj(PROTO_PATH util OBJ_NAME render_data)
protobuf_generate_obj(PROTO_PATH util OBJ_NAME label_map)
