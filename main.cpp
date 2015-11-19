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

 //    QTimer::singleShot(0, controller, SLOT(run()));
//   QMetaObject::invokeMethod(controller,"run",Qt::QueuedConnection);

   //  cool cool;

 //   med.setBit();
 //   testJohny::test_run();

  testJohny::test_run2(control);


    return a.exec();
  //  return 0;
}
