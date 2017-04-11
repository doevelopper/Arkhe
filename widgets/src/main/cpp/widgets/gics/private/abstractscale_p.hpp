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


#ifndef GICS_PRIVATE_ABSTRACTSCALE_HPP
#define GICS_PRIVATE_ABSTRACTSCALE_HPP


#include <gics/abstractscale.hpp>
#include <QPainterPath>
#include <QColor>
#include <QFont>
#include <QString>
#include <QRectF>
#include <QLineF>
#include <QVector>


namespace gics
{
/**
 * \brief Private implementation of AbstractScale
 */
class AbstractScalePrivate
{
public:

    /**
     * \brief Create the private part with a pointer to the public part
     *
     * \param scalePublic Pointer to the public part of the scale
     */
    AbstractScalePrivate(AbstractScale* scalePublic);

    /**
     * \brief Update the cached data
     */
    void updateCache();

private:

    /**
     * \brief Compute the maximum size of labels on a given level of graduations
     *
     * \param graduations Level of graduations
     *
     * \return Maximum size of the labels
     */
    QSizeF computeMaxLabelSize(const AbstractScale::GraduationsSettings& graduations) const;

    /**
     * \brief Get the anchor point on a rectangle according to a direction
     *
     * \param rect Rectangle
     * \param angle Angle in degrees
     *
     * \return Point corresponding to \a angle on the rectangle
     */
    QPointF pointOnRect(const QRectF& rect, double angle) const;

public:

    enum {graduationsLevels = 3};

    /**
     * \brief Structure holding the cached data for rendering a label
     */
    struct LabelInfos
    {
        QString text;
        QRectF rect;
    };

    /**
     * \brief Structure holding the cached data for rendering ticks and labels
     */
    struct CachedGraduations
    {
        QVector<QLineF> ticks;
        QVector<LabelInfos> labels;
        QVector<double> values;
    };

public:

    AbstractScale* q; ///< Pointer to the public part
    double startValue; ///< Start value
    double endValue; ///< End value
    bool flipGraduations; ///< Should the graduations be displayed on the opposite side?
    QPainterPath baseLine; ///< Path followed by the scale
    qreal baseLineWidth; ///< Thickness of the baseline
    QColor baseLineColor; ///< Color of the baseline
    bool baseLineVisible; ///< Visibility of the baseline
    AbstractScale::GraduationsSettings graduations[graduationsLevels]; ///< Graduations levels settings
    CachedGraduations cache[graduationsLevels]; ///< Cache containing precomputed data for rendering ticks and labels
    bool needRebuild; ///< Flag indicating whether the cache needs to be rebuilt or not
};

/**
 * \brief Private implementation of Scale::GraduationsSettings
 */
class AbstractScaleGraduationsSettingsPrivate
{
public:

    AbstractScale* owner; ///< Pointer to the owner scale
    double step; ///< Step between two consecutive ticks
    bool ticksVisible; ///< Show or hide ticks?
    QColor ticksColor; ///< Color of ticks
    qreal ticksWidth; ///< Width (thickness) of ticks
    qreal ticksLength; ///< Length of ticks
    bool labelsVisible; ///< Show or hide labels?
    unsigned int labelsPrecision; ///< Number of decimals for labels
    QFont labelsFont; ///< Font of labels
    QColor labelsColor; ///< Color of labels
};

} // namespace gics


#endif // GICS_PRIVATE_ABSTRACTSCALE_HPP
