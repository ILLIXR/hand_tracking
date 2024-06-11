include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

protobuf_generate_obj(PROTO_PATH framework OBJ_NAME calculator_options DESCRIPTORS)
protobuf_generate_obj(PROTO_PATH framework OBJ_NAME mediapipe_options DESCRIPTORS)
protobuf_generate_obj(PROTO_PATH framework OBJ_NAME packet_factory DESCRIPTORS)
protobuf_generate_obj(PROTO_PATH framework OBJ_NAME packet_generator DESCRIPTORS)
protobuf_generate_obj(PROTO_PATH framework OBJ_NAME status_handler DESCRIPTORS)
protobuf_generate_obj(PROTO_PATH framework OBJ_NAME stream_handler DESCRIPTORS)
protobuf_generate_obj(PROTO_PATH framework OBJ_NAME thread_pool_executor)

protobuf_generate_obj(PROTO_PATH framework OBJ_NAME calculator DESCRIPTORS)

protobuf_generate_obj(PROTO_PATH framework OBJ_NAME calculator_profile)

include(src/framework/deps/protobuf.cmake)
include(src/framework/tool/protobuf.cmake)
include(src/framework/formats/object_detection/protobuf.cmake)
include(src/framework/formats/annotation/protobuf.cmake)
include(src/framework/formats/protobuf.cmake)
include(src/framework/stream_handler/protobuf.cmake)
