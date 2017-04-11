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


#include <gics/picture.hpp>
#include <gics/private/picture_p.hpp>
#include <gics/private/svgelementmanager.hpp>
#include <QPainter>


namespace gics
{
//-------------------------------------------------------------------------------------------------
Picture::Picture(QGraphicsItem* parent)
    : Component(parent)
{
}

//-------------------------------------------------------------------------------------------------
Picture::~Picture()
{
}

//-------------------------------------------------------------------------------------------------
void Picture::setFile(const QString& file)
{
    if (d->file != file)
    {
        d->file = file;
        d->updateElements();
        updateGeometry();
        update();
        emit elementChanged();
    }
}

//-------------------------------------------------------------------------------------------------
const QString& Picture::file() const
{
    return d->file;
}

//-------------------------------------------------------------------------------------------------
void Picture::setId(const QString& id)
{
    if (d->id != id)
    {
        d->id = id;
        d->updateElements();
        updateGeometry();
        update();
        emit elementChanged();
    }
}

//-------------------------------------------------------------------------------------------------
const QString& Picture::id() const
{
    return d->id;
}

//-------------------------------------------------------------------------------------------------
void Picture::setBorderMode(BorderMode mode)
{
    if (mode != d->borderMode)
    {
        d->borderMode = mode;
        updateGeometry();
        update();
        emit elementChanged();
    }
}

//-------------------------------------------------------------------------------------------------
Picture::BorderMode Picture::borderMode() const
{
    return d->borderMode;
}

//-------------------------------------------------------------------------------------------------
bool Picture::isValid() const
{
    return d->center.isValid();
}

//-------------------------------------------------------------------------------------------------
qreal Picture::aspectRatio() const
{
    QSizeF size = initialSize();

    return !size.isNull() ? size.width() / size.height() : 0;
}

//-------------------------------------------------------------------------------------------------
qreal Picture::aspectRatio(Region region) const
{
    QSizeF size = initialSize(region);

    return !size.isNull() ? size.width() / size.height() : 0;
}

//-------------------------------------------------------------------------------------------------
QSizeF Picture::initialSize() const
{
    return initialSize(center) + QSizeF(d->leftBorder + d->rightBorder, d->topBorder + d->bottomBorder);
}

//-------------------------------------------------------------------------------------------------
QSizeF Picture::initialSize(Region region) const
{
    switch (region)
    {
        case center:      return d->center.boundingRect().size();
        case left:        return d->left.boundingRect().size();
        case top:         return d->top.boundingRect().size();
        case right:       return d->right.boundingRect().size();
        case bottom:      return d->bottom.boundingRect().size();
        case topLeft:     return d->topLeft.boundingRect().size();
        case topRight:    return d->topRight.boundingRect().size();
        case bottomLeft:  return d->bottomLeft.boundingRect().size();
        case bottomRight: return d->bottomRight.boundingRect().size();
        default:          return QSizeF(0, 0);
    }
}

//-------------------------------------------------------------------------------------------------
QRectF Picture::boundingRect(Region region) const
{
    // If the border mode is set to "proportionnal", compute the scale factor for borders
    qreal factor = 1.f;
    if (d->borderMode == proportional)
    {
        QSizeF size = geometry().size();
        QSizeF isize = initialSize();
        if (!size.isEmpty() && !isize.isEmpty())
        {
            if (isize.height() * size.width() < isize.width() * size.height())
                factor = size.width() / isize.width();
            else
                factor = size.height() / isize.height();
        }
    }

    // Compute the bounding rectangle of the center region
    qreal leftBorder   = factor * d->leftBorder;
    qreal rightBorder  = factor * d->rightBorder;
    qreal topBorder    = factor * d->topBorder;
    qreal bottomBorder = factor * d->bottomBorder;
    QRectF rect = boundingRect().adjusted(leftBorder, topBorder, -rightBorder, -bottomBorder);

    switch (region)
    {
        case center:      return rect;
        case left:        return QRectF(0, rect.top(), rect.left(), rect.height());
        case top:         return QRectF(rect.left(), 0, rect.width(), rect.top());
        case right:       return QRectF(rect.right(), rect.top(), rightBorder, rect.height());
        case bottom:      return QRectF(rect.left(), rect.bottom(), rect.width(), bottomBorder);
        case topLeft:     return QRectF(0, 0, rect.left(), rect.top());
        case topRight:    return QRectF(rect.right(), 0, rightBorder, rect.top());
        case bottomLeft:  return QRectF(0, rect.bottom(), rect.left(), bottomBorder);
        case bottomRight: return QRectF(rect.right(), rect.bottom(), rightBorder, bottomBorder);
        default:          return QRectF();
    }
}

//-------------------------------------------------------------------------------------------------
QRectF Picture::geometry(Region region) const
{
    return boundingRect(region).translated(geometry().topLeft());
}

//-------------------------------------------------------------------------------------------------
void Picture::rotate(qreal angle, const QPointF& center)
{
    translate(center.x(), center.y());
    rotate(angle);
    translate(-center.x(), -center.y());
}

//-------------------------------------------------------------------------------------------------
bool Picture::contains(const QPointF& point) const
{
    return d->contains(point, d->topLeft,     boundingRect(topLeft))    ||
           d->contains(point, d->top,         boundingRect(top))        ||
           d->contains(point, d->topRight,    boundingRect(topRight))   ||
           d->contains(point, d->left,        boundingRect(left))       ||
           d->contains(point, d->center,      boundingRect(center))     ||
           d->contains(point, d->right,       boundingRect(right))      ||
           d->contains(point, d->bottomLeft,  boundingRect(bottomLeft)) ||
           d->contains(point, d->bottom,      boundingRect(bottom))     ||
           d->contains(point, d->bottomRight, boundingRect(bottomRight));
}


//-------------------------------------------------------------------------------------------------
bool Picture::collidesWithPath(const QPainterPath& path, Qt::ItemSelectionMode mode) const
{
    // The element's mask can't help in the general case, but we can use contains()
    // if the path is in fact a point (i.e. a 1x1 rectangle).
    // This is important because a lot of internal tests in Qt (like mouse press)
    // use collidesWithPath(QRectF(pos, QSizeF(1, 1))) rather than contains(pos).

    QRectF rect = path.boundingRect();
    if (qFuzzyCompare(rect.width(), 1) && qFuzzyCompare(rect.height(), 1))
        return contains(rect.center());

    return QGraphicsItem::collidesWithPath(path, mode);
}

//-------------------------------------------------------------------------------------------------
void Picture::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    // The extra pixel is to compensate for the inaccuracy of the SVG renderer
    // (there's a 1-pixel gap between borders otherwise)

    d->topLeft.paint(painter, boundingRect(topLeft));
    d->top.paint(painter, boundingRect(top).adjusted(-1, 0, 0, 0));
    d->topRight.paint(painter, boundingRect(topRight).adjusted(-1, 0, 0, 0));
    d->left.paint(painter, boundingRect(left).adjusted(0, -1, 0, 0));
    d->center.paint(painter, boundingRect(center).adjusted(-1, -1, 0, 0));
    d->right.paint(painter, boundingRect(right).adjusted(-1, -1, 0, 0));
    d->bottomLeft.paint(painter, boundingRect(bottomLeft).adjusted(0, -1, 0, 0));
    d->bottom.paint(painter, boundingRect(bottom).adjusted(-1, -1, 0, 0));
    d->bottomRight.paint(painter, boundingRect(bottomRight).adjusted(-1, -1, 0, 0));
}

//-------------------------------------------------------------------------------------------------
void Picture::adjustment(Qt::Orientation orientation, qreal& minimum, qreal& maximum)
{
    if (orientation == Qt::Horizontal)
    {
        minimum = boundingRect(top).height();
        maximum = boundingRect(bottom).height();
    }
    else
    {
        minimum = boundingRect(left).width();
        maximum = boundingRect(right).width();
    }
}

//-------------------------------------------------------------------------------------------------
QSizeF Picture::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    QSizeF borderSize(0, 0);
    if (d->borderMode == fixed)
        borderSize = QSizeF(d->leftBorder + d->rightBorder, d->topBorder + d->bottomBorder);

    switch (which)
    {
        case Qt::MinimumSize:
        case Qt::MinimumDescent:
            return borderSize;

        case Qt::PreferredSize:
            return initialSize();

        default:
            return Component::sizeHint(which, constraint);
    }
}

//----------------------------------- PRIVATE PART ------------------------------------------------


//-------------------------------------------------------------------------------------------------
PicturePrivate::PicturePrivate()
    : leftBorder(0)
    , topBorder(0)
    , rightBorder(0)
    , bottomBorder(0)
    , borderMode(Picture::proportional)
{
}

//-------------------------------------------------------------------------------------------------
void PicturePrivate::updateElements()
{
    center      = SvgElementManager::instance().get(file, id);
    left        = SvgElementManager::instance().get(file, id + "_left");
    right       = SvgElementManager::instance().get(file, id + "_right");
    top         = SvgElementManager::instance().get(file, id + "_top");
    bottom      = SvgElementManager::instance().get(file, id + "_bottom");
    topLeft     = SvgElementManager::instance().get(file, id + "_topleft");
    topRight    = SvgElementManager::instance().get(file, id + "_topright");
    bottomLeft  = SvgElementManager::instance().get(file, id + "_bottomleft");
    bottomRight = SvgElementManager::instance().get(file, id + "_bottomright");

    // Recompute the borders size
    leftBorder = left.boundingRect().width();
    topBorder = top.boundingRect().height();
    rightBorder = right.boundingRect().width();
    bottomBorder = bottom.boundingRect().height();
}

//-------------------------------------------------------------------------------------------------
bool PicturePrivate::contains(const QPointF& point, const SvgElement& element, const QRectF& boundingRect) const
{
    // Check if the item is valid
    if (!element.isValid())
        return false;

    // Transform the point from item's coordinates to element's coordinates
    // (i.e. map from rect to element.boundingRect())
    QPointF localPoint = point;
    localPoint.rx() -= boundingRect.left();
    localPoint.ry() -= boundingRect.top();
    localPoint.rx() *= element.boundingRect().width() / boundingRect.width();
    localPoint.ry() *= element.boundingRect().height() / boundingRect.height();

    return element.contains(localPoint);
}

} // namespace gics
