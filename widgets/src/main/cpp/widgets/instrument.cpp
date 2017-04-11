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


#include <gics/instrument.hpp>
#include <gics/private/instrument_p.hpp>
#include <gics/private/instrumentcentrallayout.hpp>
#include <gics/picture.hpp>
#include <gics/state.hpp>
#include <gics/skinmanager.hpp>
#include <QGraphicsLayoutItem>
#include <QGraphicsLinearLayout>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneResizeEvent>
#include <QGraphicsScene>


namespace gics
{
//-------------------------------------------------------------------------------------------------
Instrument::Instrument(QGraphicsItem* parent)
    : QGraphicsWidget(parent)
    , d(this)
{
    setLayout(d->centralLayout);

    // Connect signals
    connect(d->background, SIGNAL(elementChanged()), this, SLOT(handleBackgroundChanged()));
}

//-------------------------------------------------------------------------------------------------
Instrument::~Instrument()
{
}

//-------------------------------------------------------------------------------------------------
void Instrument::setName(const QString& name)
{
    if (name != d->name)
    {
        d->name = name;
    }
}

//-------------------------------------------------------------------------------------------------
const QString& Instrument::name() const
{
    return d->name;
}

//-------------------------------------------------------------------------------------------------
void Instrument::setSubClass(const QString& subClass)
{
    if (subClass != d->subClass)
    {
        d->subClass = subClass;

        // @todo Apply the new subclass
        /*SkinManager::instance().applySkin(d->skin, *this);*/
    }
}

//-------------------------------------------------------------------------------------------------
const QString& Instrument::subClass() const
{
    return d->subClass;
}

//-------------------------------------------------------------------------------------------------
Picture& Instrument::background()
{
    return *d->background;
}

//-------------------------------------------------------------------------------------------------
Picture& Instrument::foreground()
{
    return *d->foreground;
}

//-------------------------------------------------------------------------------------------------
void Instrument::setHorizontalAlignment(HorizontalAlignment alignment)
{
    if (alignment != d->horizontalAlignment)
    {
        d->horizontalAlignment = alignment;
        d->updateAlignment();
    }
}

//-------------------------------------------------------------------------------------------------
HorizontalAlignment Instrument::horizontalAlignment() const
{
    return d->horizontalAlignment;
}

//-------------------------------------------------------------------------------------------------
void Instrument::setVerticalAlignment(VerticalAlignment alignment)
{
    if (alignment != d->verticalAlignment)
    {
        d->verticalAlignment = alignment;
        d->updateAlignment();
    }
}

//-------------------------------------------------------------------------------------------------
VerticalAlignment Instrument::verticalAlignment() const
{
    return d->verticalAlignment;
}

//-------------------------------------------------------------------------------------------------
void Instrument::setHorizontalSizePolicy(QSizePolicy::Policy policy)
{
    setSizePolicy(policy, verticalSizePolicy());
}

//-------------------------------------------------------------------------------------------------
QSizePolicy::Policy Instrument::horizontalSizePolicy() const
{
    return sizePolicy().horizontalPolicy();
}

//-------------------------------------------------------------------------------------------------
void Instrument::setVerticalSizePolicy(QSizePolicy::Policy policy)
{
    setSizePolicy(horizontalSizePolicy(), policy);
}

//-------------------------------------------------------------------------------------------------
QSizePolicy::Policy Instrument::verticalSizePolicy() const
{
    return sizePolicy().verticalPolicy();
}

//-------------------------------------------------------------------------------------------------
QStringList Instrument::states() const
{
    return d->states.keys();
}

//-------------------------------------------------------------------------------------------------
State* Instrument::state(const QString& name)
{
    InstrumentPrivate::StateTable::Iterator it = d->states.find(name);
    if (it != d->states.end())
        return it.value().get();
    else
        return 0;
}

//-------------------------------------------------------------------------------------------------
bool Instrument::contains(const QPointF& point) const
{
    return d->background->contains(d->background->mapFromParent(point));
}

//-------------------------------------------------------------------------------------------------
bool Instrument::collidesWithPath(const QPainterPath& path, Qt::ItemSelectionMode mode) const
{
    return d->background->collidesWithPath(d->background->mapFromParent(path), mode);
}

//-------------------------------------------------------------------------------------------------
void Instrument::setEnabled(bool enabled)
{
    QGraphicsItem::setEnabled(enabled);
}

//-------------------------------------------------------------------------------------------------
void Instrument::setDisabled(bool disabled)
{
    QGraphicsItem::setEnabled(!disabled);
}

//-------------------------------------------------------------------------------------------------
void Instrument::setCentralItem(QGraphicsLayoutItem* item)
{
    if (item != d->centralItem)
    {
        d->updateCentralItem(item);
    }
}

//-------------------------------------------------------------------------------------------------
QGraphicsLayoutItem* Instrument::centralItem() const
{
    return d->centralItem;
}

//-------------------------------------------------------------------------------------------------
bool Instrument::keepAspectRatio() const
{
   return d->keepAspectRatio;
}

//-------------------------------------------------------------------------------------------------
void Instrument::setKeepAspectRatio(bool keep)
{
    if (keep != d->keepAspectRatio)
    {
        d->keepAspectRatio = keep;
        updateGeometry();
        d->refresh();
    }
}

//-------------------------------------------------------------------------------------------------
State* Instrument::createState(const QString& name)
{
    // Create the state if it doesn't exist
    InstrumentPrivate::StateTable::iterator it = d->states.find(name);
    if (it == d->states.end())
        it = d->states.insert(name, boost::shared_ptr<State>(new State(name, *this)));

    return it.value().get();
}

//-------------------------------------------------------------------------------------------------
void Instrument::setState(const State* state)
{
    if (state && (state != d->state))
    {
        state->apply();
        d->state = state;
    }
}

//-------------------------------------------------------------------------------------------------
const State* Instrument::currentState() const
{
    return d->state;
}

//-------------------------------------------------------------------------------------------------
void Instrument::enabledChanged(bool)
{
    // The default implementation does nothing
}

//-------------------------------------------------------------------------------------------------
void Instrument::resizeEvent(QGraphicsSceneResizeEvent*)
{
    d->refresh();
}

//-------------------------------------------------------------------------------------------------
void Instrument::polishEvent()
{
    QGraphicsWidget::polishEvent();

    // Apply the current skin
    SkinManager::instance().applySkin(SkinManager::instance().globalSkin(), *this);
}

//-------------------------------------------------------------------------------------------------
QSizeF Instrument::sizeHint(Qt::SizeHint which, const QSizeF& constraint) const
{
    QSizeF sizeHint;

    if (!d->centralItem)
    {
        // When there's no central item, use the size hint of the background picture
        sizeHint = d->background->effectiveSizeHint(which, constraint);
    }
    else
    {
        // Otherwise use the base size hint + the background borders
        // Important: don't include margins as it causes endless loops in the size hint handling
        sizeHint = d->centralItem->effectiveSizeHint(which, constraint);
        sizeHint += d->background->effectiveSizeHint(Qt::MinimumSize, constraint);

        // Adjust the size hint according to the aspect ratio flag
        if (d->keepAspectRatio && d->background->isValid())
        {
            // Use the aspect ratio of the background as the base factor
            qreal ratio = d->background->aspectRatio();

            // Adjust the size hint accordingly
            if (sizeHint.width() < sizeHint.height() * ratio)
                sizeHint.setWidth(sizeHint.height() * ratio);
            else
                sizeHint.setHeight(sizeHint.width() /  ratio);
        }
    }
 
    return sizeHint;
}

//-------------------------------------------------------------------------------------------------
bool Instrument::event(QEvent* event)
{
    switch (event->type())
    {
        // Object's "enabled" state has changed: notify the derived class
        case QEvent::EnabledChange:
            enabledChanged(isEnabled());
            break;

        // We don't care about other events
        default:
            break;
    }

    return QGraphicsWidget::event(event);
}

//-------------------------------------------------------------------------------------------------
void Instrument::handleBackgroundChanged()
{
    updateGeometry();
    d->refresh();
}


//----------------------------------- PRIVATE PART ------------------------------------------------


//-------------------------------------------------------------------------------------------------
InstrumentPrivate::InstrumentPrivate(Instrument* instrumentPublic)
    : q(instrumentPublic)
    , centralItem(0)
    , centralItemSize()
    , background(new Picture(instrumentPublic))
    , foreground(new Picture(instrumentPublic))
    , keepAspectRatio(false)
    , horizontalAlignment(alignHCenter)
    , verticalAlignment(alignVCenter)
{
    // Create the central layout
    centralLayout = new InstrumentCentralLayout(q, background, foreground);
    centralLayout->setContentsMargins(0, 0, 0, 0);
}

//-------------------------------------------------------------------------------------------------
void InstrumentPrivate::refresh()
{
    // Retrieve the instrument's current size
    QSizeF size = q->size();

    if (size.isValid())
    {
        // Compute the actual size according to the aspect ratio flag
        if (keepAspectRatio && background->isValid())
        {
            // Use the aspect ratio of the background as the base factor
            qreal ratio = background->aspectRatio();

            // Adjust the new size accordingly
            if (size.width() > size.height() * ratio)
                size.setWidth(size.height() * ratio);
            else
                size.setHeight(size.width() /  ratio);
        }

        // Resize the contents of the instrument
        centralItemSize = size;
        updateAlignment();
    }
}

//-------------------------------------------------------------------------------------------------
void InstrumentPrivate::updateCentralItem(QGraphicsLayoutItem* item)
{
    // Assign the new one
    centralItem = item;
    if (centralItem)
        centralLayout->setItem(centralItem);

    // Update the alignment
    updateAlignment();
}

//-------------------------------------------------------------------------------------------------
void InstrumentPrivate::updateAlignment()
{
    QSizeF size = q->geometry().size();
    QRectF contents(QPointF(0, 0), centralItemSize);

    if (centralItemSize.isValid())
    {
        // Compute the margins according to the sizes and alignment policies
        QSizeF margin = size - centralItemSize;
        switch (horizontalAlignment)
        {
            case alignLeft:    contents.moveLeft(0); break;
            case alignHCenter: contents.moveLeft(margin.width() / 2); break;
            case alignRight:   contents.moveLeft(margin.width()); break;
        }
        switch (verticalAlignment)
        {
            case alignTop:     contents.moveTop(0); break;
            case alignVCenter: contents.moveTop(margin.height() / 2); break;
            case alignBottom:  contents.moveTop(margin.height()); break;
        }
    }

    // Adjust the inner margins of the instrument
    q->setContentsMargins(contents.left(), contents.top(), size.width() - contents.right(), size.height() - contents.bottom());

    // Request an update
    q->update();
}

} // namespace gics
