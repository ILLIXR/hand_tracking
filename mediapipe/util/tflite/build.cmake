include(${CMAKE_CURRENT_LIST_DIR}/operations/build.cmake)

set(TFLITE_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/error_reporter.cc
    ${CMAKE_CURRENT_LIST_DIR}/op_resolver.cc
    ${CMAKE_CURRENT_LIST_DIR}/tflite_model_loader.cc
    ${CMAKE_CURRENT_LIST_DIR}/tflite_signature_reader.cc
    ${CMAKE_CURRENT_LIST_DIR}/utils.cc
)

set(TFLITE_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/error_reporter.h
    ${CMAKE_CURRENT_LIST_DIR}/op_resolver.h
    ${CMAKE_CURRENT_LIST_DIR}/tflite_model_loader.h
    ${CMAKE_CURRENT_LIST_DIR}/tflite_signature_reader.h
    ${CMAKE_CURRENT_LIST_DIR}/utils.h
)

if(RUN_ON_GPU)
    list(APPEND TFLITE_HEADERS ${CMAKE_CURRENT_LIST_DIR}/tflite_gpu_runner.cc ${CMAKE_CURRENT_LIST_DIR}/tflite_gpu_runner.h)
else()
    list(APPEND TFLITE_HEADERS ${CMAKE_CURRENT_LIST_DIR}/cpu_op_resolver.cc ${CMAKE_CURRENT_LIST_DIR}/cpu_op_resolver.h)
endif()

target_sources(${PLUGIN_NAME} PRIVATE
               ${TFLITE_SOURCES}
               ${TFLITE_HEADERS}
)
