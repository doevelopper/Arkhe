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


#include <gics/button.hpp>
#include <gics/private/button_p.hpp>
#include <camp/class.hpp>


namespace gics
{
//-------------------------------------------------------------------------------------------------
void Button::registerMetaClass()
{
    camp::Enum::declare<Type>("ButtonType")
        .value("monostable", monostable)
        .value("bistable", bistable)
        ;

    camp::Enum::declare<DisplaySettings>("ButtonDisplaySettings")
        .value("nothing", showNothing)
        .value("text", showText)
        .value("icon", showIcon)
        .value("textAndIcon", showTextAndIcon)
        ;

    camp::Class::declare<ContentTransform>("ButtonContentTransform")
        .property("hScale", &ContentTransform::hScale)
        .property("vScale", &ContentTransform::vScale)
        .property("hTranslate", &ContentTransform::hTranslate)
        .property("vTranslate", &ContentTransform::vTranslate)
        ;

    camp::Class::declare<Button>("Button")
        .base<Instrument>()
        .property("type", &Button::buttonType, &Button::setButtonType)
        .property("keepAspectRatio", &Button::keepAspectRatio, &Button::setKeepAspectRatio)
        .property("iconFile", &Button::iconFile, &Button::setIconFile)
        .property("iconId", &Button::iconId, &Button::setIconId)
        .property("iconHeight", &Button::iconHeight, &Button::setIconHeight)
        .property("text", &Button::text, &Button::setText)
        .property("textFont", &Button::textFont, &Button::setTextFont)
        .property("textColor", &Button::textColor, &Button::setTextColor)
        .property("iconRelativePosition", &Button::iconRelativePosition, &Button::setIconRelativePosition)
        .property("displaySettings", &Button::displaySettings, &Button::setDisplaySettings)
        .property("contentTransform", &Button::contentTransform, &Button::setContentTransform)
        ;
}

} // namespace gics
