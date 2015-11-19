#include <QDebug>
#include <string>
#include <iostream>
#include "logics.h"
#include "controller.h"
#include <QTime>
#include <time.h>
#include <random>

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

    spBuffer buffer;
    buffer.setBufferSize(10);

    logics::generateRandFrames(10,8,8,40,buffer.getList());

   /* for(int i=0;i<10;i++)
    {

    Bit *bits = new Bit[40];
    logics::generateRandBits(40,bits);



    Frame *frame = new Frame(bits,8,8,24);

    if(!buffer.listAdd(*frame))
        delete frame;


    }
*/


    for(int i=0;i<buffer.getBufferSize();i++)
     {   qDebug()<<buffer.frameAt(i).getSource()<<buffer.frameAt(i).getDestination();
   //     std::cout<<logics::bufferToMessage(buffer.frameAt(i).getMessage(),buffer.getBufferSize())<<std::endl;
    }

 //   for(int i=0 ; i<ceil((double)frame.getMessage_length()/8) ; i++)
 //       qDebug()<<bt[i];




  // delete[] bits;

}


}
