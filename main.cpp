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

void tester_run()
{
    QList<Frame> frames;

    if(logics::generateRandFramesForAStation(1,8,10,8,10,8,frames))
        qDebug()<<"True";

    for(int i=0;i<24;i++)
        std::cout<<frames.operator [](0).getBitAt(i)<<" ";

}

int main(int argc, char *argv[])
{
  //  tester_run();


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QCoreApplication a(argc,argv);
    control::Controller *control = new control::Controller();
    w.attachController(control);
    control->addStations(5);

  /*  Byte bytes[] = {2,3,255};
    Byte byte2[] = {1,4,255};

    Bit *bits = logics::convertByteToBits(bytes,5);
    Frame *frame = new Frame(bits,FRAME_SOURCE_LENGTH,FRAME_DEST_LENGTH,FRAME_MESSAGE_LENGTH);

    Bit *bits2 = logics::convertByteToBits(byte2,5);
    Frame *frame2 = new Frame(bits2,FRAME_SOURCE_LENGTH,FRAME_DEST_LENGTH,FRAME_MESSAGE_LENGTH);
*/
    logics::generateRandFramesForAStation(1,FRAME_SOURCE_LENGTH,0,FRAME_DEST_LENGTH,5,FRAME_MESSAGE_LENGTH,control->getStationAt(0).getoutBuffer().getList());

    logics::generateRandFramesForAStation(1,FRAME_SOURCE_LENGTH,1,FRAME_DEST_LENGTH,5,FRAME_MESSAGE_LENGTH,control->getStationAt(1).getoutBuffer().getList());

 /*   if(control->getStationAt(2).addFrame(frame))
        qDebug()<<"Added";
    else
        qDebug()<<"Not Added";

    if(control->getStationAt(1).addFrame(frame2))
        qDebug()<<"Added";
    else
        qDebug()<<"Not Added";

                */

 //   control->getStationAt(2).setNext_state(States::sending);
    control->getStationAt(0).setNext_state(States::sending);
     control->getStationAt(1).setNext_state(States::sending);

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
//    return 0;
}
