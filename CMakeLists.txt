cmake_minimum_required( VERSION 3.7 FATAL_ERROR)
project (${PROJECT_NAME})

if((NOT PROJECT_NAME))
    message(FATAL_ERROR "Project name must be specified!")
endif ((NOT PROJECT_NAME))

if(${PROJECT_NAME} MATCHES " ")
    message(FATAL_ERROR "Project name cannot contain spaces!")
endif(${PROJECT_NAME} MATCHES " ")

set(${PROJECT_NAME}_MAJOR_VERSION       "${MAJOR}")
set(${PROJECT_NAME}_MINOR_VERSION       "${MINOR}")
set(${PROJECT_NAME}_MICRO_VERSION       "${MICRO}")
set(${PROJECT_NAME}_PATCH_VERSION       "${PATCH}")
set(${PROJECT_NAME}_REVISION_VERSION    "${REV}")

set(PROJECT_VERSION_MAJOR ${${PROJECT_NAME}_MAJOR_VERSION})
set(PROJECT_VERSION_MINOR ${${PROJECT_NAME}_MINOR_VERSION})
set(PROJECT_VERSION_MICRO ${${PROJECT_NAME}_MICRO_VERSION})
set(PROJECT_VERSION_PATCH ${${PROJECT_NAME}_PATCH_VERSION})

set(${PROJECT_NAME}_VERSION 
    "${${PROJECT_NAME}_MAJOR_VERSION}.
    ${${PROJECT_NAME}_MINOR_VERSION}.
    ${${PROJECT_NAME}_MICRO_VERSION}.
    ${${PROJECT_NAME}_PATCH_VERSION}"
)
set(${PROJECT_NAME}_VERSION_REV 
    "${${PROJECT_NAME}_VERSION_MAJOR}.
    ${${PROJECT_NAME}_VERSION_MINOR}.
    ${${PROJECT_NAME}_VERSION_MICRO}.
    ${${PROJECT_NAME}_VERSION_REVISION}.
    ${${PROJECT_NAME}_VERSION_PATCH}"
)
set(${PROJECT_NAME}_SO_VERSION 
    "${${PROJECT_NAME}_VERSION_MAJOR}.
    ${${PROJECT_NAME}_VERSION_MINOR}.
    ${${PROJECT_NAME}_VERSION_MICRO}"
)


list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/src/main/config/modules"
    "${CMAKE_SOURCE_DIR}/src/main/config/toolChains"
    "${CMAKE_SOURCE_DIR}/src/main/config/macros"
    "${CMAKE_SOURCE_DIR}/src/main/config/config"
    "${CMAKE_SOURCE_DIR}/src/test/config/modules"
)
include(qt)
include(PreventInSourceBuilds)
include(aol)
include(CMakeSettings)
# include(PrintVariables)
include(DefinePlatformSpecfic)
include(SuperPedanticWarnings)

option(ENABLE_QA_CHECK              "Software quality. Conformance to one or more standards"    OFF)
option(ENABLE_COVERAGE              "Build the project with coverage support"                   OFF)
option(ENABLE_CPPLINT               "Ensure that code conforms to Google's coding style guides" OFF)
option(ENABLE_FORMATING_STYLE       "Code Beautifier using Uncrustify"                          OFF)
option(ENABLE_CYCLOMATIC_COMPLEXITY "Cyclomatic Complexity Analyzer"                            OFF)
option(ENABLE_CPPCHECK              "Static code analysis tool "                                OFF)


# for Windows operating system in general
if(WIN32)
    if(MSVS OR MSYS OR MINGW)

    endif()
endif()

# for MacOS X
if(APPLE)
    
endif()

# for Linux, BSD, Solaris, Minix
if(UNIX AND NOT APPLE)
    
endif()

# Simulator i386 version
# add_custom_target(i386
    # COMMAND ${CMAKE_COMMAND}
    # --build ${IA32_BINARY_DIR}
    # --config ${CMAKE_BUILD_TYPE}
    # COMMENT "Building for i386"
    # VERBATIM
# )

# Simulator x86_64 version
# add_custom_target(x64
    # COMMAND ${CMAKE_COMMAND}
    # --clean-first
    # --build ${X64_BINARY_DIR}
    # --config ${CMAKE_BUILD_TYPE}
    # COMMENT "Building for x86_64"
# VERBATIM
# )

# ARM version
# add_custom_target(arm
    # COMMAND ${CMAKE_COMMAND}
    # --build ${ARM_BINARY_DIR}
    # --config ${CMAKE_BUILD_TYPE}
    # COMMENT "Building for armv7, armv7s,armv8-a, arm64"
    # VERBATIM
# )


# add_custom_target(cleanall
    # COMMAND ${CMAKE_COMMAND}
    # --target clean
    # COMMENT "Cleaning target"
    # VERBATIM
# )


set(QRCS ${CMAKE_CURRENT_LIST_DIR}/src/main/resources/Qtrcs/resources.qrc 
)

add_subdirectory(src/main/cpp)
add_subdirectory(src/test/cpp)
