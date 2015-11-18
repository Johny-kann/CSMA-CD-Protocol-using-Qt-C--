#include "logics.h"
#include <QDebug>


bool logics::convertMessageToBuffer(const Message message, Buffer &buffer)
{
    int byte_length = message.size();
//    buffer.initBufferLength()
    buffer.initBufferLength(byte_length);

    qDebug()<<"Byte Length Logics.cpp"<<byte_length;

    for(int i=0;i<byte_length;i++)
    {
        buffer.getBuffer()[i]= ((message.at(i)) &0xFF);
    }

    return true;
}


std::string logics::bufferToMessage(const unsigned char *buf, int length)
{
    std::string str;
    for(int i=0;i<length;i++)
    {
        str+=((char)buf[i]);
    }

    return str;
}


unsigned char *logics::pointerShifter(unsigned char *buf, int index)
{
    unsigned char *starter;

    starter = (buf+index);

    return starter;
}


Bit *logics::convertByteToBits(Byte *bytes, int num_bytes)
{
    Bit *bits = new Bit[num_bytes*8];

    for(int i=0; i<num_bytes; i++)
    {
        for(int j=0; j<8; j++)
        {
           *(bits + 8*i + j) = (*(bytes + i)>>j &1);
        }
    }

    return bits;
}


Byte *logics::convertBitsToBytes(Bit *bits, int num_bits)
{
    int numBytes = ceil(num_bits/8);

    qDebug()<<num_bits<<numBytes;
    Byte *bytes = new Byte[numBytes];

    for(int i=0;i<numBytes;i++)
    {
        *(bytes + i) = 0x00;

        for(int j=0;j<8;j++)
        {
            *(bytes + i) |= ( *(bits + j + 8*i) << j );
        }
    }

    return bytes;
}
