include(${CMAKE_CURRENT_LIST_DIR}/subgraphs/build.cmake)

if(HT_ENABLE_GPU)
    install(FILES ${CMAKE_CURRENT_LIST_DIR}/hand_tracking_desktop_live_gpu.pbtxt
            DESTINATION share/mediapipe/graphs/hand_tracking
    )
else()
    install(FILES ${CMAKE_CURRENT_LIST_DIR}/hand_tracking_desktop_live.pbtxt
            DESTINATION share/mediapipe/graphs/hand_tracking
    )
endif()