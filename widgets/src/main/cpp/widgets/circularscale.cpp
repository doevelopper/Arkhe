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


#include <gics/circularscale.hpp>
#include <gics/private/circularscale_p.hpp>

#include <QPainter>

namespace gics
{
//-------------------------------------------------------------------------------------------------
CircularScale::CircularScale(QGraphicsItem* parent)
    : AbstractScale(parent)
    , d(this)
{
}

//-------------------------------------------------------------------------------------------------
CircularScale::~CircularScale()
{
}

//-------------------------------------------------------------------------------------------------
void CircularScale::setStartAngle(qreal angle)
{
    if (angle != d->startAngle)
    {
        d->startAngle = angle;
        rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
qreal CircularScale::startAngle() const
{
    return d->startAngle;
}

//-------------------------------------------------------------------------------------------------
void CircularScale::setAngleCourse(qreal course)
{
    if (course != d->angleCourse)
    {
        d->angleCourse = course;
        rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
qreal CircularScale::angleCourse() const
{
    return d->angleCourse;
}


//-------------------------------------------------------------------------------------------------
void CircularScale::setBaseLinePosition(qreal factor)
{
    qreal clampedFactor = qBound(0.0, factor, 1.0);
    if (clampedFactor != d->baseLineFactor)
    {
        d->baseLineFactor = clampedFactor;
        rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
qreal CircularScale::baseLinePosition() const
{
    return d->baseLineFactor;
}

//-------------------------------------------------------------------------------------------------
void CircularScale::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

    // To avoid drawing tick and tick labels outside my bounds
    if (d->isTickOutside())
        painter->setClipRect(boundingRect().toRect().adjusted(-1, -1, 1, 1));

    AbstractScale::paint(painter, option, widget);
}

//-------------------------------------------------------------------------------------------------
QPainterPath CircularScale::updateBaseLine(const QRectF& bounds) const
{
    // Compute the base line bounding rectangle
    qreal side = qMin(bounds.width(), bounds.height()) * d->baseLineFactor;
    QRectF baseLineRect(bounds.center().x() - side / 2.0
                        , bounds.center().y() - side / 2.0
                        , side
                        , side);

    // Compute the corresponding painter path
    QPainterPath path;
    path.arcMoveTo(baseLineRect, -d->startAngle);
    path.arcTo(baseLineRect, -d->startAngle, -d->angleCourse);

    return path;
}

//-------------------------------------------------------------------------------------------------
QSizeF CircularScale::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    switch (which)
    {
        case Qt::MinimumSize:
        case Qt::PreferredSize:
        {
            QSizeF sizeHint = QSizeF();

            // Compute the total minimum size of the scale
            const GraduationsSettings& grad = graduations(0);
            double factor = d->isTickOutside() ? 4.0 : 2.0;

            if (baseLineVisible())
            {
                sizeHint.rwidth() += baseLineWidth() * 2.0;
                sizeHint.rheight() += baseLineWidth() * 2.0;
            }
            if (grad.ticksVisible())
            {
                sizeHint.rwidth() += grad.ticksLength() * factor;
                sizeHint.rheight() += grad.ticksLength() * factor;
            }
            if (grad.labelsVisible())
            {
                const QSizeF& labelSize = grad.maxLabelSize();
                sizeHint += labelSize * factor;
            }

            return sizeHint.expandedTo(QSizeF(1.0, 1.0));
        }

        default:
            return Component::sizeHint(which, constraint);
    }
}


//-------------------------------------------------------------------------------------------------
CircularScalePrivate::CircularScalePrivate(CircularScale* circularScalePublic)
    : q(circularScalePublic)
    , startAngle(0.0)
    , angleCourse(360.0)
    , baseLineFactor(0.8)
{
}

//-------------------------------------------------------------------------------------------------
bool CircularScalePrivate::isTickOutside() const
{
    return q->flipGraduations() ^ (angleCourse > 0);
}

} // namespace gics
