include(${CMAKE_CURRENT_LIST_DIR}/subgraphs/build.cmake)

install(FILES ${CMAKE_CURRENT_LIST_DIR}/hand_tracking_desktop_live.pbtxt
        DESTINATION share/mediapipe/graphs/hand_tracking
)