#include "status.h"

status::status()
{

}

status::~status()
{

}


void status::addCollisions()
{
    collisions++;
}

void status::addFrameGenerated()
{
    frameGenerated++;
}

void status::addFrameSuccessTransmits()
{
    frameSuccessTransmits++;
}

void status::addPacketsLost()
{
    packetsLost++;
}

void status::addBufferOverFlow()
{
    bufferOverFlow++;
}

void status::addReTransmission()
{
    reTransmissionOverHead++;
}

void status::addDelayForSuccessfulFrame(unsigned long delay)
{
    delayForSuccessfulFrame+=delay;
}


unsigned long int status::collisions=0;
unsigned long int status::frameGenerated=0;
unsigned long int status::frameSuccessTransmits=0;
unsigned long int status::packetsLost=0;
unsigned long int status::bufferOverFlow = 0;
unsigned long int status::reTransmissionOverHead = 0;
unsigned long int status::delayForSuccessfulFrame = 0;
