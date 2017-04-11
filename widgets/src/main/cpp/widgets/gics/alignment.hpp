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


#ifndef GICS_ALIGNMENT_HPP
#define GICS_ALIGNMENT_HPP

#include <gics/config.hpp>
#include <camp/camptype.hpp>
#include <Qt>

namespace gics
{
/**
 * \brief Horizontal alignment modes
 */
enum HorizontalAlignment
{
    alignLeft,    ///< Align to the left
    alignHCenter, ///< Align to the horizontal center
    alignRight    ///< Align to the right
};

/**
 * \brief Vertical alignment modes
 */
enum VerticalAlignment
{
    alignTop,     ///< Align to the top
    alignVCenter, ///< Align to the vertical center
    alignBottom   ///< Align to the bottom
};


/**
 * \brief convert gics enum alignment to Qt alignment flag
 */
GICS_API Qt::Alignment horizontalAlignmentEnumToFlag(HorizontalAlignment horizontalAlignment);

/**
* \brief convert gics enum alignment to Qt alignment flag
*/
GICS_API Qt::Alignment verticalAlignmentEnumToFlag(VerticalAlignment verticalAlignment);


/**
 * \brief Declare the HorizontalAlignment meta-enum
 *
 * This function will be called automatically when needed
 */
GICS_API void registerHorizontalAlignmentMetaEnum();

/**
 * \brief Declare the VerticalAlignment meta-enum
 *
 * This function will be called automatically when needed
 */
GICS_API void registerVerticalAlignmentMetaEnum();

} // namespace gics

CAMP_AUTO_TYPE(gics::HorizontalAlignment, &gics::registerHorizontalAlignmentMetaEnum)
CAMP_AUTO_TYPE(gics::VerticalAlignment, &gics::registerVerticalAlignmentMetaEnum)


#endif // GICS_ALIGNMENT_HPP
