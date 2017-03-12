find_program(APR_CONFIG_EXECUTABLE apr-1-config
            PATHS /usr/local/apr/bin
                  ${TARGET_BUILD_DIRECTORY}/bin
            )
mark_as_advanced(APR_CONFIG_EXECUTABLE)
#message(STATUS "APR_CONFIG_EXECUTABLE ${APR_CONFIG_EXECUTABLE}")

macro(_apr_invoke _varname _regexp)
    execute_process(
        COMMAND ${APR_CONFIG_EXECUTABLE} ${ARGN}
        OUTPUT_VARIABLE _apr_output
        RESULT_VARIABLE _apr_failed
    )

    if(_apr_failed)
        message(FATAL_ERROR "${APR_CONFIG_EXECUTABLE} ${ARGN} failed")
    else()
        string(REGEX REPLACE "[\r\n]"  "" _apr_output "${_apr_output}")
        string(REGEX REPLACE " +$"     "" _apr_output "${_apr_output}")

        if(NOT ${_regexp} STREQUAL "")
            string(REGEX REPLACE "${_regexp}" " " _apr_output "${_apr_output}")
        endif()

        # XXX: We don't want to invoke separate_arguments() for APR_CFLAGS;
        # just leave as-is
        if(NOT ${_varname} STREQUAL "APR_CFLAGS")
            separate_arguments(_apr_output)
        endif()

        set(${_varname} "${_apr_output}")
    endif()
endmacro(_apr_invoke)
_apr_invoke(APR_CFLAGS     ""        --cppflags --cflags)
_apr_invoke(APR_INCLUDES  "(^| )-I" --includes)
_apr_invoke(APR_LIBS      ""        --link-ld)
_apr_invoke(APR_EXTRALIBS "(^| )-l" --libs)
_apr_invoke(APR_VERSION   ""        --version)

#message(STATUS "APR_CFLAGS ${APR_CFLAGS}")
#message(STATUS "APR_INCLUDES ${APR_INCLUDES}")
#message(STATUS "APR_LIBS ${APR_LIBS}")
#message(STATUS "APR_EXTRALIBS ${APR_EXTRALIBS}")
#message(STATUS "APR_VERSION ${APR_VERSION}")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(APR DEFAULT_MSG APR_INCLUDES APR_LIBS APR_VERSION)
