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


#ifndef GICS_LCDRENDERER_HPP
#define GICS_LCDRENDERER_HPP


#include <gics/config.hpp>
#include <QRectF>
#include <boost/noncopyable.hpp>


class QPainter;
class QString;
class QColor;

namespace gics
{
/**
 * \brief Abstract base class for LCD renderers
 */
class GICS_API LcdRenderer : boost::noncopyable
{
public:

    /**
     * \brief Get the built-in 7-segments renderer
     *
     * \return 7-segments renderer
     */
    static const LcdRenderer* seven();

    /**
     * \brief Get the built-in 14-segments renderer
     *
     * \return 14-segments renderer
     */
    static const LcdRenderer* fourteen();

    /**
     * \brief Get the built-in pixel-based renderer
     *
     * \return Pixel-based renderer
     */
    static const LcdRenderer* pixel();

public:

    /**
     * \brief Destructor
     */
    virtual ~LcdRenderer();

    /**
     * \brief Compute the bounding rectangle of a given text
     *
     * \param text Input text
     *
     * \return Bounding rectangle of \a text
     */
    virtual QRectF boundingRect(const QString& text) const = 0;

    /**
     * \brief Draw the LCD text
     *
     * \param painter Painter to use
     * \param text Text to display
     * \param activeColor Color for active (foreground) segments
     * \param inactiveColor Color for inactive (background) segments
     */
    virtual void draw(QPainter* painter, const QString& text,
                      const QColor& activeColor, const QColor& inactiveColor) const = 0;
};

} // namespace gics


#endif // GICS_LCDRENDERER_HPP


/**
 * \class gics::LcdRenderer
 *
 * This is the base class for custom LCD renderers.
 *
 * To create a renderer, there are only two virtual functions to override:
 * \li \b boundingRect computes the bounding rectangle of the given text
 * \li \b draw displays the given text using the provided painter and active/inactive colors
 *
 * There are three built-in renderers that are directly accessible:
 * \li \ref LcdRenderer::seven() (a 7-segments renderer)
 * \li \ref LcdRenderer::fourteen() (a 14-segments renderer)
 * \li \ref LcdRenderer::pixel() (a pixel-based renderer)
 */
