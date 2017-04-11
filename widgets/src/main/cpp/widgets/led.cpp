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


#include <gics/led.hpp>
#include <gics/private/led_p.hpp>


namespace gics
{
//-------------------------------------------------------------------------------------------------
Led::Led(QGraphicsItem* parent)
    : Instrument(parent)
{
    // Declare states
    d->disabledOff = createState("disabledOff");
    d->disabledOn = createState("disabledOn");
    d->enabledOff = createState("enabledOff");
    d->enabledOn = createState("enabledOn");
    setState(d->enabledOff);
}

//-------------------------------------------------------------------------------------------------
bool Led::isOn() const
{
    return (currentState() == d->enabledOn) ||
           (currentState() == d->disabledOn);
}

//-------------------------------------------------------------------------------------------------
bool Led::isOff() const
{
    return !isOn();
}

//-------------------------------------------------------------------------------------------------
bool Led::keepAspectRatio() const
{
   return Instrument::keepAspectRatio();
}

//-------------------------------------------------------------------------------------------------
void Led::setKeepAspectRatio(bool keep)
{
    Instrument::setKeepAspectRatio(keep);
}

//-------------------------------------------------------------------------------------------------
State& Led::enabledOnState()
{
    return *d->enabledOn;
}

//-------------------------------------------------------------------------------------------------
State& Led::enabledOffState()
{
    return *d->enabledOff;
}

//-------------------------------------------------------------------------------------------------
State& Led::disabledOnState()
{
    return *d->disabledOn;
}

//-------------------------------------------------------------------------------------------------
State& Led::disabledOffState()
{
    return *d->disabledOff;
}

//-------------------------------------------------------------------------------------------------
void Led::setOn(bool on)
{
    if (isOn() != on)
        toggle();
}

//-------------------------------------------------------------------------------------------------
void Led::setOff(bool off)
{
    if (isOff() != off)
        toggle();
}

//-------------------------------------------------------------------------------------------------
void Led::toggle()
{
    if (isOff())
        setState(isEnabled() ? d->enabledOn : d->disabledOn);
    else
        setState(isEnabled() ? d->enabledOff : d->disabledOff);
}

//-------------------------------------------------------------------------------------------------
void Led::enabledChanged(bool enabled)
{
    if (enabled)
        setState(isOn() ? d->enabledOn : d->enabledOff);
    else
        setState(isOn() ? d->disabledOn : d->disabledOff);
}

} // namespace gics
