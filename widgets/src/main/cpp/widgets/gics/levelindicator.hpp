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


#ifndef GICS_LEVELINDICATOR_HPP
#define GICS_LEVELINDICATOR_HPP

#include <gics/config.hpp>
#include <gics/numericlabel.hpp>
#include <gics/textlabel.hpp>
#include <gics/instrument.hpp>
#include <gics/alignment.hpp>
#include <gics/linearscale.hpp>
#include <gics/tank.hpp>
#include <goost/pimplptr.hpp>

namespace gics
{
/**
 * \brief Specialized instrument displaying a real value using a linear level indicator
 */
class GICS_API LevelIndicator : public Instrument
{
    Q_OBJECT

friend class LevelIndicatorPrivate;

public:

    /**
     * \brief Default constructor with vertical orientation
     *
     * \param parent Parent item of the instrument (0 by default)
     */
    LevelIndicator(QGraphicsItem* parent = 0);

    /**
     * \brief Default constructor
     *
     * \param orientation Orientation of the level indicator
     * \param parent Parent item of the instrument (0 by default)
     */
    LevelIndicator(Qt::Orientation orientation, QGraphicsItem* parent = 0);

     /**
     * \brief Destructor
     */
    ~LevelIndicator();

    /**
     * \brief Return the current value of the LevelIndicator
     *
     * The default value is 0.
     *
     * \return The value of the LevelIndicator
     * \see setValue.
     */
    double value();

    /**
     * \brief Change the minimum of the LevelIndicator
     *
     * \param minimum The new minimum of the LevelIndicator
     * \see minimum.
     */
    void setMinimum(double minimum);

    /**
     * \brief Return the current minimum value of the LevelIndicator
     *
     * The default value is 0.
     *
     * \return The minimum value of the LevelIndicator
     * \see setMinimum.
     */
    double minimum() const;

    /**
     * \brief Change the maximum of the Slider
     *
     * \param maximum The new maximum of the Slider
     * \see maximum.
     */
    void setMaximum(double maximum);

    /**
     * \brief Return the current maximum value of the Slider
     *
     * The default value is 0.
     *
     * \return The maximum value of the Slider
     * \see setMaximum.
     */
    double maximum() const;

    /**
     * \brief Flipped the scale position regarding the cursor
     *
     * \param flipped The new flipped : if true the main scale is positionned on the left of the cursor, if false the main scale is positionned on the right of the cursor
     * \see scalePositionFlipped.
     */
    void setScalePositionFlipped(bool flipped);

    /**
     * \brief Return the current scale position flipped flag
     *
     * The default value is false
     *
     * \return The scale position flipped flag
     * \see setScalePositionFlipped.
     */
    bool scalePositionFlipped() const;

    /**
     * \brief Flipped the value field position, switch between upContainerLayout and downContainerLayout
     *
     * \param flipped The new flipped : if true the value field is positionned into the upContainerLayout, if false the value field is positionned into the downContainerLayout
     * \see valueLabelPositionFlipped.
     */
    void setValueLabelPositionFlipped(bool flipped);

    /**
     * \brief Return the current value label position flipped flag
     *
     * The default value is true.
     *
     * \return The value label position flipped flag
     * \see setvalueLabelPositionFlipped
     */
    bool valueLabelPositionFlipped() const;

    /**
     * \brief Flipped the value label position, switch between upContainerLayout and downContainerLayout
     *
     * \param flipped The new flipped : if true the value label is positionned into the upContainerLayout, if false the value label is positionned into the downContainerLayout
     * \see titleLabelPositionFlipped.
     */
    void setTitleLabelPositionFlipped(bool flipped);

    /**
     * \brief Return the current value label position flipped flag
     *
     * The default value is false.
     *
     * \return The value label position flipped flag.
     * \see setTitleLabelPositionFlipped
     */
    bool titleLabelPositionFlipped() const;

    /**
     * \brief Indicate if the main scale has to be displayed or not 
     *
     * \param visible The new boolean value indicating if the main scale has to be displayed or not 
     * \see mainScaleVisible
     */
    void setMainScaleVisible(bool visible);

    /**
     * \brief Return the boolean value indicating if the main scale has to be displayed or not 
     *
     * The default value is true.
     *
     * \return The boolean value indicating if the main scale has to be displayed or not 
     * \see setMainScaleVisible 
     */
    bool mainScaleVisible() const;

    /**
     * \brief Indicate if the additional scale has to be displayed or not 
     *
     * \param visible The new boolean value indicating if the additional scale has to be displayed or not 
     * \see additionalScaleVisible
     */
    void setAdditionalScaleVisible(bool visible);

    /**
     * \brief Return the boolean value indicating if the additional scale has to be displayed or not 
     *
     * The default value is false.
     *
     * \return The boolean value indicating if the additional scale has to be displayed or not 
     * \see setAdditionalScaleVisible.
     */
    bool additionalScaleVisible() const;

    /**
     * \brief Indicate if the title label has to be displayed or not 
     *
     * \param visible The new boolean value indicating if the title label has to be displayed or not 
     * \see titleLabelVisible.
     */
    void setTitleLabelVisible(bool visible);

    /**
     * \brief Return the boolean value indicating if the title label has to be displayed or not 
     *
     * The default value is true.
     *
     * \return The boolean value indicating if the title label has to be displayed or not 
     * \see setTitleLabelVisible.
     */
    bool titleLabelVisible() const;

    /**
     * \brief Indicate if the value field has to be displayed or not 
     *
     * \param visible The new boolean value indicating if the value field has to be displayed or not 
     * \see valueLabelVisible.
     */
    void setValueLabelVisible(bool visible);

    /**
     * \brief Return the boolean value indicating if the value field has to be displayed or not 
     *
     * The default value is true.
     *
     * \return The boolean value indicating if the value field has to be displayed or not 
     * \see setvalueLabelVisible
     */
    bool valueLabelVisible() const;

    /**
     * \brief Change the level indicator orientation
     *
     * \param orientation New orientation (horizontal or vertical)
     * \see orientation.
     */
    void setOrientation(Qt::Orientation orientation);

    /**
     * \brief Return the level indicator orientation
     *
     * The default value is Qt::Vertical
     *
     * \return Current orientation (horizontal or vertical)
     * \see setOrientation.
     */
    Qt::Orientation orientation() const;

    /**
     * \brief Return the Scale component
     *
     * \return The Scale component
     */
    LinearScale& scale();

    /**
     * \brief Return the Scale component
     *
     * \return The Scale component
     */
    LinearScale& additionalScale();

    /**
     * \brief Return the Tank component
     *
     * \return The Tank component
     */
    Tank& tank();

    /**
     * \brief Return the NumericLabel instrument
     *
     * \return The NumericLabel instrument
     */
    NumericLabel& valueLabel();

    /**
     * \brief Return the TextLabel instrument
     *
     * \return The TextLabel instrument
     */
    TextLabel& titleLabel();

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
     * \brief Set the ratio value
     *
     * \param value The new double value
     * \see value
     */
    void setValue(double value);

signals:

    /**
     * \brief Signal emitted (once) when an OutOfRange occurs
     *
     */
    void outOfRangeEntered();

    /**
     * \brief Signal emitted (once) when an OutOfRange occurs (the parameter is true), or ends (the parameter is false)
     *
     */
    void outOfRangeToggled(bool outOfRange);

protected: 

    /**
     * \brief Function called when the "enabled" state of the instrument has changed
     *
     * \param enabled True if the instrument has been enabled, false otherwise
     */
    virtual void enabledChanged(bool enabled);

private:

    goost::PimplPtr<class LevelIndicatorPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::LevelIndicator, &gics::LevelIndicator::registerMetaClass)


#endif // GICS_LEVELINDICATOR_HPP


/**
 * \class gics::LevelIndicator
 *
 * \image html levelindicator.png
 *
 * The LevelIncator contains a \ref TextLabel (called titleLabel) to display a title or a unit 
 * and a \ref NumericLabel (called valueLabel) which value is synchronized with the \ref Tank.
 *
 * <b>List of properties</b>
 * \li \ref instrumentProperties "Properties inherited from gics::Instrument"
 * \li \ref value
 * \li \ref minimum
 * \li \ref maximum
 * \li \ref mainScaleVisible
 * \li \ref additionalScaleVisible
 * \li \ref titleLabelVisible
 * \li \ref valueLabelVisible
 * \li \ref scalePositionFlipped
 * \li \ref titleLabelPositionFlipped
 * \li \ref valueLabelPositionFlipped
 * \li \ref orientation
 * \li \ref scale
 * \li \ref additionalScale
 * \li \ref tank
 * \li \ref valueLabel
 * \li \ref titleLabel
 */
