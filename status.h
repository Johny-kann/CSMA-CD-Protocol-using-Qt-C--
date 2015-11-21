#ifndef STATUS_H
#define STATUS_H


class status
{
public:
    status();
    ~status();
    static long int collisions;
    static long int frameGenerated;
    static long int frameSuccessTransmits;

    static void addCollisions();
    static void addFrameGenerated();
    static void addFrameSuccessTransmits();
};

#endif // STATUS_H
