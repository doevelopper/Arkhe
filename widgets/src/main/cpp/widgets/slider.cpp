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


#include <gics/slider.hpp>
#include <gics/private/slider_p.hpp>
#include <gics/numericfield.hpp>
#include <gics/textlabel.hpp>
#include <gics/picture.hpp>
#include <gics/alignment.hpp>
#include <gics/linearscale.hpp>
#include <gics/adjustedlinearlayout.hpp>
#include <gics/cursor.hpp>
#include <QGraphicsScene>
#include <Qt>

namespace gics
{
//-------------------------------------------------------------------------------------------------
Slider::Slider(QGraphicsItem* parent)
    : Instrument(parent)
    , d(Qt::Vertical)
{
    setValue(0.);
    setMinimum(0.);
    setMaximum(100.);
    setAcceptHoverEvents(true);
    setCentralItem(d->linearLayout);

    //Declare states
    d->disabled = createState("disabled");
    d->enabled = createState("enabled");
    d->cursorHovered = createState("cursorHovered");
    d->valueFieldHovered = createState("valueFieldHovered");
    setState(d->enabled);

    connect(d->cursor, SIGNAL(cursorMoved(double)),  this, SLOT(handleValueChanged(double)));
    connect(d->cursor, SIGNAL(hoverCursorIn()),      this, SLOT(handleCursorHoverIn()));
    connect(d->cursor, SIGNAL(hoverCursorOut()),     this, SLOT(handleCursorHoverOut()));
    connect(d->valueField, SIGNAL(valueChanged(double)), this, SLOT(handleValueFieldValueChanged(double)));
    connect(d->valueField, SIGNAL(hoverIn()),  this, SLOT(handleValueFieldHoverIn()));
    connect(d->valueField, SIGNAL(hoverOut()), this, SLOT(handleValueFieldHoverOut()));
    connect(&d->cursor->cursorPicture(), SIGNAL(elementChanged()), this, SLOT(handlePictureChanged()));
    connect(&d->cursor->railBackground(), SIGNAL(elementChanged()), this, SLOT(handlePictureChanged()));
}

//-------------------------------------------------------------------------------------------------
Slider::Slider(Qt::Orientation orientation, QGraphicsItem* parent)
    : Instrument(parent)
    , d(orientation)
{
    setValue(0.);
    setMinimum(0.);
    setMaximum(100.);
    setAcceptHoverEvents(true);
    setCentralItem(d->linearLayout);

    //Declare states
    d->disabled = createState("disabled");
    d->enabled = createState("enabled");
    d->cursorHovered = createState("cursorHovered");
    d->valueFieldHovered = createState("valueFieldHovered");
    setState(d->enabled);

    connect(d->cursor, SIGNAL(valueChanged(double)), this, SLOT(handleValueChanged(double)));
    connect(d->cursor, SIGNAL(hoverCursorIn()),      this, SLOT(handleCursorHoverIn()));
    connect(d->cursor, SIGNAL(hoverCursorOut()),     this, SLOT(handleCursorHoverOut()));
    connect(d->valueField, SIGNAL(valueChanged(double)), this, SLOT(handleValueFieldValueChanged(double)));
    connect(d->valueField, SIGNAL(hoverIn()),  this, SLOT(handleValueFieldHoverIn()));
    connect(d->valueField, SIGNAL(hoverOut()), this, SLOT(handleValueFieldHoverOut()));
    connect(&d->cursor->cursorPicture(), SIGNAL(elementChanged()),  this, SLOT(handlePictureChanged()));
    connect(&d->cursor->railBackground(), SIGNAL(elementChanged()), this, SLOT(handlePictureChanged()));
}

//-------------------------------------------------------------------------------------------------
Slider::~Slider()
{
}

//-------------------------------------------------------------------------------------------------
void Slider::setValue(double value)
{
    if (value != d->value)
    {
        d->updateValue(value);
        emit valueChanged(value);
    }
}

//-------------------------------------------------------------------------------------------------
double Slider::value()
{
    return d->value;
}

//-------------------------------------------------------------------------------------------------
void Slider::setMinimum(double minimum)
{
    if (minimum != d->cursor->minimum() && minimum < maximum())
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
        d->cursor->setMinimum(minimum);
        d->valueField->setMinimum(minimum);
    }
    d->updateValue(d->value);
}

//-------------------------------------------------------------------------------------------------
double Slider::minimum() const
{
    return d->cursor->minimum();
}

//-------------------------------------------------------------------------------------------------
void Slider::setMaximum(double maximum)
{
    if (maximum != d->cursor->maximum() && maximum > minimum())
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
        d->cursor->setMaximum(maximum);
        d->valueField->setMaximum(maximum);
    }
    d->updateValue(d->value);
}

//-------------------------------------------------------------------------------------------------
double Slider::maximum() const
{
    return d->cursor->maximum();
}

//-------------------------------------------------------------------------------------------------
void Slider::setScalePositionFlipped(bool flipped)
{
    d->scalePositionFlipped = flipped;
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool Slider::scalePositionFlipped() const
{
    return d->scalePositionFlipped;
}

//-------------------------------------------------------------------------------------------------
void Slider::setValueFieldPositionFlipped(bool flipped)
{
    d->valueFieldPositionFlipped = flipped;
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool Slider::valueFieldPositionFlipped() const
{
    return d->valueFieldPositionFlipped;
}

//-------------------------------------------------------------------------------------------------
void Slider::setTitleLabelPositionFlipped(bool flipped)
{
    d->titleLabelPositionFlipped = flipped;
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool Slider::titleLabelPositionFlipped() const
{
    return d->titleLabelPositionFlipped;
}

//-------------------------------------------------------------------------------------------------
void Slider::setMainScaleVisible(bool visible)
{
    d->mainScaleVisible = visible;
    d->scale->setVisible(visible);
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool Slider::mainScaleVisible() const
{
    return d->mainScaleVisible;
}

//-------------------------------------------------------------------------------------------------
void Slider::setAdditionalScaleVisible(bool visible)
{
    d->additionalScaleVisible = visible;
    d->additionalScale->setVisible(visible);
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool Slider::additionalScaleVisible() const
{
    return d->additionalScaleVisible;
}

//-------------------------------------------------------------------------------------------------
void Slider::setTitleLabelVisible(bool visible)
{
    d->titleLabelVisible = visible;
    d->titleLabel->setVisible(visible);
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool Slider::titleLabelVisible() const
{
    return d->titleLabelVisible;
}

//-------------------------------------------------------------------------------------------------
void Slider::setValueFieldVisible(bool visible)
{
    d->valueFieldVisible = visible;
    d->valueField->setVisible(visible);
    d->updateLayouts();
    setCentralItem(d->linearLayout);
}

//-------------------------------------------------------------------------------------------------
bool Slider::valueFieldVisible() const
{
    return d->valueFieldVisible;
}

//-------------------------------------------------------------------------------------------------
void Slider::setOrientation(Qt::Orientation orientation)
{
    d->setOrientation(orientation);
}

//-------------------------------------------------------------------------------------------------
Qt::Orientation Slider::orientation() const
{
    return d->cursor->orientation();
}

//-------------------------------------------------------------------------------------------------
LinearScale& Slider::scale()
{
    return *d->scale;
}

//-------------------------------------------------------------------------------------------------
LinearScale& Slider::additionalScale()
{
    return *d->additionalScale;
}

//-------------------------------------------------------------------------------------------------
Cursor& Slider::cursor()
{
    return *d->cursor;
}

//-------------------------------------------------------------------------------------------------
TextLabel& Slider::titleLabel()
{
    return *d->titleLabel;
}

//-------------------------------------------------------------------------------------------------
NumericField& Slider::valueField()
{
    return *d->valueField;
}

//-------------------------------------------------------------------------------------------------
State& Slider::enabledState()
{
    return *d->enabled;
}

//-------------------------------------------------------------------------------------------------
State& Slider::disabledState()
{
    return *d->disabled;
}

//-------------------------------------------------------------------------------------------------
void Slider::enabledChanged(bool enabled)
{
    if (enabled)
    {
        setState(d->enabled);
        d->valueField->setEnabled(true);
        d->titleLabel->setEnabled(true);
    }
    else
    {
        setState(d->disabled);
        d->valueField->setEnabled(false);
        d->titleLabel->setEnabled(false);
    }
}

//-------------------------------------------------------------------------------------------------
void Slider::handleValueChanged(double value)
{
    d->valueField->setValue(value);
}

//-------------------------------------------------------------------------------------------------
void Slider::handleCursorHoverIn()
{
    setState(d->cursorHovered);
    emit hoverCursorIn();
}

//-------------------------------------------------------------------------------------------------
void Slider::handleCursorHoverOut()
{
    setState(d->enabled);
    emit hoverCursorOut();
}

//-------------------------------------------------------------------------------------------------
void Slider::handleValueFieldValueChanged(double value)
{
    setValue(value);
}

//-------------------------------------------------------------------------------------------------
void Slider::handleValueFieldHoverIn()
{
    setState(d->valueFieldHovered);
    emit hoverValueFieldIn();
}

//-------------------------------------------------------------------------------------------------
void Slider::handleValueFieldHoverOut()
{
    setState(d->enabled);
    emit hoverValueFieldOut();
}

//-------------------------------------------------------------------------------------------------
void Slider::handlePictureChanged()
{
    updateGeometry();
}

//---------------------------------------- PRIVATE PART -------------------------------------------

//-------------------------------------------------------------------------------------------------
SliderPrivate::SliderPrivate(Qt::Orientation orientation)
{
    value = 0.;
    mainScaleVisible = true;
    additionalScaleVisible = false;
    titleLabelVisible = true;
    valueFieldVisible = true;
    scalePositionFlipped = false;
    valueFieldPositionFlipped = true;
    titleLabelPositionFlipped = false;

    //Scale and Cursor
    scale = new LinearScale(orientation);
    scale->setZValue(1);
    additionalScale = new LinearScale(orientation);
    additionalScale->setZValue(2);
    cursor = new Cursor(orientation);
    cursor->setZValue(3);

    //Numeric Field
    valueField = new NumericField;
    valueField->setValidateOnFocusOut(false);
    valueField->setSubClass("slider");
    valueField->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    //ScaleCaption
    titleLabel = new TextLabel("unit");
    titleLabel->setSubClass("slider");
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
void SliderPrivate::setOrientation(Qt::Orientation orientation)
{
    cursor->setOrientation(orientation);
    scale->setOrientation(orientation);
    additionalScale->setOrientation(orientation);
    linearLayout->setOrientation(orientation);

    if (orientation == Qt::Horizontal)
    {
        scale->setStartValue(cursor->minimum());
        scale->setEndValue(cursor->maximum());
        additionalScale->setStartValue(cursor->minimum());
        additionalScale->setEndValue(cursor->maximum());
        scale->setFlipGraduations(scalePositionFlipped);
        additionalScale->setFlipGraduations(!scalePositionFlipped);
        adjustedLayout->setOrientation(Qt::Vertical);
        upContainerLayout->setOrientation(Qt::Vertical);
        downContainerLayout->setOrientation(Qt::Vertical);
    }
    else
    {
        scale->setStartValue(cursor->maximum());
        scale->setEndValue(cursor->minimum());
        additionalScale->setStartValue(cursor->maximum());
        additionalScale->setEndValue(cursor->minimum());
        scale->setFlipGraduations(!scalePositionFlipped);
        additionalScale->setFlipGraduations(scalePositionFlipped);
        adjustedLayout->setOrientation(Qt::Horizontal);
        upContainerLayout->setOrientation(Qt::Horizontal);
        downContainerLayout->setOrientation(Qt::Horizontal);
    }
}

//-------------------------------------------------------------------------------------------------
void SliderPrivate::updateLayouts()
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
    setOrientation(cursor->orientation());

    // Fill items in adjusted layout
    if (!scalePositionFlipped)
    {
        if (mainScaleVisible)
            adjustedLayout->addItem(scale);
        adjustedLayout->addItem(cursor);
        if (additionalScaleVisible)
            adjustedLayout->addItem(additionalScale);
    }
    else
    {
        if (additionalScaleVisible)
            adjustedLayout->addItem(additionalScale);
        adjustedLayout->addItem(cursor);
        if (mainScaleVisible)
            adjustedLayout->addItem(scale);
    }

    // Fill items in up and down layouts
    //Horizontal orientation
    if (cursor->orientation() == Qt::Horizontal)
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
        if (valueFieldVisible)
        {
            if (!valueFieldPositionFlipped)
            {
                upContainerLayout->addItem(valueField);
                upContainerLayout->addStretch();
            }
            else
            {
                downContainerLayout->addItem(valueField);
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
        if (valueFieldVisible)
        {
            if (!valueFieldPositionFlipped)
                upSubContainerLayout->addItem(valueField);
            else
                downSubContainerLayout->addItem(valueField);
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
void SliderPrivate::updateValue(double v)
{
    double clampedValue = qBound(cursor->minimum(), v, cursor->maximum());

    valueField->setValue(clampedValue);
    cursor->setValue(clampedValue);

    value = v;
}

} // namespace gics
