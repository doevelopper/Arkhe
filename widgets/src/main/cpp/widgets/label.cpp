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


#include <gics/label.hpp>
#include <gics/private/label_p.hpp>
#include <QBrush>
#include <QFontMetricsF>

namespace gics
{
//-------------------------------------------------------------------------------------------------
Label::Label(QGraphicsItem* parent)
    : Component(parent)
    , d(this)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    d->updateText();
    updateGeometry();
}

//-------------------------------------------------------------------------------------------------
Label::Label(const QString& text, QGraphicsItem* parent)
    : Component(parent)
    , d(this)
{
    setText(text);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    d->updateText();
    updateGeometry();
}

//-------------------------------------------------------------------------------------------------
const QString& Label::text() const
{
    return d->text;
}

//-------------------------------------------------------------------------------------------------
void Label::setText(const QString& text)
{
    if (d->text != text)
    {
        d->text = text;
        d->updateText();
        updateGeometry();
    }
}

//-------------------------------------------------------------------------------------------------
QFont Label::font() const
{
    return d->textItem->font();
}

//-------------------------------------------------------------------------------------------------
void Label::setFont(const QFont& font)
{
    if (this->font() != font)
    {
        d->textItem->setFont(font);
        d->updateText();
        updateGeometry();
    }
}

//-------------------------------------------------------------------------------------------------
QColor Label::color() const
{
    return d->textItem->brush().color();
}

//-------------------------------------------------------------------------------------------------
void Label::setColor(const QColor& color)
{
    d->textItem->setBrush(QBrush(color));
}

//-------------------------------------------------------------------------------------------------
Qt::TextElideMode Label::elideMode() const
{
    return d->elideMode;
}

//-------------------------------------------------------------------------------------------------
void Label::setElideMode(Qt::TextElideMode elideMode)
{
    if (d->elideMode != elideMode)
    {
        d->elideMode = elideMode;
        d->updateText();
        updateGeometry();
    }
}

//-------------------------------------------------------------------------------------------------
HorizontalAlignment Label::horizontalAlignment() const
{
    return d->horizontalAlignment;
}

//-------------------------------------------------------------------------------------------------
void Label::setHorizontalAlignment(HorizontalAlignment alignment)
{
    if (d->horizontalAlignment != alignment)
    {
        d->horizontalAlignment = alignment;
        d->updateText();
    }
}

//-------------------------------------------------------------------------------------------------
VerticalAlignment Label::verticalAlignment() const
{
    return d->verticalAlignment;
}

//-------------------------------------------------------------------------------------------------
void Label::setVerticalAlignment(VerticalAlignment alignment)
{
    if (d->verticalAlignment != alignment)
    {
        d->verticalAlignment = alignment;
        d->updateText();
    }
}

//-------------------------------------------------------------------------------------------------
void Label::setGeometry(const QRectF& rect)
{
    // Call parent's setGeometry
    Component::setGeometry(rect);

    // Update the text
    d->updateText();
}

//-------------------------------------------------------------------------------------------------
QSizeF Label::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    QSizeF baseSize = Component::sizeHint(which, constraint);
    QSizeF idealSize = QFontMetricsF(d->textItem->font()).size(Qt::TextSingleLine, d->text);

    switch (which)
    {
        case Qt::MinimumSize:
        case Qt::MinimumDescent:
            if (d->elideMode == Qt::ElideNone)
                return idealSize;
            else
                return QSizeF(baseSize.width(), idealSize.height());

        case Qt::PreferredSize:
            return idealSize;

        default:
            return baseSize;
    }
}


//----------------------------------- PRIVATE PART ------------------------------------------------


//-------------------------------------------------------------------------------------------------
LabelPrivate::LabelPrivate(Label* labelPublic)
    : q(labelPublic)
    , text("")
    , elideMode(Qt::ElideRight)
    , elidedText(text)
    , textItem(new QGraphicsSimpleTextItem(elidedText, q))
    , horizontalAlignment(alignLeft)
    , verticalAlignment(alignVCenter)
{

}

//-------------------------------------------------------------------------------------------------
void LabelPrivate::updateElidedText()
{
    // Compute the elided text according to the new available space
    elidedText = QFontMetricsF(textItem->font()).elidedText(text, elideMode, q->geometry().width());

    // Update the text of the item
    textItem->setText(elidedText);
}

//-------------------------------------------------------------------------------------------------
void LabelPrivate::updateAlignment()
{
    QPointF pos;

    QSizeF textSize = textItem->boundingRect().size();
    QSizeF availableSize = q->geometry().size();

    switch (horizontalAlignment)
    {
        case alignLeft:
            pos.setX(0.0);
            break;

        case alignHCenter:
            pos.setX(qMax(0.0, (availableSize.width() - textSize.width()) / 2.0));
            break;

        case alignRight:
            pos.setX(qMax(0.0, availableSize.width() - textSize.width()));
            break;
    }

    switch (verticalAlignment)
    {
        case alignTop:
            pos.setY(0.0);
            break;

        case alignVCenter:
            pos.setY(qMax(0.0, (availableSize.height() - textSize.height()) / 2.0));
            break;

        case alignBottom:
            pos.setY(qMax(0.0, availableSize.height() - textSize.height()));
            break;
    }

    textItem->setPos(pos);
}

//-------------------------------------------------------------------------------------------------
void LabelPrivate::updateText()
{
    // Updated elided text according to the available space
    updateElidedText();

    // Update the text alignment
    updateAlignment();
}

} // namespace gics
