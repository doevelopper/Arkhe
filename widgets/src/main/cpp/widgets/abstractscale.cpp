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


#include <gics/abstractscale.hpp>
#include <gics/math.hpp>
#include <gics/private/abstractscale_p.hpp>
#include <QTransform>
#include <QPainter>
#include <QPen>
#include <QPainterPathStroker>


namespace gics
{
//-------------------------------------------------------------------------------------------------
AbstractScale::AbstractScale(QGraphicsItem* parent)
    : Component(parent)
    , d(this)
{
    // Default values
    d->startValue = 0;
    d->endValue = 100;
    d->flipGraduations = false;
    d->baseLineWidth = 1;
    d->baseLineColor = Qt::black;
    d->baseLineVisible = true;

    // Setup graduations levels (important: set owner first)
    for (int i = 0; i < AbstractScalePrivate::graduationsLevels; ++i)
        d->graduations[i].d->owner = this;
    d->graduations[0].setStep(10);
    d->graduations[1].setStep(5);
    d->graduations[2].setStep(1);
    d->graduations[0].setTicksLength(10.0);
    d->graduations[1].setTicksLength(5.0);
    d->graduations[2].setTicksLength(2.5);
    d->graduations[0].setLabelsVisible(true);
    d->graduations[1].setLabelsVisible(false);
    d->graduations[2].setLabelsVisible(false);

    rebuild();
}

//-------------------------------------------------------------------------------------------------
AbstractScale::~AbstractScale()
{
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::setStartValue(double startValue)
{
    if (startValue != d->startValue)
    {
        d->startValue = startValue;
        rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
double AbstractScale::startValue() const
{
    return d->startValue;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::setEndValue(double endValue)
{
    if (endValue != d->endValue)
    {
        d->endValue = endValue;
        rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
double AbstractScale::endValue() const
{
    return d->endValue;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::setRange(double startValue, double endValue)
{
    setStartValue(startValue);
    setEndValue(endValue);
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::setFlipGraduations(bool flipGraduations)
{
    if (flipGraduations != d->flipGraduations)
    {
        d->flipGraduations = flipGraduations;
        rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
bool AbstractScale::flipGraduations() const
{
    return d->flipGraduations;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::setBaseLineWidth(qreal width)
{
    if ((width > 0) && (width != d->baseLineWidth))
    {
        d->baseLineWidth = width;
        rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
qreal AbstractScale::baseLineWidth() const
{
    return d->baseLineWidth;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::setBaseLineColor(const QColor& color)
{
    if (color != d->baseLineColor)
    {
        d->baseLineColor = color;
        update();
    }
}

//-------------------------------------------------------------------------------------------------
const QColor& AbstractScale::baseLineColor() const
{
    return d->baseLineColor;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::setBaseLineVisible(bool visible)
{
    if (visible != d->baseLineVisible)
    {
        d->baseLineVisible = visible;
        rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
bool AbstractScale::baseLineVisible() const
{
    return d->baseLineVisible;
}

//-------------------------------------------------------------------------------------------------
AbstractScale::GraduationsSettings& AbstractScale::graduations(unsigned int level)
{
    if (level < AbstractScalePrivate::graduationsLevels)
    {
        return d->graduations[level];
    }
    else
    {
        static GraduationsSettings dummy;
        return dummy;
    }
}

//-------------------------------------------------------------------------------------------------
const AbstractScale::GraduationsSettings& AbstractScale::graduations(unsigned int level) const
{
    if (level < AbstractScalePrivate::graduationsLevels)
    {
        return d->graduations[level];
    }
    else
    {
        static const GraduationsSettings dummy;
        return dummy;
    }
}

//-------------------------------------------------------------------------------------------------
QPointF AbstractScale::pointAt(double value) const
{
    double percent = (value - d->startValue) / (d->endValue - d->startValue);
    return d->baseLine.pointAtPercent(percent);
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::setGeometry(const QRectF& rect)
{
    QRectF oldRect = geometry();
    Component::setGeometry(rect);

    // Recompute the baseline according to the new geometry
    if (geometry() != oldRect)
        rebuild(true);
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    // Rebuild the cache if needed
    if (d->needRebuild)
    {
        d->updateCache();
        updateGeometry();
    }

    // Draw the baseline
    if (d->baseLineVisible)
    {
        painter->setPen(QPen(d->baseLineColor, d->baseLineWidth, Qt::SolidLine, Qt::FlatCap));
        painter->drawPath(d->baseLine);
    }

    // Draw the ticks
    for (int i = 0; i < AbstractScalePrivate::graduationsLevels; ++i)
    {
        const GraduationsSettings& graduations = d->graduations[i];

        // Draw ticks
        painter->setPen(QPen(graduations.ticksColor(), graduations.ticksWidth(), Qt::SolidLine, Qt::FlatCap));
        foreach (const QLineF& line, d->cache[i].ticks)
            painter->drawLine(line);

        // Draw labels
        painter->setFont(graduations.labelsFont());
        painter->setPen(QPen(graduations.labelsColor()));
        foreach (const AbstractScalePrivate::LabelInfos& label, d->cache[i].labels)
            painter->drawText(label.rect, label.text);
    }
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::rebuild(bool immediate)
{
    if (immediate)
    {
        d->needRebuild = false;
        d->updateCache();
    }
    else
    {
        d->needRebuild = true;
        update();
    }
}

//-------------------------------------------------------------------------------------------------
AbstractScale::GraduationsSettings::GraduationsSettings()
{
    // Set default values
    d->owner = 0;
    d->step = 10;
    d->ticksVisible = true;
    d->ticksColor = Qt::black;
    d->ticksWidth = 1;
    d->ticksLength = 10;
    d->labelsVisible = true;
    d->labelsPrecision = 2;
    d->labelsFont = QFont();
    d->labelsColor = Qt::black;
}

//-------------------------------------------------------------------------------------------------
AbstractScale::GraduationsSettings::GraduationsSettings(const AbstractScale::GraduationsSettings& copy)
    : d(copy.d)
{
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::GraduationsSettings::setStep(double step)
{
    if ((step > 0) && (step != d->step))
    {
        d->step = step;
        if (d->owner)
            d->owner->rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
double AbstractScale::GraduationsSettings::step() const
{
    return d->step;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::GraduationsSettings::setTicksVisible(bool visible)
{
    if (visible != d->ticksVisible)
    {
        d->ticksVisible = visible;
        if (d->owner)
            d->owner->rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
bool AbstractScale::GraduationsSettings::ticksVisible() const
{
    return d->ticksVisible;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::GraduationsSettings::setTicksColor(const QColor& color)
{
    if (color != d->ticksColor)
    {
        d->ticksColor = color;
        if (d->owner)
            d->owner->update();
    }
}

//-------------------------------------------------------------------------------------------------
const QColor& AbstractScale::GraduationsSettings::ticksColor() const
{
    return d->ticksColor;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::GraduationsSettings::setTicksWidth(qreal width)
{
    if ((width >= 0) && (width != d->ticksWidth))
    {
        d->ticksWidth = width;
        if (d->owner)
            d->owner->rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
qreal AbstractScale::GraduationsSettings::ticksWidth() const
{
    return d->ticksWidth;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::GraduationsSettings::setTicksLength(qreal length)
{
    if ((length > 0) && (length != d->ticksLength))
    {
        d->ticksLength = length;
        if (d->owner)
            d->owner->rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
qreal AbstractScale::GraduationsSettings::ticksLength() const
{
    return d->ticksLength;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::GraduationsSettings::setLabelsVisible(bool visible)
{
    if (visible != d->labelsVisible)
    {
        d->labelsVisible = visible;
        if (d->owner)
            d->owner->rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
bool AbstractScale::GraduationsSettings::labelsVisible() const
{
    return d->labelsVisible;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::GraduationsSettings::setLabelsPrecision(unsigned int precision)
{
    if ((precision != d->labelsPrecision) && (precision <= 15))
    {
        d->labelsPrecision = precision;
        if (d->owner)
            d->owner->rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
unsigned int AbstractScale::GraduationsSettings::labelsPrecision() const
{
    return d->labelsPrecision;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::GraduationsSettings::setLabelsFont(const QFont& font)
{
    if (font != d->labelsFont)
    {
        d->labelsFont = font;
        if (d->owner)
            d->owner->rebuild();
    }
}

//-------------------------------------------------------------------------------------------------
const QFont& AbstractScale::GraduationsSettings::labelsFont() const
{
    return d->labelsFont;
}

//-------------------------------------------------------------------------------------------------
void AbstractScale::GraduationsSettings::setLabelsColor(const QColor& color)
{
    if (color != d->labelsColor)
    {
        d->labelsColor = color;
        if (d->owner)
            d->owner->update();
    }
}

//-------------------------------------------------------------------------------------------------
const QColor& AbstractScale::GraduationsSettings::labelsColor() const
{
    return d->labelsColor;
}

//-------------------------------------------------------------------------------------------------
QSizeF AbstractScale::GraduationsSettings::maxLabelSize() const
{
    QFontMetricsF metrics(d->labelsFont);
    QSizeF min = metrics.size(Qt::TextSingleLine, QString::number(d->owner->startValue(), 'f', d->labelsPrecision));
    QSizeF max = metrics.size(Qt::TextSingleLine, QString::number(d->owner->endValue(), 'f', d->labelsPrecision));

    return QSizeF(qMax(min.width(), max.width()),
                  qMax(min.height(), max.height()));
}

//-------------------------------------------------------------------------------------------------
AbstractScale::GraduationsSettings& AbstractScale::GraduationsSettings::operator=(const AbstractScale::GraduationsSettings& other)
{
    // Important: don't change the owner

    d->step = other.d->step;
    d->ticksVisible = other.d->ticksVisible;
    d->ticksColor = other.d->ticksColor;
    d->ticksWidth = other.d->ticksWidth;
    d->ticksLength = other.d->ticksLength;
    d->labelsVisible = other.d->labelsVisible;
    d->labelsPrecision = other.d->labelsPrecision;
    d->labelsFont = other.d->labelsFont;
    d->labelsColor = other.d->labelsColor;

    if (d->owner)
        d->owner->rebuild();

    return *this;
}


//----------------------------------- PRIVATE PART ------------------------------------------------


//-------------------------------------------------------------------------------------------------
AbstractScalePrivate::AbstractScalePrivate(AbstractScale* scalePublic)
    : q(scalePublic)
{
}

//-------------------------------------------------------------------------------------------------
void AbstractScalePrivate::updateCache()
{
    // Recompute the baseline
    baseLine = q->updateBaseLine(q->boundingRect());

    // Cache every graduations level
    for (int i = 0; i < graduationsLevels; ++i)
    {
        // Clear the previously cached data
        cache[i].ticks.clear();
        cache[i].labels.clear();
        cache[i].values.clear();

        // Compute the new ticks and labels
        const AbstractScale::GraduationsSettings& grad = graduations[i];
        if (grad.ticksVisible() || grad.labelsVisible())
        {
            QFontMetricsF metrics(grad.labelsFont());
            QSizeF labelSize = grad.maxLabelSize();

            // Precompute the step and number of ticks on this level of graduations
            double step = startValue < endValue ? grad.step() : -grad.step();
            int ticksCount = static_cast<int>((endValue - startValue) / step + 1);

            double t = startValue;
            for (int j = 0; j < ticksCount + 1; ++j)
            {
                // Discard the tick if there's another one at the same position
                bool tickExists = false;
                for (int k = 0; (k < i) && !tickExists; ++k)
                {
                    foreach (double value, cache[k].values)
                    {
                        if (qFuzzyCompare(value, t))
                        {
                            tickExists = true;
                            break;
                        }
                    }
                }

                if (!tickExists)
                {
                    // Get the point on the baseline for the current value
                    double percent = (t - startValue) / (endValue - startValue);
                    QPointF start = baseLine.pointAtPercent(percent);

                    // Get the end point of the tick (tangent to the baseline)
                    qreal angleDeg = baseLine.angleAtPercent(percent);
                    if (flipGraduations)
                        angleDeg += 180;
                    qreal angle = angleDeg / 180 * GICS_PI;
                    QPointF direction = QPointF(-sin(angle), -cos(angle));

                    if (baseLineVisible)
                        start += direction * baseLineWidth / 2;
                    QPointF end = start;

                    // Add the tick
                    if (grad.ticksVisible())
                    {
                        end += direction * grad.ticksLength();
                        QLineF tick(start, end);
                        cache[i].ticks.append(tick);
                    }

                    // Add the label
                    if (grad.labelsVisible())
                    {
                        // Compute the position, size and contents of the label
                        LabelInfos label;
                        label.text = QString::number(t, 'f', grad.labelsPrecision());
                        label.rect.moveTo(0, 0);
                        label.rect.setSize(metrics.size(Qt::TextSingleLine, label.text));
                        label.rect.moveTo(end - pointOnRect(label.rect, angleDeg + 180) + 3 * direction);

                        // Add it only if it doesn't overlap the previous label ; otherwise skip it
                        // Note: we use the max label size rather than the actual one, so that the result is more uniform
                        QRectF boundingRect(label.rect.topLeft(), labelSize);
                        bool intersects = !cache[i].labels.isEmpty() && boundingRect.intersects(cache[i].labels.back().rect);
                        if (!intersects || (j == ticksCount))
                        {
                            // Special case: we always display the last tick ; remove the previous one if they overlap
                            if ((j == ticksCount) && intersects)
                                cache[i].labels.pop_back();

                            cache[i].labels.append(label);
                        }
                    }

                    // Add the value (for later computations only)
                    cache[i].values.append(t);
                }

                // Next value
                t = (j < ticksCount - 1 ? t + step : endValue);
            }
        }
    }

    emit q->settingsChanged();
    needRebuild = false;
}

//-------------------------------------------------------------------------------------------------
QPointF AbstractScalePrivate::pointOnRect(const QRectF& rect, double angle) const
{
    QPointF center = rect.center();
    QSizeF halfSize = rect.size() / 2;

    // Make sure the angle is in range [0, 360[
    if (angle < 0)    angle += 360;
    if (angle >= 360) angle -= 360;

    if ((angle >= 0) && (angle < 45))
        return QPointF(center.x() - halfSize.width() * angle / 45, rect.top());
    else if ((angle >= 45) && (angle < 135))
        return QPointF(rect.left(), center.y() + halfSize.height() * (angle - 90) / 45);
    else if ((angle >= 135) && (angle < 225))
        return QPointF(center.x() + halfSize.width() * (angle - 180) / 45, rect.bottom());
    else if ((angle >= 225) && (angle < 315))
        return QPointF(rect.right(), center.y() - halfSize.height() * (angle - 270) / 45);
    else if ((angle >= 315) && (angle < 360))
        return QPointF(center.x() - halfSize.width() * (angle - 360) / 45, rect.top());
    else
        return rect.center();
}

} // namespace gics
