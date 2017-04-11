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


#include <gics/levelindicator.hpp>
#include <camp/class.hpp>

namespace gics
{
//-------------------------------------------------------------------------------------------------
void LevelIndicator::registerMetaClass()
{
    camp::Class::declare<LevelIndicator>("LevelIndicator")
        .base<Instrument>()
        .property("value", &LevelIndicator::value, &LevelIndicator::setValue)
        .property("minimum", &LevelIndicator::minimum, &LevelIndicator::setMinimum)
        .property("maximum", &LevelIndicator::maximum, &LevelIndicator::setMaximum)
        .property("mainScaleVisible", &LevelIndicator::mainScaleVisible, &LevelIndicator::setMainScaleVisible)
        .property("additionalScaleVisible", &LevelIndicator::additionalScaleVisible, &LevelIndicator::setAdditionalScaleVisible)
        .property("titleLabelVisible", &LevelIndicator::titleLabelVisible, &LevelIndicator::setTitleLabelVisible)
        .property("valueLabelVisible", &LevelIndicator::valueLabelVisible, &LevelIndicator::setValueLabelVisible)
        .property("scalePositionFlipped", &LevelIndicator::scalePositionFlipped, &LevelIndicator::setScalePositionFlipped)
        .property("titleLabelPositionFlipped", &LevelIndicator::titleLabelPositionFlipped, &LevelIndicator::setTitleLabelPositionFlipped)
        .property("valueLabelPositionFlipped", &LevelIndicator::valueLabelPositionFlipped, &LevelIndicator::setValueLabelPositionFlipped)
        .property("orientation", &LevelIndicator::orientation, &LevelIndicator::setOrientation)
        .property("scale", &LevelIndicator::scale)
        .property("additionalScale", &LevelIndicator::additionalScale)
        .property("tank", &LevelIndicator::tank)
        .property("valueLabel", &LevelIndicator::valueLabel)
        .property("titleLabel", &LevelIndicator::titleLabel)
        ;
}

} // namespace gics
