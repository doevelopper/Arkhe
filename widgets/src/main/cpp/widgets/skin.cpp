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


#include <gics/private/skin.hpp>
#include <gics/instrument.hpp>
#include <camp/class.hpp>
#include <camp/classget.hpp>
#include <QDomDocument>
#include <QFile>


namespace gics
{
//-------------------------------------------------------------------------------------------------
Skin::Skin()
{
}

//-------------------------------------------------------------------------------------------------
bool Skin::load(const QString& filename)
{
    // Open the file
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
        return false;

    // Parse it
    QDomDocument document;
    if (!document.setContent(&file))
        return false;
    QDomElement root = document.documentElement();

    // Extract the identifier
    if (!root.hasAttribute("id"))
        return false;
    m_id = root.attribute("id");

    // Extract instruments
    for (QDomElement instrElement = root.firstChildElement("instrument");
         !instrElement.isNull();
         instrElement = instrElement.nextSiblingElement("instrument"))
    {
        // Class name is mandatory
        if (instrElement.hasAttribute("class"))
        {
            // Make sure that the instrument doesn't already exists
            QString instrumentClass = instrElement.attribute("class") + instrElement.attribute("subclass");
            if (!m_instruments.contains(instrumentClass))
            {
                // Load the instrument skin
                InstrumentSkin instrumentSkin;
                if (instrumentSkin.load(instrElement))
                    m_instruments.insert(instrumentClass, instrumentSkin);
            }
        }
    }

    return true;
}

//-------------------------------------------------------------------------------------------------
const QString& Skin::id() const
{
    return m_id;
}

//-------------------------------------------------------------------------------------------------
void Skin::apply(Instrument& instrument) const
{
    // Get the class of the instrument from its metaclass
    QString instrumentClass = QString::fromStdString(camp::classByObject(instrument).name()) + instrument.subClass();

    // Forward to the corresponding instrument skin
    InstrumentTable::ConstIterator it = m_instruments.find(instrumentClass);
    if (it != m_instruments.end())
        it.value().apply(instrument);
}

} // namespace gics
