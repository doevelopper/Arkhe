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


#include <gics/state.hpp>
#include <gics/instrument.hpp>
#include <gics/private/state_p.hpp>
#include <camp/class.hpp>
#include <QtDebug>


namespace gics
{
//-------------------------------------------------------------------------------------------------
const QString& State::name() const
{
    return d->name;
}

//-------------------------------------------------------------------------------------------------
const camp::Value& State::property(const QString& name) const
{
    StatePrivate::PropertyTable::const_iterator it = d->properties.find(name);

    return it != d->properties.end() ? it.value() : camp::Value::nothing;
}

//-------------------------------------------------------------------------------------------------
void State::setProperty(const QString& name, const camp::Value& value)
{
    if (value != camp::Value::nothing)
    {
        // Store the new value of the property
        d->properties[name] = value;

        // Apply it directly if we are the current state of the instrument
        if (d->owner->currentState() == this)
            d->applyProperty(name, value);
    }
    else
    {
        resetProperty(name);
    }
}

//-------------------------------------------------------------------------------------------------
void State::resetProperty(const QString& name)
{
    d->properties.remove(name);
}

//-------------------------------------------------------------------------------------------------
bool State::hasProperty(const QString& name) const
{
    return d->properties.contains(name);
}

//-------------------------------------------------------------------------------------------------
void State::apply() const
{
    // Browse all properties defined in the state
    StatePrivate::PropertyTable::const_iterator end = d->properties.end();
    for (StatePrivate::PropertyTable::const_iterator it = d->properties.begin(); it != end; ++it)
    {
        d->applyProperty(it.key(), it.value());
    }
}

//-------------------------------------------------------------------------------------------------
State::State(const QString& name, Instrument& owner)
{
    d->name = name;
    d->owner = &owner;
}


//----------------------------------- PRIVATE PART ------------------------------------------------


//-------------------------------------------------------------------------------------------------
void StatePrivate::applyProperty(const QString& propName, const camp::Value& propValue) const
{
    try
    {
        if (!setPropertyValue(owner, propName, propValue))
        {
            qWarning() << "State" << name << "failed to override property" << propName;
        }
    }
    catch (const camp::Error& error)
    {
        // We handle CAMP errors here and make sure they are not propagated upwards
        qWarning() << "Error while setting the property" << propName << "in state"
            << name << "of instrument" << camp::classByObject(owner).name().c_str()
                   << "(" << error.what() << ")";
    }
}

//-------------------------------------------------------------------------------------------------
bool StatePrivate::setPropertyValue(const camp::UserObject& object, const QString& propName, const camp::Value& propValue)
{
    int position = propName.indexOf('.');
    if (position == -1)
    {
        // No more sub-properties: we can set the value
        const camp::Property& property = object.getClass().property(propName.toStdString());
        property.set(object, propValue);
        return true;
    }
    else
    {
        // We found a sub-property: continue parsing the name
        QString propertyName = propName.left(position);
        QString subPropertyName = propName.right(propName.size() - position - 1);
        const camp::Property& property = object.getClass().property(propertyName.toStdString());
        if (property.type() == camp::userType)
        {
            const camp::UserProperty& userProperty = static_cast<const camp::UserProperty&>(property);
            return setPropertyValue(camp::UserObject(object, userProperty), subPropertyName, propValue);
        }
        else
        {
            return false;
        }
    }
}

} // namespace gics
