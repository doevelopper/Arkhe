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


// <insert copyright>

#ifndef GICS_RAIL_HPP
#define GICS_RAIL_HPP


#include <gics/component.hpp>
#include <camp/qt/qt.hpp>
#include <goost/pimplptr.hpp>
#include <QPainter>



namespace gics
{
/**
 * \brief Specialized component displaying text or numeric content, editable or not
 */
class GICS_API Rail : public Component
{

    
public:

    
     /**
     * \brief Constructor with an initial orientation
     *
     * \param orientation Orientation of the rail
     * \param parent Parent item of the component (0 by default)
     */
    Rail(Qt::Orientation orientation = Qt::Vertical, QGraphicsItem * parent = 0);

    /**
     * \brief Destructor
     */
    ~Rail();
    
     /**
     * \brief Set the ratio value
     *
     */
    void setRatio(double ratio);

    /**
     * \brief Return the current text value
     *
     */
    double ratio() const;

    /**
     * \brief Change the rail orientation
     *
     * \param orientation New orientation (horizontal or vertical)
     */
    void setOrientation(Qt::Orientation orientation);

    /**
     * \brief Return the rail orientation
     *
     * \return Current orientation (horizontal or vertical)
     */
    Qt::Orientation orientation() const;

    /**
     * \brief how the item is resized
     */
    virtual void setGeometry(const QRectF& rect);

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();


protected:

     /**
     * \brief define size behaviour
     */
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const;

 


private:

    goost::PimplPtr<class RailPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
    
    
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::Rail, &gics::Rail::registerMetaClass)


#endif // GICS_FIELD_HPP
