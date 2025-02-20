function(make_proto_binary)
    set(_singleargs BINARY_NAME FILE_ROOT FILE_BASE_NAME CLASS_NAME)
    set(_multiargs PROTO_LIBRARIES)
    cmake_parse_arguments(make_proto_binary "" "${_singleargs}" "${_multiargs}" "${ARGN}")
    set(SUBGRAPH_CLASS_NAME ${make_proto_binary_CLASS_NAME})
    set(FILE_PATH_NAME  "${make_proto_binary_FILE_ROOT}/${make_proto_binary_FILE_BASE_NAME}")
    set(SUBGRAPH_INC_FILE_PATH ${FILE_PATH_NAME}.inc)
    add_executable(${make_proto_binary_BINARY_NAME}
                   ${CMAKE_SOURCE_DIR}/mediapipe/framework/deps/ret_check.cc
                   ${CMAKE_SOURCE_DIR}/mediapipe/framework/deps/status_builder.cc
                   ${CMAKE_SOURCE_DIR}/mediapipe/framework/deps/status.cc
                   ${CMAKE_SOURCE_DIR}/mediapipe/framework/tool/text_to_binary_graph.cc
                   ${make_proto_binary_PROTO_LIBRARIES}
    )
    target_include_directories(${make_proto_binary_BINARY_NAME} BEFORE PUBLIC
                               ${Protobuf_INCLUDE_DIRS}
    )
    get_target_property(TFL_INCLUDE_DIR tensorflow-lite::tensorflow-lite${TF_POSTFIX} INTERFACE_INCLUDE_DIRECTORIES)
    target_include_directories(${make_proto_binary_BINARY_NAME} PUBLIC
                               ${CMAKE_SOURCE_DIR}
                               ${CMAKE_BINARY_DIR}
                               ${glog_INCLUDE_DIR}
                               ${CMAKE_INSTALL_PREFIX}/include
                               ${TFL_INCLUDE_DIR}/tensorflow
                               ${TFL_INCLUDE_DIR}/tensorflow/lite
                               ${zlib_INCLUDE_DIR}
    )

    target_link_libraries(${make_proto_binary_BINARY_NAME} PUBLIC
                          protobuf::libprotobuf
                          ${glog_LIBRARIES}
                          tensorflow-lite::tensorflow-lite${TF_POSTFIX}
                          ${zlib_LIBRARIES}
                          absl::status
                          absl::absl_log
                          absl::flags_parse
                          gemmlowp::gemmlowp
    )

    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${make_proto_binaryFILE_ROOT})

    add_custom_command(TARGET ${make_proto_binary_BINARY_NAME}
                       POST_BUILD
                       COMMAND ${CMAKE_COMMAND} -E env "LD_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib" ./${make_proto_binary_BINARY_NAME}
                       ARGS --proto_source=${CMAKE_SOURCE_DIR}/mediapipe/${FILE_PATH_NAME}.pbtxt --proto_output=${CMAKE_BINARY_DIR}/${FILE_PATH_NAME}.binarypb
                       COMMENT "Processing protobuf file from mediapipe/${FILE_PATH_NAME}.pbtxt"
                       VERBATIM
                       BYPRODUCTS ${CMAKE_BINARY_DIR}/${FILE_PATH_NAME}.binarypb
    )
    add_custom_command(COMMAND ${CMAKE_COMMAND} -E env "LD_LIBRARY_PATH=${CMAKE_INSTALL_PREFIX}/lib" ${CMAKE_BINARY_DIR}/encode_as_c_string
                       ARGS ${CMAKE_BINARY_DIR}/${FILE_PATH_NAME}.binarypb > ${CMAKE_BINARY_DIR}/${FILE_PATH_NAME}.inc
                       COMMENT "Producing include file from ${FILE_PATH_NAME}.binarypb"
                       VERBATIM
                       OUTPUT ${CMAKE_BINARY_DIR}/${FILE_PATH_NAME}.inc
    )
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/simple_subgraph_template.cc.in
                   ${CMAKE_BINARY_DIR}/${FILE_PATH_NAME}_linked.cc
    )
    add_library(${make_proto_binary_FILE_BASE_NAME}_linked OBJECT
                ${CMAKE_BINARY_DIR}/${FILE_PATH_NAME}_linked.cc
                ${CMAKE_BINARY_DIR}/${FILE_PATH_NAME}.inc
    )
    target_include_directories(${make_proto_binary_FILE_BASE_NAME}_linked PUBLIC
                               ${CMAKE_SOURCE_DIR}
                               ${CMAKE_BINARY_DIR}
    )
    target_link_libraries(${make_proto_binary_FILE_BASE_NAME}_linked PUBLIC
                          absl::statusor
    )
    add_dependencies(${make_proto_binary_FILE_BASE_NAME}_linked
                     ${make_proto_binary_BINARY_NAME}
    )
    target_compile_definitions(${make_proto_binary_FILE_BASE_NAME}_linked PUBLIC
                               "GLOG_DEPRECATED=__attribute__((deprecated))"
                               "GLOG_EXPORT=__attribute__((visibility(\"default\")))"
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
    )
    unset(SUBGRAPH_CLASS_NAME)
    unset(SUBGRAPH_INC_FILE_PATH)

endfunction()
