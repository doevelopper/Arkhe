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


#ifndef GICS_TANK_HPP
#define GICS_TANK_HPP

#include <gics/component.hpp>
#include <goost/pimplptr.hpp>

namespace gics
{

class Picture;

/**
 * \brief Specialized component displaying a linear tank filled according to its ratio value 
 */
class GICS_API Tank : public QObject, public Component
{
    Q_OBJECT

public:

    /**
     * \brief Default constructor (vertical orientation)
     *
     * \param parent Parent item of the component (0 by default)
     */
    Tank(QGraphicsItem* parent = 0);

    /**
     * \brief Constructor with an initial orientation
     *
     * \param orientation Orientation of the tank
     * \param parent Parent item of the component (0 by default)
     */
    Tank(Qt::Orientation orientation, QGraphicsItem* parent = 0);

    /**
     * \brief Destructor
     */
    ~Tank();

    /**
     * \brief Change the current value of the tank
     *
     * \param value The new value of the tank
     * \see value
     */
    void setValue(double value);

    /**
     * \brief Return the current value of the tank
     *
     * The default value is 0.
     *
     * \return The current value of the tank
     * \see setValue
     */
    double value() const;

    /**
     * \brief Change the minimum value of the tank

     * \param minimum The new minimum value of the tank
     * \see minimum
     */
    void setMinimum(double minimum);

    /**
     * \brief Return the current minimum value of the tank
     *
     * The default value is 0.

     * \return The minimum value of the tank
     * \see setMinimum
     */
    double minimum() const;

    /**
     * \brief Change the maximum value of the tank
     *
     * \param maximum The new maximum value of the tank
     * \see maximum
     */
    void setMaximum(double maximum);

    /**
     * \brief Return the current maximum value of the tank
     *
     * The default value is 100.
     *
     * \return The maximum value of the tank
     * \see setMaximum
     */
    double maximum() const;

    /**
     * \brief Return a reference to the background picture of the tank
     *
     * \return The background picture 
     */
    Picture& background();

    /**
     * \brief Return a reference to the foreground picture of the tank
     *
     * \return The foreground picture 
     */
    Picture& foreground();

    /**
     * \brief Change the global orientation of the tank
     *
     * \param orientation New orientation (horizontal or vertical)
     * \see orientation
     */
    void setOrientation(Qt::Orientation orientation);

    /**
     * \brief Return the global orientation of the tank
     *
     * The orientation can be either Qt::Horizontal or Qt::Vertical. \n
     * The default value is Qt::Vertical.
     *
     * \return Current orientation
     * \see setOrientation
     */
    Qt::Orientation orientation() const;

    /**
     * \brief Change the geometry (position and size) of the component
     *
     * \param rect New geometry
     */
    virtual void setGeometry(const QRectF& rect);

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

signals:

    /**
     * \brief This Signal is emitted when the Tank value has changed
     *
     * \param value Corresponds to the new entered value
     */
    void valueChanged(double value);

private:

    goost::PimplPtr<class TankPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()

};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::Tank, &gics::Tank::registerMetaClass)

#endif // GICS_FIELD_HPP


/**
 * \class gics::Tank
 *
 * \image html tank.png
 *
 * This component is composed of two \ref Picture, a background and a foreground which is extended regarding the current ratio value.
 *
 * <b>List of properties</b>
 * \li \ref value
 * \li \ref minimum
 * \li \ref maximum
 * \li \ref orientation
 * \li \ref background
 * \li \ref foreground
 */
