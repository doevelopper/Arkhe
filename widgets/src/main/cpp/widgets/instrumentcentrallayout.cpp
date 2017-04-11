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


#include <gics/private/instrumentcentrallayout.hpp>
#include <gics/private/instrumentcentrallayout_p.hpp>
#include <gics/picture.hpp>
#include <QGraphicsItem>


namespace gics
{
//-------------------------------------------------------------------------------------------------
InstrumentCentralLayout::InstrumentCentralLayout(QGraphicsItem* parent, Picture* background, Picture* foreground)
{
    d->background = background;
    d->foreground = foreground;
    d->item = 0;

    if (d->background)
    {
        d->background->setParentItem(parent);
        d->background->setZValue(-1000);
    }

    if (d->foreground)
    {
        d->foreground->setParentItem(parent);
        d->foreground->setZValue(1000);
    }
}

//-------------------------------------------------------------------------------------------------
void InstrumentCentralLayout::setItem(QGraphicsLayoutItem* item)
{
    if (d->item)
        removeItem(d->item);

    d->item = item;

    if (d->item)
        addItem(d->item);
}

//-------------------------------------------------------------------------------------------------
void InstrumentCentralLayout::setGeometry(const QRectF& rect)
{
    QGraphicsLinearLayout::setGeometry(rect);
    QRectF actualRect = geometry();

    if (d->background)
    {
        d->background->setGeometry(actualRect);
        QRectF centerRect = d->background->boundingRect(Picture::center);
        setContentsMargins(centerRect.left(), centerRect.top(), actualRect.width() - centerRect.right(), actualRect.height() - centerRect.bottom());
    }

    if (d->foreground)
        d->foreground->setGeometry(actualRect);
}

} // namespace gics
