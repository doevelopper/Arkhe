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


#ifndef GICS_INSTRUMENT_HPP
#define GICS_INSTRUMENT_HPP


#include <gics/config.hpp>
#include <gics/alignment.hpp>
#include <gics/qt.hpp>
#include <goost/pimplptr.hpp>
#include <QGraphicsWidget>


namespace gics
{
class State;
class Picture;

/**
 * \brief Base class for all instruments
 */
class GICS_API Instrument : public QGraphicsWidget
{
    Q_OBJECT 

public:

    /**
     * \brief Destructor
     */
    ~Instrument();

    /**
     * \brief Set the name of the instrument
     *
     * This name identifies the instrument in skins and scripts,
     * and thus should be unique. However it is optional. \n
     * The default value is an empty string.
     *
     * \param name New Name
     * \see name
     */
    void setName(const QString& name);

    /**
     * \brief Return the name of the instrument
     *
     * \return Name of the instrument
     * \see setName
     */
    const QString& name() const;

    /**
     * \brief Set the subclass of the instrument
     *
     * \param subClass New sub-class
     * \see subClass
     */
    void setSubClass(const QString& subClass);

    /**
     * \brief Return the subclass of the instrument
     *
     * The sub-class identifies the type of instrument within the skin.
     * It allows to define different types (skins) of the same instrument,
     * e.g. "power" button, "play" button, "emergency stop" button, etc. \n
     * The default value is an empty string.
     *
     * \return Subclass of the instrument
     * \see setSubClass
     */
    const QString& subClass() const;

    /**
     * \brief Return the background picture of the instrument
     *
     * \return Read-write reference to the background picture
     * \see foreground
     */
    Picture& background();

    /**
     * \brief Return the foreground picture of the instrument
     *
     * \return Read-write reference to the foreground picture
     * \see foreground
     */
    Picture& foreground();

    /**
     * \brief Set the horizontal alignment of the instrument's components within its area
     *
     * \param alignment New horizontal alignment
     * \see horizontalAlignment
     */
    void setHorizontalAlignment(HorizontalAlignment alignment);

    /**
     * \brief Return the horizontal alignment of the instrument's components within its area
     *
     * This alignment flag is used when the derived class activates the \ref keepAspectRatio
     * property; otherwise it is ignored. \n
     * The default value is gics::alignHCenter.
     *
     * \return Current horizontal alignment mode
     * \see setHorizontalAlignment
     */
    HorizontalAlignment horizontalAlignment() const;

    /**
     * \brief Set the vertical alignment of the instrument's components within its area
     *
     * \param alignment New vertical alignment
     * \see verticalAlignment
     */
    void setVerticalAlignment(VerticalAlignment alignment);

    /**
     * \brief Return the vertical alignment of the instrument's components within its area
     *
     * This alignment flag is used when the derived class activates the \ref keepAspectRatio
     * property; otherwise it is ignored. \n
     * The default value is gics::alignVCenter.
     *
     * \return Current vertical alignment mode
     * \see setVerticalAlignment
     */
    VerticalAlignment verticalAlignment() const;

    /**
     * \brief Set the horizontal size policy of the instrument
     *
     * \param policy New size policy
     * \see horizontalSizePolicy
     */
    void setHorizontalSizePolicy(QSizePolicy::Policy policy);

    /**
     * \brief Return the current horizontal size policy
     *
     * For more informations about size policies, please refer to
     * QSizePolicy in the Qt reference documentation. \n
     * The default value is QSizePolicy::Preferred.
     *
     * \return Current horizontal size policy
     * \see setHorizontalSizePolicy
     */
    QSizePolicy::Policy horizontalSizePolicy() const;

    /**
     * \brief Set the vertical size policy of the instrument
     *
     * \param policy New vertical size policy
     * \see verticalSizePolicy
     */
    void setVerticalSizePolicy(QSizePolicy::Policy policy);

    /**
     * \brief Return the vertical current alignment
     *
     * For more informations about size policies, please refer to
     * QSizePolicy in the Qt reference documentation. \n
     * The default value is QSizePolicy::Preferred.
     *
     * \return Current vertical size policy
     * \see setVerticalSizePolicy
     */
    QSizePolicy::Policy verticalSizePolicy() const;

    /**
     * \brief Return a list of the instrument's states
     *
     * \return List containing the names of the instrument's states
     * \see state
     */
    QStringList states() const;

    /**
     * \brief Return a state of the instrument by its name
     *
     * \param name Name of the state to get
     * \return Pointer to the state, or 0 if \a name doesn't name a valid state
     * \see states
     */
    State* state(const QString& name);

    /**
     * \brief Check if a point lies within the visible area of the instrument
     *
     * \param point Point to test, in local coordinates
     * \return True if \a point is inside the instrument, false otherwise
     * \see collidesWithPath
     */
    virtual bool contains(const QPointF& point) const;

    /**
     * \brief Check if the instrument collides with a path
     *
     * \param path Path to test
     * \param mode Collision test to perform
     * \return True if the instrument collides with \a path, false otherwise
     * \see contains
     */
    virtual bool collidesWithPath(const QPainterPath& path, Qt::ItemSelectionMode mode) const;

    /**
     * \brief Register the metaclass
     */
    static void registerMetaClass();

public slots:

    /**
     * \brief Enable the instrument
     *
     * \param enabled True to enable the instrument, false to disable it (true by default)
     */
    void setEnabled(bool enabled = true);

    /**
     * \brief Disable the instrument
     *
     * \param disabled True to disable the instrument, false to enable it (true by default)
     */
    void setDisabled(bool disabled = true);

protected:

     /**
     * \brief Default constructor
     *
     * \param parent Parent item of the component (0 by default)
     */
    Instrument(QGraphicsItem* parent = 0);

    /**
     * \brief Set the central item of the instrument
     *
     * \param item New central item (can be a layout or a component)
     */
    void setCentralItem(QGraphicsLayoutItem* item);

    /**
     * \brief Return the central item of the instrument
     *
     * \return Current central item
     */
    QGraphicsLayoutItem* centralItem() const;

    /**
     * \brief Tells if the instrument keeps a constant width/height ratio
     *
     * \return True if the width/height ratio is constant
     */
    bool keepAspectRatio() const;

    /**
     * \brief Change the width/height ratio policy
     *
     * \param keep True to keep a constant ratio, or false to remove size constraints
     */
    void setKeepAspectRatio(bool keep);

     /**
     * \brief Create a new state for the instrument
     *
     * If the state already exists, this function just returns it
     *
     * \param name Name of the new state
     * \return Pointer to the new state
     */
    State* createState(const QString& name);

     /**
     * \brief Change the current state of the instrument
     *
     * This function applies all the properties overriden
     * in the new state. It does nothing if the state doesn't
     * exist or is already the current one.
     *
     * \param state Pointer to the new state
     */
    void setState(const State* state);

     /**
     * \brief Get the current state of the instrument
     *
     * \return Read-only pointer to the current state
     */
    const State* currentState() const;

    /**
     * \brief Function called when the "enabled" state of the instrument has changed
     *
     * \param enabled True if the instrument has been enabled, false otherwise
     */
    virtual void enabledChanged(bool enabled);

    /**
     * \brief Event received when the instrument is resized
     *
     * \param event Event's attributes
     */
    virtual void resizeEvent(QGraphicsSceneResizeEvent* event);

    /**
     * \brief Event received right after the instrument was constructed
     */
    virtual void polishEvent();

    /**
     * \brief Return a size hint of the instrument
     *
     * \param which Identifier of the hint
     * \param constraint Size constraint for this hint (no constraint by default)
     * \return Size hint
     */
    virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF& constraint = QSizeF()) const;

    /**
     * \brief Function called when an event is sent to the object
     *
     * We hook this function in order to catch useful events (like EnableChanged)
     * and properly notify the derived instrument.
     *
     * \param event Event sent to the object
     * \return True if the event was processed
     */
    virtual bool event(QEvent* event);

private slots:

    /**
     * \brief Slot called when the background picture has changed
     */
    void handleBackgroundChanged();

private:

    friend class State;

    goost::PimplPtr<class InstrumentPrivate> d; ///< Pointer to the private implementation

    CAMP_RTTI()
};

} // namespace gics

CAMP_AUTO_TYPE_NONCOPYABLE(gics::Instrument, &gics::Instrument::registerMetaClass)


#endif //GICS_INSTRUMENT_HPP


/**
 * \class gics::Instrument
 *
 * The Instrument class is an abstract base for all instruments. It inherits from QGraphicsWidget, so that
 * all instruments are widgets that can be put into graphics scenes.
 *
 * An instrument has a \ref background picture, a \ref foreground picture and a central item.
 * The central item is defined by the derived class, and can be either a layout, a component,
 * another instrument, or nothing. The central item is always resized so that it fits into the central
 * part of the background picture (in case it has borders). Here is an example of how to setup the central item
 * in a derived instrument:
 * \code
 * class MyInstrument : public gics::Instrument
 * {
 * public:
 *
 *     MyInstrument()
 *     {
 *         m_scale = new gics::Scale;
 *         m_tank = new gics::tank;
 * 
 *         QGraphicsLinearLayout* layout = new QGraphicsLinearLayout;
 *         layout->addItem(m_scale);
 *         layout->addItem(m_tank);
 * 
 *         setCentralItem(layout);
 *     }
 *
 * private:
 * 
 *     gics::LinearScale* m_scale;
 *     gics::Tank* m_tank;
 * };
 * \endcode
 *
 * An instrument defines a set of states, such as "enabled", "on", "pressed", etc. Here is an example of how to handle
 * states in a derived instrument:
 * \code
 * class MyInstrument : public gics::Instrument
 * {
 * public:
 *
 *     MyInstrument()
 *     {
 *         m_released = createState("released");
 *         m_pressed = createState("pressed");
 *         setState(m_released);
 *     }
 *
 *     void press()
 *     {
 *         setState(m_pressed);
 *     }
 *
 * private:
 * 
 *     gics::State* m_released;
 *     gics::State* m_pressed;
 * };
 * \endcode
 * Each state can have its own visual appearance, by overriding some properties of the instrument.
 * For more informations about this, please refer to the documentation of the skin system.
 *
 * \anchor instrumentProperties
 * <b>List of properties</b>
 * \li \ref setEnabled "enabled"
 * \li \ref name
 * \li \ref subClass
 * \li \ref background
 * \li \ref foreground
 * \li \ref verticalAlignment
 * \li \ref horizontalAlignment
 * \li \ref verticalSizePolicy
 * \li \ref horizontalSizePolicy
 */
