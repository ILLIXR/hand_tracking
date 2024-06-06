add_executable(message_type_util
               ${CMAKE_SOURCE_DIR}/src/framework/tool/message_type_util.cc
               ${CMAKE_SOURCE_DIR}/src/framework/deps/file_helpers.h
               ${CMAKE_SOURCE_DIR}/src/framework/deps/file_helpers.cc
               ${CMAKE_SOURCE_DIR}/src/framework/deps/status.h
               ${CMAKE_SOURCE_DIR}/src/framework/deps/status.cc
               ${CMAKE_SOURCE_DIR}/src/framework/deps/status_builder.h
               ${CMAKE_SOURCE_DIR}/src/framework/deps/status_builder.cc
               ${CMAKE_SOURCE_DIR}/src/framework/deps/file_path.h
               ${CMAKE_SOURCE_DIR}/src/framework/deps/file_path.cc
)

target_link_libraries(message_type_util PUBLIC
                      protobuf::protobuf
                      zlib
                      absl-cpp
                      glog
                      gflags
)