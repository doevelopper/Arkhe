cmake_minimum_required(VERSION 3.8)

if((NOT PROJECT_CMAKE_MODULE_ROOT_PATH))
    message(FATAL_ERROR "User module path should be given. It is shared accros module!")
endif ((NOT PROJECT_CMAKE_MODULE_ROOT_PATH))


string(REPLACE "\\" "/" PROJECT_CMAKE_MODULE_ROOT_PATH "${PROJECT_CMAKE_MODULE_ROOT_PATH}" ) 

message (STATUS "CTK PROJECT_CMAKE_MODULE_ROOT_PATH ${PROJECT_CMAKE_MODULE_ROOT_PATH}")

list(APPEND CMAKE_MODULE_PATH
    "${PROJECT_CMAKE_MODULE_ROOT_PATH}/src/main/config/modules"
    "${PROJECT_CMAKE_MODULE_ROOT_PATH}/src/main/config/toolChains"
    "${PROJECT_CMAKE_MODULE_ROOT_PATH}/src/main/config/macros"
    "${PROJECT_CMAKE_MODULE_ROOT_PATH}/src/main/config/config"
    "${PROJECT_CMAKE_MODULE_ROOT_PATH}/src/test/config/modules"
)

# include(aol)
include(qt)
include(PreventInSourceBuilds)
include(CMakeSettings)
# include(PrintVariables)
include(DefinePlatformSpecfic)
include(SuperPedanticWarnings)


# set(CORE_MODULE_ROOT_CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# add_subdirectory (src/main/cpp)
#add_subdirectory (src/test/cpp)
