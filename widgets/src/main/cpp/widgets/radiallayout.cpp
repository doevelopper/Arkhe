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


#include <gics/radiallayout.hpp>
#include <gics/math.hpp>
#include <gics/private/radiallayout_p.hpp>
#include <gics/private/layoututils.hpp>
#include <QGraphicsItem>
#include <math.h>


namespace gics
{
//-------------------------------------------------------------------------------------------------
RadialLayout::RadialLayout(QGraphicsLayoutItem* parent)
    : QGraphicsLayout(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

//-------------------------------------------------------------------------------------------------
RadialLayout::~RadialLayout()
{
    // Remove all items
    foreach (RadialLayoutPrivate::Item* item, d->items)
    {
        if (item->item)
        {
            item->item->setParentLayoutItem(0);
            if (item->item->ownedByLayout())
                delete item->item;
        }

        delete item;
    }
}

//-------------------------------------------------------------------------------------------------
void RadialLayout::addItem(QGraphicsLayoutItem* item, double radialFactor, double angle, const QSizeF& sizeConstraint)
{
    if (!item)
        return;

    RadialLayoutPrivate::Item* newItem = new RadialLayoutPrivate::Item;
    newItem->item = item;
    newItem->radialFactor = qBound(-1.0, radialFactor, 1.0);
    double clampedAngle = fmod(angle, 360.0);
    newItem->angle = (clampedAngle < 0.0 ? 360.0 + clampedAngle : clampedAngle);
    newItem->sizeConstraint = sizeConstraint.boundedTo(QSizeF(1.0, 1.0)).expandedTo(QSizeF(0.0, 0.0));

    LayoutUtils::addChildLayoutItem(this, item);
    d->items.append(newItem);
    invalidate();
}

//-------------------------------------------------------------------------------------------------
void RadialLayout::removeItem(QGraphicsLayoutItem* item)
{
    removeAt(indexOf(item));
}

//-------------------------------------------------------------------------------------------------
double RadialLayout::radialFactor(QGraphicsLayoutItem* item) const
{
    int index = indexOf(item);
    if (index != -1)
        return d->items[index]->radialFactor;
    return 0.0;
}

//-------------------------------------------------------------------------------------------------
void RadialLayout::setRadialFactor(QGraphicsLayoutItem* item, double radialFactor)
{
    int index = indexOf(item);
    if (index != -1)
    {
        double clampedRadialFactor = qBound(-1.0, radialFactor, 1.0);
        RadialLayoutPrivate::Item* item = d->items[index];
        if (item->radialFactor != clampedRadialFactor)
        {
            item->radialFactor = clampedRadialFactor;
            invalidate();
        }
    }
}

//-------------------------------------------------------------------------------------------------
double RadialLayout::angle(QGraphicsLayoutItem* item) const
{
    int index = indexOf(item);
    if (index != -1)
        return d->items[index]->angle;
    return 0.0;
}

//-------------------------------------------------------------------------------------------------
void RadialLayout::setAngle(QGraphicsLayoutItem* item, double angle)
{
    int index = indexOf(item);
    if (index != -1)
    {
        double clampedAngle = fmod(angle, 360.0);
        if (clampedAngle < 0.0)
            clampedAngle = 360.0 + clampedAngle;

        RadialLayoutPrivate::Item* item = d->items[index];
        if (item->angle != clampedAngle)
        {
            item->angle = clampedAngle;
            invalidate();
        }
    }
}

//-------------------------------------------------------------------------------------------------
QSizeF RadialLayout::sizeConstraint(QGraphicsLayoutItem* item) const
{
    int index = indexOf(item);
    if (index != -1)
        return d->items[index]->sizeConstraint;
    return QSizeF();
}

//-------------------------------------------------------------------------------------------------
void RadialLayout::setSizeConstraint(QGraphicsLayoutItem* item, const QSizeF& sizeConstraint)
{
    int index = indexOf(item);
    if (index != -1)
    {
        RadialLayoutPrivate::Item* item = d->items[index];
        QSizeF clampedSizeConstraint = sizeConstraint.boundedTo(QSizeF(1.0, 1.0)).expandedTo(QSizeF(0.0, 0.0));
        if (item->sizeConstraint != clampedSizeConstraint)
        {
            item->sizeConstraint = clampedSizeConstraint;
            updateGeometry();
            invalidate();
        }
    }
}

//-------------------------------------------------------------------------------------------------
int RadialLayout::indexOf(QGraphicsLayoutItem* item) const
{
    for (int i = 0; i < d->items.size(); ++i)
    {
        if (d->items.at(i)->item == item)
            return i;
    }

    return -1;
}

//-------------------------------------------------------------------------------------------------
int RadialLayout::count() const
{
    return d->items.size();
}

//-------------------------------------------------------------------------------------------------
QGraphicsLayoutItem* RadialLayout::itemAt(int index) const
{
    return (index >= 0 && index < count()) ? d->items.value(index)->item : 0;
}

//-------------------------------------------------------------------------------------------------
void RadialLayout::removeAt(int index)
{
    RadialLayoutPrivate::Item* item = d->items.takeAt(index);
    if (item->item)
        item->item->setParentLayoutItem(0);
    delete item;
    invalidate();
}

//-------------------------------------------------------------------------------------------------
void RadialLayout::updateGeometry()
{
    // Workaround for experimental ScaleContainer class
    // See RadialLayout::invalidate() for details
    QGraphicsLayout::updateGeometry();
    if (!parentLayoutItem())
        invalidate();
}

//-------------------------------------------------------------------------------------------------
void RadialLayout::invalidate()
{
    // Workaround for experimental ScaleContainer class
    // This workaround will force the layout to recalculate if there is no parentlayoutItem.
    //
    // For now Qt allows only to set a layout on a QGraphicsWidget or a QGraphicsLayout.
    // If you attempt to set a layout to a custom QGraphicsLayoutItem it will crash because Qt will
    // attempt to cast the layout parent into a QGraphicsWidget or a QGraphicsLayout.
    // Doing layout->setParentLayoutItem(myCustomLayoutItem) will then lead to a crash.

    if (parentLayoutItem())
    {
        // Use default implemetation
        QGraphicsLayout::invalidate();
    }
    else
    {
        // Force layout calculation
        setGeometry(geometry());
    }
}

//-------------------------------------------------------------------------------------------------
void RadialLayout::setGeometry(const QRectF& rect)
{
    // Apply the new geometry
    QGraphicsLayout::setGeometry(rect);

    // Update the items geometry
    QRectF layoutGeometry = geometry();
    QPointF center = layoutGeometry.center();
    double radius = qMin(layoutGeometry.width(), layoutGeometry.height()) / 2;

    foreach (RadialLayoutPrivate::Item* item, d->items)
    {
        if (item->item)
        {
            // Retrieve the new item geometry
            QRectF desiredGeometry = item->updatedGeometry(center, radius);

            // Correct the geometry in order to fit in the layout
            desiredGeometry.moveRight(qMin(desiredGeometry.right(), layoutGeometry.right()));
            desiredGeometry.moveLeft(qMax(desiredGeometry.left(), layoutGeometry.left()));
            desiredGeometry.moveBottom(qMin(desiredGeometry.bottom(), layoutGeometry.bottom()));
            desiredGeometry.moveTop(qMax(desiredGeometry.top(), layoutGeometry.top()));

            // Apply the new geometry
            item->item->setGeometry(desiredGeometry);
        }
    }
}

//-------------------------------------------------------------------------------------------------
QSizeF RadialLayout::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    // Return the maximum of the minimum size of the different items for the Minimum size hint
    if (which == Qt::MinimumSize || which == Qt::MinimumDescent)
    {
        QSizeF sizeHint(0.0, 0.0);
        foreach (RadialLayoutPrivate::Item* itemWrapper, d->items)
        {
            QGraphicsLayoutItem* item = itemWrapper->item;
            if (item)
            {
                // Retrieve the size hint of the current item
                QSizeF itemSizeHint = item->effectiveSizeHint(which, constraint);

                // According to its size policy and size constraint, the item size hint is adjusted
                QSizePolicy policy = item->sizePolicy();
                QSizePolicy::Policy horizontalPolicy = policy.horizontalPolicy();
                QSizePolicy::Policy verticalPolicy = policy.verticalPolicy();

                if ((horizontalPolicy & QSizePolicy::ExpandFlag || horizontalPolicy & QSizePolicy::IgnoreFlag)
                        && itemSizeHint.width() > 0.0 && itemWrapper->sizeConstraint.width() > 0.0)
                    itemSizeHint.rwidth() /= itemWrapper->sizeConstraint.width();
                if ((verticalPolicy & QSizePolicy::ExpandFlag || verticalPolicy & QSizePolicy::IgnoreFlag)
                        && itemSizeHint.height() > 0.0 && itemWrapper->sizeConstraint.height() > 0.0)
                    itemSizeHint.rheight() /= itemWrapper->sizeConstraint.height();

                // Update the layout size hint according the current item one
                sizeHint = sizeHint.expandedTo(itemSizeHint);
            }
        }

        return sizeHint;
    }

    return QSizeF();
}

//-------------------------------------------------------------------------------------------------
QRectF RadialLayoutPrivate::Item::updatedGeometry(const QPointF& layoutCenter, qreal layoutRadius) const
{
    // Compute the item center position
    double radian = angle / 180.0 * GICS_PI;
    double centerRadius = layoutRadius * radialFactor;
    double centerX = layoutCenter.x() + centerRadius * cos(radian);
    double centerY = layoutCenter.y() + centerRadius * sin(radian);

    // Compute the item size
    QSizeF size;
    QSizePolicy policy = item->sizePolicy();
    QSizePolicy::Policy horizontalPolicy = policy.horizontalPolicy();
    QSizePolicy::Policy verticalPolicy = policy.verticalPolicy();

    switch (horizontalPolicy)
    {
        case QSizePolicy::Fixed:
            size.setWidth(item->preferredWidth());
            break;

        case QSizePolicy::Minimum:
            size.setWidth(item->minimumWidth());
            break;

        case QSizePolicy::Maximum:
            size.setWidth(item->maximumWidth());
            break;

        case QSizePolicy::Preferred:
            size.setWidth(item->preferredWidth());
            break;

        case QSizePolicy::Expanding:
            size.setWidth(item->maximumWidth());
            break;

        case QSizePolicy::MinimumExpanding:
            size.setWidth(item->minimumWidth());
            break;

        case QSizePolicy::Ignored:
            size.setWidth(item->maximumWidth());
            break;
    }

    switch (verticalPolicy)
    {
        case QSizePolicy::Fixed:
            size.setHeight(item->preferredHeight());
            break;

        case QSizePolicy::Minimum:
            size.setHeight(item->minimumHeight());
            break;

        case QSizePolicy::Maximum:
            size.setHeight(item->maximumHeight());
            break;

        case QSizePolicy::Preferred:
            size.setHeight(item->preferredHeight());
            break;

        case QSizePolicy::Expanding:
            size.setHeight(item->maximumHeight());
            break;

        case QSizePolicy::MinimumExpanding:
            size.setHeight(item->minimumHeight());
            break;

        case QSizePolicy::Ignored:
            size.setHeight(item->maximumHeight());
            break;
    }

    // Apply size constraint
    double layoutDiameter = layoutRadius * 2.0;
    if (horizontalPolicy & QSizePolicy::ExpandFlag || horizontalPolicy & QSizePolicy::IgnoreFlag)
        size.setWidth(layoutDiameter * sizeConstraint.width());
    if (verticalPolicy & QSizePolicy::ExpandFlag || verticalPolicy & QSizePolicy::IgnoreFlag)
        size.setHeight(layoutDiameter * sizeConstraint.height());

    // Apply the new geometry
    return QRectF(
            centerX - size.width() / 2.0,
            centerY - size.height() / 2.0,
            size.width(),
            size.height());
}

} // namespace gics

