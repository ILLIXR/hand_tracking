#[=======================================================================[.rst:
Generate protbuf files and object library

.. command:: protobuf_generate_obj

  Process the given protbuf file into C++ files and object library::
    
    protobuf_generate_obj(<PROTO_PATH> <OBJ_NAME> [DESCRIPTORS])

  ``PROTO_PATH``
    The the relative path to the protobuf file (relative to CMAKE_CURRENT_SOURCE_DIR). Also used
    to generate the TARGET name of the object library.
  ``OBJ_NAME``
    The name of the protobuf file (without the .proto extension). Also used to generate the TARGET name of
    the object library.
  ``DESCRIPTORS``
    A flag that will append descriptor files to the master list in CACHE

  Products:

    The function will generate an object library with a name based on the PROTO_PATH and OBJ_NAME
    inputs.

    Example:

    .. code-block:: cmake

      protobuf_generate_obj(framework/util color)

    will produce a TARGET named framework.util.color_proto

#]=======================================================================]

function(protobuf_generate_obj)
    set(options DESCRIPTORS)
    set(oneValueArgs PROTO_PATH OBJ_NAME)
    cmake_parse_arguments(protobuf_generate_obj "${options}" "${oneValueArgs}" "" ${ARGV})
    set(_proto_file "${protobuf_generate_obj_OBJ_NAME}.proto")
    if(protobuf_generate_obj_DESCRIPTORS)
        set(_descriptors DESCRIPTORS)
    endif()
    set(library_base_name ${TARGET_BASE_NAME}.${protobuf_generate_obj_OBJ_NAME}_proto)
    add_library(${library_base_name}
                OBJECT
    )

    set(_outvar)
    string(REPLACE "." "/" TARGET_BASE_NAME ${protobuf_generate_obj_PROTO_PATH})
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/mediapipe/${protobuf_generate_obj_PROTO_PATH})
    protobuf_generate(${_descriptors}
                      LANGUAGE cpp 
                      OUT_VAR _outvar
                      IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
                      #PROTOC_OUT_DIR ${protobuf_generate_obj_PROTO_PATH}
                      TARGET ${library_base_name}
                      PROTOS mediapipe/${protobuf_generate_obj_PROTO_PATH}/${_proto_file})
    set(SRCS)
    set(HDRS)
    if(protobuf_generate_obj_DESCRIPTORS)
        set(${protobuf_generate_obj_DESCRIPTORS})
    endif()
    foreach(_file ${_outvar})
        if(_file MATCHES "cc$")
            list(APPEND ${SRCS} ${_file})
        elseif(_file MATCHES "desc$")
            list(APPEND ${protobuf_generate_obj_DESCRIPTORS} ${_file})
        else()
            list(APPEND ${HDRS} ${_file})
        endif()
    endforeach()
    
    target_include_directories(${library_base_name} PUBLIC
                               ${Protobuf_INCLUDE_DIRS}
                               ${CURRENT_CMAKE_SOURCE_DIR}/mediapipe
                               ${CMAKE_BINARY_DIR}
    )
    if(protobuf_generate_obj_DESCRIPTORS)
        set(TEMP $CACHE{PROTOBUF_DESCRIPTORS})
        list(APPEND TEMP ${protobuf_generate_obj_DESCRIPTORS})
        set(PROTOBUF_DESCRIPTORS ${TEMP} CACHE INTERNAL "")
    endif()
endfunction()

#function(PROTOBUF_GENERATE_OBJ_WITH_DEPS OBJ_ROOT  OBJ_BASE_NAME OBJ_DEPS)
#    include_directories(${Protobuf_INCLUDE_DIRS})
#    include_directories(${CMAKE_SOURCE_DIR})
#    set(EXTRA_ARGS ${ARGN})
#    list(LENGTH EXTRA_ARGS ARG_COUNT)
#    if(${ARG_COUNT} GREATER 0)
#        protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS DESCRIPTORS PROTO_DESCS ${OBJ_BASE_NAME}.proto)
#        set(TEMP $CACHE{PROTOBUF_DESCRIPTORS})
#        list(APPEND TEMP ${PROTO_DESCS})
#        set(PROTOBUF_DESCRIPTORS ${TEMP} CACHE INTERNAL "")
#    else()
#        protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${OBJ_BASE_NAME}.proto)
#    endif()
#    message("XXXXX ${PROTO_SRCS} ${PROTO_HDRS}")
#    add_library(${OBJ_ROOT}.${OBJ_BASE_NAME}_proto OBJECT ${PROTO_SRCS} ${PROTO_HDRS})
    #target_link_libraries(${OBJ_BASE_NAME}_proto PUBLIC ${Protobuf_LIBRARIES})
    #if(OBJ_DEPS)
    #    foreach(ITEM IN LISTS OBJ_DEPS)
    #        target_link_libraries(${OBJ_BASE_NAME}_proto PUBLIC ${ITEM}_proto)
    #    endforeach()
    #endif()
#endfunction()
