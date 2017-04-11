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


#ifndef GICS_PANEL_HPP
#define GICS_PANEL_HPP


#include <gics/config.hpp>
#include <gics/instrument.hpp>
#include <goost/pimplptr.hpp>


namespace gics
{
/**
 * \brief Panel instrument
 */
class GICS_API Panel : public Instrument
{
public:

    /**
     * \brief Constructor
     *
     * \param parent Parent item (0 by default)
     */
    Panel(QGraphicsItem* parent = 0);

    /**
     * \brief Set the central item of the panel
     *
     * The central item can be an instrument, a layout or any graphics layout item.
     *
     * \param item New central item
     * \see centralItem
     */
    void setCentralItem(QGraphicsLayoutItem* item);

    /**
     * \brief Return the central item of the instrument
     *
     * \return Current central item
     * \see setCentralItem
     */
    QGraphicsLayoutItem* centralItem() const;

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();

private:

    goost::PimplPtr<class PanelPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::Panel, &gics::Panel::registerMetaClass)


#endif // GICS_PANEL_HPP


/**
 * \class gics::Panel
 *
 * \image html panel.png
 *
 * The panel acts as a container with background/foreground pictures.
 * It can be populated with graphics items (instruments, components) or layouts.
 *
 * If the background picture has borders, the contents are automatically adjusted to
 * fit into its central area.
 *
 * Example:
 * \code
 * gics::Gauge* gauge = new gics::Gauge;
 * gics::Button* button = new gics::Button;
 *
 * QGraphicsLinearLayout* layout = new QGraphicsLinearLayout;
 * layout->addItem(gauge);
 * layout->addItem(button);
 *
 * gics::Panel* panel = new gics::Panel;
 * panel->setCentralItem(layout);
 * \endcode
 *
 * <b>List of properties</b>
 * \li \ref instrumentProperties "Properties inherited from gics::Instrument"
 */
