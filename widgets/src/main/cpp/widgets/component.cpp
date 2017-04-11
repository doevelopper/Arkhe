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


#include <gics/component.hpp>
#include <gics/private/component_p.hpp>


namespace gics
{
//-------------------------------------------------------------------------------------------------
Component::Component(QGraphicsItem* parent)
    : QGraphicsItem(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setGraphicsItem(this);
}

//-------------------------------------------------------------------------------------------------
Component::~Component()
{
}

//-------------------------------------------------------------------------------------------------
QRectF Component::boundingRect() const
{
    return QRectF(0, 0, geometry().width(), geometry().height());
}

//-------------------------------------------------------------------------------------------------
bool Component::contains(const QPointF& point) const
{
    return boundingRect().contains(point);
}

//-------------------------------------------------------------------------------------------------
void Component::setGeometry(const QRectF& rect)
{
    prepareGeometryChange();
    QGraphicsLayoutItem::setGeometry(rect);
    setPos(geometry().topLeft());
}

//-------------------------------------------------------------------------------------------------
void Component::updateGeometry()
{
    QGraphicsLayoutItem::updateGeometry();

    // If the parent item is a layout, notify it
    QGraphicsLayoutItem* parentItem = parentLayoutItem();
    if (parentItem && parentItem->isLayout())
       parentItem->updateGeometry();
}

//-------------------------------------------------------------------------------------------------
void Component::paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*)
{
    // The default implementation does nothing
}

//-------------------------------------------------------------------------------------------------
void Component::adjustment(Qt::Orientation, qreal& minimum, qreal& maximum)
{
    // The default implementation returns 0 offsets (no adjustment)
    minimum = 0;
    maximum = 0;
}

//-------------------------------------------------------------------------------------------------
QSizeF Component::sizeHint(Qt::SizeHint which, const QSizeF&) const
{
    // These sizes are all arbitrary and define acceptable default values
    switch (which)
    {
        case Qt::MinimumSize :   return QSizeF(1, 1);
        case Qt::PreferredSize : return QSizeF(50, 50);
        case Qt::MaximumSize :   return QSizeF(16777215, 16777215);
        default :                return QSizeF();
    }
}

} // namespace gics
