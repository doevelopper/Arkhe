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


#ifndef GICS_INSTRUMENTCENTRALLAYOUT_HPP
#define GICS_INSTRUMENTCENTRALLAYOUT_HPP


#include <goost/pimplptr.hpp>
#include <QGraphicsLinearLayout>


class QGraphicsItem;

namespace gics
{
class Picture;

/**
 * \brief Specialized layout for instrument's central item
 *
 * This layout stacks up the background, the central item and the foreground.
 *
 * \sa Instrument
 */
class InstrumentCentralLayout : public QGraphicsLinearLayout
{
public:

    /**
     * \brief Constructor
     *
     * \param parent Parent graphics item of the layout
     * \param background Background picture
     * \param foreground Foreground picture
     */
    InstrumentCentralLayout(QGraphicsItem* parent, Picture* background, Picture* foreground);

    /**
     * \brief Set the unique item of the layout
     *
     * The previous item, if any, is automatically removed from the layout.
     *
     * \param item Item to set in the layout
     */
    void setItem(QGraphicsLayoutItem* item);

    /**
     * \brief Change the geometry (position and size) of the layout
     *
     * \param rect Rectangle defining the new geometry
     */
    virtual void setGeometry(const QRectF& rect);

private:

    goost::PimplPtr<class InstrumentCentralLayoutPrivate> d; ///< Pointer to the private implementation
};

} // namespace gics


#endif // GICS_INSTRUMENTCENTRALLAYOUT_HPP
