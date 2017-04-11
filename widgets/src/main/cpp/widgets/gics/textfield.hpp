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


#ifndef GICS_TEXTFIELD_HPP
#define GICS_TEXTFIELD_HPP

#include <gics/config.hpp>
#include <gics/alignment.hpp>
#include <gics/instrument.hpp>
#include <goost/pimplptr.hpp>

namespace gics
{
/**
 * \brief TextField instrument
 */
class GICS_API TextField : public Instrument
{
    Q_OBJECT

public:

    /**
     * \brief Default constructor
     *
     * \param parent Parent item of the instrument (0 by default)
     */
    TextField(QGraphicsItem* parent = 0);

    /**
     * \brief Constructor
     *
     * \param text default text to be displayed
     * \param parent Parent item of the instrument(0 by default)
     */
    TextField(const QString& text, QGraphicsItem* parent = 0);

    /**
     * \brief Destructor
     */
    ~TextField();

    /**
     * \brief Return the current text of the TextField
     *
     * The default value is an empty string.
     *
     * \return The text of the TextField
     * \see setText
     */
    QString text() const;

    /**
     * \brief Change the font used to render the text of the TextField
     *
     * \param font The new font of the TextField
     * \see font
     */
    void setFont(const QFont& font);

    /**
     * \brief Return the font used to render the text of the TextField
     *
     * The default value is QFont().
     *
     * \return The font of the TextField
     * \see setFont
     */
    const QFont& font() const;

    /**
     * \brief Change the color used to render the text of the TextField
     *
     * \param color The new color of the TextField
     * \see color
     */
    void setColor(const QColor& color);

    /**
     * \brief Return the color used to render the text of the TextField
     *
     * The default value is Qt::black.
     *
     * \return The color of the TextField
     * \see setColor
     */
    const QColor& color() const;

    /**
     * \brief Change the horizontal alignment mode
     *
     * \param alignment The new horizontal alignment mode
     * \see horizontalAlignment
     */
    void setHorizontalTextAlignment(HorizontalAlignment alignment);

    /**
     * \brief Return the horizontal alignment for the text of the TextField
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
     * \brief Change the vertical alignment mode of the TextField
     *
     * \param alignment The new vertical alignment mode
     * \see verticalAlignment
     */
    void setVerticalTextAlignment(VerticalAlignment alignment);

    /**
     * \brief Return the vertical alignment mode for the text of the TextField
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
     * \brief Change the validation mode flag. of the TextField
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
     * \brief Change the text
     *
     * \param text The new text
     * \see text
     */
    void setText(const QString& text);

signals:

    /**
     * \brief This Signal is emitted when the TextField text has changed
     *
     * The Signal is emitted when the text has been changed by a manual
     * edition of by code via the setText method.
     *
     * \param text Corresponds to the new entered string
     */
    void textChanged(const QString& text);

    /**
     * \brief Signal emitted when the Field enters or leaves the edit mode
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
     * \brief Function called when the "enabled" state of the instrument has changed
     *
     * \param enabled True if the instrument has been enabled, false otherwise
     */
    virtual void enabledChanged(bool enabled);

private slots:

    /**
     * \brief emit editModeToggled signal and set the TextField state to "editing" (edited = true) or enabled (edited = false)
     *
     * \param edited True if the TextField is entering the edit mode, False if the TextField is leaving the edit mode
     */
    void handleEditModeToggled(bool edited);

    /**
    * \brief emit HoverIn signal and change the TextField state to "hovered"
    */
    void handleHoverIn();

    /**
    * \brief emit t HoverOut signal and change the TextField state to "enabled"
    */
    void handleHoverOut();

private:

    goost::PimplPtr<class TextFieldPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::TextField, &gics::TextField::registerMetaClass) 


#endif // GICS_TEXTFIELD_HPP


/**
 * \class gics::TextField
 *
 * \image html textfield.png
 *
 * A TextField allows the user to edit a single line of plain text, with editing features as undo/redo, copy/cut and paste.
 *
 * The TextField instrument defines four states:
 * \li State "enabled" : the TextField is enabled (default state)
 * \li State "disabled" : the TextField is disabled, so not editable
 * \li State "editing" : the TextField is being edited
 * \li State "hovered" : the TextField is hovered by the mouse cursor
 *
 * <b>List of properties</b>
 * \li \ref instrumentProperties "Properties inherited from gics::Instrument"
 * \li \ref text
 * \li \ref font
 * \li \ref color
 * \li \ref horizontalTextAlignment
 * \li \ref verticalTextAlignment
 * \li \ref validateOnFocusOut
 * \li \ref keepAspectRatio
 */
