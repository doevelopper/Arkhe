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


#ifndef GICS_PRIVATE_CURSOR_HPP
#define GICS_PRIVATE_CURSOR_HPP

namespace gics
{
class Cursor;
class Picture;

/**
 * \brief Private implementation of Cursor
 */
class CursorPrivate
{
public:

    /**
     * \brief Constructor
     */
    CursorPrivate(Qt::Orientation orientation, Cursor* cursorPublic);

    /**
     * \brief Calculate the ratio between cursor/rail height (if orientaion is Horizontal) or between cursor/rail width (if orientation is Vertical)
     */
    double cursorRailRatio() const;

public:

    Cursor* q; ///< Pointer to the public implementation

    QPointF pressedPointOffset; ///< On cursor click, store the offset regarding the cursor center
    Picture* cursor; ///< Background picture of the cursor
    Picture* railBackground; ///< Background picture of the rail
    Picture* railForeground; ///< Foreground picture of the rail (filled part)
    unsigned int railThickness; ///< Width of the rail 
    double value; ///< Cursor doule value
    double minimum; ///< Minimum cursor value
    double maximum; ///< Maximum cursor value 
    double singleStep; ///< Step used on wheel scrolling or on rail clicking 
    bool pressed; ///< Indicate if the mouse has been pressed over the cursor picture
    bool hovered; ///< Indicate if the mouse is currently hovering the cursor picture
    bool valueChangedEmitted; ///< Indicate if the valueChanged signal has already been emitted when the value is clamped to minimum or maximum
    QPointF pressedPoint; ///< Store the point inside the cursor picture where the mouse has been pressed
    Qt::Orientation orientation; ///< Cursor orientation, vertical (default value) or horizontal

};

} // namespace gics

#endif // GICS_PRIVATE_CURSOR_HPP
