add_executable(message_type_util
               ${CMAKE_SOURCE_DIR}/mediapipe/framework/tool/message_type_util.cc
               ${CMAKE_SOURCE_DIR}/mediapipe/framework/deps/file_helpers.h
               ${CMAKE_SOURCE_DIR}/mediapipe/framework/deps/file_helpers.cc
               ${CMAKE_SOURCE_DIR}/mediapipe/framework/deps/status.h
               ${CMAKE_SOURCE_DIR}/mediapipe/framework/deps/status.cc
               ${CMAKE_SOURCE_DIR}/mediapipe/framework/deps/status_builder.h
               ${CMAKE_SOURCE_DIR}/mediapipe/framework/deps/status_builder.cc
               ${CMAKE_SOURCE_DIR}/mediapipe/framework/deps/file_path.h
               ${CMAKE_SOURCE_DIR}/mediapipe/framework/deps/file_path.cc
               $<TARGET_OBJECTS:framework.calculator_options_proto>
               $<TARGET_OBJECTS:framework.calculator_proto>
               $<TARGET_OBJECTS:framework.packet_generator_proto>
               $<TARGET_OBJECTS:framework.mediapipe_options_proto>
               $<TARGET_OBJECTS:framework.stream_handler_proto>
               $<TARGET_OBJECTS:framework.packet_factory_proto>
               $<TARGET_OBJECTS:framework.status_handler_proto>
)

target_include_directories(message_type_util PUBLIC
                           ${glog_INCLUDEDIR}
                           ${ZLIB_INCLUDE_DIR}
                           ${gflags_INCLUDE_DIR}
                           ${Protobuf_INCLUDE_DIRS}
                           ${CMAKE_SOURCE_DIR}

)
target_link_libraries(message_type_util PUBLIC
                      ${Protobuf_LIBRARIES}
                      ${gflags_LIBRARIES}
                      ${glog_LIBRARIES}
                      ${OpenCV_LIBRARIES}
                      ${ZLIB_LIBRARIES}
                      absl::flags
                      absl::log
                      absl::strings
                      absl::flags_parse
                      absl::status
)