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


#include <gics/private/svgmask.hpp>
#include <QSvgRenderer>
#include <QPainter>


namespace gics
{
//-------------------------------------------------------------------------------------------------
SvgMask::SvgMask(QSvgRenderer& renderer, const QString& id, QSize imageSize)
{
    // Retrieve the size of the item
    QSizeF itemSize = renderer.boundsOnElement(id).size();

    // If no image size is provided, we use the bounding rectangle of the item
    if (!imageSize.isValid())
        imageSize = itemSize.toSize();

    // Render the item into a temporary 32 bits image (the only format handling alpha)
    QImage itemImage(imageSize.width(), imageSize.height(), QImage::Format_ARGB32);
    itemImage.fill(0);
    QPainter painter(&itemImage);
    renderer.render(&painter, id);
    painter.end();

    // Extract the alpha channel of the image, it's our transparency mask
    m_mask = itemImage.alphaChannel();

    // Store the factor to map from item coordinates to image coordinates
    m_mapFactor.setWidth(m_mask.size().width() / itemSize.width());
    m_mapFactor.setHeight(m_mask.size().height() / itemSize.height());
}

//-------------------------------------------------------------------------------------------------
bool SvgMask::contains(const QPointF& point) const
{
    // Convert from item space to image space
    int x = qRound(point.x() * m_mapFactor.width());
    int y = qRound(point.y() * m_mapFactor.height());

    // Make sure the point lies within the image's area
    if (!m_mask.valid(x, y))
        return false;

    // Extract any channel of the pixel in the mask (they all store the transparency)
    int alpha = qRed(m_mask.pixel(x, y));

    return alpha > 0;
}

} // namespace gics
