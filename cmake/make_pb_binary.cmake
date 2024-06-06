function(MAKE_PB_BINARY BINARY_NAME)
    add_executable(${BINARY_NAME}
                   ${CMAKE_SOURCE_DIR}/src/framework/deps/ret_check.cc
                   ${CMAKE_SOURCE_DIR}/src/framework/deps/status_builder.cc
                   ${CMAKE_SOURCE_DIR}/src/framework/deps/status.cc
                   ${CMAKE_SOURCE_DIR}/src/framework/tool/text_to_binary_graph.cc
    )
    target_include_directories(${BINARY_NAME} PUBLIC
                               ${Protobuf_INCLUDE_DIR}
                               ${glog_INCLUDE_DIR}
                               ${tensorflow-lite_INCLUDE_DIR}
                               ${zlib_INCLUDE_DIR}
                               ${absl-cpp_INCLUDE_DIR}
    )
    target_link_libraries(${BINARY_NAME} PUBLIC
                          protobuf::libprotobuf
                          ${glog_LIBRARIES}
                          ${tensorflow-lite_LIBRARIES}
                          ${zlib_LIBRARIES}
                          ${absl-cpp_LIBRARIES}
    )
endfunction()

function(MAKE_LINKED CMD FILE_ROOT FILE_BASE_NAME CLASS_NAME)
    set(SUBGRAPH_CLASS_NAME ${CLASS_NAME})
    set(SUBGRAPH_INC_FILE_PATH ${FILE_ROOT}/${FILE_BASE_NAME}.inc)

    add_custom_target(${CMD}_output
                      COMMAND ${CMD}
                      "--proto_source=${CMAKE_SOURCE_DIR}/${FILE_ROOT}/${FILE_BASE_NAME}.pbtxt --proto_output=${CMAKE_BINARY_DIR}/${FILE_ROOT}/${FILE_BASE_NAME}.binarypb"
                      DEPENDS ${CMD}
                      BYPRODUCTS ${FILE_BASE_NAME}.binarypb
    )

    add_custom_target(encode_${FILE_BASE_NAME}
                      COMMAND encode_as_c_string "${CMAKE_BINARY_DIR}/${FILE_ROOT}/${FILE_BASE_NAME}.binarypb > ${CMAKE_BINARY_DIR}/${SUBGRAPH_INC_FILE_PATH}"
                      DEPENDS encode_as_c_string ${CMD}_output
                      BYPRODUCTS ${FILE_BASE_NAME}.inc
    )

    configure_file(${CMAKE_SOURCE_DIR}/simple_subgraph_template.cc.in
                   ${CMAKE_BINARY_DIR}/${FILE_ROOT}/${FILE_BASE_NAME}_linked.cc
    )

    add_library(${FILE_BASE_NAME}_linked OBJECT
                ${CMAKE_BINARY_DIR}/${FILE_ROOT}/${FILE_BASE_NAME}_linked.cc
    )
    add_dependencies(${FILE_BASE_NAME}_linked encode_${FILE_BASE_NAME})
    target_compile_definitions(${FILE_BASE_NAME}_linked PUBLIC
                               GLOG_DEPRECATED=__attribute__((deprecated))
                               GLOG_EXPORT=__attribute__((visibility("default")))
                               MEDIAPIPE_PROFILER_AVAILABLE
                               TFLITE_KERNEL_USE_XNNPACK
                               XNNPACK_DELEGATE_ENABLE_QS8=1
                               XNNPACK_DELEGATE_ENABLE_QU8=1
                               PTHREADPOOL_NO_DEPRECATED_API
                               EIGEN_NEON_GEBP_NR=4
                               EIGEN_MAX_ALIGN_BYTES=64
                               EIGEN_ALLOW_UNALIGNED_SCALARS
                               EIGEN_USE_AVX512_GEMM_KERNELS=0
                               FC_4BIT_SSE
                               EIGEN_ALTIVEC_USE_CUSTOM_PACK=0
                               XNN_LOG_LEVEL=0
                               XNN_ENABLE_GEMM_M_SPECIALIZATION=1
                               XNN_ENABLE_JIT=0
                               XNN_ENABLE_ASSEMBLY=1
                               XNN_ENABLE_AVX512AMX=1
                               XNN_ENABLE_AVXVNNI=1
                               XNN_ENABLE_DWCONV_MULTIPASS=1
                               XNN_ENABLE_ARM_FP16_SCALAR=0
                               XNN_ENABLE_ARM_FP16_VECTOR=0
                               XNN_ENABLE_ARM_BF16=0
                               XNN_ENABLE_ARM_DOTPROD=0
                               XNN_ENABLE_ARM_I8MM=0
                               XNN_ENABLE_RISCV_FP16_VECTOR=0
                               XNN_ENABLE_AVX512VNNIGFNI=1
                               XNN_ENABLE_SPARSE=1
                               XNN_ENABLE_MEMOPT=1
                               TFLITE_BUILD_WITH_XNNPACK_DELEGATE
                               __DATE__="redacted"
                               __TIMESTAMP__="redacted"
                               __TIME__="redacted"
    )
    unset(SUBGRAPH_CLASS_NAME)
    unset(SUBGRAPH_INC_FILE_PATH)
endfunction()