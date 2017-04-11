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


#ifndef GICS_PRIVATE_GAUGE_HPP
#define GICS_PRIVATE_GAUGE_HPP

#include <QObject>
#include <QGraphicsLayoutItem>
#include <QGraphicsRectItem>

class QGraphicsLayout;

namespace gics
{
    class Gauge;
    class Lcd;
    class State;
    class RadialLayout;
    class CircularScale;
    class Picture;
    class Label;

/**
 * \brief Private implementation of Gauge
 */
class GaugePrivate : public QObject
{
    Q_OBJECT  

public:
    /**
     * \brief Constructor
     *
     * \param gaugePublic is a pointer to the associate public part.
     */
    GaugePrivate(Gauge* gaugePublic);

    /**
      * \brief Update gauge value
      * \param value New value
      */
    void updateValue(double value);

    /**
     * \brief Update the needle rotation angle
     */
    void updateNeedleAngle();

public slots:

    /**
      * \brief Handle any change in the scale
      */
    void handleScaleChanged();

    /**
     * \brief Update the size of the element in the layout
     */
    void adjustLayout();

public:
    Gauge* q; ///< Pointer to the public implementation

    // Graphical states
    State* enabled; ///< Enabled graphical state
    State* disabled; ///< Disabled graphical state

    // Graphical items
    RadialLayout* layout; ///< Radial layout used to organize items
    CircularScale* scale; ///< Scale of the gauge
    Picture* needle; ///< Needle picture
    Picture* hat; /// Hat picture
    Lcd* valueLabel; ///< Numeric label to display the current value
    Label* titleLabel; ///< Label to display scale informations

    // Value
    double value; ///< Current value (not clamped)
    bool outOfRange; ///< Out of range flag
};


/**
  * \brief Experimental implementation of a scale container
  * This container adjust its geometry by scaling instead of resizing.
  * It also supports layouts with setLayout() and layout(). Please note that this feature
  * is experimental due to the current QGraphicsLayoutItem implementation.
  * \see RadialLayout::invalidate() for details
  */
class ScaleContainer : public QGraphicsLayoutItem, public QGraphicsRectItem
{
public:

    /**
     * \brief Constructor
     *
     * \param width Original container width
     * \param height Original container height
     * \param parent Optional parent graphics item
     */
    ScaleContainer(qreal width, qreal height, QGraphicsItem* parent = 0);

    /**
      * \brief Set container layout
      */
    void setLayout(QGraphicsLayout* layout);

    /**
      * \brief Return the container layout
      */
    QGraphicsLayout* layout() const;

    /**
      * \brief Set container geometry
      * Scale to fit new geometry instead of resizing
      */
    virtual void setGeometry(const QRectF& rect);

protected:

    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const;

private:
    QGraphicsLayout* m_layout; //! Reference to the container layout
};

} // namespace gics


#endif // GICS_PRIVATE_GAUGE_HPP

