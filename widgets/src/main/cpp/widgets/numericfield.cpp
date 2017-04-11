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


#include <gics/numericfield.hpp>
#include <gics/private/numericfield_p.hpp>
#include <QGraphicsProxyWidget>
#include <QDoubleSpinBox>
#include <gics/alignment.hpp>
#include <gics/label.hpp>
#include <gics/picture.hpp>


namespace gics
{
//-------------------------------------------------------------------------------------------------
NumericField::NumericField(QGraphicsItem* parent)
    : Instrument(parent)
    , d(this)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setCentralItem(d->proxy);

    // Declare states
    d->disabled = createState("disabled");
    d->enabled = createState("enabled");
    d->editing = createState("editing");
    d->hovered = createState("hovered");
    setState(d->enabled);

    connect(d->doubleSpinBox, SIGNAL(editingFinished()), this, SLOT(handleEditingFinished()));
    d->doubleSpinBox->installEventFilter(this);

    setValue(0);
}

//-------------------------------------------------------------------------------------------------
NumericField::NumericField(double value, QGraphicsItem* parent)
    : Instrument(parent)
    , d(this)
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setCentralItem(d->proxy);

    // Declare states
    d->disabled = createState("disabled");
    d->enabled = createState("enabled");
    d->editing = createState("editing");
    d->hovered = createState("hovered");
    setState(d->enabled);

    connect(d->doubleSpinBox, SIGNAL(editingFinished()), this, SLOT(handleEditingFinished()));
    d->doubleSpinBox->installEventFilter(this);

    setValue(value);
}

//-------------------------------------------------------------------------------------------------
NumericField::~NumericField()
{
}

//-------------------------------------------------------------------------------------------------
void NumericField::setValue(double value)
{
   if (d->doubleSpinBox->textFromValue(d->validatedValue) != d->doubleSpinBox->textFromValue(value))
   {
      d->doubleSpinBox->setValue(value);
      d->validatedValue = value;
      emit valueChanged(d->validatedValue);
      updateGeometry();
   }
}

//-------------------------------------------------------------------------------------------------
double NumericField::value() const
{
    return d->doubleSpinBox->value();
}

//-------------------------------------------------------------------------------------------------
void NumericField::setPrefix(const QString& prefix)
{
    d->doubleSpinBox->setPrefix(prefix);
}

//-------------------------------------------------------------------------------------------------
QString NumericField::prefix() const
{
    return d->doubleSpinBox->prefix();
}

//-------------------------------------------------------------------------------------------------
void NumericField::setSuffix(const QString& suffix)
{
    d->doubleSpinBox->setSuffix(suffix);
}

//-------------------------------------------------------------------------------------------------
QString NumericField::suffix() const
{
    return d->doubleSpinBox->suffix();
}

//-------------------------------------------------------------------------------------------------
void NumericField::setMinimum(double minimum)
{
    if (minimum < maximum())
    {
        d->doubleSpinBox->setMinimum(minimum);
        if (d->doubleSpinBox->value() < minimum)
            setValue(minimum);
    }
}

//-------------------------------------------------------------------------------------------------
double NumericField::minimum() const
{
    return d->doubleSpinBox->minimum();
}

//-------------------------------------------------------------------------------------------------
void NumericField::setMaximum(double maximum)
{
    if (maximum > minimum())
    {
        d->doubleSpinBox->setMaximum(maximum);
        if (d->doubleSpinBox->value() > maximum)
            setValue(maximum);
    }
}

//-------------------------------------------------------------------------------------------------
 double NumericField::maximum() const
{
    return d->doubleSpinBox->maximum();
}

//-------------------------------------------------------------------------------------------------
void NumericField::setPrecision(int precision)
{
    d->doubleSpinBox->setDecimals(precision);
    updateGeometry();
}

//-------------------------------------------------------------------------------------------------
unsigned int NumericField::precision() const
{
    return d->doubleSpinBox->decimals();
}

//-------------------------------------------------------------------------------------------------
void NumericField::setSingleStep(double step)
{
    d->doubleSpinBox->setSingleStep(step);
}

//-------------------------------------------------------------------------------------------------
double NumericField::singleStep() const
{
    return d->doubleSpinBox->singleStep();
}

//-------------------------------------------------------------------------------------------------
void NumericField::setColor(const QColor& color)
{
    QPalette palette(d->doubleSpinBox->palette());
    palette.setColor(QPalette::Text,color);
    d->doubleSpinBox->setPalette(palette);
}

//-------------------------------------------------------------------------------------------------
const QColor& NumericField::color() const
{
    QPalette palette(d->doubleSpinBox->palette());
    return palette.color(QPalette::Text);
}

//-------------------------------------------------------------------------------------------------
void NumericField::setFont(const QFont& font)
{
    d->doubleSpinBox->setFont(font);
    updateGeometry();
}

//-------------------------------------------------------------------------------------------------
const QFont& NumericField::font() const
{
   return d->doubleSpinBox->font();
}
 
//-------------------------------------------------------------------------------------------------
void NumericField::setHorizontalTextAlignment(HorizontalAlignment alignment)
{
    switch (alignment)
    {
        case alignLeft:
            d->doubleSpinBox->setAlignment(verticalAlignmentEnumToFlag(d->verticalTextAlignment) | Qt::AlignLeft);
            break;

        case alignHCenter:
            d->doubleSpinBox->setAlignment(verticalAlignmentEnumToFlag(d->verticalTextAlignment) | Qt::AlignHCenter);
            break;

        case alignRight:
            d->doubleSpinBox->setAlignment(verticalAlignmentEnumToFlag(d->verticalTextAlignment) | Qt::AlignRight);
            break;
    }
    d->horizontalTextAlignment = alignment;
}

//-------------------------------------------------------------------------------------------------
HorizontalAlignment NumericField::horizontalTextAlignment() const
{
    return d->horizontalTextAlignment;
}

//-------------------------------------------------------------------------------------------------
void NumericField::setVerticalTextAlignment(VerticalAlignment alignment)
{
    switch (alignment)
    {
        case alignTop:
            d->doubleSpinBox->setAlignment(horizontalAlignmentEnumToFlag(d->horizontalTextAlignment) | Qt::AlignTop);
            break;

        case alignVCenter:
            d->doubleSpinBox->setAlignment(horizontalAlignmentEnumToFlag(d->horizontalTextAlignment) | Qt::AlignVCenter);
            break;

        case alignBottom:
            d->doubleSpinBox->setAlignment(horizontalAlignmentEnumToFlag(d->horizontalTextAlignment) | Qt::AlignBottom);
            break;
    }
    d->verticalTextAlignment = alignment;
}

//-------------------------------------------------------------------------------------------------
VerticalAlignment NumericField::verticalTextAlignment() const
{
    return d->verticalTextAlignment;
}

//-------------------------------------------------------------------------------------------------
void NumericField::setValidateOnFocusOut(bool validateOnFocusOut)
{
    d->validateOnFocusOut = validateOnFocusOut;
}

//-------------------------------------------------------------------------------------------------
bool NumericField::validateOnFocusOut() const
{
    return d->validateOnFocusOut;
}

//-------------------------------------------------------------------------------------------------
bool NumericField::keepAspectRatio() const
{
   return Instrument::keepAspectRatio();
}

//-------------------------------------------------------------------------------------------------
void NumericField::setKeepAspectRatio(bool keep)
{
    Instrument::setKeepAspectRatio(keep);
}

//-------------------------------------------------------------------------------------------------
State& NumericField::enabledState()
{
    return *d->enabled;
}

//-------------------------------------------------------------------------------------------------
State& NumericField::disabledState()
{
    return *d->disabled;
}

//-------------------------------------------------------------------------------------------------
State& NumericField::editingState()
{
    return *d->editing;
}

//-------------------------------------------------------------------------------------------------
State& NumericField::hoveredState()
{
    return *d->hovered;
}

//-------------------------------------------------------------------------------------------------
QSizeF NumericField::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    switch (which)
    {
        case Qt::PreferredSize:
        case Qt::MinimumSize:
            return d->doubleSpinBox->sizeHint();

        default:
            return Instrument::sizeHint(which, constraint);
    }
}

//-------------------------------------------------------------------------------------------------
void NumericField::enabledChanged(bool enabled)
{
    d->doubleSpinBox->setEnabled(!enabled);
    if(!enabled)
        setState(d->disabled);
    else
        setState(d->enabled);
}

//-------------------------------------------------------------------------------------------------
bool NumericField::eventFilter(QObject* obj, QEvent* event)
{
    switch (event->type())
    {
        case QEvent::FocusIn:
            if (d->editMode == false)
            {
                setState(d->editing);
                d->validatedValue = d->doubleSpinBox->value();
                emit editModeToggled(true);
                d->editMode = true;
                return false;
            }
            break;

        case QEvent::FocusOut:
            if (d->validateOnFocusOut == false)
                d->doubleSpinBox->setValue(d->validatedValue);
            setState(d->enabled);
            emit editModeToggled(false);
            d->editMode = false;
            return false;
            break;

        case QEvent::Enter:
            if (currentState() == d->enabled)
            {
                emit hoverIn();
                setState(d->hovered);
            }
            break;
            
        case QEvent::Leave:
            if (currentState() == d->hovered)
            {
                emit hoverOut();
                setState(d->enabled);
            }
            break;

        case QEvent::EnabledChange:
            QGraphicsItem::clearFocus();
        break;

        default:
            break;
    }
    return QObject::eventFilter(obj, event);
}

//-------------------------------------------------------------------------------------------------
void NumericField::handleEditingFinished()
{
    setValue(d->doubleSpinBox->value());
}


//----------------------------------- PRIVATE PART ------------------------------------------------


//-------------------------------------------------------------------------------------------------
NumericFieldPrivate::NumericFieldPrivate(NumericField* numericFieldPublic)
    : validateOnFocusOut(true)
    , editMode(false)
    , horizontalTextAlignment(alignHCenter)
    , verticalTextAlignment(alignVCenter)
{
    doubleSpinBox = new QDoubleSpinBox;
    doubleSpinBox->setRange(0, 100);
    doubleSpinBox->setValue(0);
    doubleSpinBox->setDecimals(2);
    doubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
    doubleSpinBox->setFrame(false);
    doubleSpinBox->setAttribute(Qt::WA_NoSystemBackground,true);
    doubleSpinBox->setAlignment(Qt::AlignHCenter);
    doubleSpinBox->setContextMenuPolicy(Qt::NoContextMenu);
    doubleSpinBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QPalette palette(doubleSpinBox->palette());
    palette.setBrush(QPalette::Base,Qt::transparent);
    doubleSpinBox->setPalette(palette);

    proxy = new QGraphicsProxyWidget(numericFieldPublic);
    proxy->setWidget(doubleSpinBox);
}

} // namespace gics
