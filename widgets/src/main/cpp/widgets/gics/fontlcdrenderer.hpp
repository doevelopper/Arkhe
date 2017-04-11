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


#ifndef GICS_FONTLCDRENDERER_HPP
#define GICS_FONTLCDRENDERER_HPP


#include <gics/lcdrenderer.hpp>
#include <goost/pimplptr.hpp>


class QPainter;
class QString;
class QColor;
class QFont;

namespace gics
{
/**
 * \brief Specialization of LcdRenderer using a font
 */
class GICS_API FontLcdRenderer : public LcdRenderer
{
public:

    /**
     * \brief Construct the renderer from a font
     *
     * \param font Font to use
     * \param backgroundChars String containing a combination of one or more
     *        characters to use to draw all the inactive segments of a digit
     */
    FontLcdRenderer(const QFont& font, const QString& backgroundChars);

    /**
     * \brief Compute the bounding rectangle of a given text
     *
     * \param text Input text
     *
     * \return Bounding rectangle of \a text
     */
    virtual QRectF boundingRect(const QString& text) const;

    /**
     * \brief Draw the LCD text
     *
     * \param painter Painter to use
     * \param text Text to display
     * \param activeColor Color for active (foreground) segments
     * \param inactiveColor Color for inactive (background) segments
     */
    virtual void draw(QPainter* painter, const QString& text,
                      const QColor& activeColor, const QColor& inactiveColor) const;

private:

    goost::PimplPtr<class FontLcdRendererPrivate> d; ///< Pointer to the private implementation
};

} // namespace gics


#endif // GICS_FONTLCDRENDERER_HPP
