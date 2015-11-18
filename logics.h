#include "models.h"


#ifndef LOGICS
#define LOGICS

namespace logics
{

bool convertMessageToBuffer(const Message message, Buffer &buffer);

std::string bufferToMessage(const unsigned char* buf, int length);

}
#endif // LOGICS

