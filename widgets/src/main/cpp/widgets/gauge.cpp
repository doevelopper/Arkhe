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


#include <gics/gauge.hpp>
#include <gics/private/gauge_p.hpp>

#include <gics/label.hpp>
#include <gics/radiallayout.hpp>
#include <gics/lcd.hpp>
#include <gics/circularscale.hpp>
#include <gics/picture.hpp>
#include <gics/state.hpp>

#include <gics/private/layoututils.hpp>

#include <QPen>

namespace gics
{

//-------------------------------------------------------------------------------------------------
Gauge::Gauge(QGraphicsItem* parent)
    : Instrument(parent)
    , d(this)
{
    setKeepAspectRatio(true);
    setState(d->enabled);
}

//-------------------------------------------------------------------------------------------------
State& Gauge::enabledState()
{
    return *d->enabled;
}

//-------------------------------------------------------------------------------------------------
State& Gauge::disabledState()
{
    return *d->disabled;
}

//-------------------------------------------------------------------------------------------------
CircularScale& Gauge::scale()
{
    return *d->scale;
}

//-------------------------------------------------------------------------------------------------
double Gauge::scaleBaseLinePosition() const
{
    return d->scale->baseLinePosition();
}

//-------------------------------------------------------------------------------------------------
void Gauge::setScaleBaseLinePosition(qreal position)
{
    d->scale->setBaseLinePosition(position);
}

//-------------------------------------------------------------------------------------------------
Picture& Gauge::needle()
{
    return *d->needle;
}

//-------------------------------------------------------------------------------------------------
Picture& Gauge::hat()
{
    return *d->hat;
}

//-------------------------------------------------------------------------------------------------
Lcd& Gauge::valueLabel()
{
    return *d->valueLabel;
}

//-------------------------------------------------------------------------------------------------
double Gauge::valueLabelPosition() const
{
    return d->layout->radialFactor(d->valueLabel);
}

//-------------------------------------------------------------------------------------------------
void Gauge::setValueLabelPosition(double position)
{
    d->layout->setRadialFactor(d->valueLabel, position);
}

//-------------------------------------------------------------------------------------------------
Label& Gauge::titleLabel()
{
    return *d->titleLabel;
}

//-------------------------------------------------------------------------------------------------
double Gauge::titleLabelPosition() const
{
    return d->layout->radialFactor(d->titleLabel);
}

//-------------------------------------------------------------------------------------------------
void Gauge::setTitleLabelPosition(double position)
{
    d->layout->setRadialFactor(d->titleLabel, position);
}

//-------------------------------------------------------------------------------------------------
double Gauge::value() const
{
    return d->valueLabel->value();
}

//-------------------------------------------------------------------------------------------------
void Gauge::setValue(double value)
{
    if (value != d->value)
        d->updateValue(value);
}

//-------------------------------------------------------------------------------------------------
void Gauge::enabledChanged(bool enabled)
{
    setState(enabled ? d->enabled : d->disabled);
}


//-------------------------------------------------------------------------------------------------
GaugePrivate::GaugePrivate(Gauge* gaugePublic)
    : q(gaugePublic)
    , layout(new RadialLayout)
    , scale(new CircularScale)
    , needle(new Picture)
    , hat(new Picture)
    , valueLabel(new Lcd)
    , titleLabel(new Label)
    , outOfRange(false)
{
    // Declare graphical states
    enabled = q->createState("enabled");
    disabled = q->createState("disabled");

    // Setup items Z-orders
    scale->setZValue(0.0);
    titleLabel->setZValue(1.0);
    valueLabel->setZValue(2.0);
    needle->setZValue(3.0);
    hat->setZValue(4.0);

    // Setup size policies
    scale->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    needle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    valueLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    titleLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

    // Add items to the layout
    layout->addItem(scale, 0.0, 0.0, QSizeF(1.0, 1.0));
    layout->addItem(valueLabel, -0.4, -90.0);
    layout->addItem(titleLabel, 0.4, -90.0);
    layout->addItem(needle, 0.0, 0.0);
    layout->addItem(hat, 0.0, 0.0);

    ScaleContainer* container = new ScaleContainer(400.0, 400.0); // Changing the container size will affect the size ratio.
    container->setLayout(layout);
    q->setCentralItem(container);

    // Synchronize the needle with scale changes
    connect(scale, SIGNAL(settingsChanged()), this, SLOT(handleScaleChanged()));

    // Synchronize picture sizes in the layout
    connect(&q->background(), SIGNAL(elementChanged()), this, SLOT(adjustLayout()));
    connect(needle, SIGNAL(elementChanged()), this, SLOT(adjustLayout()));
    connect(hat, SIGNAL(elementChanged()), this, SLOT(adjustLayout()));
    connect(&valueLabel->background(), SIGNAL(elementChanged()), this, SLOT(adjustLayout()));
}

//-------------------------------------------------------------------------------------------------
void GaugePrivate::handleScaleChanged()
{
    updateValue(value);
}

//-------------------------------------------------------------------------------------------------
void GaugePrivate::updateValue(double v)
{
    bool oldOutOfRange = outOfRange;

    double clampedValue = qBound(scale->startValue(), v, scale->endValue());
    outOfRange = clampedValue != v;

    valueLabel->setValue(clampedValue);
    updateNeedleAngle();

    value = v;

    if (outOfRange)
        emit q->outOfRangeEntered();

    if (outOfRange != oldOutOfRange)
        emit q->outOfRangeToggled(outOfRange);
}

//-------------------------------------------------------------------------------------------------
void GaugePrivate::updateNeedleAngle()
{
    // Rotate the needle
    QLineF line(scale->boundingRect().center(), scale->pointAt(valueLabel->value()));
    needle->setTransform(QTransform());
    needle->rotate(-line.angle(), needle->boundingRect().center());
}

//-------------------------------------------------------------------------------------------------
void GaugePrivate::adjustLayout()
{
    // Keep aspect ratio defined in SVG between the background and other gauge elements
    QSizeF backgroundSize(q->background().initialSize());

    if ((sender() == &q->background()) || (sender() == needle))
    {
        // Compute the needle size
        QSizeF size(needle->initialSize());
        QSizeF ratio(size.width() / backgroundSize.width()
                    , size.height() / backgroundSize.height());
        layout->setSizeConstraint(needle, ratio);
    }

    if ((sender() == &q->background()) || (sender() == hat))
    {
        // Compute the hat size
        QSizeF size(hat->initialSize());
        QSizeF ratio(size.width() / backgroundSize.width()
                    , size.height() / backgroundSize.height());
        layout->setSizeConstraint(hat, ratio);
    }

    if ((sender() == &q->background()) || (sender() == &valueLabel->background()))
    {
        // Compute the hat size
        QSizeF size(valueLabel->background().initialSize());
        QSizeF ratio(size.width() / backgroundSize.width()
                    , size.height() / backgroundSize.height());
        layout->setSizeConstraint(valueLabel, ratio);
    }
}

//-------------------------------------------------------------------------------------------------
ScaleContainer::ScaleContainer(qreal width, qreal height, QGraphicsItem* parent)
    : QGraphicsLayoutItem()
    , QGraphicsRectItem(QRectF(0.0, 0.0, width, height), parent)
    , m_layout(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setPen(Qt::NoPen);
    setBrush(Qt::NoBrush);
    setGraphicsItem(this);
}

//-------------------------------------------------------------------------------------------------
void ScaleContainer::setLayout(QGraphicsLayout* layout)
{
    // Release current layout
    if (layout == m_layout)
        return;

    delete m_layout;
    m_layout = layout;

    if (!m_layout)
        return;

    // Install and activate the layout.

    // I can not be set layout as parent due to Qt limitation.
    // See RadialLayout::invalidate() for details
    //m_layout->setParentLayoutItem(this);

    if (m_layout->graphicsItem())
        m_layout->graphicsItem()->setParentItem(this);

    gics::LayoutUtils::reparentChildItems(m_layout, this);
    m_layout->invalidate();
}

//-------------------------------------------------------------------------------------------------
QGraphicsLayout* ScaleContainer::layout() const
{
    return m_layout;
}

//-------------------------------------------------------------------------------------------------
void ScaleContainer::setGeometry(const QRectF& rect)
{
    if (m_layout)
        m_layout->setGeometry(this->rect());

    QGraphicsLayoutItem::setGeometry(rect);

    // Scale to fit new geometry
    QRectF g = geometry();
    setPos(g.topLeft());
    resetTransform();
    scale(g.width() / this->rect().width(), g.height() / this->rect().height());
}

//-------------------------------------------------------------------------------------------------
QSizeF ScaleContainer::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    QSizeF sh;
    if (m_layout)
    {
        sh = m_layout->effectiveSizeHint(which, constraint);
    }
    else
    {
        switch (which) {
            case Qt::MinimumSize:
                sh = QSizeF(0, 0);
                break;
            case Qt::PreferredSize:
                sh = QSizeF(50, 50);    //rather arbitrary
                break;
            case Qt::MaximumSize:
                sh = QSizeF(16777215, 16777215);
                break;
            default:
                qWarning("QGraphicsWidget::sizeHint(): Don't know how to handle the value of 'which'");
                break;
        }
    }
    return sh;
}

} // namespace gics

