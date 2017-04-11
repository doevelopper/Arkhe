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


// <insert copyright>

#include <gics/rail.hpp>
#include <gics/private/rail_p.hpp>
#include <gics/picture.hpp>

namespace gics
{
//-------------------------------------------------------------------------------------------------
Rail::Rail(Qt::Orientation orientation, QGraphicsItem* parent)
        :Component()
{     
    d->ratio = 1;
   
    d->railBackground = new gics::Picture(this); 
    d->railBackground->setFile("skin.svg");
    d->railBackground->setId("lcd_background");
    //d->railBackground->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); 
          
    d->railForeground = new gics::Picture(d->railBackground);
    d->railForeground->setFile("skin.svg");
    d->railForeground->setId("tankForeground");
    //d->railForeground->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); 
    
    setOrientation(orientation);
}



//-------------------------------------------------------------------------------------------------
Rail::~Rail()
{
}

//-------------------------------------------------------------------------------------------------
void Rail::setRatio(double ratio)
{
    if(ratio >= 0 && ratio <= 1)
    {
        d->ratio = ratio;

        QRectF innerRect = d->railBackground->innerGeometry();
        if (d->orientation == Qt::Vertical)           
            d->railForeground->setGeometry(QRectF(innerRect.left(), innerRect.top() + innerRect.height() * (1 - d->ratio), innerRect.width(), innerRect.height() * d->ratio));    
        else    
            d->railForeground->setGeometry(QRectF(innerRect.left(), innerRect.top(), innerRect.width() * d->ratio, innerRect.height()));    

        update();
    }
}

//-------------------------------------------------------------------------------------------------
double Rail::ratio() const
{
    return d->ratio;
}

//-------------------------------------------------------------------------------------------------
void Rail::setOrientation(Qt::Orientation orientation)
{
    if (orientation != d->orientation)
    {
        d->orientation = orientation;
        /*if (d->orientation == Qt::Horizontal)
            setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        else
            setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);*/

        updateGeometry();
    }
}

//-------------------------------------------------------------------------------------------------
Qt::Orientation Rail::orientation() const
{
    return d->orientation;
}

//-------------------------------------------------------------------------------------------------
QSizeF Rail::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
   /* if(which == Qt::PreferredSize)
    {    
         return geometry().size();
    }*/
    return Component::sizeHint(which, constraint);
}

//-------------------------------------------------------------------------------------------------
void Rail::setGeometry(const QRectF& rect)
{
    Component::setGeometry(rect);
    d->railBackground->setGeometry(QRectF(0,0,geometry().width(),geometry().height()));

    QRectF innerRect = d->railBackground->innerGeometry();
    if (d->orientation == Qt::Vertical)           
        d->railForeground->setGeometry(QRectF(innerRect.left(), rect.top() + innerRect.height() * (1 - d->ratio), innerRect.width(), innerRect.height() * d->ratio));    
    else    
        d->railForeground->setGeometry(QRectF(innerRect.left(), rect.top(), innerRect.width() * d->ratio, innerRect.height()));    
}

} // namespace gics
