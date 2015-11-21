#include "models.h"
//#include "status.h"


#ifndef LOGICS
#define LOGICS

#define RAND_SEED_CONST QTime::currentTime().msec()*time(NULL)
#define ONE_NANO_SEC_WAIT std::this_thread::sleep_for(std::chrono::nanoseconds(1))

namespace logics
{

bool convertMessageToBuffer(const Message message, Buffer &buffer);

std::string bufferToMessage(const unsigned char* buf, int length);

unsigned char *pointerShifter(unsigned char* buf,int index);

bool *convertByteToBits(Byte *bytes,int num_bytes, Bit *bits);

Bit *convertByteToBits(Byte *bytes,int num_bytes);

Byte *convertBitsToBytes(Bit *bits,int num_bits);

short convertSignalStrenthToShort(SignalPower strength);

SignalPower convertShortToSignalPower(short strength);

int generateRand(int lowEnd,int highEnd,int prob);

bool generateRandBits(int numBits, Bit* bits);

bool generateRandFrames(int numFrames, int source_length, int dest_length, int message_length, QList<Frame> &frame);

bool generateRandFramesForAStation(int numFrames, int source_len,int sourc_id, int dest_len,int num_stations, int mess_len, QList<Frame> &frame);

}
#endif // LOGICS

