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


#include <gics/linearscale.hpp>
#include <gics/private/linearscale_p.hpp>


namespace gics
{
//-------------------------------------------------------------------------------------------------
LinearScale::LinearScale(QGraphicsItem* parent)
    : AbstractScale(parent)
{
    setOrientation(Qt::Horizontal);
}

//-------------------------------------------------------------------------------------------------
LinearScale::LinearScale(Qt::Orientation orientation, QGraphicsItem* parent)
    : AbstractScale(parent)
{
    setOrientation(orientation);
}

//-------------------------------------------------------------------------------------------------
LinearScale::~LinearScale()
{
}

//-------------------------------------------------------------------------------------------------
void LinearScale::setOrientation(Qt::Orientation orientation)
{
    if (orientation != d->orientation)
    {
        d->orientation = orientation;
        if (d->orientation == Qt::Horizontal)
            setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        else
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);

        updateGeometry();
    }
}

//-------------------------------------------------------------------------------------------------
Qt::Orientation LinearScale::orientation() const
{
    return d->orientation;
}

//-------------------------------------------------------------------------------------------------
void LinearScale::adjustment(Qt::Orientation orientation, qreal& minimum, qreal& maximum)
{
    if (orientation == Qt::Horizontal)
    {
        minimum = pointAt(startValue()).y();
        maximum = boundingRect().height() - pointAt(endValue()).y();
    }
    else
    {
        minimum = pointAt(startValue()).x();
        maximum = boundingRect().width() - pointAt(endValue()).x();
    }
}

//-------------------------------------------------------------------------------------------------
QPainterPath LinearScale::updateBaseLine(const QRectF& bounds) const
{
    // Compute the maximum size of labels
    QSizeF maxLabelSize;
    if (graduations(0).labelsVisible())
        maxLabelSize = graduations(0).maxLabelSize();

    bool flipped = flipGraduations() ^ (d->orientation == Qt::Horizontal);

    // Compute the maximum extent outside the base line
    qreal extent = 0;
    if (graduations(0).labelsVisible() && flipped)
    {
        extent += (d->orientation == Qt::Horizontal ? maxLabelSize.height() : maxLabelSize.width());
    }
    if (graduations(0).ticksVisible() && flipped)
    {
        extent += graduations(0).ticksLength();
    }
    if (baseLineVisible())
    {
        extent += baseLineWidth() / 2;
    }

    // Rebuild the linear path
    QPainterPath path;
    if (d->orientation == Qt::Horizontal)
    {
        path.moveTo(bounds.left() + maxLabelSize.width() / 2, bounds.top() + extent);
        path.lineTo(bounds.right() - maxLabelSize.width() / 2, bounds.top() + extent);
    }
    else
    {
        path.moveTo(bounds.left() + extent, bounds.top() + maxLabelSize.height() / 2);
        path.lineTo(bounds.left() + extent, bounds.bottom() - maxLabelSize.height() / 2);
    }

    return path;
}

//-------------------------------------------------------------------------------------------------
QSizeF LinearScale::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    switch (which)
    {
        case Qt::MinimumSize:
        case Qt::PreferredSize:
        {
            // Compute the total minimum size of the scale
            const GraduationsSettings& grad = graduations(0);
            const QSizeF& labelSize = grad.maxLabelSize();
            qreal size = 0;
            if (baseLineVisible())    size += baseLineWidth();
            if (grad.ticksVisible())  size += grad.ticksLength();
            if (grad.labelsVisible()) size += d->orientation == Qt::Horizontal ? labelSize.height() : labelSize.width();

            if (d->orientation == Qt::Horizontal)
            {
                return QSizeF(labelSize.width(), size);
            }
            else
            {
                return QSizeF(size, labelSize.height());
            }
        }

        default:
            return Component::sizeHint(which, constraint);
    }
}

} // namespace gics
