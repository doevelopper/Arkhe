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


#include <gics/adjustedlinearlayout.hpp>
#include <gics/private/adjustedlinearlayout_p.hpp>
#include <gics/component.hpp>


namespace gics
{
//-------------------------------------------------------------------------------------------------
AdjustedLinearLayout::AdjustedLinearLayout(QGraphicsLayoutItem* parent)
    : QGraphicsLinearLayout(parent)
{
}

//-------------------------------------------------------------------------------------------------
AdjustedLinearLayout::AdjustedLinearLayout(Qt::Orientation orientation, QGraphicsLayoutItem* parent)
    : QGraphicsLinearLayout(orientation, parent)
{
}

//-------------------------------------------------------------------------------------------------
AdjustedLinearLayout::~AdjustedLinearLayout()
{
}

//-------------------------------------------------------------------------------------------------
void AdjustedLinearLayout::addItem(Component* item)
{
    QGraphicsLinearLayout::addItem(item);
    d->components[item] = AdjustedLinearLayoutPrivate::AlignedItem(item);
}

//-------------------------------------------------------------------------------------------------
void AdjustedLinearLayout::insertItem(int index, Component* item)
{
    QGraphicsLinearLayout::insertItem(index, item);
    d->components[item] = AdjustedLinearLayoutPrivate::AlignedItem(item);
}

//-------------------------------------------------------------------------------------------------
void AdjustedLinearLayout::removeItem(Component* item)
{
    QGraphicsLinearLayout::removeItem(item);
    d->components.remove(item);
}

//-------------------------------------------------------------------------------------------------
void AdjustedLinearLayout::removeAt(int index)
{
    QGraphicsLinearLayout::removeAt(index);
    d->components.remove(itemAt(index));
}

//-------------------------------------------------------------------------------------------------
void AdjustedLinearLayout::setGeometry(const QRectF& rect)
{
    // First apply the regular resizing from the base class
    QGraphicsLinearLayout::setGeometry(rect);

    // Find the biggest minimum and smallest maximum among all the items
    qreal minimum = 0;
    qreal maximum = 0;
    for (AdjustedLinearLayoutPrivate::ComponentList::Iterator it = d->components.begin();
         it != d->components.end();
         ++it)
    {
        it.value().component->adjustment(orientation(), it.value().minimum, it.value().maximum);
        minimum = qMax(minimum, it.value().minimum);
        maximum = qMax(maximum, it.value().maximum);
    }

    // Then align all the other items on the calculated bounds
    int itemsCount = count();
    for (int i = 0; i < itemsCount; ++i)
    {
        // Get the current item
        QGraphicsLayoutItem* item = itemAt(i);

        // Adjust its geometry so that it is aligned with the reference bounds
        qreal min = minimum - d->components[item].minimum;
        qreal max = maximum - d->components[item].maximum;
        QRectF itemRect = item->geometry();
        if (orientation() == Qt::Horizontal)
        {
            itemRect.setTop(itemRect.top() + min);
            itemRect.setBottom(itemRect.bottom() - max);
        }
        else
        {
            itemRect.setLeft(itemRect.left() + min);
            itemRect.setRight(itemRect.right() - max);
        }
        item->setGeometry(itemRect);
    }
}

} // namespace gics
