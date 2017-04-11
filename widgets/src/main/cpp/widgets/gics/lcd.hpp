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


#ifndef GICS_LCD_HPP
#define GICS_LCD_HPP


#include <gics/config.hpp>
#include <gics/instrument.hpp>
#include <goost/pimplptr.hpp>


namespace gics
{
/**
 * \brief LCD instrument
 */
class GICS_API Lcd : public Instrument
{
    Q_OBJECT

public:

    /**
     * \brief Predefined built-in types of LCD renderers
     */
    enum DisplayType
    {
        sevenSegments,    ///< 7-segments LCD display
        fourteenSegments, ///< 14-segments LCD display
        pixelSegments     ///< Pixel-based LCD display
    };

public:

    /**
     * \brief Constructor
     */
    Lcd(QGraphicsItem* parent = 0);

    /**
     * \brief Get the current value
     *
     * The default value is 0.
     *
     * \return Current value
     * \see setValue
     */
    double value() const;

    /**
     * \brief Get the number of digits displayed for the integer part
     *
     * If the number of integer digits of the current value is higher
     * than this property, the displayed value is clamped and the
     * \ref outOfRangeEntered signal is emitted. \n
     * The default value is 3.
     *
     * \return Number of digits for the integer part
     * \see setIntegerPrecision
     */
    unsigned int integerPrecision() const;

    /**
     * \brief Set the number of digits to display for the integer part
     *
     * \param precision New integer precision
     * \see integerPrecision
     */
    void setIntegerPrecision(unsigned int precision);

    /**
     * \brief Get the number of digits displayed for the decimal part
     *
     * If the number of decimal digits of the current value is higher
     * than this property, the number is rounded to the nearest number.
     *
     * The default value is 2.
     *
     * \return Number of digits for the decimal part
     * \see setDecimalPrecision
     */
    unsigned int decimalPrecision() const;

    /**
     * \brief Set the number of digits to display for the decimal part
     *
     * \param precision New decimal precision
     * \see decimalPrecision
     */
    void setDecimalPrecision(unsigned int precision);

    /**
     * \brief Tell whether the value is padded with zeros or spaces
     *
     * This property controls how the empty space is padded, when
     * the number of integer digits of the current value is higher
     * than \ref integerPrecision. \n
     * The default value is false.
     *
     * \return True if leading zeros are displayed, false otherwise
     * \see setShowLeadingZeros
     */
    bool showLeadingZeros() const;

    /**
     * \brief Display or hide leading zeros for padding the value
     *
     * \param show True to pad with zeros, false to pad with spaces
     * \see showLeadingZeros
     */
    void setShowLeadingZeros(bool show);

    /**
     * \brief Tell if a minus sign is reserved in front of the value
     *
     * When this property is set, a minus sign digit appears in front
     * of the value (including padding if any). It is lit/unlit
     * according to the sign of the current value. \n
     * The default value is true.
     *
     * \return True if the minus sign is shown, false if it is hidden
     * \see setShowMinusSign
     */
    bool showMinusSign() const;

    /**
     * \brief Display or hide the minus sign in front of the value
     *
     * \param show True to show the minus sign, false to hide it
     * \see showMinusSign
     */
    void setShowMinusSign(bool show);

    /**
     * \brief Get the type of display
     *
     * The type is a value from the \ref DisplayType enumeration. \n
     * The default value is \ref sevenSegments.
     *
     * \return Current display type
     * \see setDisplayType
     */
    DisplayType displayType() const;

    /**
     * \brief Set the type of LCD
     *
     * \param type New type of LCD
     * \see displayType
     */
    void setDisplayType(DisplayType type);

    /**
     * \brief Get the color which is used to draw active (lit) segments
     *
     * The default value is QColor(210, 0, 20).
     *
     * \return Current active color
     * \see setActiveColor
     */
    const QColor& activeColor() const;

    /**
     * \brief Set the color whic is used to draw active (lit) segments
     *
     * \param activeColor New active color
     * \see activeColor
     */
    void setActiveColor(const QColor& activeColor);

    /**
     * \brief Get the color which is used to draw inactive (unlit) segments
     *
     * The default value is QColor(80, 20, 20).
     *
     * \return Current inactive color
     * \see setInactiveColor
     */
    const QColor& inactiveColor() const;

    /**
     * \brief Set the color which is used to draw inactive (unlit) segments
     *
     * \param inactiveColor New inactive color
     * \see inactiveColor
     */
    void setInactiveColor(const QColor& inactiveColor);

    /**
     * \brief Tells if contents of the LCD keeps a constant width/height ratio
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

public slots:

    /**
     * \brief Set the current value to display
     *
     * \param value New value to display
     * \see value
     */
    void setValue(double value);

signals:

    /**
     * \brief Signal emitted when the out-of-range state is triggered
     *
     * The out-of-range state is entered when the value to display requires
     * more digits than what the LCD can display.
     * This signal is not emitted if the LCD was already in out-of-range state.
     */
    void outOfRangeEntered();

    /**
     * \brief Signal emitted when the out-of-range state is entered or exited
     *
     * \param entered True if the out-of-range state is entered, false if it is exited
     */
    void outOfRangeToggled(bool entered);

protected:

    /**
     * \brief Function called when the "enabled" state of the instrument has changed
     *
     * \param enabled True if the instrument has been enabled, false otherwise
     */
    virtual void enabledChanged(bool enabled);

private:

    /**
     * \brief Update the displayed value according to the new settings
     */
    void updateValue();

private:

    goost::PimplPtr<class LcdPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE(gics::Lcd::DisplayType, &gics::Lcd::registerMetaClass)
CAMP_AUTO_TYPE_NONCOPYABLE(gics::Lcd, &gics::Lcd::registerMetaClass)

#endif // GICS_LCD_HPP


/**
 * \class gics::Lcd
 *
 * \image html lcd.png
 *
 * The LCD instrument displays a numeric value in a LCD style. This can be used to simuate counters, clocks, etc.
 *
 * The LCD displays a fixed number of digits (see \ref integerPrecision, \ref decimalPrecision). If the current
 * value cannot fit in the number of digits defined by these properties, it is clamped and the \ref
 * outOfRangeEntered and \ref outOfRangeToggled signals are emitted.
 *
 * <b>List of properties</b>
 * \li \ref instrumentProperties "Properties inherited from gics::Instrument"
 * \li \ref value
 * \li \ref integerPrecision
 * \li \ref decimalPrecision
 * \li \ref showLeadingZeros
 * \li \ref showMinusSign
 * \li \ref displayType "type"
 * \li \ref activeColor
 * \li \ref inactiveColor
 * \li \ref keepAspectRatio
 */
