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


#ifndef GICS_LED_HPP
#define GICS_LED_HPP


#include <gics/config.hpp>
#include <gics/instrument.hpp>
#include <goost/pimplptr.hpp>


namespace gics
{
/**
 * \brief LED instrument
 */
class GICS_API Led : public Instrument
{
    Q_OBJECT

public:

    /**
     * \brief Default constructor
     *
     * \param parent Parent item of the instrument (0 by default)
     */
    Led(QGraphicsItem* parent = 0);

    /**
     * \brief Tell whether the LED is currently on or not
     *
     * The default value is false.
     *
     * \return True if the LED is on, false if it is off
     * \see setOn
     */
    bool isOn() const;

    /**
     * \brief Tell whether the LED is currently off or not
     *
     * The default value is true.
     *
     * \return True if the LED is off, false if it is on
     * \see setOff
     */
    bool isOff() const;

    /**
     * \brief Tells if the LED keeps a constant width/height ratio
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
     * \brief Return the "enabledOn" state
     *
     * \return Reference to the "enabledOn" state
     */
    State& enabledOnState();

    /**
     * \brief Return the "enabledOff" state
     *
     * \return Reference to the "enabledOff" state
     */
    State& enabledOffState();

    /**
     * \brief Return the "disabledOn" state
     *
     * \return Reference to the "disabledOn" state
     */
    State& disabledOnState();

    /**
     * \brief Return the "disabledOff" state
     *
     * \return Reference to the "disabledOff" state
     */
    State& disabledOffState();

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();

public slots:

    /**
     * \brief Set the state of the LED to either on or off
     *
     * \param on True to turn the LED on, false to turn it off
     * \see isOn
     */
    void setOn(bool on = true);

    /**
     * \brief Set the state of the LED to either off or on
     *
     * \param off True to turn the LED off, false to turn it on
     * \see isOff
     */
    void setOff(bool off = true);

    /**
     * \brief Toggle the state of the LED
     */
    void toggle();

protected:

    /**
     * \brief Function called when the "enabled" state of the instrument has changed
     *
     * \param enabled True if the instrument has been enabled, false otherwise
     */
    virtual void enabledChanged(bool enabled);

private:

    goost::PimplPtr<class LedPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::Led, &gics::Led::registerMetaClass)

#endif // GICS_LED_HPP


/**
 * \class gics::Led
 *
 * \image html led.png
 *
 * The LED is a simple instrument composed of a picture, which can be turned on and off.
 *
 * <b>List of properties</b>
 * \li \ref instrumentProperties "Properties inherited from gics::Instrument"
 * \li \ref isOn "on"
 * \li \ref keepAspectRatio
 */
