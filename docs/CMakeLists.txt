if(BUILD_DOCS)
    include(GNUInstallDirs)
    find_package(Doxygen QUIET)
    if(NOT Doxygen_FOUND)
        message(WARNING "Cannot find doxygen, documentation cannot be built")
        set(BUILD_DOCS NO CACHE BOOL "")
    endif()
endif()

if(BUILD_DOCS)
    if((DEFINED ENV{VIRTUAL_ENV}) OR (DEFINED ENV{CONDA_PREFIX}))
        set(IN_VENV YES)
        if(DEFINED ENV{VIRTUAL_ENV})
            set(VENV_ROOT $ENV{VIRTUAL_ENV})
        else()
            set(VENV_ROOT $ENV{CONDA_PREFIX})
        endif()
        find_program(Python3_EXECUTABLE python3
                     HINTS "${VENV_ROOT}/bin"
                     NO_DEFAULT_PATH
        )
        if(NOT Python3_EXECUTABLE AND (DEFINED $ENV{VIRTUAL_ENV}))
            message(WARNING "You are running in a Python venv, but python3 could not be found. documentation cannot be built.")
            set(BUILD_DOCS NO CACHE BOOL "")
        endif()
    endif()
    if(BUILD_DOCS AND (NOT Python3_EXECUTABLE))
        find_package(Python3 QUIET COMPONENTS Interpreter)
        if(NOT Python3_FOUND)
            message(WARNING "Cannot find Python3, documentation cannot be built")
            set(BUILD_DOCS NO CACHE BOOL "")
        endif()
    endif()
endif()

if(BUILD_DOCS)
    if(IN_VENV)
        set(VENV_BIN_PATH "${VENV_ROOT}/bin")
    else()
        set(VENV_BIN_PATH "")
    endif()
    find_program(MKDOCS_EXEC mkdocs
                 HINTS "${VENV_BIN_PATH}" "$ENV{HOME}/.local/bin" "/usr/bin" "/usr/local/bin" "${MKDOCS_LOCATION}"
    )
    if(BUILD_DOCS_FOR_RELEASE)
        find_program(MIKE_EXEC mike
                     HINTS "${VENV_BIN_PATH}" "$ENV{HOME}/.local/bin" "/usr/bin" "/usr/local/bin"
        )
        if(NOT MIKE_EXEC)
            message(WARNING "BUILD_DOCS_FOR_RELEASE was set to ON, but the 'mike' executable was not found. Please be sure to install it from PyPi before deploying the documentation.")
        endif()
    endif()
    if(NOT PY_PACKAGES_FOUND)
        execute_process(COMMAND ${Python3_EXECUTABLE} -c "from material.plugins.info import plugin
from materialx import emoji
from pygments import plugin
from mkdocs_include_markdown_plugin import plugin
from mkdoxy import plugin
from mkdocs_glightbox import plugin
"
                        RESULT_VARIABLE PY_RESULT
                        OUTPUT_QUIET)
        if((${PY_RESULT} NOT EQUAL 0) OR (NOT MKDOCS_EXEC))
            message(WARNING "Some required Python packages are not installed. Will try to install them.")

            find_program(PIP_FOUND pip3
                         HINTS "$ENV{HOME}/.local/bin" "/usr/bin/" "/usr/local/bin" "${PIP_LOCATION}"
            )
            if(IN_VENV)
                find_program(UV_FOUND uv
                             HINTS "$ENV{HOME}/.local/bin" "/usr/bin/" "/usr/local/bin" "$ENV{HOME}/.cargo/bin"
                )
            endif()

            set(PIP_RUN NO)
            if(UV_FOUND)
                execute_process(COMMAND ${UV_FOUND} pip install -r ${CMAKE_SOURCE_DIR}/docs/requirements.txt
                                RESULT_VARIABLE PIP_RESULT
                                ERROR_VARIABLE PIP_MESSAGE
                )
                set(PIP_RUN YES)
            elseif(PIP_FOUND)
                if(IN_VENV)
                    set(_pip_args)
                else()
                    set(_pip_args "--user")
                endif()
                execute_process(COMMAND ${Python3_EXECUTABLE} -m pip install ${_pip_args} -r ${CMAKE_SOURCE_DIR}/docs/requirements.txt
                                RESULT_VARIABLE PIP_RESULT
                                ERROR_VARIABLE PIP_MESSAGE
                )
                set(PIP_RUN YES)
            else()
                message(WARNING "Cannot locate pip. If it is installed try setting -DPIP_LOCATION to its path")
                set(BUILD_DOCS NO CACHE BOOL "")
            endif()
            if(PIP_RUN)
                if(NOT ${PIP_RESULT} EQUAL 0)
                    message(WARNING "Could not install Python packages. Output from pip was:\n${PIP_MESSAGE}\n\n Cannot build documentation\n  See ${CMAKE_SOURCE_DIR}/docs/requirements.txt for package listing.")
                    set(BUILD_DOCS NO CACHE BOOL "")
                else()
                    set(PY_PACKAGES_FOUND ON CACHE BOOL "" FORCE)
                endif()
            endif()
        endif()
    endif()
endif()

if(BUILD_DOCS)
    find_program(DOT_EXEC dot)
    set(DOC_BUILD_DIR "${CURRENT_BUILD_DIR}/_docs/docs" CACHE INTERNAL "")
    set(DOC_ROOT_BUILD_DIR "${CURRENT_BUILD_DIR}/docs/docs")
    file(COPY ${CMAKE_SOURCE_DIR}/docs/docs
         DESTINATION ${CURRENT_BUILD_DIR}/_docs
         FOLLOW_SYMLINK_CHAIN
         PATTERN "*.in" EXCLUDE
         PATTERN "*.rst" EXCLUDE
    )
    file(MAKE_DIRECTORY "${CURRENT_BUILD_DIR}/docs/docs/api")

    # ---------------------------------------------------------
    # configure some input files
    # ---------------------------------------------------------
    file(READ docs/index.md.in INDEX_TEMP)
    string(REPLACE "docs/images/LogoWithHeader.png" "images/LogoWithHeader.png" INDEX_TEMP "${INDEX_TEMP}")
    string(REPLACE "docs/images/flow.png" "images/flow.png" INDEX_TEMP "${INDEX_TEMP}")
    file(WRITE ${DOC_BUILD_DIR}/index.md "${INDEX_TEMP}")

    # configure the Doxyfile
    set(DOXYGEN_BUILD_DIR "${DOC_BUILD_DIR}/api" CACHE INTERNAL "")
    set(DOXYGEN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/doc/ILLIXR_hand_tracking" CACHE INTERNAL "")
    set(DOXY_DOC_DIR "${CMAKE_INSTALL_DATAROOTDIR}/doc/ILLIXR_hand_tracking" CACHE INTERNAL "")
    set(DOXYGEN_SOURCE_DIR "${CMAKE_SOURCE_DIR}/plugin.hpp ${CMAKE_SOURCE_DIR}/plugin.cpp ${CMAKE_SOURCE_DIR}/hand_tracking_publisher.hpp ${CMAKE_SOURCE_DIR}/hand_tracking_publisher.cpp ${CMAKE_SOURCE_DIR}/openxr/interface.h ${CMAKE_SOURCE_DIR}/openxr/interface.cpp ${CMAKE_SOURCE_DIR}/openxr/ixr_openxr.hpp ${CMAKE_SOURCE_DIR}/openxr/openxr.cpp ${CMAKE_SOURCE_DIR}/mediapipe ${CURRENT_BUILD_DIR}/modules ${CURRENT_BUILD_DIR}/graphs ${CURRENT_BUILD_DIR}/mediapipe")
    set(DOXYGEN_EXCLUDE_FILES "")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CURRENT_BUILD_DIR}/_docs/Doxyfile)

    # configure the mkdocs file
    set(MKDOCS_DOCS_DIR "${CURRENT_BUILD_DIR}/_docs/docs")
    set(MKDOCS_BUILD_DIR "${CURRENT_BUILD_DIR}/docs/docs" CACHE INTERNAL "")
    set(MKDOCS_INSTALL_DIR "${DOXYGEN_INSTALL_DIR}" CACHE INTERNAL "")
    set(MKDOCS_DOXY_CFG "${CURRENT_BUILD_DIR}/_docs/Doxyfile")
    if(BUILD_DOCS_FOR_RELEASE AND MIKE_EXEC)
        set(MKDOCS_MIKE "
  - mike:
      alias_type: symlink
      redirect_template: null
      deploy_prefix: ''
      canonical_version: latest
      version_selector: true
      css_dir: css
      javascript_dir: js"
        )
        set(MIKE_VERSIONING "
extra:
  version:
    provider: mike"
        )
    endif()
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mkdocs.yaml.in ${CURRENT_BUILD_DIR}/_docs/mkdocs.yaml)

    # ---------------------------------------------------------
    # begin processing
    # ---------------------------------------------------------
    add_custom_target(doc_mkdocs
                      COMMAND ${MKDOCS_EXEC} build -c -f ${CURRENT_BUILD_DIR}/_docs/mkdocs.yaml)
    add_dependencies(doc_mkdocs docs_dummy_target)
    add_custom_target(doc_mkdocs_api
                      COMMAND ${MKDOCS_EXEC} build -c -f ${CURRENT_BUILD_DIR}/_docs/mkdocs.yaml
    )
    add_dependencies(doc_mkdocs_api doc_mkdocs)
    add_custom_target(docs ALL)
    add_dependencies(docs doc_mkdocs_api)

endif()

install(DIRECTORY ${DOC_ROOT_BUILD_DIR}
        DESTINATION ${DOXYGEN_INSTALL_DIR}
        OPTIONAL
)
