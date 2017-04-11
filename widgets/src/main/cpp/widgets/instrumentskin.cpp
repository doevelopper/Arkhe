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


#include <gics/private/instrumentskin.hpp>
#include <gics/instrument.hpp>
#include <gics/state.hpp>
#include <gics/qt.hpp>
#include <QDomElement>


namespace gics
{
//-------------------------------------------------------------------------------------------------
bool InstrumentSkin::load(QDomElement& element)
{
    // Load the global properties
    m_globalState = loadProperties(element);

    // Load states
    for (QDomElement stateElement = element.firstChildElement("state");
         !stateElement.isNull();
         stateElement = stateElement.nextSiblingElement("state"))
    {
        // Name is mandatory
        if (stateElement.hasAttribute("name"))
        {
            PropertyTable state = loadProperties(stateElement);
            m_states.insert(stateElement.attribute("name"), state);
        }
    }

    return true;
}

//-------------------------------------------------------------------------------------------------
void InstrumentSkin::apply(Instrument& instrument) const
{
    // Apply every state
    QStringList states = instrument.states();
    foreach (const QString& stateName, states)
    {
        State* state = instrument.state(stateName);
        if (state)
        {
            // Get the corresponding set of properties in the skin
            StateTable::ConstIterator it = m_states.find(stateName);
            const PropertyTable* properties = (it != m_states.end() ? &it.value() : 0);

            // First apply global properties
            PropertyTable::ConstIterator end = m_globalState.end();
            for (PropertyTable::ConstIterator itProp = m_globalState.begin(); itProp != end; ++itProp)
            {
                if (!properties || !properties->contains(itProp.key()))
                    state->setProperty(itProp.key(), itProp.value());
            }

            // Then apply the state's properties
            if (properties)
            {
                end = properties->end();
                for (PropertyTable::ConstIterator itProp = properties->begin(); itProp != end; ++itProp)
                {
                    state->setProperty(itProp.key(), itProp.value());
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------
InstrumentSkin::PropertyTable InstrumentSkin::loadProperties(QDomElement& element)
{
    PropertyTable properties;

    // Load properties
    for (QDomElement propertyElement = element.firstChildElement("property");
         !propertyElement.isNull();
         propertyElement = propertyElement.nextSiblingElement("property"))
    {
        // Name is mandatory
        if (propertyElement.hasAttribute("name"))
        {
            properties.insert(propertyElement.attribute("name"), propertyElement.text());
        }
    }

    return properties;
}

} // namespace gics
