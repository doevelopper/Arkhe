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


#ifndef GICS_ABSTRACTSCALE_HPP
#define GICS_ABSTRACTSCALE_HPP


#include <gics/component.hpp>
#include <goost/pimplptr.hpp>
#include <QObject>
#include <QPainterPath>


namespace gics
{
/**
 * \brief Specialized component displaying a scale with ticks and labels
 */
class GICS_API AbstractScale : public QObject, public Component
{
    Q_OBJECT

public:

    class GraduationsSettings;

public:

    /**
     * \brief Default constructor
     *
     * \param parent Parent item of the component (0 by default)
     */
    AbstractScale(QGraphicsItem* parent = 0);

    /**
     * \brief Destructor
     */
    virtual ~AbstractScale();

    /**
     * \brief Set the start value
     *
     * \param startValue New start value
     * \see startValue setRange
     */
    void setStartValue(double startValue);

    /**
     * \brief Return the start value
     *
     * The default value is 0.
     *
     * \return Start value
     * \see setStartValue
     */
    double startValue() const;

    /**
     * \brief Set the end value
     *
     * \param endValue New end value
     * \see endValue setRange
     */
    void setEndValue(double endValue);

    /**
     * \brief Return the end value
     *
     * The default value is 100.
     *
     * \return End value
     * \see setEndValue
     */
    double endValue() const;

    /**
     * \brief Set the start and end values
     *
     * \param startValue New start value
     * \param endValue New end value
     * \see setStartValue setEndValue
     */
    void setRange(double startValue, double endValue);

    /**
     * \brief Choose which side of the baseline the graduations should be displayed on
     *
     * \param flipGraduations True to display the graduations on the opposite side of the baseline
     * \see flipGraduations
     */
    void setFlipGraduations(bool flipGraduations);

    /**
     * \brief Tell whether the graduations are displayed on the opposite side of the baseline or not
     *
     * The default value is false.
     *
     * \return True if the graduations are displayed on the opposite side, false if they are
     *         displayed on the default side
     * \see setFlipGraduations
     */
    bool flipGraduations() const;

    /**
     * \brief Set the baseline width
     *
     * \param width New baseline width
     * \see baseLineWidth
     */
    void setBaseLineWidth(qreal width);

    /**
     * \brief Return the thickness of the baseline
     *
     * The default value is 1.
     *
     * \return Baseline width
     * \see setBaseLineWidth
     */
    qreal baseLineWidth() const;

    /**
     * \brief Set the color of the baseline
     *
     * \param color New baseline color
     * \see baseLineColor
     */
    void setBaseLineColor(const QColor& color);

    /**
     * \brief Return the color of the baseline
     *
     * The default value is Qt::black.
     *
     * \return Baseline color
     * \see setBaseLineColor
     */
    const QColor& baseLineColor() const;

    /**
     * \brief Show or hide the baseline
     *
     * \param visible True to show the baseline, false to hide it
     * \see baseLineVisible
     */
    void setBaseLineVisible(bool visible);

    /**
     * \brief Tell whether the baseline is visible or not
     *
     * The default value is true.
     *
     * \return True if the baseline is visible, false otherwise
     * \see setBaseLineVisible
     */
    bool baseLineVisible() const;

    /**
     * \brief Return the settings of the the requested level of graduations
     *
     * This functions returns a direct reference to the settings, which
     * means that you can set their properties directly.
     * example:
     * \code
     * scale->graduations(0).setStep(20);
     * \endcode
     * The \a level parameter must be 0, 1 or 2.
     *
     * \param level Level of graduations to get
     *
     * \return Reference to the level's settings,
     *         or to a dummy instance if \a level is out of range
     */
    GraduationsSettings& graduations(unsigned int level);

    /**
     * \brief Return the settings of the the requested level of graduations
     *
     * This functions is a read-only version, you cannot modify the
     * returned graduation settings.
     * The \a level parameter must be 0, 1 or 2.
     *
     * \param level Level of graduations to get
     *
     * \return The level's settings, or to dummy instance if \a level is out of range
     */
    const GraduationsSettings& graduations(unsigned int level) const;

    /**
     * \brief Get the position of a given value on the scale
     *
     * \param value Value to convert to position
     *
     * \return Visual position of \a value on the scale, in local coordinates
     */
    QPointF pointAt(double value) const;

    /**
     * \brief Change the geometry (position and size) of the component
     *
     * \param rect New geometry
     */
    virtual void setGeometry(const QRectF& rect);

    /**
     * \brief Draw the component
     *
     * \param painter Painter to use to draw the component
     * \param option Some global drawing options
     * \param widget Parent widget (0 by default)
     */
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();

signals:

    /**
     * \brief Signal emitted whenever the scale has changed
     */
    void settingsChanged();

protected:

    /**
     * \brief Recompute the shape of the baseline to fit in a given bounding rectangle
     *
     * This function must take in account the labels and ticks so that the whole scale
     * fits exactly in the given bounding rectangle.
     *
     * \param bounds Bounding rectangle to fit in
     *
     * \return Shape describing the new baseline
     */
    virtual QPainterPath updateBaseLine(const QRectF& bounds) const = 0;

    /**
     * \brief Rebuild the scale when one of its settings have changed
     *
     * \param immediate Pass true to rebuild the scale directly; otherwise it is delayed for performances reason (false by default)
     */
    void rebuild(bool immediate = false);

private:

    friend class AbstractScalePrivate;

    goost::PimplPtr<class AbstractScalePrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

/**
 * \brief This class holds the properties of a level of graduations in a scale
 */
class GICS_API AbstractScale::GraduationsSettings
{
public:

    /**
     * \brief Default constructor
     */
    GraduationsSettings();

    /**
     * \brief Copy constructor
     *
     * \param copy Object to copy
     */
    GraduationsSettings(const GraduationsSettings& copy);

    /**
     * \brief Set the step between two consecutive ticks
     *
     * \param step New step
     * \see step
     */
    void setStep(double step);

    /**
     * \brief Get the step between two consecutive ticks
     *
     * The default value is 10.0 for level 0, 5.0 for level 1, 1.0 for level 2
     *
     * \return Step
     * \see setStep
     */
    double step() const;

    /**
     * \brief Set the visibility of the ticks
     *
     * \param visible True to show the ticks, false to hide them
     * \see ticksVisible
     */
    void setTicksVisible(bool visible);

    /**
     * \brief Tell whether the ticks are visible or not
     *
     * The default value is true
     *
     * \return True if the ticks are visible, false if they are hidden
     * \see setTicksVisible
     */
    bool ticksVisible() const;

    /**
     * \brief Set the color of the ticks
     *
     * \param color New color
     * \see ticksColor
     */
    void setTicksColor(const QColor& color);

    /**
     * \brief Get the color of the ticks
     *
     * The default value is Qt::black.
     *
     * \return Ticks color
     * \see setTicksColor
     */
    const QColor& ticksColor() const;

    /**
     * \brief Set the width (thickness) of the ticks
     *
     * \param width New width
     * \see ticksWidth
     */
    void setTicksWidth(qreal width);

    /**
     * \brief Get the width (thickness) of the ticks
     *
     * The default value is 1.
     *
     * \return Ticks width
     * \see setTicksWidth
     */
    qreal ticksWidth() const;

    /**
     * \brief Set the length of the ticks
     *
     * \param length New length
     * \see ticksLength
     */
    void setTicksLength(qreal length);

    /**
     * \brief Get the length of the ticks
     *
     * The default value is 10.0 for level 0, 5.0 for level 1, 2.5 for level 2.
     *
     * \return Ticks length
     * \see setTicksLength
     */
    qreal ticksLength() const;

    /**
     * \brief Set the visibility of the labels
     *
     * \param visible True to show the labels, false to hide them
     * \see labelsVisible
     */
    void setLabelsVisible(bool visible);

    /**
     * \brief Tell whether the labels are visible or not
     *
     * The default value is true for level 0, false for other levels.
     *
     * \return True if the labels are visible, false if they are hidden
     * \see setLabelsVisible
     */
    bool labelsVisible() const;

    /**
     * \brief Set the decimal precision of the labels
     *
     * \param precision New precision (number of decimal digits to display)
     * \see labelsPrecision
     */
    void setLabelsPrecision(unsigned int precision);

    /**
     * \brief Get the number of decimal digits displayed in the labels
     *
     * The default value is 2.
     *
     * \return Labels precision
     * \see setLabelsPrecision
     */
    unsigned int labelsPrecision() const;

    /**
     * \brief Set the font of the labels
     *
     * \param font New font
     * \see labelsFont
     */
    void setLabelsFont(const QFont& font);

    /**
     * \brief Get the font used to display the labels
     *
     * The default value is QFont().
     *
     * \return Labels font
     * \see setLabelsFont
     */
    const QFont& labelsFont() const;

    /**
     * \brief Set the color of the labels
     *
     * \param color New color
     * \see labelsColor
     */
    void setLabelsColor(const QColor& color);

    /**
     * \brief Get the color of the labels
     *
     * The default value is Qt::black.
     *
     * \return Labels color
     * \see labelsColor
     */
    const QColor& labelsColor() const;

    /**
     * \brief Compute the maximum label size of this level
     *
     * \return Maximum label size
     */
    QSizeF maxLabelSize() const;

    /**
     * \brief Assignment operator
     *
     * \param other Object to assign
     *
     * \return Reference to self
     */
    GraduationsSettings& operator=(const GraduationsSettings& other);

private:

    friend class AbstractScaleGraduationsSettingsPrivate;
    friend class AbstractScale;

    goost::PimplPtr<class AbstractScaleGraduationsSettingsPrivate> d; ///< Pointer to the private implementation
};

} // namespace gics

CAMP_AUTO_TYPE(gics::AbstractScale, &gics::AbstractScale::registerMetaClass)
CAMP_AUTO_TYPE_NONCOPYABLE(gics::AbstractScale::GraduationsSettings, &gics::AbstractScale::registerMetaClass)


#endif // GICS_ABSTRACTSCALE_HPP


/**
 * \class gics::AbstractScale
 *
 * This class is an abstract base for derived scales with shape information
 * (LinearScale, CircularScale, ...).
 *
 * Scales are dynamic, they automatically adapt their baseline, ticks and labels so that they fit into
 * the current size. Labels are also adjusted so that they never overlap.
 *
 * The visual appearance of the scale is highly customizable, you can modify the baseline (thickness, color, shape)
 * and 3 independant levels of graduations (ticks, color, font, step, precision, ...).
 *
 * Scales can also provide geometrical informations related to values, to help synchronization with other components (like needles or cursors).
 * For example, the \ref pointAt function can compute the geometrical position of a point on the baseline corresponding
 * to a given value.
 *
 * \anchor scaleProperties
 * <b>List of properties</b>
 * \li \ref startValue
 * \li \ref endValue
 * \li \ref flipGraduations
 * \li \ref baseLineWidth
 * \li \ref baseLineColor
 * \li \ref baseLineVisible
 * \li \ref graduations "graduations0"
 * \li \ref graduations "graduations1"
 * \li \ref graduations "graduations2"
 */

/**
 * \class gics::AbstractScale::GraduationsSettings
 *
 * <b>List of properties</b>
 * \li \ref step
 * \li \ref ticksVisible
 * \li \ref ticksColor
 * \li \ref ticksWidth
 * \li \ref ticksLength
 * \li \ref labelsVisible
 * \li \ref labelsPrecision
 * \li \ref labelsFont
 * \li \ref labelsColor
 */
