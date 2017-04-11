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


#ifndef GICS_TEXTLABEL_HPP
#define GICS_TEXTLABEL_HPP


#include <gics/config.hpp>
#include <gics/instrument.hpp>
#include <gics/alignment.hpp>
#include <goost/pimplptr.hpp>


namespace gics
{
class Picture;

 /**
 * \brief TextLabel instrument
 */
class GICS_API TextLabel : public Instrument
{
    Q_OBJECT

public:

    /**
     * \brief Default constructor
     *
     * \param parent Parent item (0 by default)
     */
    TextLabel(QGraphicsItem* parent = 0);

    /**
     * \brief Constructor
     *
     * \param text Text to be displayed
     * \param parent Parent item (0 by default)
     */
    TextLabel(const QString& text, QGraphicsItem* parent = 0);

    /**
     * \brief Return the text of the label
     *
     * The default value is an empty string.
     *
     * \return The text of the label
     * \see setText
     */
    const QString& text() const;

public slots:

    /**
     * \brief Change the text of the label
     *
     * \param text The new text of the label
     * \see text
     */
    void setText(const QString& text);

public:

    /**
     * \brief Return the font used to render the text of the label
     *
     * The default value is QFont().
     *
     * \return The font of the label
     * \see setFont
     */
    QFont font() const;

    /**
     * \brief Change the font used to render the text of the label
     *
     * \param font The new font of the label
     * \see font
     */
    void setFont(const QFont& font);

    /**
     * \brief Return the color used to render the text of the label
     *
     * The default value is Qt::black;
     *
     * \return The color of the label
     * \see setColor
     */
    QColor color() const;

    /**
     * \brief Change the color used to render the text of the label
     *
     * \param color The new color of the label
     * \see color
     */
    void setColor(const QColor& color);

    /**
     * \brief Return the elide mode to use when the text is too large
     *
     * The elide mode selects where the text is cut if it is wider than
     * its geometry. When elided, the cut text is replaced with "...". \n
     * The default value is Qt::ElideRight.
     * 
     * \return The elide mode of the label
     * \see setElideMode
     */
    Qt::TextElideMode elideMode() const;

    /**
     * \brief Change the elide mode to use when the text is too large
     *
     * \param elideMode The new elide mode
     * \see elideMode
     */
    void setElideMode(Qt::TextElideMode elideMode);

    /**
     * \brief Return the horizontal alignment for the text
     *
     * The alignment selects where the text will be located if it is smaller
     * than the width of the component. \n
     * The default value is gics::alignLeft.
     *
     * \return The current horizontal alignment mode
     * \see setHorizontalTextAlignment
     */
    HorizontalAlignment horizontalTextAlignment() const;

    /**
     * \brief Change the horizontal alignment mode
     *
     * \param alignment The new horizontal alignment mode
     * \see horizontalTextAlignment
     */
    void setHorizontalTextAlignment(HorizontalAlignment alignment);

    /**
     * \brief Return the vertical alignment mode for the text
     *
     * The alignment selects where the text will be located if it is smaller
     * than the height of the component. \n
     * The default value is gics::alignHCenter.
     *
     * \return The current vertical alignment mode
     * \see setVerticalTextAlignment
     */
    VerticalAlignment verticalTextAlignment() const;

    /**
     * \brief Change the vertical alignment mode
     *
     * \param alignment The new vertical alignment mode
     * \see verticalTextAlignment
     */
    void setVerticalTextAlignment(VerticalAlignment alignment);

    /**
     * \brief Tells if contents of the label keeps a constant width/height ratio
     *
     * The default value is false.
     *
     * \return True if the width/height ratio is constant
     * \see setKeepAspectRatio
     */
    bool keepAspectRatio() const;

    /**
     * \brief Change the width/height ratio policy
     *
     * \param keep True to keep a constant ratio, or false to remove size constraints
     * \see keepAspectRatio
     */
    void setKeepAspectRatio(bool keep);

    /**
     * \brief Return the "enabled" state
     *
     * \return Reference to the "enabled" state
     */
    State& enabledState();

    /**
     * \brief Return the "disabled" state
     *
     * \return Reference to the "disabled" state
     */
    State& disabledState();

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();

protected:

    /**
     * \brief Function called when the "enabled" state of the instrument has changed
     *
     * \param enabled True if the instrument has been enabled, false otherwise
     */
    virtual void enabledChanged(bool enabled);

private:

    goost::PimplPtr<class TextLabelPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::TextLabel, &gics::TextLabel::registerMetaClass)


#endif // GICS_TEXTLABEL_HPP


/**
 * \class gics::TextLabel
 *
 * \image html textlabel.png
 *
 * The TextLabel instrument displays a simple text, with elide and alignment options.
 *
 * <b>List of properties</b>
 * \li \ref instrumentProperties "Properties inherited from gics::Instrument"
 * \li \ref text
 * \li \ref font
 * \li \ref color
 * \li \ref elideMode
 * \li \ref horizontalTextAlignment
 * \li \ref verticalTextAlignment
 * \li \ref keepAspectRatio
 */
