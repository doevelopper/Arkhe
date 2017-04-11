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


#ifndef GICS_SKINMANAGER_HPP
#define GICS_SKINMANAGER_HPP


#include <gics/config.hpp>
#include <goost/pimplptr.hpp>
#include <boost/noncopyable.hpp>
#include <QString>
#include <QStringList>


namespace gics
{
class Instrument;

/**
 * \brief Manager for skins
 *
 * This manager registers, stores and gives access to the instruments skins.
 * It also holds the default and global skins.
 *
 * This class implements the singleton pattern, and thus has a unique instance.
 */
class GICS_API SkinManager : boost::noncopyable
{
public:

    /**
     * \brief Return the unique instance of the class
     *
     * \return Instance of the skin manager
     */
    static SkinManager& instance();

    /**
     * \brief Register a new skin from its filename
     *
     * If a skin was already registered, it will just return true.
     * Once registered, skins are accessed by their unique identifier.
     *
     * \param filename Path of the skin file to register
     *
     * \return The identifier of the registered skin, or an empty string if registration failed
     */
    QString registerSkin(const QString& filename);

    /**
     * \brief Unregister a new skin from its identifier
     *
     * If the skin was not registered, it won't do anything.
     *
     * \param id Identifier of the skin
     *
     * \return True if the skin was registered successfully, false on error
     */
    void unregisterSkin(const QString& id);

    /**
     * \brief Return a list of all the registered skins
     *
     * \return List containing the identifiers of all the registered skins
     */
    QStringList skins() const;

    /**
     * \brief Get the current global skin
     *
     * The global skin is the fallback for instruments that do not have
     * a specific skin assigned. By default, the global skin is the default skin.
     *
     * \return Identifier of the current global skin
     */
    const QString& globalSkin() const;

    /**
     * \brief Change the current global skin
     *
     * If the given skin is not registered, the default skin is used.
     *
     * \param id Identifier of the new global skin
     *
     * \return True if the new skin was properly assigned
     */
    bool setGlobalSkin(const QString& id);

    /**
     * \brief Get the built-in default skin
     *
     * The default skin is the one that is bundled with the library,
     * and is used by default by every instruments until you register and
     * set your own skins.
     *
     * \return Identifier of the default skin
     */
    const QString& defaultSkin() const;

    /**
     * \brief Apply a particular skin to an instrument
     *
     * If the skin is not registered, this function does nothing.
     *
     * \param id Identifier of the skin to apply
     * \param instrument Target instrument
     */
    void applySkin(const QString& id, Instrument& instrument) const;

private:

    /**
     * \brief Default constructor
     */
    SkinManager();

private:

    goost::PimplPtr<class SkinManagerPrivate> d; ///< Pointer to the private implementation
};

} // namespace gics


#endif // GICS_SKINMANAGER_HPP
