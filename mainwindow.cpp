#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

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

bool MainWindow::attachController(control::Controller *controller)
{
    this->controller = controller;
    return true;
}

