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


#ifndef GICS_PRIVATE_PICTURE_HPP
#define GICS_PRIVATE_PICTURE_HPP


#include <gics/picture.hpp>
#include <gics/private/svgelement.hpp>
#include <QString>


namespace gics
{
/**
 * \brief Private implementation of Picture
 */
class PicturePrivate
{
public:

    /**
     * \brief Default constructor
     */
    PicturePrivate();

    /**
     * \brief Update the SVG elements after the file or id has changed
     */
    void updateElements();

    /**
     * \brief Test if a given element contains a point
     *
     * \param point Point to test in picture coordinates
     * \param element Element to test
     * \param boundingRect Bounding rectangle of the element in picture coordinates
     */
    bool contains(const QPointF& point, const SvgElement& element, const QRectF& boundingRect) const;

public:

    SvgElement center; ///< SVG element to display (center)
    SvgElement left; ///< Optional SVG element for the left border
    SvgElement top; ///< Optional SVG element for the top border
    SvgElement right; ///< Optional SVG element for the right border
    SvgElement bottom; ///< Optional SVG element for the bottom border
    SvgElement topLeft; ///< Optional SVG element for the top-left corner
    SvgElement topRight; ///< Optional SVG element for the top-right corner
    SvgElement bottomLeft; ///< Optional SVG element for the bottom-left corner
    SvgElement bottomRight; ///< Optional SVG element for the bottom-right corner
    QString file; ///< Source file for the SVG element
    QString id; ///< Identifier of the element within the SVG file
    qreal leftBorder; ///< Left border thickness
    qreal topBorder; ///< Top border thickness
    qreal rightBorder; ///< Right border thickness
    qreal bottomBorder; ///< Bottom border thickness
    Picture::BorderMode borderMode; ///< Resize policy for borders
};

} // namespace gics


#endif // GICS_PRIVATE_PICTURE_HPP
