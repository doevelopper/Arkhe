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


#ifndef GICS_GAUGE_HPP
#define GICS_GAUGE_HPP


#include <gics/config.hpp>
#include <gics/instrument.hpp>
#include <goost/pimplptr.hpp>


namespace gics
{
class CircularScale;
class Label;
class Lcd;

/**
 * \brief Gauge instrument
 */
class GICS_API Gauge : public Instrument
{
    Q_OBJECT    

    friend class GaugePrivate;

public:
    /**
     * \brief Default constructor
     *
     * \param parent Parent item (0 by default)
     */
    Gauge(QGraphicsItem* parent = 0);

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
     * \brief Return a reference to the internal scale of the gauge
     *
     * \return Reference to the circular scale
     */
    CircularScale& scale();

    /**
     * \brief Return the position of the scale's base line, as a factor of the radius
     *
     * This property adjusts the position of the scale along the radius of the gauge. \n
     * The default value is 0.8.
     *
     * \return Radial position in [-1.0, 1.0]
     * \see setScaleBaseLinePosition
     */
    qreal scaleBaseLinePosition() const;

    /**
     * \brief Change the position of the scale's base line, as a factor of the radius
     *
     * \param position New factor in [-1.0, 1.0]
     * \see scaleBaseLinePosition
     */
    void setScaleBaseLinePosition(qreal position);

    /**
     * \brief Return a reference to the internal needle picture of the gauge
     *
     * \return Reference to the needle picture
     */
    Picture& needle();

    /**
     * \brief Return a reference to the internal hat picture of the gauge
     *
     * \return Reference to the hat picture
     */
    Picture& hat();

    /**
     * \brief Return a reference to the internal Lcd displaying the value of the gauge
     *
     * \return Reference to the value label
     */
    Lcd& valueLabel();

    /**
     * \brief Return the position of the value label, as a factor of the radius
     *
     * This property adjusts the position of the value label along the radius of the gauge. \n
     * The default value is -0.4.
     *
     * \return Radial position factor of the value label
     * \see setValueLabelPosition
     */
    double valueLabelPosition() const;

    /**
     * \brief Change the position of the value label, as a factor of the radius
     *
     * \param position New radial position [-1.0, 1.0]
     * \see valueLabelPosition
     */
    void setValueLabelPosition(double position);

    /**
     * \brief Return a reference to the internal title of the gauge
     *
     * \return Reference to the title label
     */
    Label& titleLabel();

    /**
     * \brief Return the position of the title label, as a factor of the radius
     *
     * This property adjusts the position of the title label along the radius of the gauge. \n
     * The default value is 0.4.
     *
     * \return Radial position factor of the title label
     * \see settitleLabelPosition
     */
    double titleLabelPosition() const;

    /**
     * \brief Change the position of the title label, as a factor of the radius
     *
     * \param position New radial position [0.0, 1.0]
     * \see titleLabelPosition
     */
    void setTitleLabelPosition(double position);

    /**
     * \brief Return the current gauge value
     *
     * The default value is 0.
     *
     * \return The current value
     * \see setValue
     */
    double value() const;

public slots:

    /**
     * \brief Change the current gauge value
     *
     * \param value The new value
     * \see value
     */
    void setValue(double value);

signals:

    /**
     * \brief Signal emitted (once) when the value is out of the [min, max] range
     */
    void outOfRangeEntered();

    /**
     * \brief Signal emitted (once) when an OutOfRange occurs (the parameter is true), or ends (the parameter is false)
     *
     */
    void outOfRangeToggled(bool outOfRange);

public:

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

    goost::PimplPtr<class GaugePrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::Gauge, &gics::Gauge::registerMetaClass)

#endif // GICS_GAUGE_HPP


/**
 * \class gics::Gauge
 *
 * \image html gauge.png
 *
 * The Gauge instrument is a complex instrument composed by:
 * \li a circular scale that displays the range of possible values
 * \li a needle (and a hat) that indicates the current value on the scale
 * \li a caption label that displays a custom static information (like the unit of the displayed value, or a multiplier coefficient)
 * \li a value LCD label that displays the current value as text
 *
 * Each of these sub-components can be accessed directly and modified (see \ref scale, \ref needle, \ref hat, \ref valueLabel and \ref titleLabel).
 *
 * If the input value goes out the [minimum, maximum] range, an \ref outOfRangeEntered() signal is emitted.
 *
 * <b>List of properties</b>
 * \li \ref instrumentProperties "Properties inherited from gics::Instrument"
 * \li \ref value
 * \li \ref scaleBaseLinePosition
 * \li \ref valueLabelPosition
 * \li \ref titleLabelPosition
 * \li \ref scale
 * \li \ref titleLabel
 * \li \ref valueLabel
 * \li \ref needle
 * \li \ref hat
 */
