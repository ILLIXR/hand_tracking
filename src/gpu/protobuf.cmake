include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

PROTOBUF_GENERATE_OBJ(gpu.gl_context_options "framework.calculator_options;framework.calculator")
PROTOBUF_GENERATE_OBJ(gpu.gpu_origin)
