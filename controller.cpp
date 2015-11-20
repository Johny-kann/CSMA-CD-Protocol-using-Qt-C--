#include "controller.h"
#include "models.h"
#include <QDebug>
#include <QtCore>
#include "logics.h"

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
    QList<int> executeOrder;

    for(int i=0;i<stations.size();i++)
    {
        if(stations.at(i).getCurrent_state()==States::sending)
            executeOrder.push_back(i);
        else
            executeOrder.push_front(i);

    }

    for(int i=0;i<stations.size();i++)
      stations.operator [](executeOrder.operator [](i)).executeStation();

    this->addPinStrength();
}

void control::Controller::addStations(int num)
{
    for(int i=0;i<num;i++)
    {
    Stations *station = new Stations(i);
    station->attachChannel(&med);
    this->stations.append(*station);
    }
}

Stations &control::Controller::getStationAt(int num)
{
    return this->stations.operator [](num);
}

void control::Controller::addPinStrength()
{
    short strength = 0;
    for(int i=0 ; i<stations.size() ; i++)
        strength += logics::convertSignalStrenthToShort(stations.at(i).getPinStrength());

    this->med.setStrength(strength);
}

/*control::Controller::Controller(QObject *parent)
{

}
*/

void control::Controller::run()
{
    qDebug()<<"Inside Run";


  //  med.setStrength(1);

 //   QObject::connect(&med,SIGNAL(done()),this,SLOT(exit()));

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
