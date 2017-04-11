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


#ifndef GICS_LCDLABEL_HPP
#define GICS_LCDLABEL_HPP


#include <gics/component.hpp>
#include <goost/pimplptr.hpp>


namespace gics
{
class LcdRenderer;

/**
 * \brief Label component displaying LCD-like characters
 */
class GICS_API LcdLabel : public Component
{
public:

    /**
     * \brief Default constructor
     *
     * \param parent Component's parent (0 by default)
     */
    LcdLabel(QGraphicsItem* parent = 0);

    /**
     * \brief Get the text displayed in the LCD label
     *
     * The default value is an empty string.
     *
     * \return Current text
     * \see setText
     */
    const QString& text() const;

    /**
     * \brief Set the text to display
     *
     * \param text Text to display in the label
     * \see text
     */
    void setText(const QString& text);

    /**
     * \brief Get the color used to draw active segments
     *
     * The default value is QColor(210, 0, 20).
     *
     * \return Current active color
     * \see setActiveColor
     */
    const QColor& activeColor() const;

    /**
     * \brief Set the color used to draw active segments
     *
     * \param activeColor New active color
     * \see activeColor
     */
    void setActiveColor(const QColor& activeColor);

    /**
     * \brief Get the color used to draw inactive segments
     *
     * The default value is QColor(80, 20, 20).
     *
     * \return Current inactive color
     * \see setInactiveColor
     */
    const QColor& inactiveColor() const;

    /**
     * \brief Set the color used to draw inactive segments
     *
     * \param inactiveColor New inactive color
     * \see inactiveColor
     */
    void setInactiveColor(const QColor& inactiveColor);

    /**
     * \brief Get the renderer used to draw digits
     *
     * \return The current renderer
     * \see setRenderer
     */
    const LcdRenderer* renderer() const;

    /**
     * \brief Set the renderer used to draw digits
     *
     * \param renderer New renderer
     * \see renderer
     */
    void setRenderer(const LcdRenderer* renderer);

    /**
     * \brief Draw the component
     *
     * \param painter Painter to use to draw the component
     * \param option Some global drawing options
     * \param widget Parent widget (0 by default)
     */
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();

private:

    goost::PimplPtr<class LcdLabelPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::LcdLabel, &gics::LcdLabel::registerMetaClass)


#endif // GICS_LCDLABEL_HPP


/**
 * \class gics::LcdLabel
 *
 * \image html lcdlabel.png
 *
 * This component renders digits in a LCD-like style, with lit/unlit segments.
 * The set of digits that can be displayed by this component is limited to the
 * following characters : '0123456789.- '
 *
 * When resized, the LCD label scales its contents to automatically adjust to its new size.
 *
 * The actual rendering of the digits is performed in the LcdRenderer class, which is
 * an abstract base and thus can be derived to create custom LCD renderer. There are
 * three built-in LCD renderers that are directly accessible:
 * \li a 7-segments renderer
 * \li a 14-segments renderer
 * \li a pixel-based renderer
 *
 * To learn more about creating your own renderer, please refer to the LcdRenderer class.
 *
 * <b>List of properties</b>
 * \li \ref text
 * \li \ref activeColor
 * \li \ref inactiveColor
 */
