#include "models.h"
#include <QTimer>
#include <QDebug>
#include <QApplication>

ChannelMedium::ChannelMedium()
{

}

ChannelMedium::~ChannelMedium()
{

}

void ChannelMedium::setBit(int value)
{
    this->bitValue = value;
    QTimer::singleShot(2000,this,SLOT(unsetBit()));

     qDebug()<<"set Executed "<<this->bitValue;

}

void ChannelMedium::timeOut()
{
    qDebug()<<"Timer Executed";
     emit done();
}

void ChannelMedium::unsetBit()
{
    this->bitValue = 0;
}
