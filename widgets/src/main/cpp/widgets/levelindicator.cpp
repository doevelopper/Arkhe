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
#include <gics/private/levelindicator_p.hpp>
#include <gics/numericlabel.hpp>
#include <gics/textlabel.hpp>
#include <gics/picture.hpp>
#include <gics/alignment.hpp>
#include <gics/linearscale.hpp>
#include <gics/adjustedlinearlayout.hpp>
#include <gics/tank.hpp>
#include <gics/label.hpp>
#include <QGraphicsScene>


#include <gics/numericfield.hpp>
#include <gics/cursor.hpp>


namespace gics
{
//-------------------------------------------------------------------------------------------------
LevelIndicator::LevelIndicator(QGraphicsItem* parent)
    : Instrument(parent)
    , d(Qt::Vertical, this)
{
    setValue(0.);
    setMinimum(0.);
    setMaximum(100.);
    setCentralItem(d->linearLayout);

    // Declare states
    d->disabled = createState("disabled");
    d->enabled = createState("enabled");
    setState(d->enabled);
}

//-------------------------------------------------------------------------------------------------
LevelIndicator::LevelIndicator(Qt::Orientation orientation, QGraphicsItem* parent)
    : Instrument(parent)
    , d(orientation, this)
{
    setValue(0.);
    setMinimum(0.);
    setMaximum(100.);
    setCentralItem(d->linearLayout);

    // Declare states
    d->disabled = createState("disabled");
    d->enabled = createState("enabled");
    setState(d->enabled);
}

//-------------------------------------------------------------------------------------------------
LevelIndicator::~LevelIndicator()
{
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::setValue(double value)
{
    if (value != d->value)
        d->updateValue(value);
}

//-------------------------------------------------------------------------------------------------
double LevelIndicator::value()
{
    return d->valueLabel->value();
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::setMinimum(double minimum)
{
    if (minimum != d->tank->minimum() && minimum < maximum())
    {
        if (orientation() == Qt::Horizontal)
        {
            d->scale->setStartValue(minimum);
            d->additionalScale->setStartValue(minimum);
        }
        else
        {
            d->scale->setEndValue(minimum);
            d->additionalScale->setEndValue(minimum);
        }
        d->tank->setMinimum(minimum);
    }
    d->updateValue(d->value);
}

//-------------------------------------------------------------------------------------------------
double LevelIndicator::minimum() const
{
    return d->tank->minimum();
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::setMaximum(double maximum)
{
    if (maximum != d->tank->maximum() && maximum > minimum())
    {
        if (orientation() == Qt::Horizontal)
        {
            d->scale->setEndValue(maximum);
            d->additionalScale->setEndValue(maximum);
        }
        else
        {
            d->scale->setStartValue(maximum);
            d->additionalScale->setStartValue(maximum);
        }
        d->tank->setMaximum(maximum);
    }
    d->updateValue(d->value);
}

//-------------------------------------------------------------------------------------------------
double LevelIndicator::maximum() const
{
    return d->tank->maximum();
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::setScalePositionFlipped(bool flipped)
{
    d->scalePositionFlipped = flipped;
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool LevelIndicator::scalePositionFlipped() const
{
    return d->scalePositionFlipped;
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::setValueLabelPositionFlipped(bool flipped)
{
    d->valueLabelPositionFlipped = flipped;
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool LevelIndicator::valueLabelPositionFlipped() const
{
    return d->valueLabelPositionFlipped;
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::setTitleLabelPositionFlipped(bool flipped)
{
    d->titleLabelPositionFlipped = flipped;
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool LevelIndicator::titleLabelPositionFlipped() const
{
    return d->titleLabelPositionFlipped;
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::setMainScaleVisible(bool visible)
{
    d->mainScaleVisible = visible;
    d->scale->setVisible(visible);
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool LevelIndicator::mainScaleVisible() const
{
    return d->mainScaleVisible;
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::setAdditionalScaleVisible(bool visible)
{
    d->additionalScaleVisible = visible;
    d->additionalScale->setVisible(visible);
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool LevelIndicator::additionalScaleVisible() const
{
    return d->additionalScaleVisible;
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::setTitleLabelVisible(bool visible)
{
    d->titleLabelVisible = visible;
    d->titleLabel->setVisible(visible);
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool LevelIndicator::titleLabelVisible() const
{
    return d->titleLabelVisible;
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::setValueLabelVisible(bool visible)
{
    d->valueLabelVisible = visible;
    d->valueLabel->setVisible(visible);
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool LevelIndicator::valueLabelVisible() const
{
    return d->valueLabelVisible;
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::setOrientation(Qt::Orientation orientation)
{
    d->setOrientation(orientation);
}

//-------------------------------------------------------------------------------------------------
Qt::Orientation LevelIndicator::orientation() const
{
    return d->tank->orientation();
}

//-------------------------------------------------------------------------------------------------
LinearScale& LevelIndicator::scale()
{
    return *d->scale;
}

//-------------------------------------------------------------------------------------------------
LinearScale& LevelIndicator::additionalScale()
{
    return *d->additionalScale;
}

//-------------------------------------------------------------------------------------------------
Tank& LevelIndicator::tank()
{
    return *d->tank;
}

//-------------------------------------------------------------------------------------------------
NumericLabel& LevelIndicator::valueLabel()
{
    return *d->valueLabel;
}

//-------------------------------------------------------------------------------------------------
TextLabel& LevelIndicator::titleLabel()
{
    return *d->titleLabel;
}

//-------------------------------------------------------------------------------------------------
State& LevelIndicator::enabledState()
{
    return *d->enabled;
}

//-------------------------------------------------------------------------------------------------
State& LevelIndicator::disabledState()
{
    return *d->disabled;
}

//-------------------------------------------------------------------------------------------------
void LevelIndicator::enabledChanged(bool enabled)
{
    if (enabled)
    {
        setState(d->enabled);
        d->valueLabel->setEnabled(true);
        d->titleLabel->setEnabled(true);
    }
    else
    {
        setState(d->disabled);
        d->valueLabel->setEnabled(false);
        d->titleLabel->setEnabled(false);
    }
}

//----------------------------------- PRIVATE PART ------------------------------------------------


//-------------------------------------------------------------------------------------------------
LevelIndicatorPrivate::LevelIndicatorPrivate(Qt::Orientation orientation, LevelIndicator* levelIndicatorPublic)
    :q(levelIndicatorPublic)
{
    outOfRange = false;
    mainScaleVisible = true;
    additionalScaleVisible = false;
    titleLabelVisible = true;
    valueLabelVisible = true;
    scalePositionFlipped = false;
    valueLabelPositionFlipped = true;
    titleLabelPositionFlipped = false;

    // Scale and Tank
    scale = new LinearScale(orientation);
    additionalScale = new LinearScale(orientation);
    tank = new Tank(orientation);

    // Label
    valueLabel = new NumericLabel;
    valueLabel->setSubClass("levelIndicator");
    valueLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    // ScaleCaption
    titleLabel = new TextLabel("unit");
    titleLabel->setSubClass("levelIndicator");
    titleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    linearLayout = new QGraphicsLinearLayout;

    adjustedLayout = 0;
    upContainerLayout = 0;
    downContainerLayout = 0;
    upSubContainerLayout = 0;
    downSubContainerLayout = 0;

    updateLayouts();
}

//-------------------------------------------------------------------------------------------------
void LevelIndicatorPrivate::setOrientation(Qt::Orientation orientation)
{
    tank->setOrientation(orientation);
    scale->setOrientation(orientation);
    additionalScale->setOrientation(orientation);
    linearLayout->setOrientation(orientation);

    if (orientation == Qt::Horizontal)
    {
        scale->setStartValue(tank->minimum());
        scale->setEndValue(tank->maximum());
        additionalScale->setStartValue(tank->minimum());
        additionalScale->setEndValue(tank->maximum());
        scale->setFlipGraduations(scalePositionFlipped);
        additionalScale->setFlipGraduations(!scalePositionFlipped);
        adjustedLayout->setOrientation(Qt::Vertical);
        upContainerLayout->setOrientation(Qt::Vertical);
        downContainerLayout->setOrientation(Qt::Vertical);
    }
    else
    {
        scale->setStartValue(tank->maximum());
        scale->setEndValue(tank->minimum());
        additionalScale->setStartValue(tank->maximum());
        additionalScale->setEndValue(tank->minimum());
        scale->setFlipGraduations(!scalePositionFlipped);
        additionalScale->setFlipGraduations(scalePositionFlipped);
        adjustedLayout->setOrientation(Qt::Horizontal);
        upContainerLayout->setOrientation(Qt::Horizontal);
        downContainerLayout->setOrientation(Qt::Horizontal);
    }
}

//-------------------------------------------------------------------------------------------------
void LevelIndicatorPrivate::updateLayouts()
{
    // Clean all layouts
    delete adjustedLayout;
    delete upSubContainerLayout;
    delete downSubContainerLayout;
    delete upContainerLayout;
    delete downContainerLayout;

    adjustedLayout = 0;
    upContainerLayout = 0;
    downContainerLayout = 0;
    upSubContainerLayout = 0;
    downSubContainerLayout = 0;

    // Re-create layouts
    adjustedLayout = new AdjustedLinearLayout;

    upContainerLayout = new QGraphicsLinearLayout;
    upContainerLayout->addStretch();
    upSubContainerLayout = new QGraphicsLinearLayout(Qt::Vertical);

    downContainerLayout = new QGraphicsLinearLayout;
    downContainerLayout->addStretch();
    downSubContainerLayout = new QGraphicsLinearLayout(Qt::Vertical);

    // Set layouts orientations
    setOrientation(tank->orientation());

    // Fill items in adjusted layout
    if (!scalePositionFlipped)
    {
        if (mainScaleVisible)
            adjustedLayout->addItem(scale);
        adjustedLayout->addItem(tank);
        if (additionalScaleVisible)
            adjustedLayout->addItem(additionalScale);
    }
    else
    {
        if (additionalScaleVisible)
            adjustedLayout->addItem(additionalScale);
        adjustedLayout->addItem(tank);
        if (mainScaleVisible)
            adjustedLayout->addItem(scale);
    }

    // Fill items in up and down layouts
    //Horizontal orientation
    if (tank->orientation() == Qt::Horizontal)
    {
        if (titleLabelVisible)
        {
            if (!titleLabelPositionFlipped)
            {
                upContainerLayout->addItem(titleLabel);
                upContainerLayout->addStretch();
            }
            else
            {
                downContainerLayout->addItem(titleLabel);
                downContainerLayout->addStretch();
            }
        }

        if (valueLabelVisible)
        {
            if (!valueLabelPositionFlipped)
            {
                upContainerLayout->addItem(valueLabel);
                upContainerLayout->addStretch();
            }
            else
            {
                downContainerLayout->addItem(valueLabel);
                downContainerLayout->addStretch();
            }
        }
    }
   else //Vertical orientation
    {
        if (titleLabelVisible)
        {
            if (!titleLabelPositionFlipped)
                upSubContainerLayout->addItem(titleLabel);
            else
                downSubContainerLayout->addItem(titleLabel);
        }
        if (valueLabelVisible)
        {
            if (!valueLabelPositionFlipped)
                upSubContainerLayout->addItem(valueLabel);
            else
                downSubContainerLayout->addItem(valueLabel);
        }
        if (upSubContainerLayout->count() > 0)
        {
            upContainerLayout->addItem(upSubContainerLayout);
            upContainerLayout->setStretchFactor(upSubContainerLayout, 0);
            upContainerLayout->addStretch();
        }
        if (downSubContainerLayout->count() > 0)
        {
            downContainerLayout->addItem(downSubContainerLayout);
            downContainerLayout->setStretchFactor(downSubContainerLayout, 0);
            downContainerLayout->addStretch();
        }
    }

    // Add Up and Down containers to global layout
    if (upContainerLayout->count() > 1)
    {
        linearLayout->addItem(upContainerLayout);
        linearLayout->setStretchFactor(upContainerLayout, 0);
    }
    
    linearLayout->addItem(adjustedLayout);


    if (downContainerLayout->count() > 1)
    {
        linearLayout->addItem(downContainerLayout);
        linearLayout->setStretchFactor(downContainerLayout, 0);
    }

    linearLayout->setContentsMargins(15, 15, 15, 15);
}

//-------------------------------------------------------------------------------------------------
void LevelIndicatorPrivate::updateValue(double v)
{
    bool oldOutOfRange = outOfRange;

    double clampedValue = qBound(tank->minimum(), v, tank->maximum());
    outOfRange = clampedValue != v;

    valueLabel->setValue(clampedValue);
    tank->setValue(clampedValue);

    value = v;

    if (outOfRange)
        emit q->outOfRangeEntered();

    if (outOfRange != oldOutOfRange)
        emit q->outOfRangeToggled(outOfRange);
}
} // namespace gics
