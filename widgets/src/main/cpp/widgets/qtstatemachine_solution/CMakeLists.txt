#############################################################################
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
#############################################################################



set(QTSTATEMACHINE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/qtstatemachine_solution)

# include directories
include_directories(${QTSTATEMACHINE_SOURCE_DIR}/src ${QTSTATEMACHINE_SOURCE_DIR}/buildlib)

# define some macro
add_definitions(-DQT_STATEMACHINE_SOLUTION -DQT_NO_ANIMATION)

# all source files
set(QTSTATEMACHINE_SRCS
    ${QTSTATEMACHINE_SOURCE_DIR}/buildlib/moc_qabstractstate.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/buildlib/moc_qabstracttransition.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/buildlib/moc_qactionstate.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/buildlib/moc_qeventtransition.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/buildlib/moc_qfinalstate.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/buildlib/moc_qhistorystate.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/buildlib/moc_qsignaltransition.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/buildlib/moc_qstateaction.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/buildlib/moc_qstate.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/buildlib/moc_qstatefinishedtransition.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/buildlib/moc_qtransition.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qabstractstate.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qabstractstate.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qabstractstate_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qabstracttransition.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qabstracttransition.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qabstracttransition_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qactionstate.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qactionstate.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qactionstate_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qboundevent_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qeventtransition.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qeventtransition.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qeventtransition_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qfinalstate.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qfinalstate.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qguistatemachine.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qhistorystate.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qhistorystate.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qhistorystate_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qsignaleventgenerator_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qsignalevent.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qsignaltransition.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qsignaltransition.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qsignaltransition_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstateaction.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstateaction.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstateaction_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstate.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstatefinishedevent.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstatefinishedtransition.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstatefinishedtransition.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstate.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstatemachine.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstatemachine.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstatemachine_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qstate_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtAbstractState
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtAbstractTransition
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtActionState
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtEventTransition
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtFinalState
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtHistoryState
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qtransition.cpp
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qtransition.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qtransition_p.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtScriptedEvent
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtScriptedTransition
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtSignalEvent
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtSignalTransition
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtSsmAutoInvokerFactory
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtSsmInvoker
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtState
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtStateAction
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtStateFinishedEvent
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtStateFinishedTransition
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtStateInvokeMethodAction
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtStateMachine
    ${QTSTATEMACHINE_SOURCE_DIR}/src/qtstatemachineglobal.h
    ${QTSTATEMACHINE_SOURCE_DIR}/src/QtTransition
)

