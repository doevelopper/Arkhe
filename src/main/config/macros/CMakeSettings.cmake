#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE ON)
#set(CMAKE_RULE_MESSAGES ON)

   # Always include srcdir and builddir in include path
   # This saves typing ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} in about every subdir
   # since cmake 2.4.0
   set(CMAKE_INCLUDE_CURRENT_DIR ON)

   # put the include dirs which are in the source or build tree
   # before all other include dirs, so the headers in the sources
   # are prefered over the already installed ones
   # since cmake 2.4.1
   set(CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE ON)

   # Add the src and build dir to the BUILD_INTERFACE include directories
   # of all targets. Similar to CMAKE_INCLUDE_CURRENT_DIR, but transitive.
   # Since CMake 2.8.11
   set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

   # When a shared library changes, but its includes do not, don't relink
   # all dependencies. It is not needed.
   # Since CMake 2.8.11
   set(CMAKE_LINK_DEPENDS_NO_SHARED ON)

   # Default to shared libs for KDE, if no type is explicitely given to add_library():
   set(BUILD_SHARED_LIBS TRUE CACHE BOOL "If enabled, shared libs will be built by default, otherwise static libs")

# Force output directory destination, especially for MSVC (@so7747857).
function(setTargetOutputDirectory target)
    foreach(type RUNTIME LIBRARY ARCHIVE)
        set_target_properties(${target} PROPERTIES
            ${type}_OUTPUT_DIRECTORY         ${CMAKE_${type}_OUTPUT_DIRECTORY}
            ${type}_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_${type}_OUTPUT_DIRECTORY}
            ${type}_OUTPUT_DIRECTORY_RELEASE ${CMAKE_${type}_OUTPUT_DIRECTORY}
        )
    endforeach()
endfunction()

#Find Qt5 libraries.
#foreach(module Core Gui Widgets)
#    find_package(Qt5 REQUIRED COMPONENTS ${module})
#    list(APPEND QT_INCLUDE_DIRS "${Qt5${module}_INCLUDE_DIRS}")
#    list(APPEND QT_LIBRARIES    "${Qt5${module}_LIBRARIES}")
#    list(APPEND QT_FLAGS        "${Qt5${module}_EXECUTABLE_COMPILE_FLAGS}")
#    list(APPEND QT_DEFINITIONS  "${Qt5${module}_DEFINITIONS}")
#endforeach()
