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


#ifndef GICS_LINEARSCALE_HPP
#define GICS_LINEARSCALE_HPP


#include <gics/abstractscale.hpp>


namespace gics
{
/**
 * \brief Specialization of AbstractScale for linear scales
 */
class GICS_API LinearScale : public AbstractScale
{
public:

    /**
     * \brief Default constructor
     *
     * This default constructor creates an horizontal scale.
     *
     * \param parent Parent item of the component (0 by default)
     */
    LinearScale(QGraphicsItem* parent = 0);

    /**
     * \brief Construct the scale with an initial orientation
     *
     * \param orientation Orientation of the scale
     * \param parent Parent item of the component (0 by default)
     */
    LinearScale(Qt::Orientation orientation, QGraphicsItem* parent = 0);

    /**
     * \brief Destructor
     */
    virtual ~LinearScale();

    /**
     * \brief Change the orientation of the scale
     *
     * \param orientation New orientation (horizontal or vertical)
     * \see orientation
     */
    void setOrientation(Qt::Orientation orientation);

    /**
     * \brief Return the orientation of the scale
     *
     * This can be either Qt::Horizontal or Qt::Vertical. \n
     * The default value is Qt::Horizontal.
     *
     * \return Current orientation
     * \see setOrientation
     */
    Qt::Orientation orientation() const;

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

    /**
     * \brief Return a size hint of the component
     *
     * \param which Identifier of the hint
     * \param constraint Size constraint for this hint (no constraint by default)
     *
     * \return Size hint
     */
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const;

private:

    goost::PimplPtr<class LinearScalePrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::LinearScale, &gics::LinearScale::registerMetaClass)


#endif // GICS_LINEARSCALE_HPP


/**
 * \class gics::LinearScale
 *
 * \image html linearscale.png
 *
 * A LinearScale is a specialized scale that is either horizontal or vertical (see \ref orientation).
 *
 * By default, the linear scale automatically expands on its main direction, and keep a fixed size on the other.
 *
 * <b>List of properties</b>
 * \li \ref scaleProperties "Properties inherited from gics::AbstractScale"
 * \li \ref orientation
 */
