# clean sweep
add_custom_target (cleansweep
    COMMAND rm -f ${CMAKE_SOURCE_DIR}/*.log
    COMMAND rm -f ${CMAKE_SOURCE_DIR}/Makefile
    COMMAND rm -f ${CMAKE_SOURCE_DIR}/install_manifest.txt
    COMMAND rm -f ${CMAKE_SOURCE_DIR}/cmake_install.cmake
    COMMAND find ${CMAKE_SOURCE_DIR} -type f -name CMakeCache.txt | xargs -r rm -f
    COMMAND find ${CMAKE_SOURCE_DIR} -type d -name CMakeFiles | xargs -r rm -rf
    COMMAND find ${CMAKE_SOURCE_DIR} -type f -name "*.marks" | xargs -r rm -f
    COMMAND rm -f ${CMAKE_SOURCE_DIR}/LV2_Plugin/Makefile
    COMMAND rm -f ${CMAKE_SOURCE_DIR}/LV2_Plugin/cmake_install.cmake
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set(CMAKE_BUILD_ARTIFACTS ${CMAKE_BINARY_DIR}/CMakeCache.txt
                          ${CMAKE_BINARY_DIR}/cmake_install.cmake
                          ${CMAKE_BINARY_DIR}/Makefile
                          ${CMAKE_BINARY_DIR}/CMakeFiles)

add_custom_target(clean-artifact rm -rf ${CMAKE_BUILD_ARTIFACTS})