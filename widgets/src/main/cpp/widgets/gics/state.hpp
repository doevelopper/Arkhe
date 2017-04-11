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


#ifndef GICS_STATE_HPP
#define GICS_STATE_HPP


#include <gics/config.hpp>
#include <goost/pimplptr.hpp>
#include <boost/noncopyable.hpp>
#include <QMap>


class QString;

namespace camp
{
class Value;
}

namespace gics
{
class Instrument;

/**
 * \brief Holds the properties of an instrument's state
 *
 * This class defines all the properties to override when
 * an instrument switches to a new state, or is applied a new skin.
 *
 * \sa Instrument, SkinManager
 */
class GICS_API State : boost::noncopyable
{
public:

    /**
     * \brief Get the name of the state
     *
     * \return Name of the state
     */
    const QString& name() const;

    /**
     * \brief Get the value of a property
     *
     * If the property is not overriden in the state, camp::Value::nothing is returned.
     *
     * \param name Name of the property to get
     *
     * \return Value of the property, or camp::Value::nothing if not defined in this state
     */
    const camp::Value& property(const QString& name) const;

    /**
     * \brief Set the value of a property
     *
     * \param name Name of the property to change
     * \param value Value to assign to the property
     */
    void setProperty(const QString& name, const camp::Value& value);

    /**
     * \brief Reset a property, so that it is no longer overriden by the state
     *
     * \param name Name of the property to reset
     */
    void resetProperty(const QString& name);

    /**
     * \brief Check if the state overrides a given property
     *
     * \param name Name of the property to check
     *
     * \return True if the state defines the \a name property, false otherwise
     */
    bool hasProperty(const QString& name) const;

private:

    /**
     * \brief Create the state from its name and owner
     *
     * This constructor is only accessible from Instrument.
     *
     * \param name Name of the state within the instrument
     * \param owner Instrument owning the state
     */
    State(const QString& name, Instrument& owner);

    /**
     * \brief Apply the property to its owner instrument
     *
     * This function is only accessible from Instrument.
     */
    void apply() const;

private:

    friend class Instrument;

    goost::PimplPtr<class StatePrivate> d; ///< Pointer to the private implementation
};

} // namespace gics


#endif // GICS_STATE_HPP
