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


#include "mainwindow.hpp"
#include "view.hpp"
#include "inputpanel.hpp"
#include "outputpanel.hpp"
#include <gics/button.hpp>
#include <gics/panel.hpp>
#include <gics/picture.hpp>
#include <gics/textlabel.hpp>
#include <QGraphicsLinearLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFont>


//-------------------------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget* parent, Qt::WFlags flags)
    : QMainWindow(parent, flags | Qt::FramelessWindowHint)
{
    // Setup the window
    setStyleSheet("background: black");
    setWindowTitle("GICS - Instrument framework demo");
    resize(800, 700);

    // Create the title
    gics::TextLabel* title = new gics::TextLabel("GICS demo");
    title->setHorizontalTextAlignment(gics::alignHCenter);
    title->setHorizontalSizePolicy(QSizePolicy::MinimumExpanding);
    title->setColor(Qt::white);
    QFont font = title->font();
    font.setPointSize(30);
    font.setBold(true);
    title->setFont(font);

    // Create the input panel
    m_input = new InputPanel;

    // Create the output panel
    m_output = new OutputPanel;

    // Create the logo
    gics::Picture* logo = new gics::Picture;
    logo->setFile(":/skins/logo.svg");
    logo->setId("tegesoft");
    logo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Create the "about" button
    gics::Button* about = new gics::Button("About");
    about->setButtonType(gics::Button::monostable);
    about->setMinimumSize(100, 30);
    about->setMaximumSize(100, 30);
    about->setDisplaySettings(gics::Button::showText);
    about->setHorizontalSizePolicy(QSizePolicy::Fixed);

    // Create the "quit" button
    gics::Button* quit = new gics::Button("Quit");
    quit->setButtonType(gics::Button::monostable);
    quit->setMinimumSize(100, 30);
    quit->setMaximumSize(100, 30);
    quit->setDisplaySettings(gics::Button::showText);
    quit->setHorizontalSizePolicy(QSizePolicy::Fixed);

    // Create the about title
    gics::TextLabel* aboutTitle = new gics::TextLabel("About GICS demo");
    aboutTitle->setHorizontalSizePolicy(QSizePolicy::MinimumExpanding);
    aboutTitle->setHorizontalTextAlignment(gics::alignHCenter);
    aboutTitle->setColor(Qt::white);
    font = aboutTitle->font();
    font.setPointSize(30);
    font.setBold(true);
    aboutTitle->setFont(font);

    // Create the about text
    gics::TextLabel* aboutText = new gics::TextLabel;
    aboutText->setColor(Qt::white);
    aboutText->setText("GICS demo version 0.1.\n\nCopyright 2009 Tegesoft.\n\nCompiled using Qt version " + QString(qVersion()) + ".");
    aboutText->setHorizontalTextAlignment(gics::alignHCenter);

    // Create the "close about" button
    gics::Button* closeAbout = new gics::Button("Back");
    closeAbout->setButtonType(gics::Button::monostable);
    closeAbout->setMinimumSize(100, 30);
    closeAbout->setMaximumSize(100, 30);
    closeAbout->setDisplaySettings(gics::Button::showText);
    closeAbout->setHorizontalSizePolicy(QSizePolicy::Fixed);

    // Create the buttons layout
    QGraphicsLinearLayout* buttonsLayout = new QGraphicsLinearLayout(Qt::Horizontal);
    buttonsLayout->addItem(logo);
    buttonsLayout->addStretch(1);
    buttonsLayout->addItem(about);
    buttonsLayout->addItem(quit);
    buttonsLayout->setStretchFactor(about, 0);
    buttonsLayout->setStretchFactor(quit, 0);
    buttonsLayout->setAlignment(about, Qt::AlignCenter);
    buttonsLayout->setAlignment(quit, Qt::AlignCenter);

    // Create the "close about" button layout
    QGraphicsLinearLayout* closeButtonLayout = new QGraphicsLinearLayout(Qt::Horizontal);
    closeButtonLayout->addStretch(1);
    closeButtonLayout->addItem(closeAbout);
    closeButtonLayout->addStretch(1);
    closeButtonLayout->setStretchFactor(closeAbout, 0);

    // Create the front layout
    QGraphicsLinearLayout* frontLayout = new QGraphicsLinearLayout(Qt::Vertical);
    frontLayout->setSpacing(15);
    frontLayout->addItem(title);
    frontLayout->addItem(m_input);
    frontLayout->addItem(m_output);
    frontLayout->addItem(buttonsLayout);
    frontLayout->setStretchFactor(title, 0);
    frontLayout->setStretchFactor(m_input, 0);
    frontLayout->setStretchFactor(m_output, 1);
    frontLayout->setStretchFactor(buttonsLayout, 0);

    // Create the back layout
    QGraphicsLinearLayout* backLayout = new QGraphicsLinearLayout(Qt::Vertical);
    backLayout->addItem(aboutTitle);
    backLayout->addItem(aboutText);
    backLayout->addItem(closeButtonLayout);
    backLayout->setStretchFactor(aboutTitle, 0);
    backLayout->setStretchFactor(aboutText, 1);
    backLayout->setStretchFactor(closeButtonLayout, 0);

    // Create the front panel
    gics::Panel* front = new gics::Panel;
    front->setSubClass("noframe");
    front->background().setBorderMode(gics::Picture::fixed);
    front->setCentralItem(frontLayout);

    // Create the back panel
    gics::Panel* back = new gics::Panel;
    back->setSubClass("noframe");
    back->background().setBorderMode(gics::Picture::fixed);
    back->setCentralItem(backLayout);

    // Create the view
    m_view = new View(this);
    m_view->setFrontInstrument(front);
    m_view->setBackInstrument(back);
    setCentralWidget(m_view);

    // Set a default minimum size
    setMinimumSize(600, 600);

    // Connect signals
    connect(about, SIGNAL(clicked()), m_view, SLOT(flip()));
    connect(closeAbout, SIGNAL(clicked()), m_view, SLOT(flip()));
    connect(quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_input, SIGNAL(valueChanged(double)), m_output, SLOT(setValue(double)));
}

//-------------------------------------------------------------------------------------------------
void MainWindow::mousePressEvent(QMouseEvent* event)
{
    // Reset the drag position
    if (event->buttons() & Qt::LeftButton)
        m_dragPosition = event->globalPos();
}

//-------------------------------------------------------------------------------------------------
void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    // Move the window accordingly
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint offset = event->globalPos() - m_dragPosition;
        m_dragPosition = event->globalPos();

        if (event->modifiers() & Qt::ControlModifier)
        {
            // Resize
            resize(width() + offset.x(), height() + offset.y());
            setMinimumSize(m_view->frontInstrument()->minimumSize().toSize());
        }
        else
        {
            // Move
            move(x() + offset.x(), y() + offset.y());
        }
    }
}

//-------------------------------------------------------------------------------------------------
void MainWindow::keyPressEvent(QKeyEvent* event)
{
    // Close the window if escape is pressed
    if (event->key() == Qt::Key_Escape)
        close();
}
