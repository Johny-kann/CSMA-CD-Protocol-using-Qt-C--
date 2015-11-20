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


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QCoreApplication a(argc,argv);
    control::Controller *control = new control::Controller();
    w.attachController(control);
    control->addStations(4);

    Byte bytes[] = {0,1,255,123,89};

    Bit *bits = logics::convertByteToBits(bytes,5);
    Frame *frame = new Frame(bits,FRAME_SOURCE_LENGTH,FRAME_DEST_LENGTH,FRAME_MESSAGE_LENGTH);



    if(control->getStationAt(0).addFrame(frame))
        qDebug()<<"Added";
    else
        qDebug()<<"Not Added";
    control->getStationAt(0).setNext_state(States::sending);

    qDebug()<<control->getStationAt(0).getoutBuffer().frameAt(0).getMessage_length();
     control->startTimer();

 //    QTimer::singleShot(0, controller, SLOT(run()));
//   QMetaObject::invokeMethod(controller,"run",Qt::QueuedConnection);


 //   testJohny::test_run();

/*    Stations station1(1);
    testJohny::test_run3(station1);

    qDebug()<<station1.getBuffer().getBufferSize();
*/
//  testJohny::test_run2(control);


    return a.exec();
 //   return 0;
}
