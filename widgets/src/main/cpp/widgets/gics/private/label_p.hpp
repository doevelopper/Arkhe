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


#ifndef GICS_PRIVATE_LABEL_HPP
#define GICS_PRIVATE_LABEL_HPP

#include <gics/label.hpp>

namespace gics
{
class Label;

/**
 * \brief Private implementation of Label
 */
class LabelPrivate
{
public:
    /**
     * \brief Constructor
     * \param labelPublic Pointer to the associated public part
     */
    LabelPrivate(Label* labelPublic);

    /**
     * \brief Compute the elided text according to the current text, font, and elide mode
     */
    void updateElidedText();

    /**
     * \brief Update the text item position according to the current alignment
     */
    void updateAlignment();

    /**
     * \brief Update the displayed text
     */
    void updateText();

public:
    Label* q; ///< Pointer to the public part
    QString text; ///< The text that must be rendered (= whole text)
    Qt::TextElideMode elideMode; ///< Eliding mode used if the text is too long
    QString elidedText; ///< The text that will actualy be rendered
    QGraphicsSimpleTextItem* textItem; ///< The text item that will render the text
    HorizontalAlignment horizontalAlignment; ///< Text horizontal alignment
    VerticalAlignment verticalAlignment; ///< Text vertical alignment
};

} // namespace gics


#endif // GICS_PRIVATE_LABEL_HPP
