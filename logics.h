#include "models.h"


#ifndef LOGICS
#define LOGICS

namespace logics
{

bool convertMessageToBuffer(const Message message, Buffer &buffer);

std::string bufferToMessage(const unsigned char* buf, int length);

unsigned char *pointerShifter(unsigned char* buf,int index);

Bit *convertByteToBits(Byte *bytes,int num_bytes);

Byte *convertBitsToBytes(Bit *bits,int num_bits);

}
#endif // LOGICS

