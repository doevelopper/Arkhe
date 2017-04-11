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


#include <gics/fontlcdrenderer.hpp>
#include <gics/private/fontlcdrenderer_p.hpp>
#include <QFontMetrics>
#include <QPainter>
#include <QFont>


namespace gics
{
//-------------------------------------------------------------------------------------------------
FontLcdRenderer::FontLcdRenderer(const QFont& font, const QString& backgroundChars)
{
    d->font = font;
    d->backgroundChars = backgroundChars;

    // We have to explicitely set an arbitrary size, otherwise it will get ignored
    // by QPainter::drawText but not by QFontMetrics::boundingRect, leading to inconsistent results
    d->font.setPointSize(20);
}

//-------------------------------------------------------------------------------------------------
QRectF FontLcdRenderer::boundingRect(const QString& text) const
{
    QRectF bounds = QFontMetrics(d->font).boundingRect(text);

    // This extra margin solves some issues related to badly designed fonts...
    // @todo find a cleaner way to sort this out
    bounds.adjust(-5, 0, 5, 0);

    return bounds;
}

//-------------------------------------------------------------------------------------------------
void FontLcdRenderer::draw(QPainter* painter, const QString& text,
                           const QColor& activeColor, const QColor& inactiveColor) const
{
    // Set the font
    painter->setFont(d->font);

    // Draw the inactive segments
    painter->setPen(inactiveColor);
    foreach (QChar character, d->backgroundChars)
    {
        QString backgroundText(text.size(), character);

        // Replace special character '.'
        int dotPos = text.indexOf('.');
        if (dotPos != -1)
            backgroundText[dotPos] = '.';

        painter->drawText(0, 0, backgroundText);
    }

    // Draw the active segments
    painter->setPen(activeColor);
    painter->drawText(0, 0, text);
}

} // namespace gics
