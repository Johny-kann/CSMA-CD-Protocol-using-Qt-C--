#include "controller.h"
#include "models.h"
#include <QDebug>
#include <QtCore>
#include "logics.h"
#include "status.h"

void control::Controller::test()
{
    emit finished();
}

control::Controller::Controller(QObject *parent)
{
    mainTimer = new QTimer(this);
    connect(mainTimer,SIGNAL(timeout()),this,SLOT(update()));
    this->num_collisions = 0;
    this->med.setController(this);
    this->Total_Cycles = 500;

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
    if(Total_Cycles==0)
    {
        qDebug()<<"Breaking";
        stopTimer();
        this->statusPrinter();

        return;
    }else
    {
        Total_Cycles--;
    }

    this->med.execute();

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

void control::Controller::collisionChangeMode()
{
    for(int i=0;i<stations.size();i++)
        stations.operator [](i).collisionChangeMode();

}

void control::Controller::statusPrinter()
{

    qDebug()<<"Number of collisions"<<status::collisions;
    qDebug()<<"Number of frames generated"<<status::frameGenerated;
    qDebug()<<"Number of successful transmission"<<status::frameSuccessTransmits;

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
