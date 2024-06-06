function(PROTOBUF_GENERATE_OBJ_WITH_DEPS OBJ_BASE_NAME OBJ_DEPS)
    include_directories(${Protobuf_INCLUDE_DIRS})
    include_directories(${CMAKE_SOURCE_DIR})
    set(EXTRA_ARGS ${ARGN})
    list(LENGTH EXTRA_ARGS ARG_COUNT)
    if(${ARG_COUNT} GREATER 0)
        protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS DESCRIPTORS ${OBJ_BASE_NAME}.proto)
        set(TEMP $CACHE{PROTOBUF_DESCRIPTORS})
        list(APPEND TEMP ${DESCRIPTORS})
        set(PROTOBUF_DESCRIPTORS ${TEMP} CACHE INTERNAL "")
    else()
        protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${OBJ_BASE_NAME}.proto)
    endif()

    add_library(${OBJ_BASE_NAME}_proto OBJECT ${PROTO_SRCS} ${PROTO_HDRS})
    target_link_libraries(${OBJ_BASE_NAME}_proto PUBLIC ${Protobuf_LIBRARIES})
    if(OBJ_DEPS)
        foreach(ITEM IN LISTS OBJ_DEPS)
            target_link_libraries(${OBJ_BASE_NAME}_proto PUBLIC ${ITEM}_proto)
        endforeach()
    endif()
endfunction()

function(PROTOBUF_GENERATE_OBJ OBJ_BASE_NAME)
    PROTOBUF_GENERATE_OBJ(OBJ_BASE_NAME "" ${ARGN})
endfunction()

