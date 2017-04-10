
# setup version numbers
set(VERSION_MAJOR 2)
set(VERSION_MINOR 1)
set(VERSION_PATCH 1)
set(VERSION_STR "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
message("Project version: ${VERSION_STR}")

if(NOT USES_LUA)
    set(USES_LUA FALSE
        CACHE BOOL "TRUE to include Lua support (requires Lua), FALSE otherwise."
    )
endif()

# Set the default build type to release with debug info
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo
        CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
    )
endif()

# Add an option for choosing the build type (shared or static)
if(NOT BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS TRUE
        CACHE BOOL "TRUE to build Ponder as a shared library, FALSE to build it as a static library."
    )
endif()

# Set the default test build option to false
if(NOT BUILD_TEST)
    set(BUILD_TEST FALSE
        CACHE BOOL "TRUE to build the unit tests, FALSE otherwise."
    )
endif()

if(NOT BUILD_TEST_EXAMPLESFALSE
    set(BUILD_TEST_EXAMPLES TRUE
        CACHE BOOL "TRUE to build the example tests, FALSE otherwise."
    )
endif()

if(NOT BUILD_TEST_LUA)
    set(BUILD_TEST_LUA FALSE
        CACHE BOOL "TRUE to build the Lua-specific tests (requires Lua), FALSE otherwise."
    )
endif()

if(NOT BUILD_TEST_QT)
    set(BUILD_TEST_QT FALSE
        CACHE BOOL "TRUE to build the Qt-specific unit tests (requires Qt 4.5), FALSE otherwise."
    )
endif()

# define install directory for miscelleneous files
if(WIN32 AND NOT UNIX)
    set(INSTALL_MISC_DIR .)
elseif(UNIX)
    set(INSTALL_MISC_DIR share/ponder)
endif()

# setup MacOSX build environment if necessary
include(${PONDER_SOURCE_DIR}/cmake/MacOSX.cmake)

