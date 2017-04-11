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


#include <gics/qt.hpp>
#include <camp/class.hpp>
#include <camp/enum.hpp>

namespace gics
{
//-------------------------------------------------------------------------------------------------
void registerQColorMetaClass()
{
    camp::Class::declare<QColor>("QColor")
        .property("red", &QColor::red, &QColor::setRed)
        .property("green", &QColor::green, &QColor::setGreen)
        .property("blue", &QColor::blue, &QColor::setBlue)
        .property("alpha", &QColor::alpha, &QColor::setAlpha)
        ;
}

//-------------------------------------------------------------------------------------------------
void registerQFontMetaClass()
{
    camp::Class::declare<QFont>("QFont")
        .property("family", &QFont::family, &QFont::setFamily)
        .property("size", &QFont::pointSize, &QFont::setPointSize)
        .property("bold", &QFont::bold, &QFont::setBold)
        .property("italic", &QFont::italic, &QFont::setItalic)
        .property("underline", &QFont::underline, &QFont::setUnderline)
        ;
}

//-------------------------------------------------------------------------------------------------
void registerQtOrientationMetaEnum()
{
    camp::Enum::declare<Qt::Orientation>("Orientation")
        .value("horizontal", Qt::Horizontal)
        .value("vertical", Qt::Vertical)
        ;
}

//-------------------------------------------------------------------------------------------------
void registerQtTextElideModeMetaEnum()
{
    camp::Enum::declare<Qt::TextElideMode>("TextElideMode")
        .value("elideLeft", Qt::ElideLeft)
        .value("elideRight", Qt::ElideRight)
        .value("elideMiddle", Qt::ElideMiddle)
        .value("elideNone", Qt::ElideNone)
        ;
}

//-------------------------------------------------------------------------------------------------
void registerQSizePolicyMetaEnum()
{
    camp::Enum::declare<QSizePolicy::Policy>("SizePolicy")
        .value("fixed", QSizePolicy::Fixed)
        .value("minimum", QSizePolicy::Minimum)
        .value("maximum", QSizePolicy::Maximum)
        .value("preferred", QSizePolicy::Preferred)
        .value("expanding", QSizePolicy::Expanding)
        .value("minimumExpanding", QSizePolicy::MinimumExpanding)
        .value("ignored", QSizePolicy::Ignored)
        ;
}

} // namespace gics
