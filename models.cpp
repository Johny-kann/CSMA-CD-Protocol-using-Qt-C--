#include "models.h"
#include "logics.h"
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

Buffer::Buffer()
{
    this->buffer = NULL;
}

Buffer::Buffer(int length)
{
    this->buffer = new unsigned char[length];
}

Buffer::~Buffer()
{
    if(!(this->buffer == NULL))
           delete[] this->buffer;

}

int Buffer::getBuf_length() const
{
    return buf_length;
}

void Buffer::setBuf_length(int value)
{
    buf_length = value;
}
unsigned char *Buffer::getBuffer() const
{
    return buffer;
}

unsigned char *Buffer::getBuffer()
{
    return buffer;
}

void Buffer::setBuffer(unsigned char *value)
{
    if(!(this->buffer == NULL))
           delete[] this->buffer;

    buffer = value;
}

void Buffer::setBuffer(const Message message)
{
    if(!(this->buffer == NULL))
           delete[] this->buffer;
    this->buffer = new unsigned char[sizeof(message)/8];
    logics::convertMessageToBuffer(message,*this);
}
int Buffer::getStart_pos() const
{
    return start_pos;
}

void Buffer::setStart_pos(int value)
{
    start_pos = value;
}
int Buffer::getEnd_pos() const
{
    return end_pos;
}

void Buffer::setEnd_pos(int value)
{
    end_pos = value;
}

bool Buffer::initBufferLength(int length)
{

    if(!(this->buffer == NULL))
    {
        qDebug()<<"Gonna delete Buffer";
        delete[] this->buffer;
    }
    this->buffer = new unsigned char[length];
    return true;
}

void Buffer::resetPos()
{
    this->setStart_pos(0);
    this->setEnd_pos(buf_length-1);
}



