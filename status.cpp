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


unsigned long int status::collisions=0;
unsigned long int status::frameGenerated=0;
unsigned long int status::frameSuccessTransmits=0;
unsigned long int status::packetsLost=0;
unsigned long int status::bufferOverFlow = 0;
