include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

PROTOBUF_GENERATE_OBJ(deps.proto_descriptor)
