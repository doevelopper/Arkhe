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


#ifndef GICS_CURSOR_HPP
#define GICS_CURSOR_HPP

#include <gics/component.hpp>
#include <goost/pimplptr.hpp>
#include <gics/picture.hpp>

namespace gics
{
class Picture;

/**
 * \brief Specialized component displaying a linear cursor which can be translated along a rail.
 */
class GICS_API Cursor : public QObject, public Component
{
    Q_OBJECT

public:

    /**
     * \brief Default constructor (vertical orientation)
     *
     * \param parent Parent item of the component (0 by default)
     */
    Cursor(QGraphicsItem* parent = 0);
  
    /**
     * \brief Constructor with an initial orientation
     *
     * \param orientation Orientation of the cursor
     * \param parent Parent item of the component (0 by default)
     */
    Cursor(Qt::Orientation orientation, QGraphicsItem* parent = 0);

    /**
     * \brief Destructor
     */
    ~Cursor();

    /**
     * \brief Change the current value of the Cursor
     *
     * \param value The new value of the cursor
     * \see value
     */
    void setValue(double value);

    /**
     * \brief Return the current value of the cursor
     *
     * The default value is 0.
     *
     * \return The value of the cursor
     * \see setValue
     */
    double value() const;

    /**
     * \brief Change the thickness of the rail
     *
     * \param railThickness The new value for the rail thickness 
     * \see railThickness
     */
    void setRailThickness(unsigned int railThickness);

    /**
     * \brief Return the rail thickness
     *
     * The default value is 5.
     *
     * \return The current rail thickness
     * \see setRailThickness
     */
    unsigned int railThickness() const;

    /**
     * \brief Change the minimum value of the cursor
     *
     * \param minimum The new minimum of the cursor
     * \see minimum
     */
    void setMinimum(double minimum);

    /**
     * \brief Return the current minimum value of the cursor
     *
     * The default value is 0.
     *
     * \return The minimum value of the cursor
     * \see setMinimum
     */
    double minimum() const;

    /**
     * \brief Change the maximum value of the cursor
     *
     * \param maximum The new maximum of the cursor
     * \see maximum
     */
    void setMaximum(double maximum);

    /**
     * \brief Return the current maximum value of the cursor
     *
     * The default value is 100.
     *
     * \return The maximum value of the cursor
     * \see setMaximum
     */
    double maximum() const;

    /**
     * \brief Change the cursor single step
     *
     * \param singleStep The new single step value
     * \see singleStep
     */
    void setSingleStep(double singleStep);

    /**
     * \brief Return the single step
     *
     * The single step is the offset applied to the cursor when the up/down
     * keys are pressed, on mouse wheel, or on a click on the rail.
     *
     * \return The current single step
     * \see setSingleStep
     */
    double singleStep() const;

    /**
     * \brief Return a reference to the cursor picture
     *
     * \return The cursor picture 
     */
    Picture& cursorPicture();

    /**
     * \brief Return a reference to the rail background picture
     *
     * \return The rail background picture 
     */
    Picture& railBackground();

    /**
     * \brief Return a reference to the rail foreground picture
     *
     * \return The rail foreground picture 
     */
    Picture& railForeground();

    /**
     * \brief Change the global orientation of the component
     *
     * \param orientation New orientation (horizontal or vertical)
     * \see orientation
     */
    void setOrientation(Qt::Orientation orientation);

    /**
     * \brief Return the global orientation of the component
     *
     * The orientation can be either Qt::Horizontal or Qt::Vertical. \n
     * The default value is Qt::Vertical.
     *
     * \return Current orientation
     * \see setOrientation
     */
    Qt::Orientation orientation() const;

    /**
     * \brief how the item is resized
     */
    virtual void setGeometry(const QRectF& rect);

    /**
     * \brief Get the adjustment offset of the component
     *
     * Components which want to be aligned properly in AdjustedLinearLayouts
     * must override this function to provide their min and max adjustment offsets.
     *
     * This function is automatically called each time the component calls updateGeometry().
     *
     * \param orientation Orientation of the parent layout
     * \param minimum Variable to fill with the component's minimum offset
     * \param maximum Variable to fill with the component's maximum offset
     */
    virtual void adjustment(Qt::Orientation orientation, qreal& minimum, qreal& maximum);

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();

signals:

    /**
     * \brief This Signal is emitted when the cursor value has changed
     *
     * \param value Corresponds to the new entered value
     */
    void valueChanged(double value);

    /**
     * \brief This Signal is emitted when the cursor has been moved 
     *
     * \param value Corresponds to the new cursor value
     */
    void cursorMoved(double value);

    /**
     * \brief Signal emitted on mouse hover in 
     */
    void hoverCursorIn();

    /**
     * \brief Signal emitted on mouse hover in 
     */
    void hoverCursorOut();

protected:

    /**
     * \brief Return a size hint of the component
     *
     * \param which Identifier of the hint
     * \param constraint Size constraint for this hint (no constraint by default)
     *
     * \return Size hint
     */
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const;

    /**
     * \brief Catch the hover move event to emit the hoverIn signal
     *
     * \param event Event's attributes
     */
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent* event);

    /**
     * \brief Catch the hover move event to emit the hoverOut signal
     *
     * \param event Event's attributes
     */
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

     /**
     * \brief Catch the mouse move event to translate the cursor picture
     *
     * \param event Event's attributes
     */
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

    /**
     * \brief Catch the mouse press event to store the current mouse position
     *
     * \param event Event's attributes
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);

    /**
     * \brief Catch the mouse release event to stop to translate the cursor
     *
     * \param event Event's attributes
     */
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    /**
     * \brief Catch the wheel mouse event to translate the cursor of one step
     *
     * \param event Event's attributes
     */
    virtual void wheelEvent(QGraphicsSceneWheelEvent* event);

    /**
     * \brief Catch the key press event to translate the cursor of one step
     *
     * \param event Event's attributes
     */
    virtual void keyPressEvent(QKeyEvent* event);

private slots:

    /**
     * \brief Update cursor and rail geometry when the cursor or the rail background picture has changed
     */
    void handlePictureChanged();

private:

    goost::PimplPtr<class CursorPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()

};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::Cursor, &gics::Cursor::registerMetaClass)


#endif // GICS_FIELD_HPP


/**
 * \class gics::Cursor
 *
 * \image html cursor.png
 *
 * This component allow the user to translate a cursor Picture along a linear rail composed of two Picture for the background and the foreground (filled part).
 *
 * The Cursor \ref value can be moved step by step using the Up/Down keys, the wheel mouse or by clicking above/below the cursor, the single step can be configured by \ref singleStep.
 *
 * The cursor aspectRatio is always keep but its size depends on two parameters:
 * \li the \ref railThickness property
 * \li the initial ratio between the cursor and the rail background svg elements.
 *
 * This ratio is evaluated as the following (at the beginning and every time the cursor or the background picture is changed):
 * \li Vertical orientation : ratio = cursor svg element width / rail background svg element width.
 * \li Horizontal orientation : ratio = cursor svg element height / rail background svg element height.
 *
 * Then the current cursor size is deducted from the \ref railThickness and the ratio previously evaluated.
 * \li Vertical orientation : cursor width = \ref railThickness * ratio.
 * \li Horizontal orientation : cursor height = \ref railThickness / ratio.
 *
 * <b>List of properties</b>
 * \li \ref value
 * \li \ref minimum
 * \li \ref maximum
 * \li \ref singleStep
 * \li \ref orientation
 * \li \ref railThickness
 * \li \ref cursorPicture "cursor"
 * \li \ref railBackground
 * \li \ref railForeground
 */
