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


#ifndef GICS_COMPONENT_HPP
#define GICS_COMPONENT_HPP

#include <gics/config.hpp>
#include <gics/qt.hpp>
#include <goost/pimplptr.hpp>
#include <QGraphicsItem>
#include <QGraphicsLayoutItem>


namespace gics
{
/**
 * \brief Base class for all graphical components
 */
class GICS_API Component : public QGraphicsItem, public QGraphicsLayoutItem
{
public:

    /**
     * \brief Destructor
     */
    virtual ~Component();

    /**
     * \brief Returns the bounding rectangle of the item in local coordinates
     *
     * \return Local bounding rectangle
     */
    virtual QRectF boundingRect() const;

    /**
     * \brief Check if a point is inside the component
     *
     * \param point Point to test
     *
     * \return True if \a point lies within the area of the component
     */
    virtual bool contains(const QPointF& point) const;

    /**
     * \brief Change the geometry (position and size) of the component
     *
     * \param rect New geometry
     */
    virtual void setGeometry(const QRectF& rect);

    /**
     * \brief Clear the size hint cache
     *
     * You must call this function if one of the item's size hint has changed.
     * If the item is managed by a layout, this function will notify it
     * so that it will be adjusted according to the new size hint, if necessary.
     */
    virtual void updateGeometry();

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
     * \brief Default constructor
     *
     * \param parent Item's parent (0 by default)
     */
    Component(QGraphicsItem* parent = 0);

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

    goost::PimplPtr<class ComponentPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::Component, &gics::Component::registerMetaClass)


#endif // GICS_COMPONENT_HPP


/**
 * \class gics::Component
 *
 * Component is the base class for every custom component. It inherits from both QGraphicsItem
 * and QGraphicsLayoutItem, so that it defines objects that can be transformed/painted as well
 * as be put inside graphics layouts.
 *
 * There are two main functions to override in derived classes:
 * \li \ref paint to draw the component into the scene
 * \li \ref sizeHint to specify hints used by layouts to resize the component
 *
 * A few other functions can be overriden is necessary:
 * \li \ref contains to test if the component contains a given point;
 *     by default the test is performed using the bounding rectangle
 * \li \ref setGeometry which is called to resize/move the component
 * \li \ref adjustment to return the internal margins to use if the component
 *     is put inside an AdjustedLinearLayout
 */
