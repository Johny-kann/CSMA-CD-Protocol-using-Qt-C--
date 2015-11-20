#include "logics.h"
#include <QDebug>
#include <time.h>
#include <QTime>
#include <random>
#include <chrono>
#include <thread>

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

bool *logics::convertByteToBits(Byte *bytes, int num_bytes,Bit *bits)
{
 //   Bit *bits = new Bit[num_bytes*8];

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
//  long int rnd = qrand();
//  qsrand(rnd);
 //   qsrand(time(0));
 // qDebug()<<RAND_MAX;
   return ((qrand()
            %(highEnd - lowEnd))+lowEnd);


}


bool logics::generateRandBits(int numBits, Bit *bits)
{
    int num_bytes = ceil((double)numBits/8);

    Byte *bytes = new Byte[num_bytes];

    for(int i=0; i<num_bytes; i++)
        bytes[i] = (Byte)generateRand(0,255,QTime::currentTime().msec()*time(NULL)*(i+1));

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

    delete bytes;

    return true;
}


bool logics::generateRandFrames(int numFrames, int source_length, int dest_length, int message_length, QList<Frame> &frame)
{
    for(int i=0;i<numFrames;i++)
    {
        int total = source_length + dest_length + message_length;
        Bit *bits = new Bit[total];
        logics::generateRandBits(total,bits);

        Frame *tempframe = new Frame(bits,source_length,dest_length,message_length);

        frame.append(*tempframe);

        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
    return true;
}



SignalPower logics::convertShortToSignalPower(short strength)
{
    if(strength == CHANNEL_POS)
        return SignalPower::positive;
    else if(strength == CHANNEL_NEG)
        return SignalPower::negative;
    else
        return SignalPower::idle;

}


bool logics::generateRandFramesForAStation(int numFrames, int source_len, int sourc_id, int dest_len, int num_stations, int mess_len, QList<Frame> &frame)
{
    for(int i=0;i<numFrames;i++)
    {
        int total = source_len + dest_len + mess_len;

        Byte source = sourc_id;
        Byte dest = generateRand(0,num_stations-1,QTime::currentTime().msec()*time(NULL)*(i+1));

        std::this_thread::sleep_for(std::chrono::nanoseconds(1));

        if(dest == sourc_id)
            dest = dest+1;


        Bit *bits = new Bit[total];

        logics::convertByteToBits(&source,1,bits);  // source

    /*    for(int i=0;i<source_len;i++)
            std::cout<<bits[i]<<" ";
        std::cout<<'\n';
*/
        logics::convertByteToBits(&dest,1,bits+source_len);

  /*      for(int i=0;i<soure_len+dest_len;i++)
            std::cout<<bits[i]<<" ";
        std::cout<<'\n';
*/
        logics::generateRandBits(mess_len,bits+source_len+dest_len);

        Frame *tempframe = new Frame(bits,source_len,dest_len,mess_len);

        frame.append(*tempframe);

        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
    return true;
}
