target_sources(${PLUGIN_NAME} PRIVATE
               ${CMAKE_CURRENT_LIST_DIR}/const_str.h
               ${CMAKE_CURRENT_LIST_DIR}/contract.h
               ${CMAKE_CURRENT_LIST_DIR}/node.h
               ${CMAKE_CURRENT_LIST_DIR}/node.cc
               ${CMAKE_CURRENT_LIST_DIR}/packet.h
               ${CMAKE_CURRENT_LIST_DIR}/packet.cc
               ${CMAKE_CURRENT_LIST_DIR}/port.h
               ${CMAKE_CURRENT_LIST_DIR}/tag.h
               ${CMAKE_CURRENT_LIST_DIR}/tuple.h
)
