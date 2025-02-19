include(${CMAKE_CURRENT_LIST_DIR}/subgraphs/build.cmake)

if(HT_ENABLE_GPU)
    file(COPY ${CMAKE_CURRENT_LIST_DIR}/hand_tracking_desktop_live_gpu.pbtxt
         DESTINATION ${CMAKE_BINARY_DIR}/mediapipe
    )
else()
    file(COPY ${CMAKE_CURRENT_LIST_DIR}/hand_tracking_desktop_live.pbtxt
         DESTINATION ${CMAKE_BINARY_DIR}/mediapipe
    )
endif()
