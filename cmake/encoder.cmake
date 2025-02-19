
add_executable(encode_as_c_string ${CMAKE_SOURCE_DIR}/mediapipe/framework/tool/encode_as_c_string.cc)
#target_include_directories(encode_as_c_string PUBLIC
#                           ${absl_INCLUDE_DIR}
#)
target_link_libraries(encode_as_c_string PUBLIC
                      absl::strings
)
