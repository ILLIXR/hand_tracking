set(UTIL_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/annotation_overlay_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/association_norm_rect_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/collection_has_min_size_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/detection_letterbox_removal_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/detections_to_rects_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/detections_to_render_data_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/filter_collection_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/illixr_output_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/labels_to_render_data_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/landmark_letterbox_removal_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/landmark_projection_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/landmarks_to_render_data_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/local_file_contents_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/non_max_suppression_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/rect_to_render_data_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/rect_transformation_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/thresholding_calculator.cc
    ${CMAKE_CURRENT_LIST_DIR}/world_landmark_projection_calculator.cc
)

set(UTIL_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/association_calculator.h
    ${CMAKE_CURRENT_LIST_DIR}/collection_has_min_size_calculator.h
    ${CMAKE_CURRENT_LIST_DIR}/detections_to_rects_calculator.h
    ${CMAKE_CURRENT_LIST_DIR}/filter_collection_calculator.h
    ${CMAKE_CURRENT_LIST_DIR}/landmarks_to_render_data_calculator.h
    ${CMAKE_CURRENT_LIST_DIR}/illixr_output_calculator.h
    ${CMAKE_CURRENT_LIST_DIR}/illixr_data.h
)

target_sources(${PLUGIN_NAME} PRIVATE
               ${UTIL_SOURCES}
               ${UTIL_HEADERS}
)
