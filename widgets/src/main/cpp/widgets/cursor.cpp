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


#include <gics/cursor.hpp>
#include <gics/private/cursor_p.hpp>
#include <gics/picture.hpp>
#include <QGraphicsSceneMouseEvent>

namespace gics
{
//-------------------------------------------------------------------------------------------------
Cursor::Cursor(QGraphicsItem* parent)
    : Component(parent)
    , d(Qt::Vertical, this)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    setAcceptHoverEvents(true);
    setOrientation(d->orientation);

    connect(d->cursor, SIGNAL(elementChanged()), this, SLOT(handlePictureChanged()));
    connect(d->railBackground, SIGNAL(elementChanged()), this, SLOT(handlePictureChanged()));
}

//-------------------------------------------------------------------------------------------------
Cursor::Cursor(Qt::Orientation orientation, QGraphicsItem* parent)
    : Component(parent)
    , d(orientation, this)
{
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    setAcceptHoverEvents(true);
    setOrientation(d->orientation);

    connect(d->cursor, SIGNAL(elementChanged()), this, SLOT(handlePictureChanged()));
    connect(d->railBackground, SIGNAL(elementChanged()), this, SLOT(handlePictureChanged()));
}

//-------------------------------------------------------------------------------------------------
Cursor::~Cursor()
{
}

//-------------------------------------------------------------------------------------------------
void Cursor::setValue(double value)
{
    value = qBound(d->minimum, value, d->maximum);
    if (value != d->value)
    {
        d->value = value;
        emit valueChanged(value);
        updateGeometry();
    }
}

//-------------------------------------------------------------------------------------------------
double Cursor::value() const
{
    return d->value;
}

//-------------------------------------------------------------------------------------------------
void Cursor::setRailThickness(unsigned int railThickness)
{
    if (railThickness != 0)
    {
        d->railThickness = railThickness;
        updateGeometry();
    }
}

//-------------------------------------------------------------------------------------------------
unsigned int Cursor::railThickness() const
{
    return d->railThickness;
}

//-------------------------------------------------------------------------------------------------
void Cursor::setMinimum(double minimum)
{
    if (minimum != d->minimum && minimum < maximum())
    {
        d->minimum = minimum;
        if (d->value < minimum)
            setValue(minimum);
    }
}

//-------------------------------------------------------------------------------------------------
double Cursor::minimum() const
{
    return d->minimum;
}

//-------------------------------------------------------------------------------------------------
void Cursor::setMaximum(double maximum)
{
    if (maximum != d->maximum && maximum > minimum())
    {
        d->maximum = maximum;
        if (d->value > maximum)
            setValue(maximum);
    }
}

//-------------------------------------------------------------------------------------------------
 double Cursor::maximum() const
{
    return d->maximum;
}

//-------------------------------------------------------------------------------------------------
void Cursor::setSingleStep(double singleStep)
{
    d->singleStep = singleStep;
}

//-------------------------------------------------------------------------------------------------
double Cursor::singleStep() const
{
    return d->singleStep;
}

//-------------------------------------------------------------------------------------------------
Picture& Cursor::cursorPicture()
{
    return *d->cursor;
}

//-------------------------------------------------------------------------------------------------
Picture& Cursor::railBackground()
{
    return *d->railBackground;
}

//-------------------------------------------------------------------------------------------------
Picture& Cursor::railForeground()
{
    return *d->railForeground;
}

//-------------------------------------------------------------------------------------------------
void Cursor::setOrientation(Qt::Orientation orientation)
{
    if (orientation != d->orientation)
    {
        d->orientation = orientation;
        if(d->orientation == Qt::Horizontal)
        {
            d->railBackground->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
            d->railForeground->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
        }
        else
        {
            d->railBackground->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
            d->railForeground->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed); 
        }
        updateGeometry();
    }
}

//-------------------------------------------------------------------------------------------------
Qt::Orientation Cursor::orientation() const
{
    return d->orientation;
}

//-------------------------------------------------------------------------------------------------
void Cursor::setGeometry(const QRectF& rect)
{
    Component::setGeometry(rect);

    unsigned int cursorWidth = static_cast<unsigned int>(d->railThickness * d->cursorRailRatio());
    double ratio = (d->value - d->minimum)/(d->maximum - d->minimum);

    if (d->orientation == Qt::Vertical)
    {
        unsigned int cursorHeight = static_cast<unsigned int>(cursorWidth / d->cursor->aspectRatio());

        if ((1- ratio) * (rect.height() - cursorHeight) >= 0)
        {
            d->cursor->setGeometry(QRectF(rect.width() / 2 - cursorWidth / 2 
                                       , (1- ratio) * (rect.height()- cursorHeight)
                                       , cursorWidth
                                       , cursorHeight));
        }

        double course = rect.height() - d->cursor->geometry().height();

        d->railBackground->setGeometry(QRectF(rect.width() / 2 - d->railThickness / 2 
                                             , d->cursor->geometry().height() / 2
                                             , d->railThickness
                                             , course));

        d->railForeground->setGeometry(QRectF(rect.width() / 2 - d->railThickness/2 
                                             , d->cursor->geometry().height() / 2 + (1- ratio) * course
                                             , d->railThickness
                                             , ratio * course));
    }
    else
    {
        unsigned int cursorHeight = static_cast<unsigned int>(cursorWidth * d->cursor->aspectRatio());

        if (ratio*(rect.width()- cursorWidth*d->cursor->aspectRatio()) >= 0)
        {
            d->cursor->setGeometry(QRectF(ratio * (rect.width() - cursorHeight)
                                        , rect.height() / 2 - cursorWidth /2
                                        , cursorHeight
                                        , cursorWidth));
        }

        double course = rect.width() - d->cursor->geometry().width();

        d->railBackground->setGeometry(QRectF(d->cursor->geometry().width() / 2
                                             , rect.height() / 2 - d->railThickness / 2
                                             , course
                                             , d->railThickness));

        d->railForeground->setGeometry(QRectF(d->cursor->geometry().width() / 2
                                             ,rect.height() / 2 - d->railThickness / 2
                                             ,ratio * course
                                             ,d->railThickness));
    }
}

//-------------------------------------------------------------------------------------------------
void Cursor::adjustment(Qt::Orientation orientation, qreal& minimum, qreal& maximum)
{
    QRectF rect = d->cursor->geometry();

    if (orientation == Qt::Horizontal)
    {
        minimum = rect.height() / 2;
        maximum = rect.height() / 2;
    }
    else
    {
        minimum = rect.width() / 2;
        maximum = rect.width() / 2;
    }
}

//-------------------------------------------------------------------------------------------------
QSizeF Cursor::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    if (which == Qt::MinimumSize)
    {
        unsigned int cursorWidth = static_cast<unsigned int>(d->railThickness * d->cursorRailRatio());

        if (d->orientation == Qt::Horizontal)
            return QSizeF(qMax(cursorWidth, d->railThickness), d->cursor->geometry().height());
        else
            return QSizeF(cursorWidth, qMax(cursorWidth*d->cursor->aspectRatio(), static_cast<double>(d->railThickness)));
    }
    return Component::sizeHint(which, constraint);
}

//-------------------------------------------------------------------------------------------------
void Cursor::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    if (d->cursor->contains(d->cursor->mapFromParent(event->pos())))
    {
        if (!d->hovered)
        {
            d->hovered = true;
            emit hoverCursorIn();
        }
    }
    else if (d->hovered)
    {
            d->hovered = false;
            emit hoverCursorOut();
    }
}

//-------------------------------------------------------------------------------------------------
void Cursor::hoverLeaveEvent(QGraphicsSceneHoverEvent* /*event*/)
{
    if (d->hovered)
    {
        d->hovered = false;
        emit hoverCursorOut();
    }
}

//-------------------------------------------------------------------------------------------------
void Cursor::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    unsigned int cursorWidth = static_cast<unsigned int>(d->railThickness * d->cursorRailRatio());
    double ratio = (d->value - d->minimum) / (d->maximum - d->minimum);

    //If vertical orientation
    if (d->orientation == Qt::Vertical && d->pressed == true)
    {
        // New cursor position
        double x = geometry().width() / 2 - cursorWidth / 2;
        double y = d->cursor->geometry().y() + event->pos().y() - d->pressedPoint.y();

        //Clamp to minimum
        if( y >= geometry().height() - d->cursor->geometry().height())
        {
            d->cursor->setGeometry(QRectF(QPointF(x, geometry().height() - d->cursor->geometry().height()), d->cursor->geometry().size()));
            d->pressedPoint = QPointF(d->pressedPointOffset.x(), geometry().height() - d->cursor->geometry().height() + d->pressedPointOffset.y());
            d->value = d->minimum;
            if (!d->valueChangedEmitted)
            {
                emit valueChanged(d->value);
                emit cursorMoved(d->value);
                d->valueChangedEmitted = true;
            }
        } //Clamp to maximum
        else if (y <= 0)
        {
             d->cursor->setGeometry(QRectF(QPointF(x, 0), d->cursor->geometry().size()));
             d->pressedPoint = d->pressedPointOffset;
             d->value = d->maximum;
             if (!d->valueChangedEmitted)
             {
                 emit valueChanged(d->value);
                 emit cursorMoved(d->value);
                d->valueChangedEmitted = true;
             }
        } 
        else //Move the cursor
        {
           d->cursor->setGeometry(QRectF(QPointF(x, y), d->cursor->geometry().size()));
           d->pressedPoint = QPointF(d->pressedPoint.x(), event->pos().y());
           ratio = (geometry().height() - d->cursor->geometry().y() - d->cursor->geometry().height()) /(geometry().height() - d->cursor->geometry().height());
           d->value = d->minimum + ratio * (d->maximum - d->minimum);
           emit valueChanged(d->value);
           emit cursorMoved(d->value);
           d->valueChangedEmitted = false;
        }
        d->railForeground->setGeometry(QRectF(geometry().width() / 2 - d->railThickness / 2 , d->cursor->geometry().y() + d->cursor->geometry().height() / 2, d->railThickness, ratio * (geometry().height()- cursorWidth / d->cursor->aspectRatio())));
    }
    else if (d->pressed == true) //Horizontal orientation 
    {
        // New cursor position
        double x = d->cursor->geometry().x() + event->pos().x() - d->pressedPoint.x();
        double y = geometry().height() / 2 - cursorWidth /2;

        //Clamp to minimum
        if (x <= 0)
        {
            d->cursor->setGeometry(QRectF(QPointF(0, y), d->cursor->geometry().size()));
            d->pressedPoint = d->pressedPointOffset;
            d->value = d->minimum;
            if (!d->valueChangedEmitted)
            {
                emit valueChanged(d->value);
                emit cursorMoved(d->value);
                d->valueChangedEmitted = true;
            }
        } //Clamp to maximum
        else if (x >= geometry().width() - d->cursor->geometry().width())
        {
               d->cursor->setGeometry(QRectF(QPointF(geometry().width() - d->cursor->geometry().width(), y), d->cursor->geometry().size()));
               d->pressedPoint = QPointF(geometry().width()- d->cursor->geometry().width() + d->pressedPointOffset.x(), d->pressedPointOffset.y());
               d->value = d->maximum;
               if (!d->valueChangedEmitted)
               {
                  emit valueChanged(d->value);
                  emit cursorMoved(d->value);
                  d->valueChangedEmitted = true;
               }
        }
        else
        { //Move the cursor
               d->cursor->setGeometry(QRectF(QPointF(x, y), d->cursor->geometry().size()));
               d->pressedPoint = QPointF(event->pos().x(), d->pressedPoint.y());
               ratio = d->cursor->geometry().x()/(geometry().width() - d->cursor->geometry().width());
               d->value = d->minimum + ratio * (d->maximum - d->minimum);
               emit valueChanged(d->value);
               emit cursorMoved(d->value);
               d->valueChangedEmitted = false;
        }
        d->railForeground->setGeometry(QRectF(d->cursor->geometry().width() / 2 , geometry().height() / 2 - d->railThickness/2, ratio*(geometry().width()- cursorWidth * d->cursor->aspectRatio()),d->railThickness));
    }
}

//-------------------------------------------------------------------------------------------------
void Cursor::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    //Check if the mouse cursor is inside the cursor picture and save its position
    if (d->cursor->contains(d->cursor->mapFromParent(event->pos())))
    {
        d->pressed = true;
        d->pressedPoint = event->pos();
        d->pressedPointOffset = QPointF(event->pos().x() - d->cursor->geometry().x(), event->pos().y() - d->cursor->geometry().y());
    } //Check if the mouse is clicked above or under the cursor to translate the cursor of one step
    else if (d->orientation == Qt::Horizontal)
    {
        if (event->pos().x() < d->cursor->geometry().x())
        {
            setValue(d->value - d->singleStep);
        }
        else if (event->pos().x() > d->cursor->geometry().x() + d->cursor->geometry().width())
        {
            setValue(d->value + d->singleStep);
        }
    }
    else
    {
        if (event->pos().y() < d->cursor->geometry().y())
        {
            setValue(d->value + d->singleStep);
        }
        else if (event->pos().y() > d->cursor->geometry().y() + d->cursor->geometry().height())
        {
            setValue(d->value - d->singleStep);
        }
    }
}

//-------------------------------------------------------------------------------------------------
void Cursor::mouseReleaseEvent(QGraphicsSceneMouseEvent* /*event*/)
{
    d->pressed = false;
}

//-------------------------------------------------------------------------------------------------
void Cursor::wheelEvent(QGraphicsSceneWheelEvent* event)
{
    if (event->delta() > 0)
        setValue(d->value + d->singleStep);
    else
        setValue(d->value - d->singleStep);
}

//-------------------------------------------------------------------------------------------------
void Cursor::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Down)
        setValue(d->value - d->singleStep);
    else if (event->key() == Qt::Key_Up)
        setValue(d->value + d->singleStep);
}

//-------------------------------------------------------------------------------------------------
void Cursor::handlePictureChanged()
{
    updateGeometry();
}

//----------------------------------------- PRIVATE PART ------------------------------------------

//-------------------------------------------------------------------------------------------------
CursorPrivate::CursorPrivate(Qt::Orientation orientation, Cursor* cursorPublic)
    : q(cursorPublic)
    , value(0.)
    , minimum(0.)
    , maximum(100.)
    , railThickness(5)
    , singleStep(5.)
    , valueChangedEmitted(false)
    , pressed(false)
    , hovered(false)
    , orientation(orientation)
    , railBackground(new Picture(q))
    , railForeground(new Picture(q))
    , cursor(new Picture(q))
{
    railBackground->setZValue(0);
    railForeground->setZValue(1);
    cursor->setZValue(2);
}

//-------------------------------------------------------------------------------------------------
double CursorPrivate::cursorRailRatio() const
{
    double cursorRailRatio = 1;
    if (orientation == Qt::Horizontal)
    {
        if (cursor->initialSize().height() == 0 || railBackground->initialSize().height() == 0)
            cursorRailRatio = 1;
        else
            cursorRailRatio = cursor->initialSize().height() / railBackground->initialSize().height();
    }
    else
    {
        if (cursor->initialSize().width() == 0 || railBackground->initialSize().width() == 0)
            cursorRailRatio = 1;
        else
            cursorRailRatio = cursor->initialSize().width() / railBackground->initialSize().width();
    }
    return cursorRailRatio;
}

} // namespace gics
