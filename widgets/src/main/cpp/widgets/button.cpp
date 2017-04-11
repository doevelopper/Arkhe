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


#include <gics/button.hpp>
#include <gics/private/button_p.hpp>

#include <QtState>
#include <QtSignalTransition>

#include <QGraphicsGridLayout>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QTransform>

namespace gics
{
//-------------------------------------------------------------------------------------------------
Button::ContentTransform::ContentTransform()
    : hScale(1.0)
    , vScale(1.0)
    , hTranslate(0.0)
    , vTranslate(0.0)
{
}

//-------------------------------------------------------------------------------------------------
bool Button::ContentTransform::operator==(const ContentTransform& other) const
{
    return (hScale == other.hScale)
        && (vScale == other.vScale)
        && (hTranslate == other.hTranslate)
        && (vTranslate == other.vTranslate);
}

//-------------------------------------------------------------------------------------------------
bool Button::ContentTransform::operator!=(const ContentTransform& other) const
{
    return !(*this == other);
}

//-------------------------------------------------------------------------------------------------
Button::Button(QGraphicsItem* parent)
    : Instrument(parent)
    , d("Button", this)
{
    setAcceptHoverEvents(true);
}

//-------------------------------------------------------------------------------------------------
Button::Button(const QString& text, QGraphicsItem* parent)
    : Instrument(parent)
    , d(text, this)
{
    setAcceptHoverEvents(true);
}


//-------------------------------------------------------------------------------------------------
Button::Type Button::buttonType() const
{
    return d->type;
}

//-------------------------------------------------------------------------------------------------
void Button::setButtonType(Button::Type type)
{
    if (type != d->type)
    {
        d->type = type;

        // Stop the stateMachine and schedule a deletion
        // We use a schedule deletion to avoid a segfault if the caller of the method is a state of
        // the machine to be deleted
        d->stateMachine->stop();
        d->stateMachine->deleteLater();

        // Create the new state machine
        d->stateMachine = (type == Button::monostable
                ? d->createMonostableStateMachine()
                : d->createBistableStateMachine());
    }
}

//-------------------------------------------------------------------------------------------------
bool Button::isUp() const
{
    return (currentState() == d->enabledUp)  ||
           (currentState() == d->disabledUp) ||
           (currentState() == d->hoveredUp)  ||
           (currentState() == d->pressedUpDown);
}

//-------------------------------------------------------------------------------------------------
bool Button::isDown() const
{
    return !isUp();
}

//-------------------------------------------------------------------------------------------------
bool Button::isHovered() const
{
    return d->isMouseInside();
}

//-------------------------------------------------------------------------------------------------
bool Button::keepAspectRatio() const
{
   return Instrument::keepAspectRatio();
}

//-------------------------------------------------------------------------------------------------
void Button::setKeepAspectRatio(bool keep)
{
    Instrument::setKeepAspectRatio(keep);
}

//-------------------------------------------------------------------------------------------------
State& Button::enabledUpState()
{
    return *d->enabledUp;
}

//-------------------------------------------------------------------------------------------------
State& Button::enabledDownState()
{
    return *d->enabledDown;
}

//-------------------------------------------------------------------------------------------------
State& Button::disabledUpState()
{
    return *d->disabledUp;
}

//-------------------------------------------------------------------------------------------------
State& Button::disabledDownState()
{
    return *d->disabledDown;
}

//-------------------------------------------------------------------------------------------------
State& Button::hoveredUpState()
{
    return *d->hoveredUp;
}

//-------------------------------------------------------------------------------------------------
State& Button::hoveredDownState()
{
    return *d->hoveredDown;
}

//-------------------------------------------------------------------------------------------------
State& Button::pressedUpDownState()
{
    return *d->pressedUpDown;
}

//-------------------------------------------------------------------------------------------------
State& Button::pressedDownUpState()
{
    return *d->pressedDownUp;
}


//-------------------------------------------------------------------------------------------------
void Button::press()
{
    emit pressed();
}

//-------------------------------------------------------------------------------------------------
void Button::release()
{
    emit released();
}

//-------------------------------------------------------------------------------------------------
void Button::click()
{
    press();
    release();
}

//-------------------------------------------------------------------------------------------------
void Button::animateClick(int msec)
{
    press();
    QTimer::singleShot(msec, this, SLOT(release()));
}

//-------------------------------------------------------------------------------------------------
void Button::enabledChanged(bool enabled)
{
    d->enabledChanged(enabled);
}

//-------------------------------------------------------------------------------------------------
void Button::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    d->setMouseInside(contains(event->pos()));
}

//-------------------------------------------------------------------------------------------------
void Button::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    d->setMouseInside(contains(event->pos()));
}

//-------------------------------------------------------------------------------------------------
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    d->setMouseInside(false);
}

//-------------------------------------------------------------------------------------------------
void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if ((event->buttons() & Qt::LeftButton) && d->isMouseInside())
        press();
}

//-------------------------------------------------------------------------------------------------
void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    release();
}

//-------------------------------------------------------------------------------------------------
const QString& Button::iconFile() const
{
    return d->icon->file();
}

//-------------------------------------------------------------------------------------------------
void Button::setIconFile(const QString& filename)
{
    d->icon->setFile(filename);

    // Recompute the icon size as it can have a different aspect ratio now
    setIconHeight(iconHeight());
}

//-------------------------------------------------------------------------------------------------
const QString& Button::iconId() const
{
    return d->icon->id();
}

//-------------------------------------------------------------------------------------------------
void Button::setIconId(const QString& id)
{
    d->icon->setId(id);

    // Recompute the icon size as it can have a different aspect ratio now
    setIconHeight(iconHeight());
}

//-------------------------------------------------------------------------------------------------
qreal Button::iconHeight() const
{
    return d->icon->geometry().height();
}

//-------------------------------------------------------------------------------------------------
void Button::setIconHeight(qreal height)
{
    qreal width = height * d->icon->aspectRatio();

    if ((d->icon->geometry().width() != width) || (iconHeight() != height))
    {
        d->icon->setMinimumSize(width, height);
        d->icon->setMaximumSize(width, height);
        d->icon->setPreferredSize(width, height);
    }
}

//-------------------------------------------------------------------------------------------------
const QString& Button::text() const
{
    return d->text->text();
}

//-------------------------------------------------------------------------------------------------
void Button::setText(const QString& text)
{
    d->text->setText(text);
}

//-------------------------------------------------------------------------------------------------
QFont Button::textFont() const
{
    return d->text->font();
}

//-------------------------------------------------------------------------------------------------
void Button::setTextFont(const QFont& font)
{
    d->text->setFont(font);
}

//-------------------------------------------------------------------------------------------------
QColor Button::textColor() const
{
    return d->text->color();
}

//-------------------------------------------------------------------------------------------------
void Button::setTextColor(const QColor& color)
{
    d->text->setColor(color);
}

//-------------------------------------------------------------------------------------------------
Direction Button::iconRelativePosition() const
{
    return d->iconPosition;
}

//-------------------------------------------------------------------------------------------------
void Button::setIconRelativePosition(Direction position)
{
    if (d->iconPosition != position)
    {
        d->iconPosition = position;
        d->updateLayout();
    }
}

//-------------------------------------------------------------------------------------------------
Button::DisplaySettings Button::displaySettings() const
{
    return d->displaySettings;
}

//-------------------------------------------------------------------------------------------------
void Button::setDisplaySettings(Button::DisplaySettings settings)
{
    if (d->displaySettings != settings)
    {
        d->displaySettings = settings;
        d->updateLayout();
    }
}

//-------------------------------------------------------------------------------------------------
const Button::ContentTransform& Button::contentTransform() const
{
    return d->transform;
}

//-------------------------------------------------------------------------------------------------
void Button::setContentTransform(const Button::ContentTransform& transform)
{
    if (d->transform != transform)
    {
        d->transform = transform;
        d->updateContentTransform();
    }
}

//-------------------------------------------------------------------------------------------------
void Button::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    d->updateContentTransform();
    Instrument::paint(painter, option, widget);
}

//-------------------------------------------------------------------------------------------------
QSizeF Button::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    return Instrument::sizeHint(which, constraint).expandedTo(QSizeF(1.0, 1.0));
}

//-------------------------------------------------------------------------------------------------
ButtonPrivate::ButtonPrivate(const QString& buttonText, Button* buttonPublic)
    : q(buttonPublic)
    , type(Button::monostable)
    , contentWidget(new QGraphicsWidget(q))
    , layout(new QGraphicsLinearLayout(contentWidget))
    , displaySettings(Button::showText)
    , iconPosition(left)
    , icon(new Picture(contentWidget))
    , text(new Label(buttonText, contentWidget))
    , stateMachine(0)
    , m_mouseInside(false)
{
    // Declare graphical states
    disabledUp = q->createState("disabledUp");
    disabledDown = q->createState("disabledDown");
    enabledUp = q->createState("enabledUp");
    enabledDown = q->createState("enabledDown");
    hoveredUp = q->createState("hoveredUp");
    hoveredDown = q->createState("hoveredDown");
    pressedUpDown = q->createState("pressedUpDown");
    pressedDownUp = q->createState("pressedDownUp");

    // Setup icon + text items and layout
    icon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    text->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    text->setHorizontalAlignment(alignHCenter);
    contentWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    contentWidget->setLayout(layout);
    contentWidget->setContentsMargins(0, 0, 0, 0);
    layout->setContentsMargins(0, 0, 0, 0);

    QGraphicsGridLayout* gridLayout = new QGraphicsGridLayout;
    gridLayout->addItem(contentWidget, 1, 1, Qt::AlignCenter);
    gridLayout->setColumnStretchFactor(0, 1);
    gridLayout->setColumnStretchFactor(1, 0);
    gridLayout->setColumnStretchFactor(2, 1);
    gridLayout->setRowStretchFactor(0, 1);
    gridLayout->setRowStretchFactor(1, 0);
    gridLayout->setRowStretchFactor(2, 1);

    q->setCentralItem(gridLayout);

    // Create the state machine
    stateMachine = createMonostableStateMachine();

    updateLayout();
}

//-------------------------------------------------------------------------------------------------
void ButtonPrivate::updateLayout()
{
    // Add the icon and/or text according to display settings and icon position
    switch (displaySettings)
    {
        case Button::showNothing:
            layout->removeItem(text);
            layout->removeItem(icon);
            text->hide();
            icon->hide();
            break;

        case Button::showText:
            layout->addItem(text);
            layout->removeItem(icon);
            layout->setAlignment(text, Qt::AlignCenter);
            icon->hide();
            text->show();
            break;

        case Button::showIcon:
            layout->addItem(icon);
            layout->removeItem(text);
            layout->setAlignment(icon, Qt::AlignCenter);
            text->hide();
            icon->show();
            break;

        case Button::showTextAndIcon:
            switch (iconPosition)
            {
                case top:
                    layout->setOrientation(Qt::Vertical);
                    layout->addItem(icon);
                    layout->addItem(text);
                    break;

                case bottom:
                    layout->setOrientation(Qt::Vertical);
                    layout->addItem(text);
                    layout->addItem(icon);
                    break;

                case left:
                    layout->setOrientation(Qt::Horizontal);
                    layout->addItem(icon);
                    layout->addItem(text);
                    break;

                case right:
                    layout->setOrientation(Qt::Horizontal);
                    layout->addItem(text);
                    layout->addItem(icon);
                    break;
            }

            layout->setAlignment(icon, Qt::AlignCenter);
            layout->setAlignment(text, Qt::AlignCenter);
            icon->show();
            text->show();
            break;
    }

    q->layout()->invalidate();
    q->update();
}

//-------------------------------------------------------------------------------------------------
void ButtonPrivate::updateContentTransform()
{
    // Reset current transform
    contentWidget->setTransform(QTransform());

    // Apply transform (order matters: translate then scale in the code, scale then translate in
    // reality)

    // Apply translate
    // Compute the offset according to the button size
    QSizeF size = q->layout()->contentsRect().size();
    qreal hOffset = size.width() * transform.hTranslate;
    qreal vOffset = size.height() * transform.vTranslate;
    contentWidget->translate(hOffset, vOffset);

    // Apply scale
    QPointF contentCenter = contentWidget->boundingRect().center();
    contentWidget->translate(contentCenter.x(), contentCenter.y());
    contentWidget->scale(transform.hScale, transform.vScale);
    contentWidget->translate(-contentCenter.x(), -contentCenter.y());
}

//-------------------------------------------------------------------------------------------------
bool ButtonPrivate::isMouseInside() const
{
    return m_mouseInside;
}

//-------------------------------------------------------------------------------------------------
void ButtonPrivate::setMouseInside(bool in)
{
    if (m_mouseInside != in)
    {
        m_mouseInside = in;
        in ? emit mouseEnter() : emit mouseLeave();
    }
}
 
//-------------------------------------------------------------------------------------------------
void ButtonPrivate::enabledChanged(bool enabled)
{
    enabled ? emit this->enabled() : this->disabled();
}

//-------------------------------------------------------------------------------------------------
void ButtonPrivate::setState(State* state)
{
    q->setState(state);
}

//-------------------------------------------------------------------------------------------------
void ButtonPrivate::clicked(bool down)
{
    emit q->clicked(down);
}

//-------------------------------------------------------------------------------------------------
QtStateMachine* ButtonPrivate::createMonostableStateMachine()
{
    //////////////////////////////////
    // Create the state machine states
    //////////////////////////////////

    QtState* monoEnabled = new QtState();
    QtState* monoHovered = new QtState();
    QtState* monoPressed = new QtState();
    QtState* monoCancel = new QtState();
    QtState* monoDisabled = new QtState();

    ///////////////////////////////////
    // Setup transitions between states
    ///////////////////////////////////

    // enabled --> hovered
    monoEnabled->addTransition(this, SIGNAL(mouseEnter()), monoHovered);

    // enabled --> pressedDown
    monoEnabled->addTransition(q, SIGNAL(pressed()), monoPressed);

    // enabled --> disabled
    monoEnabled->addTransition(this, SIGNAL(disabled()), monoDisabled);

    // hovered --> enabled
    monoHovered->addTransition(this, SIGNAL(mouseLeave()), monoEnabled);

    // hovered --> pressedDown
    monoHovered->addTransition(q, SIGNAL(pressed()), monoPressed);

    // hovered --> disabled
    monoHovered->addTransition(this, SIGNAL(disabled()), monoDisabled);

    // pressedDown --> hovered (trigger a ClickedAction)
    monoPressed->addTransition(q, SIGNAL(released()), monoHovered)
        ->addAction(new ClickedAction(this, false));

    // pressedDown --> pressedUp
    monoPressed->addTransition(this, SIGNAL(mouseLeave()), monoCancel);

    // pressedDown --> disabled
    monoPressed->addTransition(this, SIGNAL(disabled()), monoDisabled);

    // pressedUp --> enabled
    monoCancel->addTransition(q, SIGNAL(released()), monoEnabled);

    // pressedUp --> pressedDown
    monoCancel->addTransition(this, SIGNAL(mouseEnter()), monoPressed);

    // pressedUp --> disabled
    monoCancel->addTransition(this, SIGNAL(disabled()), monoDisabled);

    // disabled --> enabled
    monoDisabled->addTransition(this, SIGNAL(enabled()), monoEnabled);

    //////////////////////////////////////////
    // Setup actions when states are activated
    //////////////////////////////////////////

    monoEnabled->addEntryAction(new SetStateAction(this, enabledUp));
    monoHovered->addEntryAction(new SetStateAction(this, hoveredUp));
    monoPressed->addEntryAction(new SetStateAction(this, pressedUpDown));
    monoCancel->addEntryAction(new SetStateAction(this, enabledUp));
    monoDisabled->addEntryAction(new SetStateAction(this, disabledUp));

    //////////////////////////
    // Setup the state machine
    //////////////////////////

    QtStateMachine* monoMachine = new QtStateMachine(this);

    monoMachine->addState(monoEnabled);
    monoMachine->addState(monoHovered);
    monoMachine->addState(monoPressed);
    monoMachine->addState(monoCancel);
    monoMachine->addState(monoDisabled);

    monoMachine->setInitialState(q->isEnabled() ? monoEnabled : monoDisabled);
    monoMachine->start();

    return monoMachine;
}

//-------------------------------------------------------------------------------------------------
QtStateMachine* ButtonPrivate::createBistableStateMachine()
{
    //////////////////////////////////
    // Create the state machine states
    //////////////////////////////////

    QtState* biEnabledUp = new QtState();
    QtState* biHoveredUp = new QtState();
    QtState* biPressedUpDown = new QtState();
    QtState* biCancelUpDown = new QtState();
    QtState* biDisabledUp = new QtState();
    QtState* biEnabledDown = new QtState();
    QtState* biHoveredDown = new QtState();
    QtState* biPressedDownUp = new QtState();
    QtState* biCancelDownUp = new QtState();
    QtState* biDisabledDown = new QtState();

    ///////////////////////////////////
    // Setup transitions between states
    ///////////////////////////////////

    //// Transitions to push the button

    // enabledUp --> hoveredUp
    biEnabledUp->addTransition(this, SIGNAL(mouseEnter()), biHoveredUp);

    // enabledUp --> pressedUpDownIn
    biEnabledUp->addTransition(q, SIGNAL(pressed()), biPressedUpDown);

    // enabledUp --> disabledUp
    biEnabledUp->addTransition(this, SIGNAL(disabled()), biDisabledUp);

    // hoveredUp --> enabledUp
    biHoveredUp->addTransition(this, SIGNAL(mouseLeave()), biEnabledUp);

    // hoveredUp --> pressedUpDownIn
    biHoveredUp->addTransition(q, SIGNAL(pressed()), biPressedUpDown);

    // hoveredUp --> disabledUp
    biHoveredUp->addTransition(this, SIGNAL(disabled()), biDisabledUp);

    // pressedUpDownIn --> hoveredDown (trigger a ClickedAction)
    biPressedUpDown->addTransition(q, SIGNAL(released()), biHoveredDown)
        ->addAction(new ClickedAction(this, true));

    // pressedUpDownIn --> pressedUpDownOut
    biPressedUpDown->addTransition(this, SIGNAL(mouseLeave()), biCancelUpDown);

    // pressedUpDownIn --> disabledUp
    biPressedUpDown->addTransition(this, SIGNAL(disabled()), biDisabledUp);

    // pressedUpDownOut --> enabledUp
    biCancelUpDown->addTransition(q, SIGNAL(released()), biEnabledUp);

    // pressedUpDownOut --> pressedUpDownIn
    biCancelUpDown->addTransition(this, SIGNAL(mouseEnter()), biPressedUpDown);

    // pressedUpDownOut --> disbaledUp
    biCancelUpDown->addTransition(this, SIGNAL(disabled()), biDisabledUp);

    // disabledUp --> enabledUp
    biDisabledUp->addTransition(this, SIGNAL(enabled()), biEnabledUp);

    //// Transitions to pop the button

    // enabledDown --> hoveredDown
    biEnabledDown->addTransition(this, SIGNAL(mouseEnter()), biHoveredDown);

    // enabledDown --> pressedDownUpIn
    biEnabledDown->addTransition(q, SIGNAL(pressed()), biPressedDownUp);

    // enabledDown --> disabledDown
    biEnabledDown->addTransition(this, SIGNAL(disabled()), biDisabledDown);

    // hoveredDown --> enabledDown
    biHoveredDown->addTransition(this, SIGNAL(mouseLeave()), biEnabledDown);

    // hoveredDown --> pressedDownUpIn
    biHoveredDown->addTransition(q, SIGNAL(pressed()), biPressedDownUp);

    // hoveredDown --> disabledDown
    biHoveredDown->addTransition(this, SIGNAL(disabled()), biDisabledDown);

    // pressedDownUpIn --> hoveredUp (trigger a ClickedAction)
    biPressedDownUp->addTransition(q, SIGNAL(released()), biHoveredUp)
        ->addAction(new ClickedAction(this, false));

    // pressedDownUpIn --> pressedDownUpOut
    biPressedDownUp->addTransition(this, SIGNAL(mouseLeave()), biCancelDownUp);

    // pressedDownUpIn --> disabledDown
    biPressedDownUp->addTransition(this, SIGNAL(disabled()), biDisabledDown);

    // pressedDownUpOut --> enabledDown
    biCancelDownUp->addTransition(q, SIGNAL(released()), biEnabledDown);

    // pressedDownUpOut --> pressedDownUpIn
    biCancelDownUp->addTransition(this, SIGNAL(mouseEnter()), biPressedDownUp);

    // pressedDownUpOut --> disabledDown
    biCancelDownUp->addTransition(this, SIGNAL(disabled()), biDisabledDown);

    // disabledDown --> enabledDown
    biDisabledDown->addTransition(this, SIGNAL(enabled()), biEnabledDown);

    //////////////////////////////////////////
    // Setup actions when states are activated
    //////////////////////////////////////////

    biEnabledUp->addEntryAction(new SetStateAction(this, enabledUp));
    biHoveredUp->addEntryAction(new SetStateAction(this, hoveredUp));
    biPressedUpDown->addEntryAction(new SetStateAction(this, pressedUpDown));
    biCancelUpDown->addEntryAction(new SetStateAction(this, enabledUp));
    biDisabledUp->addEntryAction(new SetStateAction(this, disabledUp));
    biEnabledDown->addEntryAction(new SetStateAction(this, enabledDown));
    biHoveredDown->addEntryAction(new SetStateAction(this, hoveredDown));
    biPressedDownUp->addEntryAction(new SetStateAction(this, pressedDownUp));
    biCancelDownUp->addEntryAction(new SetStateAction(this, enabledDown));
    biDisabledDown->addEntryAction(new SetStateAction(this, disabledDown));

    //////////////////////////
    // Setup the state machine
    //////////////////////////

    QtStateMachine* biMachine = new QtStateMachine(this);

    biMachine->addState(biEnabledUp);
    biMachine->addState(biHoveredUp);
    biMachine->addState(biPressedUpDown);
    biMachine->addState(biCancelUpDown);
    biMachine->addState(biDisabledUp);
    biMachine->addState(biEnabledDown);
    biMachine->addState(biHoveredDown);
    biMachine->addState(biPressedDownUp);
    biMachine->addState(biCancelDownUp);
    biMachine->addState(biDisabledDown);

    biMachine->setInitialState(q->isEnabled() ? biEnabledUp : biDisabledUp);
    biMachine->start();

    return biMachine;
}

//-------------------------------------------------------------------------------------------------
//
//  Declare internal classes for state machines
//
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
SetStateAction::SetStateAction(ButtonPrivate* btn_p, State* state, QObject* parent)
    : QtStateAction(parent)
    , m_btn_p(btn_p)
    , m_state(state)
{
}

//-------------------------------------------------------------------------------------------------
void SetStateAction::execute()
{
    m_btn_p->setState(m_state);
}

//-------------------------------------------------------------------------------------------------
ClickedAction::ClickedAction(ButtonPrivate* btn_p, bool down, QObject* parent)
    : QtStateAction(parent)
    , m_btn_p(btn_p)
    , m_down(down)
{
}

//-------------------------------------------------------------------------------------------------
void ClickedAction::execute()
{
    m_btn_p->clicked(m_down);
}

//-------------------------------------------------------------------------------------------------
//
//  End of internal classes for state machines
//
//-------------------------------------------------------------------------------------------------

} // namespace gics

