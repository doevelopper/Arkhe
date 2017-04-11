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


#include <gics/private/svgelementmanager.hpp>
#include <QFileInfo>


namespace gics
{
//-------------------------------------------------------------------------------------------------
SvgElementManager& SvgElementManager::instance()
{
    static SvgElementManager manager;
    return manager;
}

//-------------------------------------------------------------------------------------------------
SvgElement SvgElementManager::get(const QString& filename, const QString& id)
{
    // Transform the filename to a unique representation (absolute + lower case)
    QString absoluteFilename = QFileInfo(filename).absoluteFilePath().toLower();

    // Find the file, or create it if it doesn't exist yet
    FileTable::iterator it = m_files.find(absoluteFilename);
    if (it == m_files.end())
    {
        SvgFile file;
        if (file.load(absoluteFilename))
            it = m_files.insert(absoluteFilename, file);
        else
            return SvgElement(); // @todo defaultSkin.element(id) ?
    }

    return it.value().element(id);
}

//-------------------------------------------------------------------------------------------------
SvgElementManager::SvgElementManager()
{
}

} // namespace gics
