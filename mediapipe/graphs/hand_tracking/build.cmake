include(${CMAKE_CURRENT_LIST_DIR}/subgraphs/build.cmake)

install(FILES hand_detection_desktop_live.pbtxt
        DESTINATION shared/mediapipe/graphs/hand_tracking
)