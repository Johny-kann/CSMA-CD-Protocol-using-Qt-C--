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


long int status::collisions=0;
long int status::frameGenerated=0;
long int status::frameSuccessTransmits=0;
