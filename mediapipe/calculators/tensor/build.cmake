set(TENSOR_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_utils.cc
    ${CMAKE_CURRENT_LIST_DIR}/inference_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/inference_calculator_cpu.cc
    ${CMAKE_CURRENT_LIST_DIR}/inference_calculator_utils.cc
    ${CMAKE_CURRENT_LIST_DIR}/inference_feedback_manager.cc
    ${CMAKE_CURRENT_LIST_DIR}/inference_interpreter_delegate_runner.cc
    ${CMAKE_CURRENT_LIST_DIR}/inference_io_mapper.cc
    ${CMAKE_CURRENT_LIST_DIR}/tensor_span.cc
    ${CMAKE_CURRENT_LIST_DIR}/tensors_to_classification_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/tensors_to_detections_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/tensors_to_floats_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/tensors_to_landmarks_calculator.cc
)

set(TENSOR_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_converter.h
    ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_converter_gl_buffer.h
    ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_converter_gl_texture.h
    ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_utils.h
    ${CMAKE_CURRENT_LIST_DIR}/inference_calculator.h
    ${CMAKE_CURRENT_LIST_DIR}/inference_calculator_utils.h
    ${CMAKE_CURRENT_LIST_DIR}/inference_feedback_manager.h
    ${CMAKE_CURRENT_LIST_DIR}/inference_io_mapper.h
    ${CMAKE_CURRENT_LIST_DIR}/inference_runner.h
    ${CMAKE_CURRENT_LIST_DIR}/inference_interpreter_delegate_runner.h
    ${CMAKE_CURRENT_LIST_DIR}/tensor_span.h
    ${CMAKE_CURRENT_LIST_DIR}/tflite_delegate_ptr.h
)

target_sources(${PLUGIN_NAME} PRIVATE
               ${TENSOR_SOURCES}
               ${TENSOR_HEADERS}
)

if(HT_ENABLE_GPU)
    target_sources(${PLUGIN_NAME} PRIVATE
                   ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_converter_gl_buffer.cc
                   ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_converter_gl_buffer.h
                   ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_converter_gl_utils.cc
                   ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_converter_gl_utils.h
    )
endif()

if(COMPUTE_SHADER_AVAILABLE)
    target_sources(${PLUGIN_NAME} PRIVATE
                   ${CMAKE_CURRENT_LIST_DIR}/inference_calculator_gl.cc
                   ${CMAKE_CURRENT_LIST_DIR}/inference_calculator_gl_advanced.cc
    )
endif()

if(ENABLE_OPENCV)
    target_sources(${PLUGIN_NAME} PRIVATE
                   ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_converter_opencv.cc
                   ${CMAKE_CURRENT_LIST_DIR}/image_to_tensor_converter_opencv.h
    )
endif()