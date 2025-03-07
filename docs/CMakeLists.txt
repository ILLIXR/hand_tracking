file(READ docs/index.md.in INDEX_TEMP)
string(REPLACE "docs/images/LogoWithHeader.png" "images/LogoWithHeader.png" INDEX_TEMP "${INDEX_TEMP}")
string(REPLACE "docs/images/flow.png" "images/flow.png" INDEX_TEMP "${INDEX_TEMP}")

file(WRITE docs/index.md "${INDEX_TEMP}")

if(BUILD_DOCS)
    include(GNUInstallDirs)

    find_package(Doxygen QUIET)
    if(Doxygen_FOUND)
        file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/docs/docs/api")
        set(DOC_BUILD_DIR "${CMAKE_BINARY_DIR}/_docs/docs" CACHE INTERNAL "")
        set(DOC_ROOT_BUILD_DIR "${CMAKE_BINARY_DIR}/docs/docs")
        set(DOXYGEN_BUILD_DIR "${DOC_BUILD_DIR}/api" CACHE INTERNAL "")
        set(DOXYGEN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/doc/ILLIXR_hand_tracking" CACHE INTERNAL "")
        set(DOXY_DOC_DIR "${CMAKE_INSTALL_DATAROOTDIR}/doc/ILLIXR_hand_tracking" CACHE INTERNAL "")
        set(DOXYGEN_SOURCE_DIR "${CMAKE_SOURCE_DIR}/plugin.hpp ${CMAKE_SOURCE_DIR}/plugin.cpp ${CMAKE_SOURCE_DIR}/hand_tracking_publisher.hpp ${CMAKE_SOURCE_DIR}/hand_tracking_publisher.cpp ${CMAKE_SOURCE_DIR}/openxr/interface.h ${CMAKE_SOURCE_DIR}/openxr/interface.cpp ${CMAKE_SOURCE_DIR}/openxr/ixr_openxr.hpp ${CMAKE_SOURCE_DIR}/openxr/openxr.cpp ${CMAKE_SOURCE_DIR}/mediapipe")
        set(DOXYGEN_EXCLUDE_FILES "")
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/_docs/Doxyfile)
        execute_process(COMMAND cp -rL ${CMAKE_SOURCE_DIR}/docs/docs/ ${DOC_BUILD_DIR}/)
        add_custom_target(doc_doxygen
                          COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/_docs/Doxyfile
                          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                          VERBATIM)
        install(DIRECTORY ${DOC_ROOT_BUILD_DIR}
                DESTINATION ${DOXYGEN_INSTALL_DIR}
                OPTIONAL
        )

        find_package(Python3)

        find_program(MKDOCS_EXEC mkdocs
                     HINTS "$ENV{HOME}/.local/bin" "/usr/bin/mkdocs" "/usr/local/bin/mkdocs")
        include(GNUInstallDirs)

        if(Python3_FOUND AND MKDOCS_EXEC)
            set(MKDOCS_DOCS_DIR "${CMAKE_BINARY_DIR}/_docs/docs")
            set(MKDOCS_BUILD_DIR "${CMAKE_BINARY_DIR}/docs/docs" CACHE INTERNAL "")
            set(MKDOCS_INSTALL_DIR "${DOXYGEN_INSTALL_DIR}" CACHE INTERNAL "")
            configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mkdocs.yaml.in ${CMAKE_BINARY_DIR}/_docs/mkdocs.yaml)
            add_custom_target(doc_mkdocs
                              COMMAND ${MKDOCS_EXEC} build -c -f ${CMAKE_BINARY_DIR}/_docs/mkdocs.yaml
                              DEPENDS doc_doxygen)
        else()
            message(WARNING "mkdocs could not be found. ILLIXR documentation cannot be built.")
        endif()
    else()
        message(WARNING "Cannot find doxygen, documentation cannot be built")
        set(BUILD_DOCS NO CACHE BOOL "")
    endif()

    add_custom_target(docs
                      DEPENDS doc_doxygen doc_mkdocs
    )
endif()
