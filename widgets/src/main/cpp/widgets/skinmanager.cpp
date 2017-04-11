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


#include <gics/skinmanager.hpp>
#include <gics/private/skinmanager_p.hpp>


namespace gics
{
//-------------------------------------------------------------------------------------------------
SkinManager& SkinManager::instance()
{
    static SkinManager manager;
    return manager;
}

//-------------------------------------------------------------------------------------------------
QString SkinManager::registerSkin(const QString& filename)
{
    // Load the skin
    Skin skin;
    if (!skin.load(filename))
        return "";

    // Add it to the table if its identifier is not already registered
    QString id = skin.id();
    if (!d->skins.contains(id))
        d->skins.insert(id, skin);

    return id;
}

//-------------------------------------------------------------------------------------------------
void SkinManager::unregisterSkin(const QString& id)
{
    // Unregistering the default skin is not allowed!
    if (id != d->defaultSkin->id())
        d->skins.remove(id);
}

//-------------------------------------------------------------------------------------------------
QStringList SkinManager::skins() const
{
    return d->skins.keys();
}

//-------------------------------------------------------------------------------------------------
const QString& SkinManager::globalSkin() const
{
    return d->globalSkin->id();
}

//-------------------------------------------------------------------------------------------------
bool SkinManager::setGlobalSkin(const QString& id)
{
    if (id != d->globalSkin->id())
    {
        // @todo Apply the new skin (!!)
        // see QApplication::allWidgets and filter on type (Instrument)

        SkinManagerPrivate::SkinTable::ConstIterator it = d->skins.find(id);
        if (it != d->skins.end())
        {
            d->globalSkin = &it.value();
            return true;
        }
        else
        {
            d->globalSkin = d->defaultSkin;
            return false;
        }
    }
    else
    {
        return true;
    }
}

//-------------------------------------------------------------------------------------------------
const QString& SkinManager::defaultSkin() const
{
    return d->defaultSkin->id();
}

//-------------------------------------------------------------------------------------------------
void SkinManager::applySkin(const QString& id, Instrument& instrument) const
{
    SkinManagerPrivate::SkinTable::ConstIterator it = d->skins.find(id);
    if (it != d->skins.end())
        it.value().apply(instrument);
}

//-------------------------------------------------------------------------------------------------
SkinManager::SkinManager()
{
    // Register the default skin
    QString id = registerSkin(":/skins/defaultskin.xml");
    d->defaultSkin = d->globalSkin = &d->skins[id];
}

} // namespace gics
