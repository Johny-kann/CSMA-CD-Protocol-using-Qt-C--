#include "logics.h"


bool logics::convertMessageToBuffer(const Message message, Buffer &buffer)
{
    int byte_length = sizeof(message)/8;
    buffer.setBuf_length(byte_length);

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
