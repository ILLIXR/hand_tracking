set(OPERATIONS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/landmarks_to_transform_matrix.cc
    ${CMAKE_CURRENT_LIST_DIR}/max_pool_argmax.cc
    ${CMAKE_CURRENT_LIST_DIR}/max_unpooling.cc
    ${CMAKE_CURRENT_LIST_DIR}/resampler.cc
    ${CMAKE_CURRENT_LIST_DIR}/transform_landmarks.cc
    ${CMAKE_CURRENT_LIST_DIR}/transform_tensor_bilinear.cc
    ${CMAKE_CURRENT_LIST_DIR}/transpose_conv_bias.cc
)

set(OPERATIONS_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/landmarks_to_transform_matrix.h
    ${CMAKE_CURRENT_LIST_DIR}/max_pool_argmax.h
    ${CMAKE_CURRENT_LIST_DIR}/max_unpooling.h
    ${CMAKE_CURRENT_LIST_DIR}/resampler.h
    ${CMAKE_CURRENT_LIST_DIR}/transform_landmarks.h
    ${CMAKE_CURRENT_LIST_DIR}/transform_tensor_bilinear.h
    ${CMAKE_CURRENT_LIST_DIR}/transpose_conv_bias.h
)

target_sources(${PLUGIN_NAME} PRIVATE
               ${OPERATIONS_SOURCES}
               ${OPERATIONS_HEADERS}
)