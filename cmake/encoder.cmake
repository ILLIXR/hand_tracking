
add_executable(encode_as_c_string ${CMAKE_SOURCE_DIR}/src/framework/tool/encode_as_c_string.cc)
target_include_directories(encode_as_c_string PUBLIC
                           ${absl-cpp_INCLUDE_DIR}
)
target_link_libraries(encode_as_c_string PUBLIC
                      ${absl-cpp_LIBRARIES}
)
