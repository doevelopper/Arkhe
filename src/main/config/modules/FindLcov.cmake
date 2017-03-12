################################################################################
#
# CMake script for finding lcov.
# The default CMake search process is used to locate files.
#
# This script creates the following variables:
#
#  LCOV_FOUND               Boolean that indicates if the package was found
#  LCOV_LCOV_EXECUTABLE     Where to find the 'lcov' tool
#  LCOV_GENHTML_EXECUTABLE  Where to find the 'genhtml' tool
#
################################################################################

include(FindPackageHandleStandardArgs)

find_program(GCOV_GCOV_EXECUTABLE gcov)
find_program(LCOV_LCOV_EXECUTABLE lcov)
find_program(LCOV_GENHTML_EXECUTABLE genhtml)

# Set LCOV_FOUND honoring the QUIET and REQUIRED arguments
find_package_handle_standard_args(LCOV DEFAULT_MSG LCOV_LCOV_EXECUTABLE LCOV_GENHTML_EXECUTABLE)

IF(LCOV_LCOV_EXECUTABLE AND LCOV_GENHTML_EXECUTABLE AND CMAKE_COMPILER_IS_GNUCXX)
    #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
ENDIF()

# Advanced options for not cluttering the cmake UIs
mark_as_advanced(LCOV_LCOV_EXECUTABLE LCOV_GENHTML_EXECUTABLE)
#message (STATUS "LCOV: ${LCOV_LCOV_EXECUTABLE}  GENHTML: ${LCOV_GENHTML_EXECUTABLE}")

#ADD_CUSTOM_TARGET(${_targetname}
#    ${LCOV_PATH} --directory . --zerocounters
#    COMMAND ${_testrunner} ${ARGV3}
#    COMMAND ${LCOV_PATH} --directory . --capture --output-file ${_outputname}.info
#    COMMAND ${LCOV_PATH} --remove ${_outputname}.info 'test/*' '/usr/*' 'lib/*' --output-file ${_outputname}.info.cleaned
#    COMMAND ${GENHTML_PATH} -o ${_outputname} ${_outputname}.info.cleaned
#    COMMAND mv ${_outputname}.info.cleaned ${CMAKE_BINARY_DIR}/${_outputname}/
#    COMMAND ${CMAKE_COMMAND} -E remove ${_outputname}.info
#    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#)
