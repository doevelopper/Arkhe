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


#ifndef GICS_PICTURE_HPP
#define GICS_PICTURE_HPP


#include <gics/component.hpp>
#include <goost/pimplptr.hpp>
#include <QObject>


namespace gics
{
/**
 * \brief Specialized component displaying a SVG picture
 */
class GICS_API Picture : public QObject, public Component
{
    Q_OBJECT 

public:

    /**
     * \brief Resize policies for borders
     */
    enum BorderMode
    {
        fixed, ///< The border keeps a fixed size
        proportional ///< The border gets resized according to the center element
    };

    /**
     * \brief Identifiers for the 9 parts of a picture
     */
    enum Region
    {
        center,     ///< inner region
        left,       ///< left border
        top,        ///< top border
        right,      ///< right border
        bottom,     ///< bottom border
        topLeft,    ///< top-left corner
        topRight,   ///< top-right corner
        bottomLeft, ///< bottom-left corner
        bottomRight ///< bottom-right corner
    };

public:

    using Component::boundingRect;
    using Component::geometry;

    /**
     * \brief Default constructor
     *
     * \param parent Parent item of the component (0 by default)
     */
    Picture(QGraphicsItem* parent = 0);

    /**
     * \brief Destructor
     */
    ~Picture();

    /**
     * \brief Set the owner SVG file
     *
     * \param file Path of the new SVG file
     * \see file
     */
    void setFile(const QString& file);

    /**
     * \brief Return the SVG file containing the picture
     *
     * The default value is an empty string (the picture is invalid).
     *
     * \return Path of the SVG file
     * \see setFile
     */
    const QString& file() const;

    /**
     * \brief Set the identifier of the picture element
     *
     * \param id New identifier
     * \see id
     */
    void setId(const QString& id);

    /**
     * \brief Return the identifier of the SVG element
     *
     * The default value is an empty string (the picture is invalid).
     *
     * \return Identifier of the element within the SVG file
     * \see setId
     */
    const QString& id() const;

    /**
     * \brief Set the border mode
     *
     * \param mode New mode
     * \see borderMode
     */
    void setBorderMode(BorderMode mode);

    /**
     * \brief Return the resize mode for borders, if any
     *
     * The default value is \ref proportional.
     *
     * \return Current border mode
     * \see setBorderMode
     */
    BorderMode borderMode() const;

    /**
     * \brief Check if the picture is valid
     *
     * A picture is valid if its internal SVG element is valid
     * (both file and id exist).
     *
     * \return True if the picture is valid
     */
    bool isValid() const;

    /**
     * \brief Return the aspect ratio of the picture
     *
     * The aspect ratio of the picture is its original width
     * divided by its original height. This is used for options
     * such as "keep aspect ratio".
     *
     * \return Aspect ratio (width / height)
     */
    qreal aspectRatio() const;

    /**
     * \brief Return the aspect ratio of a region of the picture
     *
     * The aspect ratio of a part of the picture is its original width
     * divided by its original height.
     *
     * \param region Region to which get the aspect ratio
     * \return Aspect ratio (width / height) or the region
     */
    qreal aspectRatio(Region region) const;

    /**
     * \brief Return the initial size of the whole picture
     *
     * This function returns the size of the elements as they are defined
     * in the SVG file.
     *
     * \return Initial size of the picture
     */
    QSizeF initialSize() const;

    /**
     * \brief Return the initial size of a region of the picture
     *
     * This function returns the size of the element as it is defined
     * in the SVG file.
     *
     * \param region Region to which get the size
     * \return Initial size of the region
     */
    QSizeF initialSize(Region region) const;

    /**
     * \brief Return the bounding rectangle of a region of the picture
     *
     * This function is different from geometry(Region) because
     * it returns the rectangle in local coordinates.
     *
     * \param region Region to which get the bounding rectangle
     * \return Bounding rectangle of the region, in local coordinates
     */
    QRectF boundingRect(Region region) const;

    /**
     * \brief Return the geometry of a region of the picture
     *
     * This function is different from boundingRect(Region) because
     * it returns the rectangle in parent coordinates.
     *
     * \param region Region to which get the geometry
     * \return Geometry of the region, in parent coordinates
     */
    QRectF geometry(Region region) const;

    /**
     * \brief Rotate the picture around the given point
     *
     * \param angle Angle of rotation in degree (clockwise)
     * \param center Center of rotation
     */
    void rotate(qreal angle, const QPointF& center);
    using QGraphicsItem::rotate;

    /**
     * \brief Check if a point is inside the component
     *
     * \param point Point to test in local coordinates
     * \return True if \a point lies within the area of the component
     */
    virtual bool contains(const QPointF& point) const;

    /**
     * \brief Check if the picture collides with a path
     *
     * \param path Path to test
     * \param mode Collision test to perform
     * \return True if the picture collides with \a path, false otherwise
     */
    virtual bool collidesWithPath(const QPainterPath& path, Qt::ItemSelectionMode mode) const;

    /**
     * \brief Draw the component
     *
     * \param painter Painter to use to draw the component
     * \param option Some global drawing options
     * \param widget Parent widget (0 by default)
     */
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    /**
     * \brief Get the adjustment offset of the component
     *
     * Components which want to be aligned properly in AdjustedLinearLayouts
     * must override this function to provide their min and max adjustment offsets.
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
     * \brief Signal emitted after the picture's SVG element has changed
     */
    void elementChanged();

protected:

    /**
     * \brief Return a size hint of the instrument
     *
     * Takes into account picture borders
     *
     * \param which Identifier of the hint
     * \param constraint Size constraint for this hint (no constraint by default)
     * \return Size hint
     */
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const;

private:

    goost::PimplPtr<class PicturePrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE(gics::Picture::BorderMode, &gics::Picture::registerMetaClass)
CAMP_AUTO_TYPE_NONCOPYABLE(gics::Picture, &gics::Picture::registerMetaClass)


#endif // GICS_PICTURE_HPP


/**
 * \class gics::Picture
 *
 * \image html picture.png
 *
 * Pictures are vector drawings that can be stretched without any loss of quality.
 *
 * A Picture is defined by two properties:
 * \li the path of the SVG file into which the picture is; SVG files must be compatible with the SVG Tiny 1.2 standard
 * \li the identifier (name) of the element inside the SVG file
 *
 * A Picture can have optional borders that are resized independantly from the center element,
 * to keep either a \ref fixed size (the size defined in the SVG file)
 * or a \ref proportional size (follows the size of the center element, but always keeps
 * its original aspect ratio).\n
 * Borders are automatically detected when the picture is loaded, if the following naming convention
 * is respected in the SVG file:
 *
 * \image html picturesplit.png
 *
 * Many functions of the Picture class are designed to be able to retrieve informations about
 * either the whole picture, or only a specific part of it (center, borders, corners) defined
 * in the \ref Picture::Region enumeration. This way, one can retrieve the bounding rectangle,
 * geometry, aspect ratio or initial size of any part of the picture, which is very useful for
 * specific internal calculations.
 *
 * <b>List of properties</b>
 * \li \ref file
 * \li \ref id
 * \li \ref borderMode
 */
