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


#ifndef GICS_PRIVATE_SVGELEMENT_HPP
#define GICS_PRIVATE_SVGELEMENT_HPP


#include <QRectF>
#include <QString>


class QSvgRenderer;
class QPainter;

namespace gics
{
class SvgMask;

/**
 * \brief Represents a single element within a SVG file
 *
 * \sa SvgMask, SvgFile
 */
class SvgElement
{
public:

    /**
     * \brief Default constructor
     *
     * This constructor creates an empty element which does nothing
     */
    SvgElement();

    /**
     * \brief Construct the element from a renderer, an id and a mask
     *
     * \param renderer Owner SVG renderer
     * \param id Identifier of the SVG element
     * \param mask Transparency mask associated to the element
     */
    SvgElement(QSvgRenderer& renderer, const QString& id, const SvgMask& mask);

    /**
     * \brief Check if the SVG element is valid
     *
     * An element is valid if it has a valid renderer
     * which contains its identifier.
     *
     * \return True if the element is valid
     */
    bool isValid() const;

    /**
     * \brief Return the bounding rectangle of the element
     *
     * \return Bounding rectangle
     */
    const QRectF& boundingRect() const;

    /**
     * \brief Check if a point is inside the opaque area of the element
     *
     * \param point Point to check, in item coordinates
     *
     * \return True if the point lies within the opaque area of the element, false otherwise
     */
    bool contains(const QPointF& point) const;

    /**
     * \brief Paint the element
     *
     * \param painter Painter into which the element must be painted
     * \param area Area where to draw the element (it will be resized to fit this area)
     */
    void paint(QPainter* painter, const QRectF& area) const;

private:

    QSvgRenderer* m_renderer; ///< SVG renderer containing the element
    QString m_id; ///< Identifier of the SVG element
    const SvgMask* m_mask; ///< Transparency mask of the element
    QRectF m_boundingRect; ///< Bounding rectangle of the element
    bool m_isValid; ///< Validity status of the element
};

} // namespace gics


#endif // GICS_PRIVATE_SVGELEMENT_HPP
