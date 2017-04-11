###############################################################################
##
## Copyright (C) 2009 TECHNOGERMA Systems France and/or its subsidiary(-ies).
## Contact: Technogerma Systems France Information (contact@technogerma.fr)
##
## This file is part of the GICS library.
##
## Commercial Usage
## Licensees holding valid GICS Commercial licenses may use this file in
## accordance with the GICS Commercial License Agreement provided with the
## Software or, alternatively, in accordance with the terms contained in
## a written agreement between you and TECHNOGERMA Systems France.
##
## GNU General Public License Usage
## Alternatively, this file may be used under the terms of the GNU
## General Public License version 3.0 as published by the Free Software
## Foundation and appearing in the file LICENSE.GPL3.txt included in the
## packaging of this file.  Please review the following information to
## ensure the GNU General Public License version 3.0 requirements will be
## met: http://www.gnu.org/copyleft/gpl.html.
##
## If you are unsure which license is appropriate for your use, please
## contact the sales department at sales@technogerma.fr.
##
###############################################################################


cmake_minimum_required(VERSION 2.6.4)

# set project's name
project(GICS)

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

# all source files
set(GICS_SRCS
    include/gics/config.hpp
    include/gics/math.hpp
    include/gics/component.hpp
    include/gics/private/component_p.hpp
    src/component.cpp
    src/component_meta.cpp
    include/gics/picture.hpp
    include/gics/private/picture_p.hpp
    src/picture.cpp
    src/picture_meta.cpp
    include/gics/private/svgmask.hpp
    src/svgmask.cpp
    include/gics/private/svgelement.hpp
    src/svgelement.cpp
    include/gics/private/svgelementmanager.hpp
    src/svgelementmanager.cpp
    include/gics/private/svgfile.hpp
    src/svgfile.cpp
    include/gics/tag.hpp
    src/tag.cpp
    include/gics/instrument.hpp
    include/gics/private/instrument_p.hpp
    src/instrument.cpp
    src/instrument_meta.cpp
    include/gics/state.hpp
    include/gics/private/state_p.hpp
    src/state.cpp
    include/gics/alignment.hpp
    src/alignment.cpp
    src/alignment_meta.cpp
    include/gics/field.hpp
    include/gics/private/field_p.hpp
    src/field.cpp
    src/field_meta.cpp
    include/gics/validationmode.hpp
    src/validationmode_meta.cpp
    include/gics/lcdrenderer.hpp
    src/lcdrenderer.cpp
    include/gics/fontlcdrenderer.hpp
    include/gics/private/fontlcdrenderer_p.hpp
    src/fontlcdrenderer.cpp
    include/gics/pixellcdrenderer.hpp
    include/gics/private/pixellcdrenderer_p.hpp
    src/pixellcdrenderer.cpp
    include/gics/lcdlabel.hpp
    include/gics/private/lcdlabel_p.hpp
    src/lcdlabel.cpp
    src/lcdlabel_meta.cpp
    include/gics/qt.hpp
    src/qt_meta.cpp
    include/gics/private/lcdpixeldigit.hpp
    src/lcdpixeldigit.cpp
    include/gics/abstractscale.hpp
    include/gics/private/abstractscale_p.hpp
    src/abstractscale.cpp
    src/abstractscale_meta.cpp
    include/gics/linearscale.hpp
    include/gics/private/linearscale_p.hpp
    src/linearscale.cpp
    src/linearscale_meta.cpp
    include/gics/adjustedlinearlayout.hpp
    include/gics/private/adjustedlinearlayout_p.hpp
    src/adjustedlinearlayout.cpp
    include/gics/direction.hpp
    src/direction_meta.cpp
    include/gics/private/layoututils.hpp
    src/layoututils.cpp
    include/gics/label.hpp
    include/gics/private/label_p.hpp
    src/label.cpp
    src/label_meta.cpp
    include/gics/tank.hpp
    include/gics/private/tank_p.hpp
    src/tank.cpp
    src/tank_meta.cpp
    include/gics/cursor.hpp
    include/gics/private/cursor_p.hpp
    src/cursor.cpp
    src/cursor_meta.cpp
    include/gics/circularscale.hpp
    include/gics/private/circularscale_p.hpp
    src/circularscale.cpp
    src/circularscale_meta.cpp
    include/gics/radiallayout.hpp
    include/gics/private/radiallayout_p.hpp
    src/radiallayout.cpp
    include/gics/skinmanager.hpp
    include/gics/private/skinmanager_p.hpp
    src/skinmanager.cpp
    include/gics/private/skin.hpp
    src/skin.cpp
    include/gics/private/instrumentskin.hpp
    src/instrumentskin.cpp
    include/gics/led.hpp
    include/gics/private/led_p.hpp
    src/led.cpp
    src/led_meta.cpp
    include/gics/lcd.hpp
    include/gics/private/lcd_p.hpp
    src/lcd.cpp
    src/lcd_meta.cpp
    include/gics/button.hpp
    include/gics/private/button_p.hpp
    src/button.cpp
    src/button_meta.cpp
    include/gics/textfield.hpp
    include/gics/private/textfield_p.hpp
    src/textfield.cpp
    src/textfield_meta.cpp
    include/gics/numericfield.hpp
    include/gics/private/numericfield_p.hpp
    src/numericfield.cpp
    src/numericfield_meta.cpp
    include/gics/levelindicator.hpp
    include/gics/private/levelindicator_p.hpp
    src/levelindicator.cpp
    src/levelindicator_meta.cpp
    include/gics/slider.hpp
    include/gics/private/slider_p.hpp
    src/slider.cpp
    src/slider_meta.cpp
    include/gics/textlabel.hpp
    include/gics/private/textlabel_p.hpp
    src/textlabel.cpp
    src/textlabel_meta.cpp
    include/gics/numericlabel.hpp
    include/gics/private/numericlabel_p.hpp
    src/numericlabel.cpp
    src/numericlabel_meta.cpp
    include/gics/gauge.hpp
    include/gics/private/gauge_p.hpp
    src/gauge.cpp
    src/gauge_meta.cpp
    include/gics/panel.hpp
    include/gics/private/panel_p.hpp
    src/panel.cpp
    src/panel_meta.cpp
    include/gics/private/instrumentcentrallayout.hpp
    include/gics/private/instrumentcentrallayout_p.hpp
    src/instrumentcentrallayout.cpp
)

# all header files that should be treated with moc
set(GICS_MOC_HDRS
    include/gics/picture.hpp
    include/gics/instrument.hpp
    include/gics/field.hpp
    include/gics/abstractscale.hpp
    include/gics/tank.hpp
    include/gics/cursor.hpp
    include/gics/led.hpp
    include/gics/lcd.hpp
    include/gics/button.hpp
    include/gics/private/button_p.hpp
    include/gics/textfield.hpp
    include/gics/numericfield.hpp
    include/gics/levelindicator.hpp
    include/gics/private/levelindicator_p.hpp
    include/gics/slider.hpp
    include/gics/textlabel.hpp
    include/gics/numericlabel.hpp
    include/gics/gauge.hpp
    include/gics/private/gauge_p.hpp
)

# all resource files
set(GICS_RCS
    resources/resources.qrc
)

# this command finds Qt4 libraries and sets all required variables
# note that it's Qt4, not QT4 or qt4
find_package(Qt4 4.5.0 COMPONENTS QtCore QtGui QtXml QtSvg REQUIRED)

# add some useful macros and variables
# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
include(${QT_USE_FILE})

# this command will generate rules that will run rcc on all resource files from <PROJECT>_RCS
# in result <PROJECT>_RC_SRCS variable will contain paths to files produced by rcc
QT4_ADD_RESOURCES(GICS_RC_SRCS ${GICS_RCS})

# and finally this will run moc:
QT4_WRAP_CPP(GICS_MOC_SRCS ${GICS_MOC_HDRS})

# find Boost
find_package(Boost 1.38.0 REQUIRED)

# find CAMP
find_package(CAMP REQUIRED)

# include files search paths
include_directories(
    ${GICS_SOURCE_DIR}/include
    ${CAMP_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

# include needed files for the Qt State Machine Framework Solution
include(${GICS_SOURCE_DIR}/src/qtstatemachine_solution/CMakeLists.txt)

# instruct CMake to build a shared library from all of the source files
add_library(gics SHARED ${GICS_SRCS} ${GICS_MOC_SRCS} ${GICS_RC_SRCS} ${QTSTATEMACHINE_SRCS})

# define export macro
set_target_properties(gics PROPERTIES DEFINE_SYMBOL GICS_EXPORTS)

# last thing we have to do is to tell CMake what libraries our executable needs,
# luckily FIND_PACKAGE prepared QT_LIBRARIES variable for us:
target_link_libraries(gics ${QT_LIBRARIES} ${CAMP_LIBRARIES})

# define the list of transitive link dependencies
set_target_properties(gics PROPERTIES LINK_INTERFACE_LIBRARIES "")

# add sub-projects
add_subdirectory(demos/simpledemo)
#add_subdirectory(demos/prototest EXCLUDE_FROM_ALL)

###############################
# doc
###############################

find_package(Doxygen)
if(DOXYGEN_FOUND)
    # setup variables to be replaced in the source Doxyfile
    set(DOXYGEN_CONFIGURED_INPUT ${CMAKE_BINARY_DIR}/doc/gicsapi.doxy)
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/doc/api CACHE PATH "Documentation directory")
    set(DOXYGEN_OUTPUT ${DOXYGEN_OUTPUT_DIR}/html/index.html)

    if(WIN32)
        set(DOXYGEN_GENERATE_MAN NO)
        find_program(HHC_PROGRAM 
            NAMES hhc.exe 
            PATHS "c:/Program Files/HTML Help Workshop"
            DOC "HTML Help Compiler program")
        if(HHC_PROGRAM)
            set(DOXYGEN_GENERATE_HTMLHELP YES)
        else()
            set(DOXYGEN_GENERATE_HTMLHELP NO)
        endif()
    else()
        set(DOXYGEN_GENERATE_MAN NO)
        set(DOXYGEN_GENERATE_HTMLHELP NO)
        set(HHC_PROGRAM)
    endif()

    # configure the source Doxyfile by copying it and replacing all @variables@
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/api/Doxyfile ${DOXYGEN_CONFIGURED_INPUT} @ONLY)

    # Copy necessary doc files
    file(GLOB image_files ${CMAKE_CURRENT_SOURCE_DIR}/doc/api/images/*)
    foreach(file ${image_files})
        get_filename_component(filename ${file} NAME)
        configure_file(${file} ${DOXYGEN_OUTPUT_DIR}/html/${filename} COPYONLY)
    endforeach()

    # add new targets to build the documentation
    add_custom_command(
        OUTPUT ${DOXYGEN_OUTPUT}
        COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
        COMMAND ${CMAKE_COMMAND} -E echo "Done."
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${DOXYGEN_CONFIGURED_INPUT}
    )

    add_custom_target(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})

    add_custom_target(apidoc_forced
        COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
        COMMAND ${CMAKE_COMMAND} -E echo "Done."
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

endif()

###############################
# installing
###############################

if(WIN32 AND NOT UNIX)
    set(INSTALL_MISC_DIR .)
elseif(UNIX)
    set(INSTALL_MISC_DIR share/gics)
endif()

install(DIRECTORY include
    DESTINATION .
    COMPONENT devel
    PATTERN "private/*" EXCLUDE
)

install(TARGETS gics
    RUNTIME DESTINATION bin COMPONENT bin
    LIBRARY DESTINATION lib COMPONENT bin 
    ARCHIVE DESTINATION lib COMPONENT devel
)

install(FILES README.txt COPYING.txt LICENSE.GPL3.txt
    DESTINATION ${INSTALL_MISC_DIR}
)

if(DOXYGEN_FOUND)
    install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}
        DESTINATION ${INSTALL_MISC_DIR}/doc
        COMPONENT apidoc
    )
endif()

install(DIRECTORY utils
    DESTINATION ${INSTALL_MISC_DIR}
    COMPONENT utils
)

###############################
# packaging
###############################

# Components setup
set(CPACK_COMPONENTS_ALL bin devel apidoc utils)
set(CPACK_ALL_INSTALL_TYPES Runtime Development)

set(CPACK_COMPONENT_BIN_DISPLAY_NAME "GICS library")
set(CPACK_COMPONENT_BIN_DESCRIPTION "The GICS library binaries")
set(CPACK_COMPONENT_BIN_INSTALL_TYPES Runtime Development)

set(CPACK_COMPONENT_DEVEL_DISPLAY_NAME "GICS development files")
set(CPACK_COMPONENT_DEVEL_DESCRIPTION "C++ header files, import library")
set(CPACK_COMPONENT_DEVEL_DEPENDS bin)
set(CPACK_COMPONENT_DEVEL_GROUP "Development")
set(CPACK_COMPONENT_DEVEL_INSTALL_TYPES Development)

set(CPACK_COMPONENT_APIDOC_DISPLAY_NAME "GICS API documentation")
set(CPACK_COMPONENT_APIDOC_DESCRIPTION "Documentation for developers")
set(CPACK_COMPONENT_APIDOC_GROUP "Development")
set(CPACK_COMPONENT_APIDOC_INSTALL_TYPES Development)

set(CPACK_COMPONENT_UTILS_DISPLAY_NAME "GICS utilities")
set(CPACK_COMPONENT_UTILS_DESCRIPTION
    "Provides a FindGICS.cmake file to be used with project based on CMake"
)
set(CPACK_COMPONENT_UTILS_GROUP "Development")
set(CPACK_COMPONENT_UTILS_DISABLED TRUE)

set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION "Components related to software development based on GICS")
set(CPACK_COMPONENT_GROUP_DEVELOPMENT_EXPANDED TRUE)

# Package setup
set(CPACK_PACKAGE_NAME GICS)
set(CPACK_PACKAGE_VENDOR Tegesoft)
set(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
set(CPACK_PACKAGE_DESCRIPTION_FILE ${GICS_SOURCE_DIR}/README.txt)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "GICS is a graphical instruments C++ library")
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_VENDOR}\\\\gics)
set(CPACK_RESOURCE_FILE_LICENSE ${GICS_SOURCE_DIR}/COPYING.txt)
set(CPACK_RESOURCE_FILE_README ${GICS_SOURCE_DIR}/README.txt)
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY GICS)

if(WIN32 AND NOT UNIX)
    set(CPACK_GENERATOR ZIP;NSIS)
elseif(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR TGZ;TBZ2)
elseif(APPLE)
    set(CPACK_GENERATOR TGZ;TBZ2;PackageMaker)
endif()
#set(CPACK_PACKAGE_EXECUTABLES "simpledemo;GICS Demo")

set(CPACK_SOURCE_GENERATOR TGZ;ZIP)

file(GLOB IGNORED_DOT_FILES ".*")
set(CPACK_SOURCE_IGNORE_FILES
    ${IGNORED_DOT_FILES}
    doc/requirements_specification
    doc/technical_note_skin
    doc/technical_specification
    doc/test_plan
    demos/prototest
    wrappers
)

# NSIS setup
#set(CPACK_NSIS_MUI_ICON ${GICS_SOURCE_DIR}/doc/images\\\\logo.ico)
#set(CPACK_NSIS_MUI_UNIICON ${GICS_SOURCE_DIR}/doc/images\\\\logo.ico)
set(CPACK_PACKAGE_ICON ${GICS_SOURCE_DIR}/doc/images\\\\logo_package.bmp)
#set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS)
#set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS)
#set(CPACK_NSIS_COMPRESSOR)
#set(CPACK_NSIS_MODIFY_PATH)
set(CPACK_NSIS_DISPLAY_NAME GICS)
#set(CPACK_NSIS_INSTALLED_ICON_NAME)
set(CPACK_NSIS_HELP_LINK "http://www.tegesoft.com")
set(CPACK_NSIS_URL_INFO_ABOUT "http://www.tegesoft.com")
set(CPACK_NSIS_CONTACT "contact@tegesoft.com")
#set(CPACK_NSIS_CREATE_ICONS_EXTRA)
#set(CPACK_NSIS_DELETE_ICONS_EXTRA)

include(CPack)

