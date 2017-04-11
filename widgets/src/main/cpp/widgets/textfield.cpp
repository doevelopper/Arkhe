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


#include <gics/textfield.hpp>
#include <gics/private/textfield_p.hpp>
#include <gics/field.hpp>
#include <gics/label.hpp>
#include <gics/state.hpp>
#include <gics/picture.hpp>

namespace gics
{
//-------------------------------------------------------------------------------------------------
TextField::TextField(QGraphicsItem* parent)
    : Instrument(parent) 
{
    d->field = new Field;
    setCentralItem(d->field);

    // Declare states
    d->disabled = createState("disabled");
    d->enabled = createState("enabled");
    d->editing = createState("editing");
    d->hovered = createState("hovered");
    setState(d->enabled);

    connect(d->field, SIGNAL(textChanged(const QString&)), this, SIGNAL(textChanged(const QString&)));
    connect(d->field, SIGNAL(editModeToggled(bool)), this, SLOT(handleEditModeToggled(bool)));
    connect(d->field, SIGNAL(hoverIn()), this, SLOT(handleHoverIn()));
    connect(d->field, SIGNAL(hoverOut()), this, SLOT(handleHoverOut()));
}

//-------------------------------------------------------------------------------------------------
TextField::TextField(const QString& text, QGraphicsItem* parent)
    : Instrument(parent) 
{
    d->field = new Field(text);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    setCentralItem(d->field);

    // Declare states
    d->disabled = createState("disabled");
    d->enabled = createState("enabled");
    d->editing = createState("editing");
    d->hovered = createState("hovered");
    setState(d->enabled);

    connect(d->field, SIGNAL(textChanged(const QString&)), this, SIGNAL(textChanged(const QString&)));
    connect(d->field, SIGNAL(editModeToggled(bool)), this, SLOT(handleEditModeToggled(bool)));
    connect(d->field, SIGNAL(hoverIn()), this, SLOT(handleHoverIn()));
    connect(d->field, SIGNAL(hoverOut()), this, SLOT(handleHoverOut()));
}

//-------------------------------------------------------------------------------------------------
TextField::~TextField()
{
}

//-------------------------------------------------------------------------------------------------
void TextField::setText(const QString& text)
{
    d->field->setText(text);
}

//-------------------------------------------------------------------------------------------------
QString TextField::text() const
{
    return d->field->text();
}

//-------------------------------------------------------------------------------------------------
void TextField::setColor(const QColor& color)
{
    d->field->setColor(color);
}

//-------------------------------------------------------------------------------------------------
const QColor& TextField::color() const
{
    return d->field->color();
}

//-------------------------------------------------------------------------------------------------
void TextField::setFont(const QFont& font)
{
    d->field->setFont(font);
}

//-------------------------------------------------------------------------------------------------
const QFont& TextField::font() const
{     
    return d->field->font();
}
 
//-------------------------------------------------------------------------------------------------
void TextField::setHorizontalTextAlignment(HorizontalAlignment alignment)
{
    d->field->setHorizontalAlignment(alignment);
}

//-------------------------------------------------------------------------------------------------
HorizontalAlignment TextField::horizontalTextAlignment() const
{
    return d->field->horizontalAlignment();
}

//-------------------------------------------------------------------------------------------------
void TextField::setVerticalTextAlignment(VerticalAlignment alignment)
{
    d->field->setVerticalAlignment(alignment);
}

//-------------------------------------------------------------------------------------------------
VerticalAlignment TextField::verticalTextAlignment() const
{
    return d->field->verticalAlignment();
}

//-------------------------------------------------------------------------------------------------
void TextField::setValidateOnFocusOut(bool validateOnFocusOut)
{
    d->field->setValidateOnFocusOut(validateOnFocusOut);	
}

//-------------------------------------------------------------------------------------------------
bool TextField::validateOnFocusOut() const
{
    return d->field->validateOnFocusOut();
}

//-------------------------------------------------------------------------------------------------
bool TextField::keepAspectRatio() const
{
   return Instrument::keepAspectRatio();
}

//-------------------------------------------------------------------------------------------------
void TextField::setKeepAspectRatio(bool keep)
{
    Instrument::setKeepAspectRatio(keep);
}

//-------------------------------------------------------------------------------------------------
State& TextField::enabledState()
{
    return *d->enabled;
}

//-------------------------------------------------------------------------------------------------
State& TextField::disabledState()
{
    return *d->disabled;
}

//-------------------------------------------------------------------------------------------------
State& TextField::editingState()
{
    return *d->editing;
}

//-------------------------------------------------------------------------------------------------
State& TextField::hoveredState()
{
    return *d->hovered;
}

//-------------------------------------------------------------------------------------------------
QSizeF TextField::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    switch (which)
    {
        case Qt::PreferredSize:
        case Qt::MinimumSize:
            return d->field->sizeHint(which, constraint);

        default:
            return Instrument::sizeHint(which, constraint);
    }
}

//-------------------------------------------------------------------------------------------------
void TextField::enabledChanged(bool enabled)
{
    d->field->setEditable(enabled);
    if(!enabled)
        setState(d->disabled);
    else
        setState(d->enabled);
}

//-------------------------------------------------------------------------------------------------
void TextField::handleEditModeToggled(bool edited)
{
    if (edited == true)
        setState(d->editing);
    else
        setState(d->enabled);
    emit editModeToggled(edited);
}

//-------------------------------------------------------------------------------------------------
void TextField::handleHoverIn()
{
    if (currentState() == d->enabled)
    {
        setState(d->hovered);
        emit hoverIn();
    }
}

//-------------------------------------------------------------------------------------------------
void TextField::handleHoverOut()
{
    if (currentState() == d->hovered)
    {
        setState(d->enabled);
        emit hoverOut();
    }
}

} // namespace gics
