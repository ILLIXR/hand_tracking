include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

PROTOBUF_GENERATE_OBJ_WITH_DEPS(internal.callback_packet_calculator "framework.calculator;framework.calculator_option")
