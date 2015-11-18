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
 // QApplication a(argc, argv);
 //   MainWindow w;
  //  w.show();

//    QCoreApplication a(argc,argv);
 //   qDebug()<<"Executing";
//    ChannelMedium med;
 //  med.setBit();

//   control::Controller *controller = new control::Controller(&a);


//   QObject::connect(controller,SIGNAL(finished()),&a,SLOT(quit()));

 //  controller->run();
  //  emit controller->finished();

  //   controller->test();

 //    QTimer::singleShot(0, controller, SLOT(run()));
//   QMetaObject::invokeMethod(controller,"run",Qt::QueuedConnection);

   //  cool cool;

 //   med.setBit();
 //   testJohny::test_run();

    Buffer buffer;
 //   buffer.initBufferLength(10);
 //   buffer.initBufferLength(20);

    std::string str = "hello";
    buffer.setBuffer("Hello");
    std::cout<<logics::bufferToMessage(buffer.getBuffer(),buffer.getBuf_length());



  //  return a.exec();
    return 0;
}
