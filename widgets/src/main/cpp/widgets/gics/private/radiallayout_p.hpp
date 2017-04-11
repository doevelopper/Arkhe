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


#ifndef GICS_PRIVATE_RADIALLAYOUT_HPP
#define GICS_PRIVATE_RADIALLAYOUT_HPP


#include <QList>

class QGraphicsLayoutItem;

namespace gics
{

/**
 * \brief Private implementation of RadialLayout
 */
class RadialLayoutPrivate
{
public:
    class Item; ///< Forward declare the class used to manage items

public:
    QList<Item*> items; ///< Set of items stored in the layout
};

/**
 * \brief Class used to manage an item added to the radial layout
 * This is a private class
 */
class RadialLayoutPrivate::Item
{
public:
    QGraphicsLayoutItem* item; ///< The item
    double radialFactor; ///< Factor of the layout's radius to determine the item's center position
    double angle; ///< Angle from 3 o'clock (clockwise) to determine the item's center position
    QSizeF sizeConstraint; ///< Size constraint to applied on the final item size

    /**
     * \brief Return the ideal item geometry according to the given layout center and radius.
     *
     * \param layoutCenter The center of the associated radial layout
     * \param layoutRadius The radius of the associated radial layout
     * \return the ideal item geometry
     */
    QRectF updatedGeometry(const QPointF& layoutCenter, qreal layoutRadius) const;
};

} // namespace gics


#endif // GICS_PRIVATE_RADIALLAYOUT_HPP
