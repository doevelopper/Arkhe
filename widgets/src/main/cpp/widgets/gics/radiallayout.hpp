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


#ifndef GICS_RADIALLAYOUT_HPP
#define GICS_RADIALLAYOUT_HPP


#include <gics/config.hpp>
#include <goost/pimplptr.hpp>
#include <QGraphicsLayout>


namespace gics
{
/**
 * \brief Specialized graphics layout which manage items positions according to an angle and two radius.
 */
class GICS_API RadialLayout : public QGraphicsLayout
{
public:

    /**
     * \brief Default constructor
     *
     * \param parent Parent item of the layout (0 by default)
     */
    RadialLayout(QGraphicsLayoutItem* parent = 0);

    /**
     * \brief Destructor
     */
    virtual ~RadialLayout();

    /**
     * \brief Add \a item to the layout.
     *
     * The center of the item will be placed to the angular position defined by \a radialFactor and
     * \a angle. \a radialFactor is the ratio of the layout's radius which determine the position of
     * the center along the radius [-1.0, 1.0]. \a angle is the angle in [0.0, 360.0[ from 3
     * o'clock, clockwise.
     * The item size will be computed according to the size policy of \a item. However, \a
     * sizeConstraint can be used to constrain the final item size according to the layout diameter
     * ratio and the item's policy flags. Thus, the width and height components of \a sizeConstraint
     * shall be contains in [0.0, 1.0]. If the item has QSizePolicy::ExpandFlag or
     * QSizePolicy::IgnoreFlag, the size constraint is used to compute the maximum allowed size for
     * the item. Otherwise, the sizeConstraint is ignored.
     *
     * \param item Item to add
     * \param radialFactor Position of the item along the radius
     * \param angle Angular position of the item
     * \param sizeConstraint Optional size constraint (not used by default)
     */
    void addItem(QGraphicsLayoutItem* item, double radialFactor, double angle, const QSizeF& sizeConstraint = QSizeF());

    /**
     * \brief Remove an item from the layout
     *
     * \param item Item to remove
     */
    void removeItem(QGraphicsLayoutItem* item);

    /**
     * \brief Retrieve the radial factor of an item
     *
     * \param item subject item (must be in the layout)
     * \return The radial factor of \a item
     */
    double radialFactor(QGraphicsLayoutItem* item) const;

    /**
     * \brief Change the radial factor of an item
     *
     * \param item subject item (must be in the layout)
     * \param radialFactor new radial factor of \a item
     */
    void setRadialFactor(QGraphicsLayoutItem* item, double radialFactor);

    /**
     * \brief Retrieve the angle of an item
     *
     * \param item subject item (must be in the layout)
     * \return The angle of \a item
     */
    double angle(QGraphicsLayoutItem* item) const;

    /**
     * \brief Change the angle of an item
     *
     * \param item subject item (must be in the layout)
     * \param angle new angle of \a item
     */
    void setAngle(QGraphicsLayoutItem* item, double angle);

    /**
     * \brief Retrieve the size constraint of an item
     *
     * \param item subject item (must be in the layout)
     * \return The size constraint of \a item
     */
    QSizeF sizeConstraint(QGraphicsLayoutItem* item) const;

    /**
     * \brief Change the size constraint of an item
     *
     * \param item subject item (must be in the layout)
     * \param sizeConstraint new size constraint of \a item
     */
    void setSizeConstraint(QGraphicsLayoutItem* item, const QSizeF& sizeConstraint);

    /**
     * \brief Return the index of \a item
     *
     * \param item The item to search for
     * \return The index of \a item, or -1 if \a item is not in the layout
     */
    int indexOf(QGraphicsLayoutItem* item) const;
    
    /**
     * \brief Return the number of items in the layout
     *
     * \return Total number of items currently in the layout
     */
    virtual int count() const;

    /**
     * \brief Retrieve the item at the specified position
     *
     * \param index Position of the item to get
     *
     * \return Item at position \a index (0 if not found)
     */
    virtual QGraphicsLayoutItem* itemAt(int index) const;

    /**
     * \brief Remove the item at the specified position
     *
     * \param index Position of the item to remove
     */
    virtual void removeAt(int index);

    /**
     * \brief Update geometry
     *
     *  Reimplement QGraphicsLayout::updateGeometry() due to Qt limitation
     */
    virtual void updateGeometry();

    /**
     * \brief Invalidate the layout
     *
     *  Reimplement QGraphicsLayout::invalidate() due to Qt limitation
     */
    virtual void invalidate();

    /**
     * \brief Change the geometry (position and size) of the component
     *
     * \param rect New geometry
     */
    virtual void setGeometry(const QRectF& rect);

private:

    /**
     * \brief Return a size hint of the layout
     *
     * \param which Identifier of the hint
     * \param constraint Size constraint for this hint (no constraint by default)
     *
     * \return Size hint
     */
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const;

private:

    goost::PimplPtr<class RadialLayoutPrivate> d; ///< Pointer to the private implementation
};

} // namespace gics


#endif // GICS_RADIALLAYOUT_HPP
