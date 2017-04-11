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


#include <gics/private/svgelement.hpp>
#include <gics/private/svgmask.hpp>
#include <QSvgRenderer>
#include <QPainter>
#include <QPointF>


namespace gics
{
//-------------------------------------------------------------------------------------------------
SvgElement::SvgElement()
    : m_renderer(0)
    , m_id()
    , m_mask(0)
    , m_boundingRect()
    , m_isValid(false)
{
}

//-------------------------------------------------------------------------------------------------
SvgElement::SvgElement(QSvgRenderer& renderer, const QString& id, const SvgMask& mask)
    : m_renderer(&renderer)
    , m_id(id)
    , m_mask(&mask)
    , m_boundingRect(QPointF(0, 0), renderer.boundsOnElement(id).size())
    , m_isValid(renderer.elementExists(id))
{
}

//-------------------------------------------------------------------------------------------------
bool SvgElement::isValid() const
{
    return m_isValid;
}

//-------------------------------------------------------------------------------------------------
const QRectF& SvgElement::boundingRect() const
{
    return m_boundingRect;
}

//-------------------------------------------------------------------------------------------------
bool SvgElement::contains(const QPointF& point) const
{
    return m_mask && m_mask->contains(point);
}

//-------------------------------------------------------------------------------------------------
void SvgElement::paint(QPainter* painter, const QRectF& area) const
{
    if (m_isValid && area.isValid())
        m_renderer->render(painter, m_id, area);
}

} // namespace gics
