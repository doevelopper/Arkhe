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


#ifndef GICS_PRIVATE_SVGELEMENTMANAGER_HPP
#define GICS_PRIVATE_SVGELEMENTMANAGER_HPP


#include <gics/private/svgfile.hpp>
#include <boost/noncopyable.hpp>
#include <QMap>
#include <QString>


namespace gics
{
/**
 * \brief Manager for SVG elements
 *
 * This manager creates, stores and gives optimized access to SVG elements within
 * SVG files. It ensures that no resource is duplicated.
 *
 * This class implements the singleton pattern, and thus has a unique instance.
 *
 * \sa SvgElement, SvgFile
 */
class SvgElementManager : boost::noncopyable
{
public:

    /**
     * \brief Return the unique instance of the class
     *
     * \return Instance of the SVG element manager
     */
    static SvgElementManager& instance();

    /**
     * \brief Get a SVG element from its SVG file and its identifier
     *
     * \param filename Point to check, in item coordinates
     * \param id Point to check, in item coordinates
     *
     * \return SvgElement instance containing the loaded element, or an empty instance if any error happened
     */
    SvgElement get(const QString& filename, const QString& id);

private:

    /**
     * \brief Default constructor
     */
    SvgElementManager();

private:

    typedef QMap<QString, SvgFile> FileTable;

    FileTable m_files; ///< Table of SVG files associated to their filenames
};

} // namespace gics


#endif // GICS_PRIVATE_SVGELEMENTMANAGER_HPP
