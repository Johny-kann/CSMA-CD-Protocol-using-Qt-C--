#include "controller.h"
#include "models.h"
#include <QDebug>
#include <QtCore>

void control::Controller::test()
{
    emit finished();
}

control::Controller::Controller(QObject *parent)
{

}

/*control::Controller::Controller(QObject *parent)
{

}
*/

void control::Controller::run()
{
    qDebug()<<"Inside Run";


    med.setBit(1);

    QObject::connect(&med,SIGNAL(done()),this,SLOT(exit()));

 //   exit();
            //emit finished();
}

void control::Controller::exit()
{
    qDebug()<<"Exit executed";
     test();
}
