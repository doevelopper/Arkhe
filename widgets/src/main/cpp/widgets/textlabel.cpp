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


#include <gics/textlabel.hpp>
#include <gics/private/textlabel_p.hpp>
#include <gics/picture.hpp>

namespace gics
{
//-------------------------------------------------------------------------------------------------
TextLabel::TextLabel(QGraphicsItem* parent)
    : Instrument(parent)
{
    d->label = new Label(this);
    d->enabled = createState("enabled");
    d->disabled = createState("disabled");

    setCentralItem(d->label);
    setState(d->enabled);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

//-------------------------------------------------------------------------------------------------
TextLabel::TextLabel(const QString& text, QGraphicsItem* parent)
    : Instrument(parent)
{
    d->label = new Label(text, this);
    d->enabled = createState("enabled");
    d->disabled = createState("disabled");

    setCentralItem(d->label);
    setState(d->enabled);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

//-------------------------------------------------------------------------------------------------
const QString& TextLabel::text() const
{
    return d->label->text();
}

//-------------------------------------------------------------------------------------------------
void TextLabel::setText(const QString& text)
{
    d->label->setText(text);
}

//-------------------------------------------------------------------------------------------------
QFont TextLabel::font() const
{
    return d->label->font();
}

//-------------------------------------------------------------------------------------------------
void TextLabel::setFont(const QFont& font)
{
    d->label->setFont(font);
}

//-------------------------------------------------------------------------------------------------
QColor TextLabel::color() const
{
    return d->label->color();
}

//-------------------------------------------------------------------------------------------------
void TextLabel::setColor(const QColor& color)
{
    d->label->setColor(color);
}

//-------------------------------------------------------------------------------------------------
Qt::TextElideMode TextLabel::elideMode() const
{
    return d->label->elideMode();
}

//-------------------------------------------------------------------------------------------------
void TextLabel::setElideMode(Qt::TextElideMode elideMode)
{
    d->label->setElideMode(elideMode);
}

//-------------------------------------------------------------------------------------------------
HorizontalAlignment TextLabel::horizontalTextAlignment() const
{
    return d->label->horizontalAlignment();
}

//-------------------------------------------------------------------------------------------------
void TextLabel::setHorizontalTextAlignment(HorizontalAlignment alignment)
{
    d->label->setHorizontalAlignment(alignment);
}

//-------------------------------------------------------------------------------------------------
VerticalAlignment TextLabel::verticalTextAlignment() const
{
    return d->label->verticalAlignment();
}

//-------------------------------------------------------------------------------------------------
void TextLabel::setVerticalTextAlignment(VerticalAlignment alignment)
{
    d->label->setVerticalAlignment(alignment);
}

//-------------------------------------------------------------------------------------------------
bool TextLabel::keepAspectRatio() const
{
   return Instrument::keepAspectRatio();
}

//-------------------------------------------------------------------------------------------------
void TextLabel::setKeepAspectRatio(bool keep)
{
    Instrument::setKeepAspectRatio(keep);
}

//-------------------------------------------------------------------------------------------------
State& TextLabel::enabledState()
{
    return *d->enabled;
}

//-------------------------------------------------------------------------------------------------
State& TextLabel::disabledState()
{
    return *d->disabled;
}

//-------------------------------------------------------------------------------------------------
void TextLabel::enabledChanged(bool enabled)
{
    setState(enabled ? d->enabled : d->disabled);
}

} // namespace gics

