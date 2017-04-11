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


#include <gics/lcd.hpp>
#include <gics/private/lcd_p.hpp>
#include <gics/lcdrenderer.hpp>
#include <math.h>


namespace gics
{
//-------------------------------------------------------------------------------------------------
Lcd::Lcd(QGraphicsItem* parent)
    : Instrument(parent)
{
    // Create the LCD label
    d->lcd = new LcdLabel;
    setCentralItem(d->lcd);

    // Default values
    d->value = 0;
    d->integerPrecision = 3;
    d->decimalPrecision = 2;
    d->showLeadingZeros = false;
    d->showMinusSign = true;
    d->outOfRange = false;
    updateValue();

    // Declare states
    d->enabled = createState("enabled");
    d->disabled = createState("disabled");
    setState(d->enabled);
}

//-------------------------------------------------------------------------------------------------
double Lcd::value() const
{
    return d->value;
}

//-------------------------------------------------------------------------------------------------
unsigned int Lcd::integerPrecision() const
{
    return d->integerPrecision;
}

//-------------------------------------------------------------------------------------------------
void Lcd::setIntegerPrecision(unsigned int precision)
{
    if (precision != d->integerPrecision)
    {
        d->integerPrecision = precision;
        updateValue();
    }
}

//-------------------------------------------------------------------------------------------------
unsigned int Lcd::decimalPrecision() const
{
    return d->decimalPrecision;
}

//-------------------------------------------------------------------------------------------------
void Lcd::setDecimalPrecision(unsigned int precision)
{
    if (precision != d->decimalPrecision)
    {
        d->decimalPrecision = precision;
        updateValue();
    }
}

//-------------------------------------------------------------------------------------------------
bool Lcd::showLeadingZeros() const
{
    return d->showLeadingZeros;
}

//-------------------------------------------------------------------------------------------------
void Lcd::setShowLeadingZeros(bool show)
{
    if (show != d->showLeadingZeros)
    {
        d->showLeadingZeros = show;
        updateValue();
    }
}

//-------------------------------------------------------------------------------------------------
bool Lcd::showMinusSign() const
{
    return d->showMinusSign;
}

//-------------------------------------------------------------------------------------------------
void Lcd::setShowMinusSign(bool show)
{
    if (show != d->showMinusSign)
    {
        d->showMinusSign = show;
        updateValue();
    }
}

//-------------------------------------------------------------------------------------------------
Lcd::DisplayType Lcd::displayType() const
{
    if (d->lcd->renderer() == LcdRenderer::seven())
    {
        return sevenSegments;
    }
    else if (d->lcd->renderer() == LcdRenderer::fourteen())
    {
        return fourteenSegments;
    }
    else if (d->lcd->renderer() == LcdRenderer::pixel())
    {
        return pixelSegments;
    }
    else
    {
        return sevenSegments;
    }
}

//-------------------------------------------------------------------------------------------------
void Lcd::setDisplayType(DisplayType type)
{
    switch (type)
    {
        case sevenSegments:    d->lcd->setRenderer(LcdRenderer::seven());    break;
        case fourteenSegments: d->lcd->setRenderer(LcdRenderer::fourteen()); break;
        case pixelSegments:    d->lcd->setRenderer(LcdRenderer::pixel());    break;
        default:               d->lcd->setRenderer(LcdRenderer::seven());    break;
    }
}

//-------------------------------------------------------------------------------------------------
const QColor& Lcd::activeColor() const
{
    return d->lcd->activeColor();
}

//-------------------------------------------------------------------------------------------------
void Lcd::setActiveColor(const QColor& activeColor)
{
    d->lcd->setActiveColor(activeColor);
}

//-------------------------------------------------------------------------------------------------
const QColor& Lcd::inactiveColor() const
{
    return d->lcd->inactiveColor();
}

//-------------------------------------------------------------------------------------------------
void Lcd::setInactiveColor(const QColor& inactiveColor)
{
    d->lcd->setInactiveColor(inactiveColor);
}

//-------------------------------------------------------------------------------------------------
bool Lcd::keepAspectRatio() const
{
   return Instrument::keepAspectRatio();
}

//-------------------------------------------------------------------------------------------------
void Lcd::setKeepAspectRatio(bool keep)
{
    Instrument::setKeepAspectRatio(keep);
}

//-------------------------------------------------------------------------------------------------
State& Lcd::enabledState()
{
    return *d->enabled;
}

//-------------------------------------------------------------------------------------------------
State& Lcd::disabledState()
{
    return *d->disabled;
}

//-------------------------------------------------------------------------------------------------
void Lcd::setValue(double value)
{
    if (value != d->value)
    {
        d->value = value;
        updateValue();
    }
}

//-------------------------------------------------------------------------------------------------
void Lcd::enabledChanged(bool enabled)
{
    setState(enabled ? d->enabled : d->disabled);
}

//-------------------------------------------------------------------------------------------------
void Lcd::updateValue()
{
    // Forward to the implementation, and handle a potential change of out-of-range state
    bool outOfRange = d->outOfRange;
    d->update();
    update();

    // If the out-of-range state has changed, we send the proper signals
    if (d->outOfRange != outOfRange)
    {
        emit outOfRangeToggled(d->outOfRange);
        if (d->outOfRange)
            emit outOfRangeEntered();
    }
}


//----------------------------------- PRIVATE PART ------------------------------------------------


//-------------------------------------------------------------------------------------------------
void LcdPrivate::update()
{
    outOfRange = false;

    // Convert the value to string
    double absValue = fabs(value);
    QString text = QString("%1").arg(absValue, 0, 'f', decimalPrecision);

    // Pad the integer part if needed
    int separator = text.indexOf('.');
    int padding = integerPrecision - (separator < 0 ? text.size() : separator);
    if (padding > 0)
    {
        text = QString(padding, showLeadingZeros ? '0' : ' ') + text;
    }
    else if (padding < 0)
    {
        if ((integerPrecision == 0) && (absValue < 1))
        {
            // Special case when no integer digit and value is in range ]-1, 1[: we remove the leading 0
            text.remove(0, 1);
        }
        else
        {
            // Too many digits: out-of-range
            outOfRange = true;
            text = QString(integerPrecision, '9');
            if (decimalPrecision > 0)
                text += "." + QString(decimalPrecision, '9');
        }
    }

    // Add the minus sign if needed
    if (showMinusSign)
        text.prepend(value < 0 ? '-' : ' ');

    // Send the new text to the LCD component
    lcd->setText(text);
}


} // namespace gics
