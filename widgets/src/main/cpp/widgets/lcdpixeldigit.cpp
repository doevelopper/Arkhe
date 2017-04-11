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


#include <gics/private/lcdpixeldigit.hpp>


namespace gics
{
//-------------------------------------------------------------------------------------------------
LcdPixelDigit::LcdPixelDigit()
    : m_width(0)
    , m_height(0)
{
}

//-------------------------------------------------------------------------------------------------
LcdPixelDigit::LcdPixelDigit(int width, int height, const int* pixels)
    : m_width(width)
    , m_height(height)
{
    for (int i = 0; i < width * height; ++i)
        m_pixels.append(pixels[i] != 0);
}

//-------------------------------------------------------------------------------------------------
int LcdPixelDigit::width() const
{
    return m_width;
}

//-------------------------------------------------------------------------------------------------
bool LcdPixelDigit::hasPixel(int x, int y) const
{
    if ((x >= 0) && (x < m_width) && (y >= 0) && (y < m_height))
        return m_pixels[x + y * m_width];
    else
        return false;
}

} // namespace gics
