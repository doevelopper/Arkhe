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


#include <gics/private/layoututils.hpp>
#include <QGraphicsItem>
#include <QGraphicsLayout>
#include <QGraphicsLayoutItem>


namespace gics
{
//-------------------------------------------------------------------------------------------------
void LayoutUtils::addChildLayoutItem(QGraphicsLayout* layout, QGraphicsLayoutItem* layoutItem)
{
    if (QGraphicsLayoutItem* maybeLayout = layoutItem->parentLayoutItem())
    {
        if (maybeLayout->isLayout())
            removeLayoutItemFromLayout(static_cast<QGraphicsLayout*>(maybeLayout), layoutItem);
    }
    layoutItem->setParentLayoutItem(layout);

    const QGraphicsLayoutItem* parent = layout;
    while (parent && parent->isLayout())
        parent = parent->parentLayoutItem();
    QGraphicsItem* parItem = parent ? parent->graphicsItem() : 0;

    if (layoutItem->isLayout())
    {
        if (parItem)
            reparentChildItems(static_cast<QGraphicsLayout*>(layoutItem), parItem);
    }
    else
    {
        if (QGraphicsItem* item = layoutItem->graphicsItem())
        {
            QGraphicsItem* newParent = parItem;
            QGraphicsItem* oldParent = item->parentItem();
            if (oldParent == newParent || !newParent)
                return;
            item->setParentItem(newParent);
        }
    }
}

//-------------------------------------------------------------------------------------------------
void LayoutUtils::reparentChildItems(QGraphicsLayout* layout, QGraphicsItem* newParent)
{
    int n = layout->count();
    for (int i = 0; i < n; ++i)
    {
        QGraphicsLayoutItem* layoutChild = layout->itemAt(i);
        if (!layoutChild)
            continue;
        if (layoutChild->isLayout())
        {
            QGraphicsLayout* l = static_cast<QGraphicsLayout*>(layoutChild);
            reparentChildItems(l, newParent);
        }
        else if (QGraphicsItem* itemChild = layoutChild->graphicsItem())
        {
            QGraphicsItem* childParent = itemChild->parentItem();
            if (childParent != newParent)
                itemChild->setParentItem(newParent);
        }
    }
}

//-------------------------------------------------------------------------------------------------
bool LayoutUtils::removeLayoutItemFromLayout(QGraphicsLayout* layout, QGraphicsLayoutItem* layoutItem)
{
    if (!layout)
        return false;

    QGraphicsLayoutItem* child;
    for (int i = 0; (child = layout->itemAt(i)); ++i)
    {
        if (child && child->isLayout())
        {
            if (removeLayoutItemFromLayout(static_cast<QGraphicsLayout*>(child), layoutItem))
                return true;
        }
        else if (child == layoutItem)
        {
            layout->removeAt(i);
            return true;
        }
    }
    return false;
}

} // namespace gics
