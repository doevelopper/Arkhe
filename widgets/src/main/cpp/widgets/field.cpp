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


#include <gics/field.hpp>
#include <gics/private/field_p.hpp>
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QGraphicsSceneMouseEvent>

namespace gics
{
//-------------------------------------------------------------------------------------------------
Field::Field(QGraphicsItem* parent)
    : QObject()
    , Component(parent)
    , d("", this)
{
    connect(d->lineEdit, SIGNAL(editingFinished()), this, SLOT(handleEditingFinished()));
    connect(d->lineEdit, SIGNAL(returnPressed()), this, SLOT(handleReturnPressed()));
}


//-------------------------------------------------------------------------------------------------
Field::Field(const QString& text, QGraphicsItem* parent)
    : QObject()
    , Component(parent)
    , d(text, this)
{
    connect(d->lineEdit, SIGNAL(editingFinished()), this, SLOT(handleEditingFinished()));
    connect(d->lineEdit, SIGNAL(returnPressed()), this, SLOT(handleReturnPressed()));
}

//-------------------------------------------------------------------------------------------------
Field::~Field()
{
}

//-------------------------------------------------------------------------------------------------
void Field::setText(const QString& text)
{
    if (d->lineEdit->text() != text)
    {
        d->lineEdit->setText(text);
        d->validatedText = text;
        emit textChanged(text);
        updateGeometry();
    }
}

//-------------------------------------------------------------------------------------------------
QString Field::text() const
{
    return d->lineEdit->text();
}

//-------------------------------------------------------------------------------------------------
void Field::setFont(const QFont& font)
{
    d->lineEdit->setFont(font);
    updateGeometry();
}

//-------------------------------------------------------------------------------------------------
const QFont& Field::font() const
{
    return d->lineEdit->font();
}

//-------------------------------------------------------------------------------------------------
const QColor& Field::color() const
{
    return d->lineEdit->palette().brush(QPalette::Text).color();
}

//-------------------------------------------------------------------------------------------------
void Field::setColor(const QColor& color)
{
    QPalette palette(d->lineEdit->palette());
    palette.setBrush(QPalette::Text, color); 
    d->lineEdit->setPalette(palette);
    update();
}

//-------------------------------------------------------------------------------------------------
void Field::setHorizontalAlignment(HorizontalAlignment alignment)
{
    switch (alignment)
    {
        case alignLeft:
            d->lineEdit->setAlignment(verticalAlignmentEnumToFlag(d->verticalAlignment) | Qt::AlignLeft);
            break;

        case alignHCenter:
            d->lineEdit->setAlignment(verticalAlignmentEnumToFlag(d->verticalAlignment) | Qt::AlignHCenter);
            break;

        case alignRight:
            d->lineEdit->setAlignment(verticalAlignmentEnumToFlag(d->verticalAlignment) | Qt::AlignRight);
            break;
    }
    d->horizontalAlignment = alignment;
}

//-------------------------------------------------------------------------------------------------
HorizontalAlignment Field::horizontalAlignment() const
{
      return d->horizontalAlignment;
}

//-------------------------------------------------------------------------------------------------
void Field::setVerticalAlignment(VerticalAlignment alignment)
{
    switch (alignment)
    {
        case alignTop:
            d->lineEdit->setAlignment(horizontalAlignmentEnumToFlag(d->horizontalAlignment) | Qt::AlignTop);
            break;

        case alignVCenter:
            d->lineEdit->setAlignment(horizontalAlignmentEnumToFlag(d->horizontalAlignment) | Qt::AlignVCenter);
            break;

        case alignBottom:
            d->lineEdit->setAlignment(horizontalAlignmentEnumToFlag(d->horizontalAlignment) |  Qt::AlignBottom);
            break;
    }
    d->verticalAlignment = alignment;
}

//-------------------------------------------------------------------------------------------------
VerticalAlignment Field::verticalAlignment() const
{
    return d->verticalAlignment;
}

//-------------------------------------------------------------------------------------------------
void Field::setValidateOnFocusOut(bool validateOnFocusOut)
{
    d->validateOnFocusOut = validateOnFocusOut;
}

//-------------------------------------------------------------------------------------------------
bool Field::validateOnFocusOut() const
{
    return d->validateOnFocusOut;
}

//-------------------------------------------------------------------------------------------------
void Field::setEditable(bool editable)
{
    d->lineEdit->setEnabled(!editable);
}

//-------------------------------------------------------------------------------------------------
bool Field::editable() const
{
    return d->lineEdit->isEnabled();
}

//-------------------------------------------------------------------------------------------------
void Field::setGeometry(const QRectF& rect)
{
     Component::setGeometry(rect);
     d->proxy->setGeometry(QRectF(QPointF(0, 0), geometry().size()));
}

//-------------------------------------------------------------------------------------------------
QSizeF Field::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    QSizeF idealSize = QFontMetricsF(d->lineEdit->font()).size(Qt::TextSingleLine, d->lineEdit->text());
    if (which == Qt::PreferredSize || which == Qt::MinimumSize)
      return QSizeF(idealSize.width(), idealSize.height());
    return Component::sizeHint(which, constraint);
}

//-------------------------------------------------------------------------------------------------
bool Field::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type())
    {
        case QEvent::FocusIn:
            if (d->editMode == false)
            {
                emit editModeToggled(true);
                d->validatedText = d->lineEdit->text();
                d->editMode = true;
                return false;
            }
            break;

        //Emit the editModeToggled signals when validateOnFocusOut is true
        case QEvent::FocusOut:
            emit editModeToggled(false);
            break;

        case QEvent::Enter:
            emit hoverIn();
            break;

        case QEvent::Leave:
            emit hoverOut();
             break;

         default:
            break;
    }
     return QObject::eventFilter(obj, event);
}

//-------------------------------------------------------------------------------------------------
void Field::handleEditingFinished()
{
    if (d->validateOnFocusOut == false)
    {
        d->lineEdit->setText(d->validatedText);
    }
    else
    {
        d->editMode = false;
        if (d->lineEdit->text() != d->validatedText)
            emit textChanged(d->validatedText);
    }
}

//-------------------------------------------------------------------------------------------------
void Field::handleReturnPressed()
{
    if (d->validateOnFocusOut == false)
    {
        if (d->validatedText != d->lineEdit->text())
        {
            d->validatedText = d->lineEdit->text();
            emit textChanged(d->validatedText);
        }
    }
}


//----------------------------------------- PRIVATE PART ------------------------------------------


//-------------------------------------------------------------------------------------------------
FieldPrivate::FieldPrivate(const QString& text, Field* fieldPublic)
    : q(fieldPublic)
    , lineEdit(new QLineEdit(text))
    , validatedText(text)
    , proxy(new QGraphicsProxyWidget(q))
    , editMode(false)
    , validateOnFocusOut(true)
    , horizontalAlignment(alignLeft)
    , verticalAlignment(alignVCenter)
{
    lineEdit->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    lineEdit->setFrame(false);
    lineEdit->setReadOnly(false);
    lineEdit->setAttribute(Qt::WA_NoSystemBackground, true);
    lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    lineEdit->installEventFilter(q);

    QPalette palette(lineEdit->palette());
    palette.setBrush(QPalette::Base, Qt::transparent);
    lineEdit->setPalette(palette);

    proxy->setWidget(lineEdit);
}

}// namespace gics

