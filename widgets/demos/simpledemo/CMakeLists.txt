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
project(SIMPLEDEMO)

# all source files
set(SIMPLEDEMO_SRCS
    main.cpp
    mainwindow.hpp
    mainwindow.cpp
    view.hpp
    view.cpp
    inputpanel.hpp
    inputpanel.cpp
    outputpanel.hpp
    outputpanel.cpp
)

# all header files that should be treated with moc
set(SIMPLEDEMO_MOC_HDRS
    view.hpp
    inputpanel.hpp
    outputpanel.hpp
)

# this command finds Qt4 libraries and sets all required variables
# note that it's Qt4, not QT4 or qt4
find_package(Qt4 4.5.0 COMPONENTS QtCore QtGui QtOpenGl REQUIRED)

# add some useful macros and variables
# (QT_USE_FILE is a variable defined by FIND_PACKAGE( Qt4 ) that contains a path to CMake script)
include(${QT_USE_FILE})

# and finally this will run moc:
QT4_WRAP_CPP(SIMPLEDEMO_MOC_SRCS ${SIMPLEDEMO_MOC_HDRS})

# find Boost
find_package(Boost 1.38.0 REQUIRED)

# include files search paths
include_directories(
    ${SIMPLEDEMO_SOURCE_DIR}/include
    ${GICS_SOURCE_DIR}/include
    ${CAMP_INCLUDE_DIR}
    ${Boost_INCLUDE_DIRS}
)

# linker search paths
link_directories(
    ${GICS_BINARY_DIR}
)

# instruct CMake to build an executable from all of the source files
add_executable(simpledemo ${SIMPLEDEMO_SRCS} ${SIMPLEDEMO_MOC_SRCS})

# last thing we have to do is to tell CMake what libraries our executable needs,
# luckily FIND_PACKAGE prepared QT_LIBRARIES variable for us:
target_link_libraries(simpledemo ${QT_LIBRARIES} ${CAMP_LIBRARIES} gics)

