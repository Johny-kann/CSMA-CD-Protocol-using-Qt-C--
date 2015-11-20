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

short convertSignalStrenthToShort(SignalPower strength);

SignalPower convertShortToSignalPower(short strength);

int generateRand(int lowEnd,int highEnd,int prob);

bool generateRandBits(int numBits, Bit* bits);

bool generateRandFrames(int numFrames, int source_length, int dest_length, int message_length, QList<Frame> &frame);

}
#endif // LOGICS

