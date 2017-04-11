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


#ifndef GICS_LCDPIXELDIGIT_HPP
#define GICS_LCDPIXELDIGIT_HPP


#include <QList>


namespace gics
{
/**
 * \brief This class defines a LCD pixel-based digit
 *
 * It stores which pixels have to be lit / unlit to display the digit.
 * This class is only meant for internal use by PixelLcdRenderer.
 */
class LcdPixelDigit
{
public:

    /**
     * \brief Default constructor
     */
    LcdPixelDigit();

    /**
     * \brief Construct the digit from an array of pixels
     *
     * \param width Number of horizontal pixels
     * \param height Number of vertical pixels
     * \param pixels Pointer to the array of pixels (must contain 0s and 1s)
     */
    LcdPixelDigit(int width, int height, const int* pixels);

    /**
     * \brief Get the digit width, in number of pixels
     *
     * \return Number of horizontal pixels in the digit
     */
    int width() const;

    /**
     * \brief Test if a given pixel is lit or unlit in the digit
     *
     * \param x Horizontal index of the pixel
     * \param y Vertical index of the pixel
     *
     * \return True if the pixel is lit, false if it is unlit
     */
    bool hasPixel(int x, int y) const;

private:

    int m_width; ///< Width, in number of pixels
    int m_height; ///< Height, in number of pixels
    QList<bool> m_pixels; ///< Array containing each pixel's state
};

} // namespace gics


#endif // GICS_LCDPIXELDIGIT_HPP
