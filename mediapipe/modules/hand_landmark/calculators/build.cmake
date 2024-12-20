set(MODULES_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/hand_landmarks_to_rect_calculator.cc
)

target_sources(${PLUGIN_NAME} PRIVATE
               ${MODULES_SOURCES}
)