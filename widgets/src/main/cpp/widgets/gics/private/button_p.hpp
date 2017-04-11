/****************************************************************************
**
** Copyright (C) 2009 TECHNOGERMA Systems France and/or its subsidiary(-ies).
** Contact: Technogerma Systems France Information (contact@technogerma.fr)
**
** This file is part of the GICS library.
**
** Commercial Usage
** Licensees holding valid GICS Commercial licenses may use this file in
** accordance with the GICS Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and TECHNOGERMA Systems France.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3.txt included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at sales@technogerma.fr.
**
****************************************************************************/


#ifndef GICS_PRIVATE_BUTTON_HPP
#define GICS_PRIVATE_BUTTON_HPP


#include <gics/button.hpp>
#include <gics/state.hpp>
#include <gics/picture.hpp>
#include <gics/label.hpp>

#include <QtStateAction>
#include <QtStateMachine>

#include <QGraphicsLinearLayout>

namespace gics
{
/**
 * \brief Private implementation of Button
 */
class ButtonPrivate : public QObject
{
    Q_OBJECT  

public:
    /**
     * \brief Constructor
     *
     * \param buttonText Button's text
     * \param buttonPublic is a pointer to the associate public part
     */
    ButtonPrivate(const QString& buttonText, Button* buttonPublic);

    /**
     * \brief Update the text + icon layout
     */
    void updateLayout();

    /**
     * \brief Update the text + icon transformation
     */
    void updateContentTransform();
    
    /**
     * \brief Tell if the mouse cursor is contained into the instrument
     *
     * \return True if the mouse cursor is inside the instrument, false otherwise
     */
    bool isMouseInside() const;

    /**
     * \brief Update the mouse cursor in/out information
     *
     * If \a in is true, the cursor is inside the instrument, otherwiser it is outside.
     * The mouseEnter() and mouseLeave() signals are emitted if the state changed.
     */
    void setMouseInside(bool in);

    /**
     * \brief Handle enabled/disabled changes
     *
     * Emit the enabled() signal if \a enabled is true, otherwise emit the disabled() one.
     */
    virtual void enabledChanged(bool enabled);

    /**
     * \brief Forward the setState call to the public side.
     */
    void setState(State* state);

    /**
     * \brief Emit the Button::clicked() signal
     */
    void clicked(bool down = false);

    /**
     * \brief Create a state machine for a monostable button
     *
     * \return A new state machine for a monostable button
     */
    QtStateMachine* createMonostableStateMachine();

    /**
     * \brief Create a state machine for a bistable button
     *
     * \return A new state machine for a bistable button
     */
    QtStateMachine* createBistableStateMachine();

public:
    Button* q; ////< Pointer to the public implementation

    Button::Type type; ///< Type of the button

    QGraphicsWidget* contentWidget; ///< Widget containing the layout with the icon and the text
    QGraphicsLinearLayout* layout; ///< Icon + text layout
    Button::DisplaySettings displaySettings; ///< What has to be rendered
    Direction iconPosition; ///< Icon position relative to the text
    Picture* icon; ///< The icon
    Label* text; ///< The text

    Button::ContentTransform transform; /// Content transformation factors

    // Graphical states
    State* enabledUp; ///< EnabledUp graphical state
    State* enabledDown; ///< EnabledDown graphical state
    State* hoveredUp; ///< HoveredUp graphical state
    State* hoveredDown; ///< HoveredDown graphical state
    State* pressedUpDown; ///< Pressed (up->down) graphical state
    State* pressedDownUp; ///< Pressed (down->up) graphical state
    State* disabledUp; ///< DisabledUp graphical state
    State* disabledDown; ///< DisabledDown graphical state

    // State machines related members
    QtStateMachine* stateMachine; ///< The current state machine which handle the logic of the button

signals:
    void mouseEnter(); ///< Emitted when the mouse cursor enter the instrument
    void mouseLeave(); ///< Emitted when the mouse cursor leave the instrument
    void enabled(); ///< Emitted when the instrument becomes enabled
    void disabled(); ///< Emitted when the instrument becomes disabled

private:
    bool m_mouseInside; ///< True if the mouse is inside the button, false otherwise
};

//-------------------------------------------------------------------------------------------------
//
//  Declare internal classes for state machines
//
//-------------------------------------------------------------------------------------------------

/**
 * \brief State action which change the gics::State of the instument when executed
 */
class SetStateAction : public QtStateAction
{
    //Q_OBJECT causes a compile error -- should probably be in a separate header if using Q_OBJECT

public:
    /**
     * \brief Construct a new state action which activate the \a state graphical state of \a btn_p
     */
    SetStateAction(ButtonPrivate* btn_p, State* state, QObject* parent = 0);

protected:
    /**
     * \brief Activate the associated gics::State
     */
    virtual void execute();

private:
    ButtonPrivate* m_btn_p; ///< Button which will have its state changed
    State* m_state; ///< State to be set
};

/**
 * \brief State action which emit the Button::clicked signal when executed
 */
class ClickedAction : public QtStateAction
{
    //Q_OBJECT causes a compile error -- should probably be in a separate header if using Q_OBJECT

public:
    /**
     * \brief Construct a new state action which emit the \a btn_p 's "clicked" signal with \a down
     * as parameter
     */
    ClickedAction(ButtonPrivate* btn_p, bool down, QObject* parent = 0);

protected:
    /**
     * \brief Emit the associated button's "clicked" signal
     */
    virtual void execute();

private:
    ButtonPrivate* m_btn_p; ///< Associated button
    bool m_down; ///< Button's state associated to the signal to be emitted
};


} // namespace gics


#endif // GICS_PRIVATE_BUTTON_HPP

