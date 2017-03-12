#
# CMake module to C++ static analysis against 
# Google C++ Style Guide (https://google.github.io/styleguide/cppguide.html)
#
# For more detials please follow links:
#
# - https://github.com/google/styleguide
# - https://pypi.python.org/pypi/cpplint
# - https://github.com/theandrewdavis/cpplint
# Usage
# -----
# Include this module via CMake include(...) command and then add each source directory 
# via introduced by this module cpplint_add_subdirectory(...) function. Added directory 
# will be recursivelly scanned and all available files will be checked. 
#
# Example
# -------
# # include CMake module
# include(cmake/cpplint.cmake)
#
# # add all source code directories
# cpplint_add_subdirectory(core)
# cpplint_add_subdirectory(modules/c-bind)

find_program(PYTHON python)
find_file(CPPLINT 
    NAMES cpplint
#    PATHS ${CMAKE_CURRENT_LIST_DIR} 
    PATHS ${PROJECT_SOURCE_DIR}/src/main/resources/scripts/
    DOC "Path to cpplint"
)

if(CPPLINT)
    message(STATUS "cpplint parser: ${CPPLINT}")
else()
    message(FATAL_ERROR "cpplint script: NOT FOUND! "
                        "Please install cpplint as described on https://pypi.python.org/pypi/cpplint. "
			"In most cases command 'sudo pip install cpplint' should be sufficent.")
endif()

# common target to concatenate all cpplint.py targets
#add_custom_target(${CPPLINT_TARGET} ALL)

add_custom_target(cpplint${TARGET_NAME}
    COMMAND "${CMAKE_COMMAND}" -E chdir
            "${CMAKE_CURRENT_SOURCE_DIR}"
            "${PYTHON_EXECUTABLE}"
            "${CMAKE_SOURCE_DIR}/misc/cpplint.py"
            "--filter=${STYLE_FILTER}"
            "--counting=detailed"
            "--extensions=cpp,hpp,h"
            "--linelength=250"
            ${SOURCES_LIST}
    DEPENDS ${SOURCES_LIST}
    COMMENT "Linting ${TARGET_NAME}"
    VERBATIM
)

# use cpplint.py to check source code files inside DIR directory
function(cpplint_add_subdirectory DIR)
    # create relative path to the directory
    set(ABSOLUTE_DIR ${CMAKE_CURRENT_LIST_DIR}/${DIR})

    # add *.c files
    set(EXTENSIONS       ${EXTENSIONS}c,)
    set(FILES_TO_CHECK   ${FILES_TO_CHECK} ${ABSOLUTE_DIR}/*.c)

    # add *.h files

    set(EXTENSIONS       ${EXTENSIONS}h,)
    set(FILES_TO_CHECK   ${FILES_TO_CHECK} ${ABSOLUTE_DIR}/*.h)

    # add *.cpp files

    set(EXTENSIONS       ${EXTENSIONS}cpp,)
    set(FILES_TO_CHECK   ${FILES_TO_CHECK} ${ABSOLUTE_DIR}/*.cpp)

    # add *.hpp files

    set(EXTENSIONS       ${EXTENSIONS}hpp,)
    set(FILES_TO_CHECK   ${FILES_TO_CHECK} ${ABSOLUTE_DIR}/*.hpp)
  
    # find all source files inside project
    file(GLOB_RECURSE LIST_OF_FILES ${FILES_TO_CHECK})

    # create valid target name for this check
    string(REGEX REPLACE "/" "." TEST_NAME ${DIR})
    set(TARGET_NAME ${CPPLINT_TARGET}.${TEST_NAME})

    # perform cpplint check
    add_custom_target(${TARGET_NAME}
        COMMAND ${CPPLINT} "--extensions=${EXTENSIONS}"
                           "--root=${CPPLINT_PROJECT_ROOT}"
                           ${LIST_OF_FILES}
        DEPENDS ${LIST_OF_FILES}
        COMMENT "cpplint: Checking source code style"
    )

    # run this target when root cpplint.py test is triggered
    add_dependencies(${CPPLINT_TARGET} ${TARGET_NAME})

    # add this test to CTest
    add_test(${TARGET_NAME} ${CMAKE_MAKE_PROGRAM} ${TARGET_NAME})
endfunction()