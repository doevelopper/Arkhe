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


#include <gics/lcdlabel.hpp>
#include <gics/lcdrenderer.hpp>
#include <gics/private/lcdlabel_p.hpp>
#include <QPainter>


namespace gics
{
//-------------------------------------------------------------------------------------------------
LcdLabel::LcdLabel(QGraphicsItem* parent)
    : Component(parent)
{
    // Default values
    setText("");
    setActiveColor(QColor(210, 0, 20));
    setInactiveColor(QColor(80, 20, 20));
    setRenderer(LcdRenderer::seven());
}

//-------------------------------------------------------------------------------------------------
const QString& LcdLabel::text() const
{
    return d->text;
}

//-------------------------------------------------------------------------------------------------
void LcdLabel::setText(const QString& text)
{
    if (text != d->text)
    {
        d->text = text;
        update();
    }
}

//-------------------------------------------------------------------------------------------------
const QColor& LcdLabel::activeColor() const
{
    return d->activeColor;
}

//-------------------------------------------------------------------------------------------------
void LcdLabel::setActiveColor(const QColor& activeColor)
{
    if (activeColor != d->activeColor)
    {
        d->activeColor = activeColor;
        update();
    }
}

//-------------------------------------------------------------------------------------------------
const QColor& LcdLabel::inactiveColor() const
{
    return d->inactiveColor;
}

//-------------------------------------------------------------------------------------------------
void LcdLabel::setInactiveColor(const QColor& inactiveColor)
{
    if (inactiveColor != d->inactiveColor)
    {
        d->inactiveColor = inactiveColor;
        update();
    }
}

//-------------------------------------------------------------------------------------------------
const LcdRenderer* LcdLabel::renderer() const
{
    return d->renderer;
}

//-------------------------------------------------------------------------------------------------
void LcdLabel::setRenderer(const LcdRenderer* renderer)
{
    if (renderer != d->renderer)
    {
        d->renderer = renderer;
        update();
    }
}

//-------------------------------------------------------------------------------------------------
void LcdLabel::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    // No renderer, no drawing :)
    if (!d->renderer)
        return;

    // Get the bounding rectangle of the text
    QRectF textRect = d->renderer->boundingRect(d->text);
    if (textRect.isEmpty())
        return;

    // Setup the painter so that the text is properly centered and scaled
    QRectF displayRect = boundingRect();
    float hratio = displayRect.width() / textRect.width();
    float vratio = displayRect.height() / textRect.height();
    if (hratio < vratio)
    {
        // Stretch horizontally, center vertically
        painter->translate(0, (displayRect.height() - textRect.height() * hratio) / 2);
        painter->scale(hratio, hratio);
    }
    else
    {
        // Stretch vertically, center horizontally
        painter->translate((displayRect.width() - textRect.width() * vratio) / 2, 0);
        painter->scale(vratio, vratio);
    }
    painter->translate(-textRect.topLeft());

    // Finally draw the text
    if (d->renderer)
        d->renderer->draw(painter, d->text, d->activeColor, d->inactiveColor);
}

} // namespace gics
