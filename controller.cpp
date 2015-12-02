#include "controller.h"
#include "models.h"
#include <QDebug>
#include <QtCore>
#include "logics.h"
#include "status.h"
#include <time.h>
#include <QTime>
#include <random>
#include <chrono>
#include <thread>
#include <iostream>
#include <stdio.h>


long control::Controller::getTotal_Cycles() const
{
    return Total_Cycles;
}

void control::Controller::setTotal_Cycles(long value)
{
    Total_Cycles = value;
}
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
  //  this->Total_Cycles = TOTAL_TIME;

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

    if(Total_Cycles % TIME_SLOT == 0)
        this->generateFrames();

    QList<int> executeOrder;

    for(int i=0;i<stations.size();i++)
    {
        if(stations.at(i).getCurrent_state()==States::sending)
            executeOrder.push_back(i);
        else
            executeOrder.push_front(i);

    }
   for(int i=0;i<stations.size();i++)
      stations[(executeOrder[i])].executeStation();

   this->addPinStrength();
}

void control::Controller::gettingInput()
{
    using namespace std;

    int a;
    cout<<"Total Time ";
  //  scanf("%d",&a);
 //   qDebug()<<"Input got";

    cout<<"Time Slot Period ";
    cin>>TIME_SLOT;

    cout<<"Frame Source and Destination Length ";
    cin>>FRAME_SOURCE_LENGTH;
    FRAME_DEST_LENGTH = FRAME_SOURCE_LENGTH;

    cout<<"Frame message Length ";
    cin>>FRAME_MESSAGE_LENGTH;

    FRAME_SIZE = FRAME_SOURCE_LENGTH+FRAME_DEST_LENGTH+FRAME_MESSAGE_LENGTH;

    cout<<"Buffer Size ";
    cin>>BUF_SIZE;

    cout<<"Number of Attempts ";
    cin>>NUMBER_OF_ATTEMPTS;


}

void control::Controller::displayingOutput()
{
    using namespace std;

    cout<<"Number of collisions "<<status::collisions<<endl;


    cout<<"Number of successful transmission "<<status::frameSuccessTransmits<<endl;
    cout<<"Number of Packets lost "<<status::packetsLost<<endl;
    cout<<"Buffer OverFlows "<<status::bufferOverFlow<<endl;

     int successfulTransmission = 0;
    for(int i=0;i<stations.size();i++)
    {
        cout<<"Frames in "<<i<<" Buffer "<<stations[i].getoutBuffer().framesInBuffer()<<endl;
        cout<<"Frames Generated"<<i<<stations[i].getFramesGenerated()<<endl;
        cout<<"Buffer OverFlows "<<i<<stations[i].getBufferOverFlows()<<endl;

        cout<<"Retransmission ratio "<<i<<
                  (double)(stations[i].getReTransmissionOverHead())/
                (double)(stations[i].getSuccessfulTransmission())<<endl;

        successfulTransmission += stations[i].getSuccessfulTransmission();
    }


    cout<<"Successful Transmission "<<successfulTransmission<<endl;
    cout<<"Throughput "<<successfulTransmission/TIME_SLOT<<endl;

    cout<<"...........status............";


    cout<<"Simulation Time in terms of Time Slot "<<(double)TOTAL_TIME/TIME_SLOT<<endl;

    for(int i=0;i<stations.size();i++)
    {
        cout<<"Frames Generated in Station "<<i<<stations[i].getFramesGenerated()<<endl;
    }
     cout<<"Total Number of frames generated "<<status::frameGenerated<<endl;

     for(int i=0;i<stations.size();i++)
     {
         cout<<"Frames Generated per Time Slot in Station "<<i<<(double)stations[i].getFramesGenerated()/(TOTAL_TIME/TIME_SLOT)<<endl;
     }
    cout<<"Average Number of Frames over entire network "<<(double)status::frameGenerated/(TOTAL_TIME/TIME_SLOT)<<endl;
    cout<<"Total number of Buffer OverFlows "<<status::bufferOverFlow<<endl;
    cout<<"Max re-transmission count Reached "<<status::reTransmissionOverHead<<endl;

    for(int i=0;i<stations.size();i++)
    {
        cout<<"Frames Waiting in Buffer of station "<<i<<stations[i].getoutBuffer().framesInBuffer()<<endl;
    }

    cout<<"Number of Successful Transmissions "<<status::frameSuccessTransmits<<endl;
    cout<<"Throughput over entire network "<<(double)status::frameSuccessTransmits/(TOTAL_TIME/TIME_SLOT)<<endl;

    cout<<"Channel Utilization "<<(double)(status::frameSuccessTransmits*ceil((double)FRAME_SIZE/TIME_SLOT))/(TOTAL_TIME/TIME_SLOT)<<endl;

    cout<<"Channel Waste \nCollision "<<(double)status::collisions/(TOTAL_TIME/TIME_SLOT)
           <<"\nIdle "<<ceil((double)this->med.getIdle()/TIME_SLOT)/(TOTAL_TIME/TIME_SLOT)<<endl;

    cout<<"Retransmission overHead "<<(double)status::reTransmissionOverHead/status::frameSuccessTransmits<<endl;

    cout<<"Delay for Successful Transmission "<<(double)status::delayForSuccessfulFrame/status::frameSuccessTransmits
           <<"\nIn Time Slots "<<((double)status::delayForSuccessfulFrame/TIME_SLOT)/status::frameSuccessTransmits<<endl;
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

void control::Controller::generateFrames()
{
    for(int i=0;i<stations.size();i++)
    {
     int frame = logics::generateRand(0,TIME_SLOT*60,RAND_SEED_CONST);
     ONE_NANO_SEC_WAIT;

     if(frame>=0 && frame<stations.size())
     {
         if(getStationAt(frame).getoutBuffer().framesInBuffer() < getStationAt(frame).getoutBuffer().getBufferSize())
     {     logics::generateRandFramesForAStation(1,FRAME_SOURCE_LENGTH,frame,FRAME_DEST_LENGTH,stations.size()
                                            ,FRAME_MESSAGE_LENGTH,this->getStationAt(frame).getoutBuffer().getList());
         }
         else
             status::addBufferOverFlow();

         stations[(frame)].addFrameRandomly(stations.size());

    //  qDebug()<<"Frame generated for "<<frame;
     }
    }

}

Stations &control::Controller::getStationAt(int num)
{
    return this->stations[num];
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
        stations[i].collisionChangeMode();

}

void control::Controller::statusPrinter()
{
  //  QString string;

   // string+=status::collisions;
    qDebug()<<"Number of collisions"<<status::collisions;


    qDebug()<<"Number of successful transmission"<<status::frameSuccessTransmits;
    qDebug()<<"Number of Packets lost"<<status::packetsLost;
    qDebug()<<"Buffer OverFlows"<<status::bufferOverFlow;

     int successfulTransmission = 0;
    for(int i=0;i<stations.size();i++)
    {
        qDebug()<<"Frames in "<<i<<" Buffer"<<stations[i].getoutBuffer().framesInBuffer();
        qDebug()<<"Frames Generated"<<i<<stations[i].getFramesGenerated();
        qDebug()<<"Buffer OverFlows"<<i<<stations[i].getBufferOverFlows();

        qDebug()<<"Retransmission ratio"<<i<<
                  (double)(stations[i].getReTransmissionOverHead())/
                (double)(stations[i].getSuccessfulTransmission());

        successfulTransmission += stations[i].getSuccessfulTransmission();
    }


    qDebug()<<"Successful Transmission"<<successfulTransmission;
    qDebug()<<"Throughput"<<successfulTransmission/TIME_SLOT;

    qDebug()<<"...........status............";


    qDebug()<<"Simulation Time in terms of Time Slot"<<(double)TOTAL_TIME/TIME_SLOT;

    for(int i=0;i<stations.size();i++)
    {
        qDebug()<<"Frames Generated in Station"<<i<<stations[i].getFramesGenerated();
    }
     qDebug()<<"Total Number of frames generated"<<status::frameGenerated;

     for(int i=0;i<stations.size();i++)
     {
         qDebug()<<"Frames Generated per Time Slot in Station"<<i<<(double)stations[i].getFramesGenerated()/(TOTAL_TIME/TIME_SLOT);
     }
    qDebug()<<"Average Number of Frames over entire network"<<(double)status::frameGenerated/(TOTAL_TIME/TIME_SLOT);
    qDebug()<<"Total number of Buffer OverFlows"<<status::bufferOverFlow;
    qDebug()<<"Max re-transmission count Reached"<<status::reTransmissionOverHead;

    for(int i=0;i<stations.size();i++)
    {
        qDebug()<<"Frames Waiting in Buffer of station"<<i<<stations[i].getoutBuffer().framesInBuffer();
    }

    qDebug()<<"Number of Successful Transmissions"<<status::frameSuccessTransmits;
    qDebug()<<"Throughput over entire network"<<(double)status::frameSuccessTransmits/(TOTAL_TIME/TIME_SLOT);

    qDebug()<<"Channel Utilization"<<(double)(status::frameSuccessTransmits*ceil((double)FRAME_SIZE/TIME_SLOT))/(TOTAL_TIME/TIME_SLOT);

    qDebug()<<"Channel Waste Collision"<<(double)status::collisions/(TOTAL_TIME/TIME_SLOT)
           <<"Idle"<<ceil((double)this->med.getIdle()/TIME_SLOT)/(TOTAL_TIME/TIME_SLOT);

    qDebug()<<"Retransmission overHead"<<(double)status::reTransmissionOverHead/status::frameSuccessTransmits;

    qDebug()<<"Delay for Successful Transmission"<<(double)status::delayForSuccessfulFrame/status::frameSuccessTransmits
           <<"In Time Slots"<<((double)status::delayForSuccessfulFrame/TIME_SLOT)/status::frameSuccessTransmits;

    displayingOutput();

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
