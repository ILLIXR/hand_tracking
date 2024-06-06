include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

PROTOBUF_GENERATE_OBJ(annotation.rasterization)
PROTOBUF_GENERATE_OBJ_WITH_DEPS(annotation.locus annotation.rasterization)
