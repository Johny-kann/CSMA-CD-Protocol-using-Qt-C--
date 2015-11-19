#include <QDebug>
#include <string>
#include <iostream>
#include "logics.h"
#include "controller.h"
#include <QTime>
#include <time.h>

namespace testJohny
{

template <typename T>
bool messageToBuffer(T var, unsigned char* buf)
{
    int byte_length = sizeof(var)/8;
  //  qDebug()<<byte_length;

    std::string str = (std::string)var;

    for(int i=0;i<byte_length;i++)
    {
        buf[i]= ((str.at(i)) &0xFF);
    }

    return true;
}

std::string bufferToMessage(const unsigned char* buf, int length)
{
    std::string str;
    for(int i=0;i<length;i++)
    {
        str+=((char)buf[i]);
    }

    return str;
}

template <typename T>
int lengthFinder(T var)
{
    return sizeof(var)/8;
}

void test_run2(control::Controller *a)
{
 //   control::Controller controller(&a);
    a->startTimer();
    a->addStations(4);
   // a->getStationAt(2).setPinStrength(SignalPower::positive);

}

void test_run()
{

  //  Byte b[] = {2,3,255,123};

//   qDebug()<<sizeof(tb);
//   qDebug()<<sizeof(b);
//    Bit bits2[] = {false,false,true,false,true,false};

 //   Bit *bits = logics::convertByteToBits(b,4);

  /*  for(int i=0;i<8;i++)
        std::cout<<bits[i];



    Byte *cBytes = logics::convertBitsToBytes(bits,24);
    */

    Bit *bits = new Bit[40];
    logics::generateRandBits(40,bits);

    Frame frame(bits,8,8,24);

    qDebug()<<frame.getDestination()<<frame.getSource()<<frame.getMessage_length();

    Byte *bt=frame.getMessage();
    std::string string = logics::bufferToMessage(bt,3);

    std::cout<<string;

 //   for(int i=0 ; i<ceil((double)frame.getMessage_length()/8) ; i++)
 //       qDebug()<<bt[i];


   delete[] bt;

  // delete[] bits;

}


}
