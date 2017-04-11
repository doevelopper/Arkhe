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


#ifndef GICS_PRIVATE_SKIN_HPP
#define GICS_PRIVATE_SKIN_HPP


#include <gics/config.hpp>
#include <gics/private/instrumentskin.hpp>
#include <QString>
#include <QHash>


namespace gics
{
class Instrument;

/**
 * \brief Holds all the settings of a skin
 */
class Skin
{
public:

    /**
     * \brief Default constructor
     */
    Skin();

    /**
     * \brief Load the skin from a file
     *
     * \param filename Path of the skin file to load
     *
     * \return True if the skin was loaded successfully, false on error
     */
    bool load(const QString& filename);

    /**
     * \brief Get the skin identifier
     *
     * \return Skin identifier
     */
    const QString& id() const;

    /**
     * \brief Apply the skin to an instrument
     *
     * \param instrument Target instrument
     */
    void apply(Instrument& instrument) const;

private:

    typedef QHash<QString, InstrumentSkin> InstrumentTable;

    QString m_id; ///< Pointer to the private implementation
    InstrumentTable m_instruments; ///< Table of instruments skins
};

} // namespace gics


#endif // GICS_PRIVATE_SKIN_HPP
