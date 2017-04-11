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


#ifndef GICS_PRIVATE_LAYOUTUTILS_HPP
#define GICS_PRIVATE_LAYOUTUTILS_HPP


#include <gics/config.hpp>


class QGraphicsLayout;
class QGraphicsItem;
class QGraphicsLayoutItem;

namespace gics
{
/**
 * \brief Utility class providing missing layout functions from Qt 4.5
 *
 * This class is only a workaround and must disappear as soon as the
 * addChildLayoutItem is made publicly available in QGraphicsLayout.
 * (see http://www.qtsoftware.com/developer/task-tracker/index_html?method=entry&id=243559)
 */
class LayoutUtils
{
public:

    /**
     * \brief Reparent a child item with the parent item of the layout (if any)
     *
     * \param layout Target layout
     * \param layoutItem Target item
     */
    static void addChildLayoutItem(QGraphicsLayout* layout, QGraphicsLayoutItem* layoutItem);

//private:

    /**
     * \brief Reparent a layout's items with a parent graphics item
     *
     * \param layout Target layout
     * \param newParent Parent graphics item
     */
    static void reparentChildItems(QGraphicsLayout* layout, QGraphicsItem* newParent);

    /**
     * \brief Remove a lyout item from a layout
     *
     * \param layout Target layout
     * \param layoutItem Item to remove
     */
    static bool removeLayoutItemFromLayout(QGraphicsLayout* layout, QGraphicsLayoutItem* layoutItem);
};

} // namespace gics


#endif // GICS_PRIVATE_LAYOUTUTILS_HPP
