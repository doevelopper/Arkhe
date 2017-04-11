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


#ifndef GICS_PRIVATE_SVGMASK_HPP
#define GICS_PRIVATE_SVGMASK_HPP


#include <QImage>
#include <QSizeF>
#include <QString>


class QSvgRenderer;

namespace gics
{
/**
 * \brief Pixel based mask of a SvgElement
 *
 * A mask is a monochrome image, which contains a rendering
 * of a SVG item and which is able to perform accurate collision
 * tests based on the alpha value (transparency) of pixels.
 *
 * This class is a workaround needed because of the lack of accurate shape support in
 * QGraphicsSvgItem. This means that SvgMask may be removed when Qt provides a better support
 * for this feature.
 *
 * \sa SvgElement
 */
class SvgMask
{
public:

    /**
     * \brief Construct the mask from an item
     *
     * \param renderer SVG renderer owning the item
     * \param id Identifier of the item within the renderer
     * \param imageSize Size of the image to generate, in pixels (size of the item by default)
     */
    SvgMask(QSvgRenderer& renderer, const QString& id, QSize imageSize = QSize());

    /**
     * \brief Check if a point is inside the opaque area of the mask
     *
     * \param point Point to check, in item coordinates
     *
     * \return True if the point lies within the opaque area of the mask, false otherwise
     */
    bool contains(const QPointF& point) const;

private:

    QImage m_mask; ///< Image containing the transparency mask
    QSizeF m_mapFactor; ///< Factor to map from item coordinates to image coordinates
};

} // namespace gics


#endif // GICS_PRIVATE_SVGMASK_HPP
