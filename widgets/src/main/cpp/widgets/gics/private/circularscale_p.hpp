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


#ifndef GICS_PRIVATE_CIRCULARSCALE_HPP
#define GICS_PRIVATE_CIRCULARSCALE_HPP


#include <QtGlobal>


namespace gics
{
    class CircularScale;
/**
 * \brief Private implementation of CircularScale
 */
class CircularScalePrivate
{
public:

    /**
     * \brief Constructor
     *
     * \param circularScalePublic is a pointer to the associate public part.
     */
    CircularScalePrivate(CircularScale* circularScalePublic);

    /**
      * \brief Returns true if ticks are outside the basline
      */
    bool isTickOutside() const;

    CircularScale* q; ///< Pointer to the public implementation
    qreal startAngle; ///< Start angle of the baseline
    qreal angleCourse; ///< Angle course of the baseline
    qreal baseLineFactor; ///< BaseLine position as a factor of the scale bounds inner circle
};

} // namespace gics


#endif // GICS_PRIVATE_CIRCULARSCALE_HPP
