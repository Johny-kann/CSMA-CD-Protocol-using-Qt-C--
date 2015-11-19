#include "models.h"
#include "logics.h"
#include <QTimer>
#include <QDebug>
#include <QApplication>

ChannelMedium::ChannelMedium()
{
    this->signalStrength = logics::convertSignalStrenthToShort(SignalPower::idle);
}

ChannelMedium::~ChannelMedium()
{

}

void ChannelMedium::setStrength(int value)
{
    qDebug()<<"Value coming"<<value;
    this->signalStrength = value;
 //   QTimer::singleShot(2000,this,SLOT(unsetBit()));



}

short ChannelMedium::getStrenth()
{
    return this->signalStrength;
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

Byte *Buffer::getBuffer() const
{
    return buffer;
}

Byte *Buffer::getBuffer()
{
    return buffer;
}

void Buffer::setBuffer(Byte *value)
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
    this->buffer = new Byte[length];
    this->setBuf_length(length);
    return true;
}

void Buffer::resetPos()
{
    this->setStart_pos(0);
    this->setEnd_pos(buf_length-1);
}




short Frame::getSource_length() const
{
    return source_length;
}

void Frame::setSource_length(short value)
{
    source_length = value;
}

short Frame::getDestination_length() const
{
    return destination_length;
}

void Frame::setDestination_length(short value)
{
    destination_length = value;
}

int Frame::getMessage_length() const
{
    return message_length;
}

void Frame::setMessage_length(int value)
{
    message_length = value;
}

Byte Frame::getSource()
{
    Byte *bytes = logics::convertBitsToBytes(getSourceBits(),source_length);
    return bytes[0];
}

Byte Frame::getDestination()
{
    Byte *bytes = logics::convertBitsToBytes(getDestinationBits(),destination_length);
    return bytes[0];
}

Byte *Frame::getMessage()
{
    Byte *bytes = logics::convertBitsToBytes(getMessageBits(),message_length);
    return bytes;
}
Frame::Frame(Bit *bits, short sour_len, short dest_len, short mess_len)
{
    this->bits = bits;
    this->setSource_length(sour_len);
    this->setDestination_length(dest_len);
    this->setMessage_length(mess_len);
}

Frame::~Frame()
{
    if(!(this->bits == NULL))
    {
       delete[] this->bits;
    }
}

int Frame::getTotalLength()
{
    return destination_length + message_length + source_length;
}

bool *Frame::getSourceBits()
{
    return bits+0;
}

bool *Frame::getDestinationBits()
{
    return bits + source_length;
}

bool *Frame::getMessageBits()
{
    return bits + source_length + destination_length;
}

void spBuffer::listAdd(Frame &frame)
{

    list.append(frame);
}

QList<Frame> &spBuffer::getList()
{
    return list;
}

QList<Frame> spBuffer::getList() const
{
    return list;
}

void spBuffer::setList(const QList<Frame> &value)
{
    list = value;
}



SignalPower Stations::getPinStrength() const
{
    return pinStrength;
}

void Stations::setPinStrength(const SignalPower &value)
{
    pinStrength = value;
}
Stations::Stations(int id)
{
    this->id = id;
    //  qDebug()<<"Station constructor"<<this->id;
    this->pinStrength = SignalPower::idle;
}

void Stations::executeStation()
{
    if(!checkChannel())
        qDebug()<<"Strength detected";
}

bool Stations::checkChannel()
{
  //  qDebug()<<this->id<<this->bus->getStrenth();
    if(this->bus->getStrenth()==CHANNEL_IDLE)
        return true;
    else
        return false;
}

bool Stations::attachChannel(ChannelMedium *channel)
{
    this->bus = channel;
    return true;
}
