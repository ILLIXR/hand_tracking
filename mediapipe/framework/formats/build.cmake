set(FORMATS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/frame_buffer.cc
    ${CMAKE_CURRENT_LIST_DIR}/image.cc
    ${CMAKE_CURRENT_LIST_DIR}/image_frame.cc
    ${CMAKE_CURRENT_LIST_DIR}/image_frame_opencv.cc
    ${CMAKE_CURRENT_LIST_DIR}/image_opencv.cc
    ${CMAKE_CURRENT_LIST_DIR}/location.cc
    ${CMAKE_CURRENT_LIST_DIR}/matrix.cc
    ${CMAKE_CURRENT_LIST_DIR}/tensor.cc
    ${CMAKE_CURRENT_LIST_DIR}/tensor_ahwb.cc
)
set(FORMATS_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/frame_buffer.h
    ${CMAKE_CURRENT_LIST_DIR}/image.h
    ${CMAKE_CURRENT_LIST_DIR}/image_frame.h
    ${CMAKE_CURRENT_LIST_DIR}/image_frame_opencv.h
    ${CMAKE_CURRENT_LIST_DIR}/image_opencv.h
    ${CMAKE_CURRENT_LIST_DIR}/location.h
    ${CMAKE_CURRENT_LIST_DIR}/matrix.h
    ${CMAKE_CURRENT_LIST_DIR}/tensor.h
    ${CMAKE_CURRENT_LIST_DIR}/tensor/internal.h
    ${CMAKE_CURRENT_LIST_DIR}/video_stream_header.h

)

target_sources(${PLUGIN_NAME} PRIVATE
               ${FORMATS_SOURCES}
               ${FORMATS_HEADERS}
)
