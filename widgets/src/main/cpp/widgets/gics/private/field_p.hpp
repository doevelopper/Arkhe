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


#ifndef GICS_PRIVATE_FIELD_HPP
#define GICS_PRIVATE_FIELD_HPP

class Field;
class QLineEdit;
class QGraphicsProxyWidget;

namespace gics
{

/**
 * \brief Private implementation of Field
 */
class FieldPrivate
{

public:

    /**
     * \brief Constructor
     */
    FieldPrivate(const QString& text, Field* fieldPublic);

public:

    Field* q; ///< Pointer to the public implementation

    QLineEdit* lineEdit; ///< Qt object which renders the text and enable to edit the text
    QGraphicsProxyWidget* proxy; ///< Proxy to embed the QLineEdit in a scene
    QString validatedText; ///< Last validated text if validateOnFocusOut is set to false
    bool editMode; ///<Flag true if in edit mode else otherwise
    bool validateOnFocusOut; ///< Flag which saves the current validation mode
    HorizontalAlignment horizontalAlignment; ///<Text horizontal alignment
    VerticalAlignment verticalAlignment; ///<Text vertical alignment

};

} // namespace gics

#endif // GICS_PRIVATE_FIELD_HPP
