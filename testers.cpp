#include <QDebug>
#include <string>
#include <iostream>

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



void test_run()
{
    unsigned char var = 0xAB;
    char b = 'b';
    int a = 600;
    int tt;

   std::string str;

    str = "hello";



//    b = (a >> 0) &0xFF;
//    tt = (a >> 8);
//    int test;

  //  qDebug()<<var<<sizeof(var)<<b<<sizeof(b)<<a<<sizeof(a);

  //  for(int i=0;i<7;i++)
   //     qDebug()<<((var>>i) &1);
//    qDebug()<<sizeof(str)<<str.size();

    int length = lengthFinder(str);
    unsigned char *aa = new unsigned char[length];

   // int length =
    messageToBuffer(str,aa);

    std::string message = bufferToMessage(aa,length);



       std::cout<<message;


}


}
