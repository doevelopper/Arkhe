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


#include <gics/numericlabel.hpp>
#include <gics/private/numericlabel_p.hpp>
#include <gics/picture.hpp>

namespace gics
{
//-------------------------------------------------------------------------------------------------
NumericLabel::NumericLabel(QGraphicsItem* parent)
    : Instrument(parent)
{
    d->label = new Label(this);
    d->enabled = createState("enabled");
    d->disabled = createState("disabled");

    d->value = 0.0;
    d->precision = 2;

    setCentralItem(d->label);
    setState(d->enabled);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    d->updateText();
}

//-------------------------------------------------------------------------------------------------
NumericLabel::NumericLabel(double value, unsigned int precision, QGraphicsItem* parent)
    : Instrument(parent)
{
    d->label = new Label(this);
    d->enabled = createState("enabled");
    d->disabled = createState("disabled");

    d->value = value;
    d->precision = precision;

    setCentralItem(d->label);
    setState(d->enabled);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    d->updateText();
}

//-------------------------------------------------------------------------------------------------
double NumericLabel::value() const
{
    return d->value;
}

//-------------------------------------------------------------------------------------------------
void NumericLabel::setValue(double value)
{
    if (d->value != value)
    {
        d->value = value;
        d->updateText();
    }
}

//-------------------------------------------------------------------------------------------------
unsigned int NumericLabel::precision() const
{
    return d->precision;
}

//-------------------------------------------------------------------------------------------------
void NumericLabel::setPrecision(unsigned int precision)
{
    if (d->precision != precision)
    {
        d->precision = precision;
        d->updateText();
    }
}

//-------------------------------------------------------------------------------------------------
const QString& NumericLabel::prefix() const
{
    return d->prefix;
}

//-------------------------------------------------------------------------------------------------
void NumericLabel::setPrefix(const QString& prefix)
{
    if (d->prefix != prefix)
    {
        d->prefix = prefix;
        d->updateText();
    }
}

//-------------------------------------------------------------------------------------------------
const QString& NumericLabel::suffix() const
{
    return d->suffix;
}

//-------------------------------------------------------------------------------------------------
void NumericLabel::setSuffix(const QString& suffix)
{
    if (d->suffix != suffix)
    {
        d->suffix = suffix;
        d->updateText();
    }
}

//-------------------------------------------------------------------------------------------------
QFont NumericLabel::font() const
{
    return d->label->font();
}

//-------------------------------------------------------------------------------------------------
void NumericLabel::setFont(const QFont& font)
{
    d->label->setFont(font);
}

//-------------------------------------------------------------------------------------------------
QColor NumericLabel::color() const
{
    return d->label->color();
}

//-------------------------------------------------------------------------------------------------
void NumericLabel::setColor(const QColor& color)
{
    d->label->setColor(color);
}

//-------------------------------------------------------------------------------------------------
Qt::TextElideMode NumericLabel::elideMode() const
{
    return d->label->elideMode();
}

//-------------------------------------------------------------------------------------------------
void NumericLabel::setElideMode(Qt::TextElideMode elideMode)
{
    d->label->setElideMode(elideMode);
}

//-------------------------------------------------------------------------------------------------
HorizontalAlignment NumericLabel::horizontalTextAlignment() const
{
    return d->label->horizontalAlignment();
}

//-------------------------------------------------------------------------------------------------
void NumericLabel::setHorizontalTextAlignment(HorizontalAlignment alignment)
{
    d->label->setHorizontalAlignment(alignment);
}

//-------------------------------------------------------------------------------------------------
VerticalAlignment NumericLabel::verticalTextAlignment() const
{
    return d->label->verticalAlignment();
}

//-------------------------------------------------------------------------------------------------
void NumericLabel::setVerticalTextAlignment(VerticalAlignment alignment)
{
    d->label->setVerticalAlignment(alignment);
}

//-------------------------------------------------------------------------------------------------
bool NumericLabel::keepAspectRatio() const
{
   return Instrument::keepAspectRatio();
}

//-------------------------------------------------------------------------------------------------
void NumericLabel::setKeepAspectRatio(bool keep)
{
    Instrument::setKeepAspectRatio(keep);
}

//-------------------------------------------------------------------------------------------------
State& NumericLabel::enabledState()
{
    return *d->enabled;
}

//-------------------------------------------------------------------------------------------------
State& NumericLabel::disabledState()
{
    return *d->disabled;
}

//-------------------------------------------------------------------------------------------------
void NumericLabel::enabledChanged(bool enabled)
{
    setState(enabled ? d->enabled : d->disabled);
}

//-------------------------------------------------------------------------------------------------
void NumericLabelPrivate::updateText()
{
    QString s;

    s.append(prefix);
    s.append(QLocale().toString(value, 'f', precision));
    s.append(suffix);

    label->setText(s);
}

} // namespace gics

