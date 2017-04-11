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


#ifndef GICS_FIELD_HPP
#define GICS_FIELD_HPP

#include <gics/alignment.hpp>
#include <gics/component.hpp>
#include <goost/pimplptr.hpp>

namespace gics
{
/**
 * \brief Specialized component displaying a one-line text editor.
 */
class GICS_API Field : public QObject, public Component
{
    Q_OBJECT

public:

    /**
     * \brief Default constructor
     *
     * \param parent Parent item of the component (0 by default)
     */
    Field(QGraphicsItem* parent = 0);

    /**
     * \brief Constructor
     *
     * \param text default text to be displayed
     * \param parent Parent item of the component (0 by default)
     */
    Field(const QString& text, QGraphicsItem* parent = 0);

    /**
     * \brief Destructor
     */
    ~Field();

    /**
     * \brief Change the text displayed in the field
     *
     * \param text The new text of the Field
     * \see text
     */
    void setText(const QString& text);

    /**
     * \brief Return the current text of the field
     *
     * The default value is an empty string.
     *
     * \return The text of the label
     * \see setText
     */
    QString text() const;

    /**
     * \brief Change the font used to render the text of the field
     *
     * \param font The new font of the field
     * \see font
     */
    void setFont(const QFont& font);

    /**
     * \brief Return the font used to render the text of the field
     *
     * The default value is QFont().
     *
     * \return The font of the field
     * \see setFont
     */
    const QFont& font() const;

    /**
     * \brief Change the color used to render the text of the field
     *
     * \param color The new color of the field
     * \see color
     */
     void setColor(const QColor& color);

    /**
     * \brief Return the color used to render the text of the field
     *
     * Teh default value is Qt::black.
     *
     * \return The color of the field
     * \see setColor
     */
    const QColor& color() const;

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
    HorizontalAlignment horizontalAlignment() const;

    /**
     * \brief Change the horizontal alignment mode
     *
     * \param alignment The new horizontal alignment mode
     * \see horizontalAlignment
     */
    void setHorizontalAlignment(HorizontalAlignment alignment);

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
    VerticalAlignment verticalAlignment() const;

    /**
     * \brief Change the vertical alignment mode
     *
     * \param alignment The new vertical alignment mode
     * \see verticalAlignment
     */
    void setVerticalAlignment(VerticalAlignment alignment);

    /**
     * \brief Set the validation mode
     *
     * \param validateOnFocusOut The new validation mode
     * \see validateOnFocusOut
     */
     void setValidateOnFocusOut(bool validateOnFocusOut);

    /**
     * \brief Return the current validation mode
     *
     * If this property is set to false, each new entered text has to be validated by pressing the Enter key to be taken into
     * account. When the component looses the focus, the last validated value is restored. 
     * If this property is set to true, when the component looses the focus the entered value is 
     * automatically validated. \n
     * The default value is true.
     *
     * \return The current validation mode
     * \see setValidateOnFocusOut
     */
    bool validateOnFocusOut() const;

    /**
     * \brief Change the editable property
     *
     * \param editable The new value of the editable property 
     * \see editable
     */
    void setEditable(bool editable);

    /**
    * \brief Tell whether the field is editable or not
    *
    * If the field is not editable, it becomes read-only, all interactions are
    * disabled. \n
    * The default value is true.
    *
    * \return True if the field is editable, false if it is read-only
    * \see setEditable
    */
    bool editable() const;

    /**
     * \brief Change the geometry (position and size) of the component
     *
     * \param rect New geometry
     */
    virtual void setGeometry(const QRectF& rect);

    /**
     * \brief Return a size hint of the component
     *
     * \param which Identifier of the hint
     * \param constraint Size constraint for this hint (no constraint by default)
     * \return Size hint
     */
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const;

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();

signals:

    /**
     * \brief This Signal is emitted when the field text has changed
     *
     * The signal is emitted when the text has been changed by a manual
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
     * \brief re-implement event filter method to manage validation modes
     * This function saves the current text when entering in edit mode, emit the hoverIn and hoverOut signals
     * This function manages the following QEvent : QEvent::FocusIn, QEvent::Enter and QEvent::Leave.
     *
     * \param obj The watched object
     * \param event The event which has triggered the eventFilter
     * \return True to stop the event being handled further, false otherwise
     */
    bool eventFilter(QObject* obj, QEvent* event);

private slots:

    /**
     * \brief Catch the QLineEdit "EditingFinished" signal to manage the two possible validation modes
     */
    void handleEditingFinished();

    /**
     * \brief Catch the QLineEdit "ReturnPressed" signal to manage the two possible validation modes
     */
    void handleReturnPressed();

private:

    goost::PimplPtr<class FieldPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

}// namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::Field, &gics::Field::registerMetaClass)


#endif // GICS_FIELD_HPP


/**
 * \class gics::Field
 *
 * \image html field.png
 *
 * A Field allows the user to edit a single line of plain text, with editing features as undo/redo, copy/cut and paste.
 *
 * <b>List of properties</b>
 * \li \ref text
 * \li \ref font
 * \li \ref color
 * \li \ref editable
 * \li \ref horizontalAlignment
 * \li \ref verticalAlignment
 * \li \ref validateOnFocusOut
 */
