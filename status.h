#ifndef STATUS_H
#define STATUS_H


class status
{
public:
    status();
    ~status();
    static unsigned long int collisions;
    static unsigned long int frameGenerated;
    static unsigned long int frameSuccessTransmits;
    static unsigned long int packetsLost;
    static unsigned long int bufferOverFlow;

    static void addCollisions();
    static void addFrameGenerated();
    static void addFrameSuccessTransmits();
    static void addPacketsLost();
    static void addBufferOverFlow();
};

#endif // STATUS_H
