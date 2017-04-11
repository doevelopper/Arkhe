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


#include <gics/pixellcdrenderer.hpp>
#include <gics/private/pixellcdrenderer_p.hpp>
#include <goost/length.hpp>
#include <QPainter>

namespace lcdpixels
{
    #include <gics/private/lcdpixels.hpp>
}


namespace gics
{
//-------------------------------------------------------------------------------------------------
PixelLcdRenderer::PixelLcdRenderer()
{
}

//-------------------------------------------------------------------------------------------------
QRectF PixelLcdRenderer::boundingRect(const QString& text) const
{
    // Compute the total width
    qreal width = d->margin;
    for (int i = 0; i < text.size(); ++i)
    { 
        const LcdPixelDigit& digit = d->digits[text[i]];
        width += digit.width() * (d->size + d->margin);

        // Add the separation column
        if (i != text.size() - 1)
            width += d->size + d->margin;
    }

    // Compute the total height
    qreal height = d->margin + d->height * (d->size + d->margin);

    return QRectF(0, 0, width, height);
}

//-------------------------------------------------------------------------------------------------
void PixelLcdRenderer::draw(QPainter* painter, const QString& text,
                            const QColor& activeColor, const QColor& inactiveColor) const
{
    // Draw all digits one by one
    qreal left = d->margin;
    for (int i = 0; i < text.size(); ++i)
    {
        // Draw the digit
        const LcdPixelDigit& digit = d->digits[text[i]];
        for (int x = 0; x < digit.width(); ++x)
        {
            qreal top = d->margin;
            for (int y = 0; y < d->height; ++y)
            {
                painter->setBrush(digit.hasPixel(x, y) ? activeColor : inactiveColor);
                painter->drawRect(QRectF(left, top, d->size, d->size));
                top += d->margin + d->size;
            }
            left += d->margin + d->size;
        }

        // Draw the separation column between adjacent digits
        if (i != text.size() -1)
        {
            painter->setBrush(inactiveColor);
            for (int y = 0; y < d->height; ++y)
                painter->drawRect(QRectF(left, d->margin + y * (d->margin + d->size), d->size, d->size));
            left += d->margin + d->size;
        }
    }
}


//----------------------------------- PRIVATE PART ------------------------------------------------


//-------------------------------------------------------------------------------------------------
PixelLcdRendererPrivate::PixelLcdRendererPrivate()
{
    height = 7;
    size = 10;
    margin = 2;

    // Fill the digits table
    digits['0'] = LcdPixelDigit(goost::length(lcdpixels::zero)  / height, height, lcdpixels::zero);
    digits['1'] = LcdPixelDigit(goost::length(lcdpixels::one)   / height, height, lcdpixels::one);
    digits['2'] = LcdPixelDigit(goost::length(lcdpixels::two)   / height, height, lcdpixels::two);
    digits['3'] = LcdPixelDigit(goost::length(lcdpixels::three) / height, height, lcdpixels::three);
    digits['4'] = LcdPixelDigit(goost::length(lcdpixels::four)  / height, height, lcdpixels::four);
    digits['5'] = LcdPixelDigit(goost::length(lcdpixels::five)  / height, height, lcdpixels::five);
    digits['6'] = LcdPixelDigit(goost::length(lcdpixels::six)   / height, height, lcdpixels::six);
    digits['7'] = LcdPixelDigit(goost::length(lcdpixels::seven) / height, height, lcdpixels::seven);
    digits['8'] = LcdPixelDigit(goost::length(lcdpixels::eight) / height, height, lcdpixels::eight);
    digits['9'] = LcdPixelDigit(goost::length(lcdpixels::nine)  / height, height, lcdpixels::nine);
    digits['.'] = LcdPixelDigit(goost::length(lcdpixels::dot)   / height, height, lcdpixels::dot);
    digits['-'] = LcdPixelDigit(goost::length(lcdpixels::minus) / height, height, lcdpixels::minus);
    digits[' '] = LcdPixelDigit(goost::length(lcdpixels::empty) / height, height, lcdpixels::empty);
}

} // namespace gics
