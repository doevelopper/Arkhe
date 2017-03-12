#set (UNCRUSTIFY_CONFIG "${PROJECT_SOURCE_DIR}/src/main/resources/config/style.cfg")
#set (UNCRUSTIFY_CONFIG "${PROJECT_SOURCE_DIR}/src/main/resources/config/uncrustify.cfg")
set (UNCRUSTIFY_CONFIG "${PROJECT_SOURCE_DIR}/src/main/resources/config/raw.style.cfg")
set(UNCRUSTIFY_FLAGS --no-backup -l CPP  -c ${UNCRUSTIFY_CONFIG})
if(ENABLE_FORMATING_STYLE)
    find_program(UNCRUSTIFY uncrustify)
    if(UNCRUSTIFY)
        execute_process(
            COMMAND ${UNCRUSTIFY} --version OUTPUT_VARIABLE UNCRUSTIFY_VERSION
            OUTPUT_STRIP_TRAILING_WHITESPACE)
            string(REGEX REPLACE ".+([0-9]+\\.[0-9]+)" "\\1" UNCRUSTIFY_VERSION ${UNCRUSTIFY_VERSION}
        )
#        message(STATUS "${UNCRUSTIFY} : ${UNCRUSTIFY_VERSION}")
        mark_as_advanced(UNCRUSTIFY)

    endif(UNCRUSTIFY)

else(ENABLE_FORMATING_STYLE)
    message(STATUS "Formating style Skipped!")
endif(ENABLE_FORMATING_STYLE)

function(apply_style_targets STYLE_TARGET BASE_DIRECTORY)
    if(UNCRUSTIFY)
        if(NOT TARGET ${STYLE_TARGET}-style) 
            file(GLOB_RECURSE SRC ${BASE_DIRECTORY} *.cpp *.hpp)
            add_custom_target(${STYLE_TARGET}-style
                COMMENT "[STYLE-Target:${STYLE_TARGET}] ${BASE_DIRECTORY}"
#                COMMENT "Beautifying ${STYLE_TARGET} source code with uncrustify ${BASE_DIRECTORY}"
                COMMAND "${UNCRUSTIFY}"  ${UNCRUSTIFY_FLAGS} ${SRC}
                WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            )
        endif()
    else(UNCRUSTIFY)
        add_custom_target(${STYLE_TARGET}-style COMMAND ${CMAKE_COMMAND} -E echo "NO Code formating applied")
    endif(UNCRUSTIFY)

    if(NOT TARGET style)
        add_custom_target(style
            COMMENT "Prettying source code with uncrustify"
        )
    endif()

    add_dependencies(style ${STYLE_TARGET}-style)

endfunction()