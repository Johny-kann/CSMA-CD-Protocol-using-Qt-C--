#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include "models.h"
#include "controller.h"
#include <QTimer>
#include "testers.cpp"
#include <string>
#include <iostream>
#include "logics.h"
#include "status.h"

void tester_run()
{
   std::cout<<status::collisions;

}



int main(int argc, char *argv[])
{
    tester_run();


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QCoreApplication a(argc,argv);
    control::Controller *control = new control::Controller();
    w.attachController(control);
    control->addStations(5);


    logics::generateRandFramesForAStation(3,FRAME_SOURCE_LENGTH,0,FRAME_DEST_LENGTH,5,FRAME_MESSAGE_LENGTH,control->getStationAt(0).getoutBuffer().getList());

    logics::generateRandFramesForAStation(1,FRAME_SOURCE_LENGTH,1,FRAME_DEST_LENGTH,5,FRAME_MESSAGE_LENGTH,control->getStationAt(1).getoutBuffer().getList());

     logics::generateRandFramesForAStation(3,FRAME_SOURCE_LENGTH,3,FRAME_DEST_LENGTH,5,FRAME_MESSAGE_LENGTH,control->getStationAt(3).getoutBuffer().getList());



    control->startTimer();




    return a.exec();

//   tester_run();
//    return 0;
}
