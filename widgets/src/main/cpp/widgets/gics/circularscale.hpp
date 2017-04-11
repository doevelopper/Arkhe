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


#ifndef GICS_CIRCULARSCALE_HPP
#define GICS_CIRCULARSCALE_HPP


#include <gics/abstractscale.hpp>


namespace gics
{
/**
 * \brief Specialization of AbstractScale for circular scales
 */
class GICS_API CircularScale : public AbstractScale
{
public:

    /**
     * \brief Default constructor
     *
     * This constructor creates a full (360 degrees) circular scale
     *
     * \param parent Parent item of the component (0 by default)
     */
    CircularScale(QGraphicsItem* parent = 0);

    /**
     * \brief Destructor
     */
    virtual ~CircularScale();

    /**
     * \brief Change the start angle of the scale
     *
     * \param angle New start angle, in degrees
     * \see startAngle
     */
    void setStartAngle(qreal angle);

    /**
     * \brief Return the start angle in degrees
     *
     * The default value is 0.
     *
     * \return Start angle
     * \see setStartAngle
     */
    qreal startAngle() const;

    /**
     * \brief Change the angle course of the scale
     *
     * \param course New angle course, in degrees
     * \see angleCourse
     */
    void setAngleCourse(qreal course);

    /**
     * \brief Return the angle course in degrees
     *
     * This property can be used to modify the length of the base circle:
     * a course of 180 defines a half-circle, 360 a full circle, etc. \n
     * The default value is 360.
     *
     * \return Angle course
     * \see setAngleCourse
     */
    qreal angleCourse() const;

    /**
     * \brief Set baseline position as a factor of the radius of the scale bounds inner circle
     *
     * \param factor Factor (between 0 and 1)
     * \see baseLinePosition
     */
    void setBaseLinePosition(qreal factor);

    /**
      * \brief Return the baseline postion as a factor of the radius of the scale bounds inner circle
      *
      * The default value is 0.8.
      *
      * \return Factor (between 0 and 1)
      * \see setBaseLinePosition
      */
    qreal baseLinePosition() const;


    /**
     * \brief Paint reimplementation
     */
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();

protected:

    /**
     * \brief Recompute the shape of the baseline to fit in a given bounding rectangle
     *
     * This function must take in account the labels and ticks so that the whole scale
     * fits exactly in the given bounding rectangle.
     *
     * \param bounds Bounding rectangle to fit in
     *
     * \return Shape describing the new baseline
     */
    virtual QPainterPath updateBaseLine(const QRectF& bounds) const;

    QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint) const;
private:

    goost::PimplPtr<class CircularScalePrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::CircularScale, &gics::CircularScale::registerMetaClass)


#endif // GICS_CIRCULARSCALE_HPP


/**
 * \class gics::CircularScale
 *
 * \image html circularscale.png
 *
 * The CircularScale is a specialized scale with a circular baseline.
 *
 * The base circle can be customized so that the start and end values can be put anywhere. Its radius
 * automatically expands so that the scale always fits exactly its geometry.
 *
 * <b>List of properties</b>
 * \li \ref scaleProperties "Properties inherited from gics::AbstractScale"
 * \li \ref startAngle
 * \li \ref angleCourse
 */
