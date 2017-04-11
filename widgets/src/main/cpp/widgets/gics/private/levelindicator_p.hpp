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


#ifndef GICS_PRIVATE_LEVELINDICATOR_HPP
#define GICS_PRIVATE_LEVELINDICATOR_HPP

#include <QObject>
#include <Qt>

class QGraphicsLinearLayout;

namespace gics
{
class LevelIndicator;
class Picture;
class LinearScale;
class AdjustedLinearLayout;
class Tank;
class State;
class NumericLabel;
class TextLabel;

/**
 * \brief Private implementation of LevelIndicator
 */
class LevelIndicatorPrivate : public QObject
{
    Q_OBJECT  

public:

    /**
     * \brief Constructor
     */
    LevelIndicatorPrivate(Qt::Orientation orientation, LevelIndicator* levelIndicatorPublic);

    /**
    * \brief The method is in charge of setting all Slider layouts orientations
    */
    void setOrientation(Qt::Orientation orientation);

    /**
     * \brief The method is in charge of adding the title label and the value label in the right layout
     */
    void updateLayouts();

    /**
     * \brief Update level indicator value
     * \param value New value
     */
    void updateValue(double value);

public:

    LevelIndicator* q; ///< Pointer to the public implementation

    bool outOfRange; ///< indicate if the OutOfRange signal has already been triggered
    double value; ///< Current value (not clamped)

    QGraphicsLinearLayout* linearLayout; ///< global linear layout
    QGraphicsLinearLayout* upContainerLayout; ///< layout containing the valueLabel and/or the titleLabel (included in the upSubContainerLayout for only vertical mode) and situated above the scale (vertical mode) or left to the scale (horizontal mode)
    QGraphicsLinearLayout* downContainerLayout; ///< layout containing the valueLabel and/or the titleLabel (included in the downSubContainerLayout for only vertical mode) and situated under the scale (vertical mode) or right to the scale (horizontal mode)
    QGraphicsLinearLayout* downSubContainerLayout; ///< layout containing the valueLabel and/or the titleLabel (only in vertical mode)
    QGraphicsLinearLayout* upSubContainerLayout; ///< layout containing the valueLabel and/or the titleLabel (only in vertical mode)

    NumericLabel* valueLabel; ///< Label to visible current value
    TextLabel* titleLabel; ///< Label to visible scale information as unit 

    LinearScale* scale; ///< Scale 
    LinearScale* additionalScale; ///< Additional scale 
    AdjustedLinearLayout* adjustedLayout; ///< Adjusted layout containing the scale(s) and the tank

    Tank* tank; ///< Tank gics component

    bool scalePositionFlipped; ///< Main scale position regarding the cursor: left (default) or right if flipped / top (default) or bottom if flipped 
    bool valueLabelPositionFlipped; ///< Value Field position regarding the scale/cursor: left (default) or right if flipped / top (default) or bottom if flipped 
    bool titleLabelPositionFlipped; ///< Title Label position regarding the scale/cursor: left (default) or right if flipped / bottom (default) or top if flipped 
    bool mainScaleVisible; ///< Indicate if the main scale has to be diplayed
    bool additionalScaleVisible; ///< Indicate if the additional scale has to be diplayed
    bool titleLabelVisible; ///< Indicate if the title label has to be diplayed
    bool valueLabelVisible; ///< Indicate if the value label has to be diplayed

    State* disabled; ///< Disabled state
    State* enabled;  ///< Enabled state
};

} // namespace gics

#endif // GICS_PRIVATE_LEVELINDICATOR_HPP
