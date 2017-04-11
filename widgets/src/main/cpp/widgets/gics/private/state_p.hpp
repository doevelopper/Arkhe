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


#ifndef GICS_PRIVATE_STATE_HPP
#define GICS_PRIVATE_STATE_HPP


#include <camp/userobject.hpp>
#include <camp/value.hpp>
#include <QMap>
#include <QString>


namespace gics
{
class Instrument;

/**
 * \brief Private implementation of State
 */
class StatePrivate
{
public:

    /**
     * \brief Apply a property to its owner instrument
     *
     * \param propName Name of the property
     * \param propValue Value to assign to the property
     */
    void applyProperty(const QString& propName, const camp::Value& propValue) const;

    /**
     * \brief Apply the value of a property to the given object
     *
     * This function parses the property name, and recursively calls itself if the
     * property is composed (i.e. has a sub-property, like "label.text").
     *
     * \param object Current object owning the property
     * \param propName Name of the property
     * \param propValue Value to assign to the property
     *
     * \return True on success, false if the property couldn't be set
     */
    static bool setPropertyValue(const camp::UserObject& object, const QString& propName, const camp::Value& propValue);

    typedef QMap<QString, camp::Value> PropertyTable;

    Instrument* owner; ///< Instrument owning the state
    QString name; ///< Name of the state
    PropertyTable properties; ///< Table of properties overriden by the state
};

} // namespace gics


#endif // GICS_PRIVATE_STATE_HPP
