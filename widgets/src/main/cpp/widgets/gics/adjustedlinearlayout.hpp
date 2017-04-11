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


#ifndef GICS_ADJUSTEDLINEARLAYOUT_HPP
#define GICS_ADJUSTEDLINEARLAYOUT_HPP


#include <gics/config.hpp>
#include <goost/pimplptr.hpp>
#include <QGraphicsLinearLayout>


namespace gics
{
class Component;

/**
 * \brief Specialized linear graphics layout which aligns items according to arbitrary anchors
 *
 * When an item is added to this layout, it provides a minimum and a maximum that will be
 * the actual positions to align. Then, the layout automatically adjusts the size
 * of the items so that all the maximums are aligned, as well as all the minumums.
 *
 * For an item to be able to specify its minimum and maximum, it has to inherit from
 * the Component base classe and override the adjustment() function.
 *
 * \sa Component
 */
class GICS_API AdjustedLinearLayout : public QGraphicsLinearLayout
{
public:

    using QGraphicsLinearLayout::addItem;
    using QGraphicsLinearLayout::insertItem;
    using QGraphicsLinearLayout::removeItem;

    /**
     * \brief Default constructor
     *
     * \param parent Parent item of the layout (0 by default)
     */
    AdjustedLinearLayout(QGraphicsLayoutItem* parent = 0);

    /**
     * \brief Construct the layout with an initial orientation
     *
     * \param orientation Initial orientation (Horizontal or Vertical)
     * \param parent Parent item of the layout (0 by default)
     */
    AdjustedLinearLayout(Qt::Orientation orientation, QGraphicsLayoutItem* parent = 0);

    /**
     * \brief Destructor
     */
    ~AdjustedLinearLayout();

    /**
     * \brief Append a component to the layout
     *
     * \param item Item to add
     */
    void addItem(Component* item);

    /**
     * \brief Insert a component into the layout
     *
     * \param index Position of insertion
     * \param item Item to insert
     */
    void insertItem(int index, Component* item);

    /**
     * \brief Remove a component from the layout
     *
     * \param item Item to remove
     */
    void removeItem(Component* item);

    /**
     * \brief Remove an item given by its index
     *
     * \param index Index of the item to remove
     */
    virtual void removeAt(int index);

    /**
     * \brief Change the geometry (position and size) of the component
     *
     * \param rect New geometry
     */
    virtual void setGeometry(const QRectF& rect);

private:

    goost::PimplPtr<class AdjustedLinearLayoutPrivate> d; ///< Pointer to the private implementation
};

} // namespace gics


#endif // GICS_ADJUSTEDLINEARLAYOUT_HPP
