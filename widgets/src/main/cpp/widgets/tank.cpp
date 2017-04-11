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


#include <gics/tank.hpp>
#include <gics/private/tank_p.hpp>
#include <gics/picture.hpp>

namespace gics
{
//-------------------------------------------------------------------------------------------------
Tank::Tank(QGraphicsItem* parent)
    : QObject()
    , Component(parent)
{
    d->value = 0.;
    d->minimum = 0.;
    d->maximum = 100.;
    d->tankBackground = new Picture(this);
    d->tankForeground = new Picture(d->tankBackground);
    setOrientation(Qt::Vertical);
}

//-------------------------------------------------------------------------------------------------
Tank::Tank(Qt::Orientation orientation, QGraphicsItem* parent)
    : QObject()
    , Component(parent)
{
    d->value = 0.;
    d->minimum = 0.;
    d->maximum = 100.;
    d->tankBackground = new Picture(this);
    d->tankForeground = new Picture(d->tankBackground);
    setOrientation(orientation);
}

//-------------------------------------------------------------------------------------------------
Tank::~Tank()
{
}

//-------------------------------------------------------------------------------------------------
void Tank::setValue(double value)
{
    value = qBound(d->minimum, value, d->maximum);
    if (value != d->value)
    {
        d->value = value;
        emit valueChanged(value);
        d->updateForeground();
    }
}

//-------------------------------------------------------------------------------------------------
double Tank::value() const
{
    return d->value;
}

//-------------------------------------------------------------------------------------------------
void Tank::setMinimum(double minimum)
{
    if (minimum != d->minimum && minimum < d->maximum)
        d->minimum = minimum;
    if (d->value < minimum)
        setValue(minimum);
    updateGeometry();
}

//-------------------------------------------------------------------------------------------------
double Tank::minimum() const
{
    return d->minimum;
}

//-------------------------------------------------------------------------------------------------
void Tank::setMaximum(double maximum)
{
    if (maximum != d->maximum && maximum > d->minimum)
        d->maximum = maximum;
    if (d->value > maximum)
        setValue(maximum);
    updateGeometry();
}

//-------------------------------------------------------------------------------------------------
 double Tank::maximum() const
{
    return d->maximum;
}

//-------------------------------------------------------------------------------------------------
Picture& Tank::background()
{
    return *d->tankBackground;
}

//-------------------------------------------------------------------------------------------------
Picture& Tank::foreground()
{
    return *d->tankForeground;
}

//-------------------------------------------------------------------------------------------------
void Tank::setOrientation(Qt::Orientation orientation)
{
    if (orientation != d->orientation)
    {
        d->orientation = orientation;
        updateGeometry();
    }
}

//-------------------------------------------------------------------------------------------------
Qt::Orientation Tank::orientation() const
{
    return d->orientation;
}

//-------------------------------------------------------------------------------------------------
void Tank::setGeometry(const QRectF& rect)
{
    Component::setGeometry(rect);
    d->tankBackground->setGeometry(QRectF(0, 0, rect.width(), rect.height()));
    d->updateForeground();
}

//-------------------------------------------------------------------------------------------------
void Tank::adjustment(Qt::Orientation orientation, qreal& minimum, qreal& maximum)
{
    d->tankBackground->adjustment(orientation, minimum, maximum);
}

//--------------------------------------PRIVATE PART -----------------------------------------------

void TankPrivate::updateForeground()
{
    QRectF innerRect = tankBackground->boundingRect(Picture::center);
    double ratio = (value - minimum)/(maximum - minimum);

    if (orientation == Qt::Vertical)
        tankForeground->setGeometry(QRectF(innerRect.left(), innerRect.top() + innerRect.height() * (1 - ratio), innerRect.width(), innerRect.height() * ratio));
    else
        tankForeground->setGeometry(QRectF(innerRect.left(), innerRect.top(), innerRect.width() * ratio, innerRect.height()));
}

} // namespace gics
