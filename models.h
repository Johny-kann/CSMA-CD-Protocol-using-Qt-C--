#include <string>



#ifndef MODELS_H
#define MODELS_H

#include <QApplication>
//#include "controller.h"
//enum bitValue {Postive, Negative};

typedef std::string Message;
typedef bool Bit;
typedef unsigned char Byte;

enum SignalPower {positive , negative, idle};
enum States {listening, sending, receving};

class Frame;
class spBuffer;

#define CLOCK_TIME 20
#define CHANNEL_POS 2
#define CHANNEL_NEG -2
#define CHANNEL_IDLE 0

#define FRAME_SIZE 24
#define FRAME_SOURCE_LENGTH 8
#define FRAME_DEST_LENGTH 8
#define FRAME_MESSAGE_LENGTH 8

#define BUF_SIZE 10

#define TIME_SLOT 5

namespace control
{
class Controller;
}
class ChannelMedium
{
private:
    short signalStrength;
    int num_collision;
    bool collisionInChannel;
    control::Controller *controller;

public:
    ChannelMedium();
    ~ChannelMedium();

    void setStrength(int value);
    short getStrenth();

    void setCollision();

    void execute();


    int getNum_collision() const;
    void setNum_collision(int value);

    control::Controller *getController() const;
    void setController(control::Controller *value);

private:
    short bitValue;


};

class spBuffer
{
private:
    QList<Frame> list;
    int buf_size;

public:
    spBuffer();
bool listAdd(Frame &frame);

QList<Frame> &getList();
QList<Frame> getList() const;
Frame &frameAt(int i);
void setList(const QList<Frame> &value);
void setBufferSize(int size);
int getBufferSize();
int framesInBuffer();
};


class Stations
{
private:
    ChannelMedium *bus;
    spBuffer outbuffer,inbuffer;
    Frame *outframe,*inframe;
    int id;
    SignalPower pinStrength;
    States current_state,next_state,prev_state;
    int frameSentPos,frameSize;
    int inFrameRecPos;
    int waitPeriod;
    bool waitingForChannel;

public:
    Stations(int id);
    void executeStation();

    bool checkChannel();
    bool isCollitionDetected();
    bool attachChannel(ChannelMedium *channel);

    void sendBit();
    void receiveBitListening();
    void receiveBitReading();

    void processInFrame();

    void collisionChangeMode();

    void bufferCheck();

    SignalPower getPinStrength() const;
    void setPinStrength(const SignalPower &value);
    spBuffer &getoutBuffer();
    void setoutBuffer(const spBuffer &value);
    States getCurrent_state() const;
    void setCurrent_state(const States &value);
    States getNext_state() const;
    void setNext_state(const States &value);

    bool addFrame(Frame *frame);
};


//#endif // MODELS_H



class Buffer
{
public:
    Buffer();
    Buffer(int length);
    ~Buffer();

    int getBuf_length() const;
    void setBuf_length(int value);

    Byte *getBuffer() const;
    Byte *getBuffer();
    void setBuffer(Byte *value);
    void setBuffer(const Message message);

    int getStart_pos() const;
    void setStart_pos(int value);

    int getEnd_pos() const;
    void setEnd_pos(int value);

    bool initBufferLength(int length);

    void resetPos();

private:
    int buf_length, start_pos, end_pos;
    Byte *buffer;


};




class Frame
{
private:
    Bit *bits;
    short source_length,destination_length;
    int message_length;

public:
    Frame(Bit *bits, short sour_len, short dest_len, short mess_len);
    ~Frame();

    int getTotalLength();
    bool *getSourceBits();
    bool *getDestinationBits();
    bool *getMessageBits();
    short getSource_length() const;
    void setSource_length(short value);
    short getDestination_length() const;
    void setDestination_length(short value);
    int getMessage_length() const;
    void setMessage_length(int value);

    Byte getSource();
    Byte getDestination();
    Byte *getMessage();
    Bit getBitAt(int index);
    void setBitAt(int index,Bit bit);

};

#endif
