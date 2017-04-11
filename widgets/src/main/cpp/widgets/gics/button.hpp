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


#ifndef GICS_BUTTON_HPP
#define GICS_BUTTON_HPP

#include <gics/config.hpp>
#include <gics/instrument.hpp>
#include <gics/direction.hpp>
#include <goost/pimplptr.hpp>

namespace gics
{
class Picture;

/**
 * \brief Button instrument
 */
class GICS_API Button : public Instrument
{
    Q_OBJECT

    friend class ButtonPrivate;

public:

    /**
     * \brief Button type
     */
    enum Type
    {
        monostable, ///< Monostable button type
        bistable ///< Bistable button type
    };

    /**
     * \brief Button display settings type
     * This is used to customize which element is displayed
     */
    enum DisplaySettings
    {
        showNothing, ///< Neither display the text, nor the icon
        showText, ///< Display only the text
        showIcon, ///< Display only the icon
        showTextAndIcon ///< Display both text and icon
    };

    /**
     * \brief Structure containing transformation information for the button content (icon and text)
     *
     * These transformations are associated to states to handle "push" effects on icon and text.
     */
    struct ContentTransform
    {
        qreal hScale; ///< Horizontal scale factor
        qreal vScale; ///< Vertical scale factor
        qreal hTranslate; ///< Horizontal translation factor
        qreal vTranslate; ///< Vertical translation factor

        /**
         * \brief Build and constant transform
         * hScale = vScale = 1.0
         * hTranslate = vTranslate = 0.0
         */
        ContentTransform();

        /**
         * \brief Compare two content transform
         *
         * \param other Instance to compare
         * \return Return true if the \p other is equals to this, false otherwise
         */
        bool operator==(const ContentTransform& other) const;

        /**
         * \brief Compare two content transform
         *
         * \param other Instance to compare
         * \return Return !(*this == other)
         */
        bool operator!=(const ContentTransform& other) const;
    };

    /**
     * \brief Default constructor
     *
     * \param parent Parent item (0 by default)
     */
    Button(QGraphicsItem* parent = 0);

    /**
     * \brief Constructor
     *
     * \param text Button's text
     * \param parent Parent item (0 by default)
     */
    Button(const QString& text, QGraphicsItem* parent = 0);

    /**
     * \brief Tell what is the current type of the button
     *
     * The default value is \ref monostable.
     *
     * \return The type of the button
     * \see setButtonType
     */
    Type buttonType() const;

    /**
     * \brief Change the current button type to \a type
     *
     * \param type New type of button
     * \see buttonType
     */
    void setButtonType(Type type);

    /**
     * \brief Tell whether the button is currently released or not
     *
     * \return True if the button is up (i.e. released), false if it is down (i.e. pressed)
     */
    bool isUp() const;

    /**
     * \brief Tells whether the button is currently pressed or not
     *
     * \return True if the button is down (i.e. pressed), false if it is up (i.e. released)
     */
    bool isDown() const;

    /**
     * \brief Tell if the mouse cursor is currently over the opaque area of the button
     *
     * \return True if the mouse cursor is over the button, false otherwise
     */
    bool isHovered() const;

    /**
     * \brief Tell if the button keeps a constant width/height ratio when resized
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
     * \brief Return the "enabledUp" state
     *
     * \return Reference to the "enabledUp" state
     */
    State& enabledUpState();

    /**
     * \brief Return the "enabledDown" state
     *
     * \return Reference to the "enabledDown" state
     */
    State& enabledDownState();

    /**
     * \brief Return the "disabledUp" state
     *
     * \return Reference to the "disabledUp" state
     */
    State& disabledUpState();

    /**
     * \brief Return the "disabledDown" state
     *
     * \return Reference to the "disabledDown" state
     */
    State& disabledDownState();

    /**
     * \brief Return the "hoveredUp" state
     *
     * \return Reference to the "hoveredUp" state
     */
    State& hoveredUpState();

    /**
     * \brief Return the "hoveredDown" state
     *
     * \return Reference to the "hoveredDown" state
     */
    State& hoveredDownState();

    /**
     * \brief Return the "pressed" state when the button goes from the up to the down state
     *
     * \return Reference to the "pressed" state for up -> down transition
     */
    State& pressedUpDownState();

    /**
     * \brief Return the "pressed" state when the button goes from the down to the up state
     *
     * \return Reference to the "pressed" state for down -> up transition
     */
    State& pressedDownUpState();

    /**
     * \brief Return the filename of the SVG file containing the icon to display on the button
     *
     * The default value is an empty string.
     *
     * \return The icon filename
     * \see setIconFile iconId
     */
    const QString& iconFile() const;

    /**
     * \brief Set the filename of the SVG file containing the icon to display on the button
     *
     * \param filename The SVG file which contains the icon
     * \see iconFile
     */
    void setIconFile(const QString& filename);

    /**
     * \brief Return the identifier of the icon inside the SVG file
     *
     * The default value is an empty string.
     *
     * \return The id of the SVG element used as icon
     * \see setIconId iconFile
     */
    const QString& iconId() const;

    /**
     * \brief Set the identifier of the icon inside the SVG file
     *
     * \param id The id of the SVG element used as icon
     * \see iconId
     */
    void setIconId(const QString& id);

    /**
     * \brief Return the height of the icon
     *
     * The default value is the initial size of the icon in the SVG file.
     *
     * \return The icon height in pixels
     * \see setIconHeight
     */
    qreal iconHeight() const;

    /**
     * \brief Set the icon height
     *
     * \param height The height of the icon in pixels.
     */
    void setIconHeight(qreal height);

    /**
     * \brief Return the text displayed in the button
     *
     * The default value is "Button".
     *
     * \return The button text
     * \see setText
     */
    const QString& text() const;

    /**
     * \brief Set the text displayed in the button
     *
     * \param text The text to be displayed on the button
     * \see text
     */
    void setText(const QString& text);

    /**
     * \brief Return the button text font
     *
     * The default value is QFont().
     *
     * \return The button text font
     * \see setTextfont
     */
    QFont textFont() const;

    /**
     * \brief Set the button text font
     *
     * \param font The font to be used for the text
     * \see font
     */
    void setTextFont(const QFont& font);

    /**
     * \brief Return the color used for the button text
     *
     * The default value is Qt::black.
     *
     * \return The text color
     * \see setTextColor
     */
    QColor textColor() const;

    /**
     * \brief Set the color used for the text
     *
     * \param color The text color
     * \see textColor
     */
    void setTextColor(const QColor& color);

    /**
     * \brief Return the position of the icon relative to the text
     *
     * This property is used when \ref displaySettings is \ref showTextAndIcon;
     * otherwise it is ignored. \n
     * The default value is gics::left.
     *
     * \return The icon position relative to the text
     * \see setIconRelativePosition
     */
    Direction iconRelativePosition() const;

    /**
     * \brief Set the icon relative position
     *
     * \param position The icon position relative to the text
     * \see iconRelativePosition
     */
    void setIconRelativePosition(Direction position);

    /**
     * \brief Return the display settings
     *
     * The display settings select what is displayed in the button:
     * text, icon, none or both. \n
     * The default value is \ref showText.
     *
     * \return Return if the text and/or the icon is displayed
     * \see setDisplaySettings
     */
    DisplaySettings displaySettings() const;

    /**
     * \brief Set the display settings
     *
     * \param settings The display settings to be used
     * \see displaySettings
     */
    void setDisplaySettings(DisplaySettings settings);

    /**
     * \brief Return the content transformation
     *
     * The content transform is applied to both the icon and text (depending on \ref displaySettings),
     * it allows to move/scale them to simulate perspective when pressing the button.
     *
     * \return The content transformation
     * \see setContentTransform
     */
    const ContentTransform& contentTransform() const;
    
    /**
     * \brief Set the content transformation
     *
     * \param transform Content transform to apply
     * \see contentTransform
     */
    void setContentTransform(const ContentTransform& transform);

    /**
     * \brief Draw the instrument
     *
     * \param painter Painter to use to draw the instrument
     * \param option Some global drawing options
     * \param widget Parent widget (0 by default)
     */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();

signals:
    /**
     * \brief This signal is emitted when the button is pressed
     *
     * For example, this occurs each time the user click on the button, but has not yet released
     * its mouse click.
     */
    void pressed();

    /**
     * \brief This signal is emitted when the button is released
     *
     * For example, this occurs each time the user release a mouse click on a button just being
     * pressed().
     */
    void released();

    /**
     * \brief This signal is emitted when a button is activated
     *
     * A button is activated, for example, if it is pressed and then released while the mouse
     * cursor is inside the button, when the shortcut key is typed, or when click() or
     * animateClick() is called. Notably, calling press() and then release() will not emit this
     * signal.
     *
     * \param down For a bistable button \a down is true if it is pushed, otherwise \a down is false.
     */
    void clicked(bool down = false);

public slots:

    /**
     * \brief Performs a click
     *
     * It is equivalent to calling press() and then release().
     */
    void click();

    /**
     * \brief Performs an animated click
     *
     * The button is pressed immediately, and released msec milliseconds later.
     *
     * \param msec Duration of the animation, in milliseconds
     */
    void animateClick(int msec = 100);

protected:

    /**
     * \brief Press the button
     *
     * If the button is already pressed, or if the button is disabled, it does nothing.
     * See also release().
     */
    void press();

    /**
     * \brief Release the button
     *
     * If the button is already released, or if the button is disabled, it does nothing.
     * See also press().
     */
    void release();

    /**
     * \brief Function called when the "enabled" state of the instrument has changed
     *
     * \param enabled True if the instrument has been enabled, false otherwise
     */
    virtual void enabledChanged(bool enabled);

    /**
     * \brief Catch the mouse move event to update the mouse inside information.
     *
     * This use a per pixel collision test instead of the bounding rectangle.
     *
     * \param event Event's attributes
     */
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    /**
     * \brief Catch the hover move event to update the mouse inside information.
     *
     * This use a per pixel collision test instead of the bounding rectangle.
     *
     * \param event Event's attributes
     */
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent* event);

    /**
     * \brief Catch the hover leave event to update the mouse inside information.
     *
     * \param event Event's attributes
     */
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

    /**
     * \brief Catch the mouse press event to handle button click.
     *
     * \param event Event's attributes
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    /**
     * \brief Catch the mouse release event to handle button click.
     *
     * \param event Event's attributes
     */
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    /**
     * \brief Return a size hint
     *
     * \param which Identifier of the hint
     * \param constraint Size constraint for this hint (no constraint by default)
     * \return Size hint
     */
    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint) const;
    
private:

    goost::PimplPtr<class ButtonPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::Button, &gics::Button::registerMetaClass)
CAMP_AUTO_TYPE(gics::Button::Type, &gics::Button::registerMetaClass)
CAMP_AUTO_TYPE(gics::Button::DisplaySettings, &gics::Button::registerMetaClass)
CAMP_AUTO_TYPE(gics::Button::ContentTransform, &gics::Button::registerMetaClass)

#endif // GICS_BUTTON_HPP


/**
 * \class gics::Button
 *
 * \image html button.png
 *
 * The Button instrument is a standard button that can be pressed / released. It can display a text, an icon, both or nothing.
 *
 * Buttons can be monostable (they can't stay in pressed state, they automatically go back to released) or bistable
 * (they can stay in both pressed and released states).
 *
 * <b>List of properties</b>
 * \li \ref instrumentProperties "Properties inherited from gics::Instrument"
 * \li \ref buttonType "type"
 * \li \ref keepAspectRatio
 * \li \ref iconFile
 * \li \ref iconId
 * \li \ref iconHeight
 * \li \ref text
 * \li \ref textFont
 * \li \ref textColor
 * \li \ref iconRelativePosition
 * \li \ref displaySettings
 * \li \ref contentTransform
 */
