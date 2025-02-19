target_sources(${PLUGIN_NAME} PRIVATE
               ${CMAKE_CURRENT_LIST_DIR}/tflite_model_calculator.cc
               ${CMAKE_CURRENT_LIST_DIR}/ssd_anchors_calculator.cc
               ${CMAKE_CURRENT_LIST_DIR}/tflite_custom_op_resolver_calculator.cc
)
