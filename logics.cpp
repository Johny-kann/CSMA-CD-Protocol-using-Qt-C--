#include "logics.h"
#include <QDebug>
#include <time.h>
#include <QTime>

bool logics::convertMessageToBuffer(const Message message, Buffer &buffer)
{
    int byte_length = message.size();
//    buffer.initBufferLength()
    buffer.initBufferLength(byte_length);

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
//            *(bits + 8*i + j) = (*(bytes + i)<<j &0x80);
        }
    }

    return bits;
}


Byte *logics::convertBitsToBytes(Bit *bits, int num_bits)
{
    int numBytes = ceil((double)num_bits/8);

    Byte *bytes = new Byte[numBytes];


    for(int i=0;i<numBytes;i++)
    {
        *(bytes + i) = 0x00;


        for(int j=0;j<8;j++)
        {
            if(num_bits<8*i+j)
            {
            *(bytes + i) |= ( 0 << j );
//                *(bytes + i) |= ( 0 << 7-j );

            }
            else
            {
            *(bytes + i) |= ( *(bits + j + 8*i) << j );
//                *(bytes + i) |= ( *(bits + j + 8*i) << 7-j );

            }

        }
    }

    return bytes;
}


short logics::convertSignalStrenthToShort(SignalPower strength)
{
    if(strength == SignalPower::positive)
        return CHANNEL_POS;
    else if(strength == SignalPower::idle)
       return CHANNEL_IDLE;
    else
        return CHANNEL_NEG;
}


int logics::generateRand(int lowEnd, int highEnd, int prob)
{

  qsrand(prob);
 // qDebug()<<RAND_MAX;
   return ((qrand()
            %(highEnd - lowEnd))+lowEnd);

}


bool logics::generateRandBits(int numBits, Bit *bits)
{
    int num_bytes = ceil((double)numBits/8);

    Byte* bytes = new Byte[num_bytes];

    for(int i=0; i<num_bytes; i++)
        bytes[i] = (Byte)generateRand(0,255,QTime::currentTime().msec()*time(NULL)*i);

    for(int i=0; i<num_bytes; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(8*i + j<numBits)
                *(bits + 8*i + j) = (*(bytes + i)>>j &1);
            else
                break;
        }
    }

    return true;
}
