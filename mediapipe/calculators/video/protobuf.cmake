include(${CMAKE_SOURCE_DIR}/cmake/protoc_generate_obj.cmake)

protobuf_generate_obj(PROTO_PATH calculators/video OBJ_NAME opencv_video_encoder_calculator)
