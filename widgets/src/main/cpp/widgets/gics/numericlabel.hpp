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


#ifndef GICS_NUMERICLABEL_HPP
#define GICS_NUMERICLABEL_HPP


#include <gics/config.hpp>
#include <gics/instrument.hpp>
#include <gics/alignment.hpp>
#include <goost/pimplptr.hpp>


namespace gics
{
class Picture;

/**
 * \brief NumericLabel instrument
 */
class GICS_API NumericLabel : public Instrument
{
    Q_OBJECT

public:

    /**
     * \brief Default constructor
     *
     * \param parent Parent item (0 by default)
     */
    NumericLabel(QGraphicsItem* parent = 0);

    /**
     * \brief Constructor
     *
     * \param value Value to be displayed
     * \param precision Number of decimals displayed (2 by default)
     * \param parent Parent item (0 by default)
     */
    NumericLabel(double value, unsigned int precision = 2, QGraphicsItem* parent = 0);

    /**
     * \brief Return the value of the label
     *
     * The default value is 0.
     *
     * \return The value of the label
     * \see setValue
     */
    double value() const;

public slots:

    /**
     * \brief Change the value of the label
     *
     * \param value The new value of the label
     * \see setValue
     */
    void setValue(double value);

public:

    /**
     * \brief Return the precision of the label
     *
     * The precision is the number of decimal digits. If the current value has too many decimals,
     * it is truncated. \n
     * The default value is 2.
     *
     * \return The number of decimals displayed
     * \see setPrecision
     */
    unsigned int precision() const;

    /**
     * \brief Change the precision of the label
     *
     * \param precision The number of decimals to display (2 by default)
     * \see precision
     */
    void setPrecision(unsigned int precision = 2);

    /**
     * \brief Return prefix string
     *
     * The prefix is concatenated in front of the numeric value, but is not editable. \n
     * The default value is an empty string.
     *
     * \return The prefix string
     * \see setPrefix
     */
    const QString& prefix() const;

    /**
     * \brief Change the prefix string
     *
     * \param prefix The new prefix string
     * \see prefix
     */
    void setPrefix(const QString& prefix);

    /**
     * \brief Return the suffix string
     *
     * The suffix is appended to the back of the numeric value, but is not editable. \n
     * The default value is an empty string.
     *
     * \return The suffix string
     * \see setSuffix
     */
    const QString& suffix() const;

    /**
     * \brief Change the suffix string
     *
     * \param suffix The new suffix string
     * \see suffix
     */
    void setSuffix(const QString& suffix);

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

    goost::PimplPtr<class NumericLabelPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::NumericLabel, &gics::NumericLabel::registerMetaClass)

#endif // GICS_NUMERICLABEL_HPP


/**
 * \class gics::NumericLabel
 *
 * \image html numericlabel.png
 *
 * The numeric label displays a numeric value, with elide and alignment options.
 *
 * The value can be concatenated to an optional prefix and/or suffix.
 *
 * <b>List of properties</b>
 * \li \ref instrumentProperties "Properties inherited from gics::Instrument"
 * \li \ref value
 * \li \ref precision
 * \li \ref prefix
 * \li \ref suffix
 * \li \ref font
 * \li \ref color
 * \li \ref elideMode
 * \li \ref horizontalTextAlignment
 * \li \ref verticalTextAlignment
 * \li \ref keepAspectRatio
 */
