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

include(mediapipe/framework/deps/protobuf.cmake)
include(mediapipe/framework/tool/protobuf.cmake)
include(mediapipe/framework/formats/object_detection/protobuf.cmake)
include(mediapipe/framework/formats/annotation/protobuf.cmake)
include(mediapipe/framework/formats/protobuf.cmake)
include(mediapipe/framework/stream_handler/protobuf.cmake)
