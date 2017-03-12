#include "mainwindow.h"
#include "ui_mainwindow.h"
Q_LOGGING_CATEGORY(mainWd, "main.wd")
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
