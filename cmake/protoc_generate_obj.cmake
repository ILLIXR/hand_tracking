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

function(my_protobuf_generate)
    set(_options APPEND_PATH DESCRIPTORS)
    set(_singleargs LANGUAGE OUT_VAR EXPORT_MACRO PROTOC_OUT_DIR PLUGIN PLUGIN_OPTIONS DEPENDENCIES)
    if(COMMAND target_sources)
        list(APPEND _singleargs TARGET)
    endif()
    set(_multiargs PROTOS IMPORT_DIRS GENERATE_EXTENSIONS PROTOC_OPTIONS)

    cmake_parse_arguments(protobuf_generate "${_options}" "${_singleargs}" "${_multiargs}" "${ARGN}")

    if(NOT protobuf_generate_PROTOS AND NOT protobuf_generate_TARGET)
        message(SEND_ERROR "Error: protobuf_generate called without any targets or source files")
        return()
    endif()

    if(NOT protobuf_generate_OUT_VAR AND NOT protobuf_generate_TARGET)
        message(SEND_ERROR "Error: protobuf_generate called without a target or output variable")
        return()
    endif()

    if(NOT protobuf_generate_LANGUAGE)
        set(protobuf_generate_LANGUAGE cpp)
    endif()
    string(TOLOWER ${protobuf_generate_LANGUAGE} protobuf_generate_LANGUAGE)

    if(NOT protobuf_generate_PROTOC_OUT_DIR)
        set(protobuf_generate_PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    if(protobuf_generate_EXPORT_MACRO AND protobuf_generate_LANGUAGE STREQUAL cpp)
        set(_dll_export_decl "dllexport_decl=${protobuf_generate_EXPORT_MACRO}")
    endif()

    foreach(_option ${_dll_export_decl} ${protobuf_generate_PLUGIN_OPTIONS})
        # append comma - not using CMake lists and string replacement as users
        # might have semicolons in options
        if(_plugin_options)
            set( _plugin_options "${_plugin_options},")
        endif()
        set(_plugin_options "${_plugin_options}${_option}")
    endforeach()

    if(protobuf_generate_PLUGIN)
        set(_plugin "--plugin=${protobuf_generate_PLUGIN}")
    endif()

    if(NOT protobuf_generate_GENERATE_EXTENSIONS)
        if(protobuf_generate_LANGUAGE STREQUAL cpp)
            set(protobuf_generate_GENERATE_EXTENSIONS .pb.h .pb.cc)
        elseif(protobuf_generate_LANGUAGE STREQUAL python)
            set(protobuf_generate_GENERATE_EXTENSIONS _pb2.py)
        else()
            message(SEND_ERROR "Error: protobuf_generate given unknown Language ${LANGUAGE}, please provide a value for GENERATE_EXTENSIONS")
            return()
        endif()
    endif()

    if(protobuf_generate_TARGET)
        get_target_property(_source_list ${protobuf_generate_TARGET} SOURCES)
        foreach(_file ${_source_list})
            if(_file MATCHES "proto$")
                list(APPEND protobuf_generate_PROTOS ${_file})
            endif()
        endforeach()
    endif()

    if(NOT protobuf_generate_PROTOS)
        message(SEND_ERROR "Error: protobuf_generate could not find any .proto files")
        return()
    endif()

    if(protobuf_generate_APPEND_PATH)
        # Create an include path for each file specified
        foreach(_file ${protobuf_generate_PROTOS})
            get_filename_component(_abs_file ${_file} ABSOLUTE)
            get_filename_component(_abs_dir ${_abs_file} DIRECTORY)
            list(FIND _protobuf_include_path ${_abs_dir} _contains_already)
            if(${_contains_already} EQUAL -1)
                list(APPEND _protobuf_include_path -I ${_abs_dir})
            endif()
        endforeach()
    else()
        set(_protobuf_include_path -I ${CMAKE_CURRENT_SOURCE_DIR})
    endif()

    foreach(DIR ${protobuf_generate_IMPORT_DIRS})
        get_filename_component(ABS_PATH ${DIR} ABSOLUTE)
        list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
        if(${_contains_already} EQUAL -1)
            list(APPEND _protobuf_include_path -I ${ABS_PATH})
        endif()
    endforeach()

    set(_generated_srcs_all)
    foreach(_proto ${protobuf_generate_PROTOS})
        get_filename_component(_abs_file ${_proto} ABSOLUTE)
        get_filename_component(_abs_dir ${_abs_file} DIRECTORY)
        get_filename_component(_basename ${_proto} NAME_WLE)
        file(RELATIVE_PATH _rel_dir ${CMAKE_CURRENT_SOURCE_DIR} ${_abs_dir})

        set(_possible_rel_dir)
        if (NOT protobuf_generate_APPEND_PATH)
            set(_possible_rel_dir ${_rel_dir}/)
        endif()

        set(_generated_srcs)
        foreach(_ext ${protobuf_generate_GENERATE_EXTENSIONS})
            list(APPEND _generated_srcs "${protobuf_generate_PROTOC_OUT_DIR}/${_possible_rel_dir}${_basename}${_ext}")
        endforeach()

        if(protobuf_generate_DESCRIPTORS AND protobuf_generate_LANGUAGE STREQUAL cpp)
            set(_descriptor_file "${CMAKE_CURRENT_BINARY_DIR}/${_basename}.desc")
            set(_dll_desc_out "--descriptor_set_out=${_descriptor_file}")
            list(APPEND _generated_srcs ${_descriptor_file})
        endif()
        list(APPEND _generated_srcs_all ${_generated_srcs})

        set(_comment "Running ${protobuf_generate_LANGUAGE} protocol buffer compiler on ${_proto}")
        if(protobuf_generate_PROTOC_OPTIONS)
            set(_comment "${_comment}, protoc-options: ${protobuf_generate_PROTOC_OPTIONS}")
        endif()
        if(_plugin_options)
            set(_comment "${_comment}, plugin-options: ${_plugin_options}")
        endif()

        add_custom_command(
                OUTPUT ${_generated_srcs}
                COMMAND protobuf::protoc
                ARGS ${protobuf_generate_PROTOC_OPTIONS} --${protobuf_generate_LANGUAGE}_out ${_plugin_options}:${protobuf_generate_PROTOC_OUT_DIR} ${_plugin} ${_dll_desc_out} ${_protobuf_include_path} ${_abs_file}
                DEPENDS ${_abs_file} protobuf::protoc ${protobuf_generate_DEPENDENCIES}
                COMMENT ${_comment}
                VERBATIM )
    endforeach()

    set_source_files_properties(${_generated_srcs_all} PROPERTIES GENERATED TRUE)
    if(protobuf_generate_OUT_VAR)
        set(${protobuf_generate_OUT_VAR} ${_generated_srcs_all} PARENT_SCOPE)
    endif()
    if(protobuf_generate_TARGET)
        target_sources(${protobuf_generate_TARGET} PRIVATE ${_generated_srcs_all})
    endif()
endfunction()

function(protobuf_generate_obj)
    set(options DESCRIPTORS)
    set(oneValueArgs PROTO_PATH OBJ_NAME)
    cmake_parse_arguments(protobuf_generate_obj "${options}" "${oneValueArgs}" "" ${ARGV})
    set(_proto_file "${protobuf_generate_obj_OBJ_NAME}.proto")
    if(protobuf_generate_obj_DESCRIPTORS)
        set(_descriptors DESCRIPTORS)
    endif()
    string(REPLACE "/" "." TARGET_BASE_NAME ${protobuf_generate_obj_PROTO_PATH})
    set(library_base_name ${TARGET_BASE_NAME}.${protobuf_generate_obj_OBJ_NAME}_proto)
    add_library(${library_base_name}
                OBJECT
    )
    set(_outvar)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/mediapipe/${protobuf_generate_obj_PROTO_PATH})
    my_protobuf_generate(${_descriptors}
                         LANGUAGE cpp
                         OUT_VAR _outvar
                         IMPORT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
                         #PROTOC_OUT_DIR ${protobuf_generate_obj_PROTO_PATH}
                         TARGET ${library_base_name}
                         PROTOS mediapipe/${protobuf_generate_obj_PROTO_PATH}/${_proto_file})
    set(SRCS)
    set(HDRS)
    set(DESCRIPTOR_FILES "")
    foreach(_file ${_outvar})
        if(_file MATCHES "cc$")
            list(APPEND SRCS ${_file})
        elseif(_file MATCHES "desc$")
            list(APPEND DESCRIPTOR_FILES ${_file})
        else()
            list(APPEND HDRS ${_file})
        endif()
    endforeach()

    target_include_directories(${library_base_name} PUBLIC
                               ${Protobuf_INCLUDE_DIRS}
                               ${CURRENT_CMAKE_SOURCE_DIR}/mediapipe
                               ${CMAKE_BINARY_DIR}
    )
    if(protobuf_generate_obj_DESCRIPTORS)
        set(TEMP $CACHE{PROTOBUF_DESCRIPTORS})
        list(APPEND TEMP ${DESCRIPTOR_FILES})
        set(PROTOBUF_DESCRIPTORS ${TEMP} CACHE INTERNAL "")
    endif()
endfunction()
