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


#ifndef GICS_PRIVATE_NUMERICFIELD_HPP
#define GICS_PRIVATE_NUMERICFIELD_HPP

#include <gics/alignment.hpp>

class QDoubleValidator;
class QGraphicsWidget;
class QDoubleSpinBox;
class QGraphicsProxyWidget;


namespace gics
{
class State;
class NumericField;

/**
 * \brief Private implementation of NumericField
 */
class NumericFieldPrivate 
{
public:

    NumericFieldPrivate(NumericField* numericFieldPublic);

    QDoubleSpinBox* doubleSpinBox; ///<Displays and manages the value, prefix and suffix
    QGraphicsProxyWidget* proxy; ///< Proxy which contains the QDoubleSpinBox

    double validatedValue; ///<Last validated value set manualy with Enter Key

    bool validateOnFocusOut; ///<How a new entered value is taking into account : on focus out or on Enter key pressed
    bool editMode; ///< Flag true if in edit mode else otherwise
    HorizontalAlignment horizontalTextAlignment; ///<How the text is horizontally aligned
    VerticalAlignment verticalTextAlignment; ///<How the text is vertically aligned

    State* disabled; ///< Disabled state
    State* enabled;  ///< Enabled state
    State* editing;  ///< Editing state
    State* hovered;  ///< Hovered state
};

} // namespace gics


#endif // GICS_PRIVATE_NUMERICFIELD_HPP
