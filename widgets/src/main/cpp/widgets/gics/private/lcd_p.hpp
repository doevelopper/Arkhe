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


#ifndef GICS_PRIVATE_LCD_HPP
#define GICS_PRIVATE_LCD_HPP


#include <gics/state.hpp>
#include <gics/lcdlabel.hpp>


namespace gics
{
/**
 * \brief Private implementation of Lcd
 */
class LcdPrivate
{
public:

    /**
     * \brief Update the text to display according to the current settings
     */
    void update();

public:

    LcdLabel* lcd; ///< LCD label component
    double value; ///< Current value displayed by the LCD
    unsigned int integerPrecision; ///< Number of digits to display for the integer part
    unsigned int decimalPrecision; ///< Number of digits to display for the decimal part
    bool showLeadingZeros; ///< Show or hide leading zeros
    bool showMinusSign; ///< Show or hide the leading minus sign
    bool outOfRange; ///< Current out-of-range state
    State* enabled; ///< Enabled state
    State* disabled; ///< Disabled state
};

} // namespace gics


#endif // GICS_PRIVATE_LCD_HPP
