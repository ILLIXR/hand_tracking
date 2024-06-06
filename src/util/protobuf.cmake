include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

PROTOBUF_GENERATE_OBJ(util.color)
PROTOBUF_GENERATE_OBJ_WITH_DEPS(util.render_data util.color)
PROTOBUF_GENERATE_OBJ(util.label_map)
