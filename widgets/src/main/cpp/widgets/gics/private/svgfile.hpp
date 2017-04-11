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


#ifndef GICS_PRIVATE_SVGFILE_HPP
#define GICS_PRIVATE_SVGFILE_HPP


#include <gics/private/svgmask.hpp>
#include <gics/private/svgelement.hpp>
#include <boost/shared_ptr.hpp>
#include <QMap>
#include <QString>


class QByteArray;
class QSvgRenderer;

namespace gics
{
/**
 * \brief Represents a SVG file containing several elements
 *
 * \sa SvgElement
 */
class SvgFile
{
public:

    /**
     * \brief Load from a SVG file
     *
     * \param filename Name of the SVG file
     *
     * \return True if loading succeeded, false if any error happened
     */
    bool load(const QString& filename);

    /**
     * \brief Load from a byte array
     *
     * \param data Byte array containing the SVG structure
     *
     * \return True if loading succeeded, false if any error happened
     */
    bool load(const QByteArray& data);

    /**
     * \brief Return a SVG element from its identifier
     *
     * \param id Identifier of the element
     *
     * \return SvgElement corresponding to \a id, or an empty instance if \a id is not a valid identifier
     */
    SvgElement element(const QString& id);

private:

    typedef QMap<QString, SvgMask> MaskTable;

    boost::shared_ptr<QSvgRenderer> m_renderer; ///< SVG renderer containing all the elements of the file
    MaskTable m_masks; ///< Table containing the transparency masks of each element
};

} // namespace gics


#endif // GICS_PRIVATE_SVGFILE_HPP
