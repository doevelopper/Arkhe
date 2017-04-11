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


#ifndef GICS_NUMERICFIELD_HPP
#define GICS_NUMERICFIELD_HPP

#include <gics/config.hpp> 
#include <gics/alignment.hpp>
#include <gics/instrument.hpp>
#include <goost/pimplptr.hpp>


namespace gics
{
/**
 * \brief Specialized instrument displaying editable numeric text with prefix, suffix and precision management
 */
class GICS_API NumericField : public Instrument
{
    Q_OBJECT

public:

    /**
     * \brief Default constructor
     *
     * \param parent Parent item of the instrument (0 by default)
     */
    NumericField(QGraphicsItem* parent = 0);

    /**
     * \brief Constructor
     *
     * \param value is the default value
     * \param parent Parent item of the instrument(0 by default)
     */
    NumericField(double value, QGraphicsItem* parent = 0);

     /**
     * \brief Destructor
     */
    ~NumericField();

    /**
     * \brief Return the current value of the NumericField
     *
     * The default value is 0.
     *
     * \return The value of the NumericField
     * \see setValue.
     */
    double value() const;

    /**
     * \brief Change the prefix of the NumericField
     *
     * \param prefix The new prefix of the NumericField
     * \see prefix.
     */
    void setPrefix(const QString& prefix);

     /**
     * \brief Return the current prefix of the NumericField
     *
     * The default value is an empty string.
     *
     * \return The prefix of the NumericField
     * \see setPrefix.
     */
    QString prefix() const;

    /**
     * \brief Change the suffix of the NumericField
     *
     * \param suffix The new suffix of the NumericField
     * \see suffix.
     */
    void setSuffix(const QString& suffix);

    /**
     * \brief Return the current suffix of the NumericField
     *
     * The default value is an empty string.
     *
     * \return The suffix of the NumericField
     * \see setSuffix.
     */
    QString suffix() const;

    /**
     * \brief Change the minimum of the NumericField
     *
     * \param minimum The new minimum of the NumericField
     * \see minimum.
     */
    void setMinimum(double minimum);

    /**
     * \brief Return the current minimum value of the NumericField
     *
     * The default value is 0.
     *
     * \return The minimum value of the NumericField
     * \see setMinimum.
     */
    double minimum() const;

    /**
     * \brief Change the maximum of the NumericField
     *
     * \param maximum The new maximum of the NumericField
     * \see maximum.
     */
    void setMaximum(double maximum);

    /**
     * \brief Return the current maximum value of the NumericField
     *
     * The default value is 0.
     *
     * \return The maximum value of the NumericField
     * \see setMaximum.
     */
    double maximum() const;

    /**
     * \brief Change the precision of the NumericField
     *
     * \param precision The number of decimals to display (2 by default)
     * \see precision.
     */
    void setPrecision(int precision);

    /**
     * \brief Return the current precision of the NumericField
     *
     * The default value is 0.
     *
     * \return The number of decimals displayed
     * \see setPrecision.
     */
    unsigned int precision() const;

    /**
     * \brief Change the single step of the NumericField.
     *
     * The single step defines the step of 
     * incrementation/decrementation when value is changed using the wheel mouse 
     * of Up/Down keys.
     *
     * \param step The new single step of the NumericField
     * \see singleStep.
     */
    void setSingleStep(double step);

    /**
     * \brief Return the current single step of the NumericField
     *
     * The single step defines the step of 
     * incrementation/decrementation when value is changed using the wheel mouse 
     * of Up/Down keys.
     * The default value is 5.
     *
     * \return The single step of the NumericField.
     * \see setSingleStep.
     */
    double singleStep() const;

    /**
     * \brief Change the color used to render the text of the NumericField.
     *
     * \param color The new color of the NumericField.
     * \see color
     */
    void setColor(const QColor& color);

    /**
    * \brief Return the current color used to render the text of the TextField
    *
    * The default value is Qt::black.
    *
    * \return The color of the TextField
    * \see setColor
    */
    const QColor& color() const;

    /**
     * \brief Change the font used to render the text of the NumericField.
     *
     * \param font The new font of the NumericField.
     * \see font.
     */
    void setFont(const QFont& font);

    /**
     * \brief Return the font used to render the text of the TextField.
     *
     * The default value is QFont().
     *
     * \return The font of the TextField
     * \see setFont.
     */
    const QFont& font() const;

    /**
     * \brief Change the horizontal alignment mode
     *
     * \param alignment The new horizontal alignment mode
     * \see horizontalAlignment
     */
    void setHorizontalTextAlignment(HorizontalAlignment alignment);

    /**
     * \brief Return the horizontal alignment for the text
     *
     * The alignment selects where the text will be located if it is smaller
     * than the width of the component. \n
     * The default value is gics::alignLeft.
     *
     * \return The current horizontal alignment mode
     * \see setHorizontalAlignment
     */
    HorizontalAlignment horizontalTextAlignment() const;

    /**
     * \brief Change the vertical alignment mode
     *
     * \param alignment The new vertical alignment mode
     * \see verticalAlignment
     */
    void setVerticalTextAlignment(VerticalAlignment alignment);

    /**
     * \brief Return the vertical alignment mode for the text
     *
     * The alignment selects where the text will be located if it is smaller
     * than the height of the component. \n
     * The default value is gics::alignHCenter.
     *
     * \return The current vertical alignment mode
     * \see setVerticalAlignment
     */
    VerticalAlignment verticalTextAlignment() const;

    /**
     * \brief Change the validation mode flag.
     *
     * \param validateOnFocusOut The new validation mode flag.
     * \see validateOnFocusOut
     */
    void setValidateOnFocusOut(bool validateOnFocusOut);

    /**
     * \brief Return the validation mode Flag
     *
     * If the Flag is set to false,each new entered text has to be validated by pressing the Enter key to be taken into
     * account. When the component looses the focus, the last validated value is forced. 
     * If the Flag is set to true, when the component loses the focus the entered value is 
     * automatically validated.
     * The default value is true.
     *
     * \return The current validation mode Flag (default is true)
     * \see setValidateOnFocusOut
     */
    bool validateOnFocusOut() const;

    /**
     * \brief Tells if the label keeps a constant width/height ratio
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
     * \see keepAspectRatio.
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
     * \brief Return the "editing" state
     *
     * \return Reference to the "editing" state
     */
    State& editingState();

    /**
     * \brief Return the "hovered" state
     *
     * \return Reference to the "hovered" state
     */
    State& hoveredState();

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();

public slots:

    /**
     * \brief Change the value of the NumericField
     *
     * \param value The new value of the NumericField
     */
    void setValue(double value);

signals:

    /**
     * \brief This Signal is emitted when the NumericField value has changed
     *
     * The Signal is emitted when the value has been changed by a manual
     * edition of by code via the setValue method.
     *
     * \param value Corresponds to the new entered value
     */
    void valueChanged(double value);

    /**
     * \brief Signal emitted when the NumericField enters or leaves the edit mode
     *
     * \param edited True when enters the edit mode, False when leaves the edit mode
     */
    void editModeToggled(bool edited);

    /**
     * \brief This Signal is emitted once when the mouse cursor enters the Field 
     *
     */
    void hoverIn();

    /**
     * \brief This Signal is emitted once when the mouse cursor leaves the Field 
     *
     */
    void hoverOut();

protected: 

    /**
     * \brief Return a size hint of the instrument
     *
     * \param which Identifier of the hint
     * \param constraint Size constraint for this hint (no constraint by default)
     *
     * \return Size hint
     */
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const;

    /**
     * \brief re-implement event filter method to manage validation modes
     * This function saves the current text when entering in edit mode, emit the hoverIn and hoverOut signals
     * This function manages the following QEvent : QEvent::FocusIn, QEvent::Enter and QEvent::Leave.
     *
     * \param obj The watched object
     * \param event The event which has triggered the eventFilter
     *
     * \return True to stop the event being handled further, false otherwise
    */
    bool eventFilter(QObject* obj, QEvent *event);

    /**
     * \brief Function called when the "enabled" state of the instrument has changed
     *
     * \param enabled True if the instrument has been enabled, false otherwise
     */
    virtual void enabledChanged(bool enabled);

private slots:

    /**
     * \brief Catch the QDoubleSpinBox "EditingFinished" signal to manage the two possible validation modes
     */
    void handleEditingFinished();

private:

    goost::PimplPtr<class NumericFieldPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::NumericField, &gics::NumericField::registerMetaClass)


#endif // GICS_NUMERICFIELD_HPP


/**
 * \class gics::NumericField
 *
 * \image html numericfield.png
 *
 * A NumericField allows the user to edit a single line of a double value, with editing features as undo/redo, copy/cut and paste.
 *
 * A prefix and a suffix can be customized with \ref setPrefix and \ref setSuffix.
 *
 * The NumericField value can be incremented or decremented using the Up/Down keys or the wheel mouse, the single step can be configured by \ref singleStep.
 *
 * <b>List of properties</b>
 * \li \ref instrumentProperties "Properties inherited from gics::Instrument"
 * \li \ref value
 * \li \ref precision
 * \li \ref minimum
 * \li \ref maximum
 * \li \ref singleStep
 * \li \ref prefix
 * \li \ref suffix
 * \li \ref font
 * \li \ref color
 * \li \ref horizontalTextAlignment
 * \li \ref verticalTextAlignment
 * \li \ref validateOnFocusOut
 * \li \ref keepAspectRatio
 */
