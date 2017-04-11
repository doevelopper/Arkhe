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


#ifndef GICS_PRIVATE_INSTRUMENT_HPP
#define GICS_PRIVATE_INSTRUMENT_HPP


#include <gics/picture.hpp>
#include <gics/state.hpp>
#include <gics/alignment.hpp>
#include <boost/shared_ptr.hpp>
#include <QHash>
#include <QString>


class QGraphicsLayoutItem;

namespace gics
{
class InstrumentCentralLayout;
class Instrument;

/**
 * \brief Private implementation of Instrument
 */
class InstrumentPrivate
{
public:

    /**
     * \brief Default constructor
     *
     * \param instrumentPublic Pointer to the public part of the instrument
     */
    InstrumentPrivate(Instrument* instrumentPublic);

    /**
     * \brief Update the central item
     *
     * \param item New central item
     */
    void updateCentralItem(QGraphicsLayoutItem* item);

    /**
     * \brief Update the alignment of the central item
     */
    void updateAlignment();

    /**
     * \brief Refresh the contents of the instrument
     */
    void refresh();

public:

    typedef QHash<QString, boost::shared_ptr<State> > StateTable;

    Instrument* q; ///< Pointer to the public part of the instrument
    QString name; ///< Name of the instrument
    QString subClass; ///< Subclass of the instrument
    InstrumentCentralLayout* centralLayout; ///< Layout containing the central item
    QGraphicsLayoutItem* centralItem; ///< Central item of the instrument
    QSizeF centralItemSize; ///< Requested size for the central item (depends on the keepAspectRatio flag)
    Picture* background; ///< Background picture of the instrument
    Picture* foreground; ///< Foreground picture of the instrument
    bool keepAspectRatio; ///< Keep a constant width/height ratio?
    HorizontalAlignment horizontalAlignment; ///< Horizontal alignment mode for the instrument's components within its area
    VerticalAlignment verticalAlignment; ///< Vertical alignment mode for the instrument's components within its area
    StateTable states; ///< Table of registered states
    const State* state; ///< Current state of the instrument
};

} // namespace gics


#endif // GICS_PRIVATE_INSTRUMENT_HPP
