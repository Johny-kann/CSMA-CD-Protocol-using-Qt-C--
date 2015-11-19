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
    mainTimer = new QTimer(this);
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(update()));

    //  qDebug()<<"Constructor";
}

control::Controller::~Controller()
{
    delete this->mainTimer;

}

bool control::Controller::startTimer()
{
 //   mainTimer->start(CLOCK_TIME);
    this->mainTimer->start(CLOCK_TIME);
    qDebug()<<"Timer started";
    return true;
}

bool control::Controller::stopTimer()
{
    mainTimer->stop();
    return true;
}

bool control::Controller::resetTimer()
{
    mainTimer->start(CLOCK_TIME);
    return true;
}

void control::Controller::executeOperations()
{
    for(int i=0;i<stations.size();i++)
        stations.operator [](i).checkChannel();
}

void control::Controller::addStations(int num)
{
    for(int i=0;i<num;i++)
    {
    Stations *station = new Stations(i);
    this->stations.append(*station);
    }
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

void control::Controller::update()
{
    //qDebug()<<"Timer done";
    this->executeOperations();
}
