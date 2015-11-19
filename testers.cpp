#include <QDebug>
#include <string>
#include <iostream>
#include "logics.h"
#include "controller.h"
#include <QTime>
#include <time.h>
#include <random>
#include <thread>
#include <chrono>

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

void test_run2(/*control::Controller *a*/)
{
    std::default_random_engine generator;
      std::uniform_int_distribution<int> distribution(0,9);

      int p[10]={};

      int nrolls = 1;

      //for (int i=0; i<nrolls; ++i) {
        int number = distribution(generator);
       // ++p[number];
      //}

     // for(int i=0;i<10;i++)
          qDebug()<<number;

}

void test_run3(Stations &station)
{
    spBuffer buffer;
    buffer.setBufferSize(50);

    logics::generateRandFrames(50,8,8,40,buffer.getList());

    for(int i=0;i<50;i++)
        qDebug()<<buffer.frameAt(i).getSource()<<buffer.frameAt(i).getDestination();

    station.setBuffer(buffer);

}

void test_run()
{
//    std::this_thread::sleep_for(std::chrono::nanoseconds(10));

    Stations station1(1);
    test_run3(station1);

    qDebug()<<station1.getBuffer().getBufferSize();


  // delete[] bits;

}


}
