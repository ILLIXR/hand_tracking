 if(Protobuf_POPULATED)
     return()
 endif()

 cmake_policy(SET CMP0135 NEW)
 include(FetchContent)

 FetchContent_Declare(
         Protobuf
         GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
         GIT_TAG v3.19.1
         GIT_SHALLOW TRUE
         GIT_PROGRESS TRUE
         PREFIX "${CMAKE_BINARY_DIR}"
         SOURCE_DIR "${CMAKE_BINARY_DIR}/protobuf"
         SOURCE_SUBDIR cmake
         GIT_SUBMODULES_RECURSE TRUE
 )

 FetchContent_GetProperties(Protobuf)
 #if(NOT Protobuf_POPULATED)
 #    FetchContent_Populate(Protobuf)
 #endif()

 FetchContent_MakeAvailable(Protobuf)