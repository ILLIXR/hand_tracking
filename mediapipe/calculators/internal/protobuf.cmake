include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

protobuf_generate_obj(PROTO_PATH calculators/internal OBJ_NAME callback_packet_calculator)
