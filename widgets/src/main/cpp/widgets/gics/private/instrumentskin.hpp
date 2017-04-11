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


#ifndef GICS_PRIVATE_INSTRUMENTSKIN_HPP
#define GICS_PRIVATE_INSTRUMENTSKIN_HPP


#include <gics/config.hpp>
#include <camp/value.hpp>
#include <QString>
#include <QHash>


class QDomElement;

namespace gics
{
class Instrument;

/**
 * \brief Holds the properties of an instrument class inside a skin
 *
 * \sa Skin
 */
class InstrumentSkin
{
public:

    /**
     * \brief Load the instrument skin from a n XML element
     *
     * \param element XML element to parse
     *
     * \return True if the skin was loaded successfully, false on error
     */
    bool load(QDomElement& element);

    /**
     * \brief Apply the skin to an instrument
     *
     * \param instrument Target instrument
     */
    void apply(Instrument& instrument) const;

private:

    typedef QHash<QString, camp::Value> PropertyTable;
    typedef QHash<QString, PropertyTable> StateTable;

    /**
     * \brief Load a set of properties from an XML element
     *
     * \param element XML element to parse
     *
     * \return Loaded table of properties
     */
    PropertyTable loadProperties(QDomElement& element);

private:

    PropertyTable m_globalState; ///< Set of properties global to every state
    StateTable m_states; ///< Table of states
};

} // namespace gics


#endif // GICS_PRIVATE_INSTRUMENTSKIN_HPP
