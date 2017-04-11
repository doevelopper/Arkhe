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


#ifndef GICS_QT_HPP
#define GICS_QT_HPP


#include <gics/config.hpp>
#include <camp/camptype.hpp>
#include <camp/qt/qt.hpp>
#include <QColor>
#include <QFont>
#include <QSizePolicy>


namespace gics
{
/**
 * \brief Declare the metaclass of QColor
 */
GICS_API void registerQColorMetaClass();

/**
 * \brief Declare the metaclass of QFont
 */
GICS_API void registerQFontMetaClass();

/**
 * \brief Declare the metaenum of Qt::Orientation
 */
GICS_API void registerQtOrientationMetaEnum();

/**
 * \brief Declare the metaclass of Qt::TextElideMode
 */
GICS_API void registerQtTextElideModeMetaEnum();

/**
 * \brief Declare the metaclass of QSizePolicy::Policy
 */
GICS_API void registerQSizePolicyMetaEnum();

} // namespace gics

CAMP_AUTO_TYPE(QColor, &gics::registerQColorMetaClass);
CAMP_AUTO_TYPE(QFont, &gics::registerQFontMetaClass);
CAMP_AUTO_TYPE(Qt::Orientation, &gics::registerQtOrientationMetaEnum);
CAMP_AUTO_TYPE(Qt::TextElideMode, &gics::registerQtTextElideModeMetaEnum);
CAMP_AUTO_TYPE(QSizePolicy::Policy, &gics::registerQSizePolicyMetaEnum);



#endif // GICS_QT_HPP
