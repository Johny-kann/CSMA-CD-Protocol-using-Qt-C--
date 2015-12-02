#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "models.h"

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


void MainWindow::on_pushButton_clicked()
{
    CLOCK_TIME = ui->clockSpeed->text().toInt();
    NO_OF_STATIONS = ui->noOfStations->text().toInt();
    TOTAL_TIME = ui->totalTime->text().toDouble();
    this->controller->setTotal_Cycles(TOTAL_TIME);
   // qDebug()<<TOTAL_TIME;
    BUF_SIZE = ui->buffSize->text().toInt();
    FRAME_MESSAGE_LENGTH = ui->frameMessage->text().toInt();
    FRAME_DEST_LENGTH = ui->frameSource->text().toInt();
    FRAME_SOURCE_LENGTH = FRAME_DEST_LENGTH;
    FRAME_SIZE = FRAME_MESSAGE_LENGTH + FRAME_DEST_LENGTH + FRAME_SOURCE_LENGTH;

    NUMBER_OF_ATTEMPTS = ui->noOfAttempts->text().toInt();
    TIME_SLOT = ui->timeSlot->text().toInt();
    this->controller->addStations(NO_OF_STATIONS);
    this->controller->startTimer();
}
