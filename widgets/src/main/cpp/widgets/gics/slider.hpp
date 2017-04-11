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


#ifndef GICS_SLIDER_HPP
#define GICS_SLIDER_HPP

#include <gics/config.hpp>
#include <gics/numericfield.hpp>
#include <gics/textlabel.hpp>
#include <gics/instrument.hpp>
#include <gics/alignment.hpp>
#include <gics/linearscale.hpp>
#include <goost/pimplptr.hpp>


namespace gics
{
class Cursor;

/**
 * \brief Specialized instrument which enables to set a real value by sliding a cursor
 */
class GICS_API Slider : public Instrument
{
    Q_OBJECT

public:

    /**
     * \brief Default constructor with vertical orientation
     *
     * \param parent Parent item of the instrument (0 by default)
     */
    Slider(QGraphicsItem* parent = 0);

    /**
     * \brief Default constructor
     *
     * \param orientation Orientation of the Slider
     * \param parent Parent item of the instrument (0 by default)
     */
    Slider(Qt::Orientation orientation, QGraphicsItem* parent = 0);

    /**
     * \brief Destructor
     */
    ~Slider();

    /**
     * \brief Return the current value of the Slider
     *
     * The default value is 0.
     *
     * \return The value of the Slider
     * \see setValue.
     */
    double value();

    /**
     * \brief Change the minimum of the Slider
     *
     * \param minimum The new minimum of the Slider
     * \see minimum.
     */
    void setMinimum(double minimum);

    /**
     * \brief Return the current minimum value of the Slider
     *
     * The default value is 0.
     *
     * \return The minimum value of the Slider
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
     * \see valueFieldPositionFlipped.
     */
    void setValueFieldPositionFlipped(bool flipped);

    /**
     * \brief Return the current value label position flipped flag
     *
     * The default value is true.
     *
     * \return The value label position flipped flag
     * \see setValueFieldPositionFlipped
     */
    bool valueFieldPositionFlipped() const;

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
     * \see valueFieldVisible.
     */
    void setValueFieldVisible(bool visible);

    /**
     * \brief Return the boolean value indicating if the value field has to be displayed or not 
     *
     * The default value is true.
     *
     * \return The boolean value indicating if the value field has to be displayed or not 
     * \see setValueFieldVisible
     */
    bool valueFieldVisible() const;

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
     * \brief Return the Cursor component 
     *
     * \return The Cursor component
     */
    Cursor& cursor();

    /**
     * \brief Return the TextLabel instrument used to display the title
     *
     * \return Return the TextLabel instrument
    */
    TextLabel& titleLabel();

    /**
     * \brief Return the NumericField instrument used to display the current value
     *
     * \return Return the NumericField instrument
    */
    NumericField& valueField();

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
     * \see value.
     */
    void setValue(double value);

signals:

    /**
     * \brief Signal emitted when the value has changed
     *
     */
    void valueChanged(double value);

    /**
     * \brief Signal emitted on cursor hover in 
     *
     */
    void hoverCursorIn();

    /**
     * \brief Signal emitted on cursor hover out 
     *
     */
    void hoverCursorOut();

    /**
     * \brief Signal emitted on value field hover in 
     *
     */
    void hoverValueFieldIn();

    /**
     * \brief Signal emitted on value field hover out 
     *
     */
    void hoverValueFieldOut();

protected:

    /**
     * \brief Function called when the "enabled" state of the instrument has changed
     *
     * \param enabled True if the instrument has been enabled, false otherwise
     */
    virtual void enabledChanged(bool enabled);

private slots:

    /**
     * \brief emit valueChanged signal and update the value field on cursor value changed event
     *
     * \param value The value coming from the cursor component
     */
    void handleValueChanged(double value);

    /**
     * \brief emit cursorHoverIn signal and change the Slider state to "cursor hovered"
     */
    void handleCursorHoverIn();

    /**
     * \brief emit cursorHoverOut signal and change the Slider state to "enabled"
     */
    void handleCursorHoverOut();

    /**
     * \brief translate the cursor according to the new entered value in the value field
     */
    void handleValueFieldValueChanged(double value);

    /**
     * \brief emit valueFieldHoverIn signal and change the Slider state to "value field hovered"
     */
    void handleValueFieldHoverIn();
  
    /**
     * \brief emit valueFieldHoverOut signal and change the Slider state to "enabled"
     */
    void handleValueFieldHoverOut();

    /**
     * \brief Update layouts geometry when the cursor or the rail background picture has changed
     */
    void handlePictureChanged();

private:

    goost::PimplPtr<class SliderPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::Slider, &gics::Slider::registerMetaClass)


#endif // GICS_SLIDER_HPP


/**
 * \class gics::Slider
 *
 * \image html slider.png
 *
 * The Slider contains a \ref TextLabel (called titleLabel) to display a title or a unit 
 * and a \ref NumericField (called valueField) which value is synchronized with the \ref Cursor. 
 *
 * The valueField allows the user to entered 
 * manually a new value. Note that the validateOnFocus property of the \ref NumericField is set to false by default, so each new value has to be validated 
 * with the Enter key to be taken into account.
 *
 * <b>List of properties</b>
 * \li \ref instrumentProperties "Properties inherited from gics::Instrument"
 * \li \ref value
 * \li \ref mainScaleVisible
 * \li \ref additionalScaleVisible
 * \li \ref titleLabelVisible
 * \li \ref valueFieldVisible
 * \li \ref scalePositionFlipped
 * \li \ref titleLabelPositionFlipped
 * \li \ref valueFieldPositionFlipped
 * \li \ref scale
 * \li \ref additionalScale
 * \li \ref cursor
 * \li \ref titleLabel
 * \li \ref valueField
 * \li \ref minimum
 * \li \ref maximum
 * \li \ref orientation
 */
