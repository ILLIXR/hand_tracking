include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

PROTOBUF_GENERATE_OBJ(framework.calculator_options TRUE)
PROTOBUF_GENERATE_OBJ(framework.mediapipe_options TRUE)
PROTOBUF_GENERATE_OBJ(framework.packet_factory TRUE)
PROTOBUF_GENERATE_OBJ(framework.packet_generator TRUE)
PROTOBUF_GENERATE_OBJWITH_DEPS(framework.status_handler framework.mediapipe_options TRUE)
PROTOBUF_GENERATE_OBJWITH_DEPS(framework.stream_handler framework.mediapipe_options TRUE)
PROTOBUF_GENERATE_OBJWITH_DEPS(framework.thread_pool_executor framework.mediapipe_options)

PROTOBUF_GENERATE_OBJ_WITH_DEPS(framework.calculator "framework.calculator_options;framework.mediapipe_options;framework.packet_factory;framework.packet_generator;framework.status_handler;framework.stream_handler" TRUE)

PROTOBUF_GENERATE_OBJ_WITH_DEPS(framework.calculator_profile "framework.calculator;framework.calculator_options")

include(deps/protobuf.cmake)
include(tool/protobuf.cmake)
include(formats/object_detection/protobuf.cmake)
include(formats/annotation/protobuf.cmake)
include(formats/protobuf.cmake)
include(stream_handler/protobuf.cmake)
