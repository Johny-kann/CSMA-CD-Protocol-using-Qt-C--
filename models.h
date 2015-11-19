#include <string>

#ifndef MODELS_H
#define MODELS_H

#include <QApplication>
//enum bitValue {Postive, Negative};

typedef std::string Message;
typedef bool Bit;
typedef unsigned char Byte;

class Frame;
class spBuffer;

#define CLOCK_TIME 1000


class ChannelMedium : public QObject
{
    Q_OBJECT
public:
    ChannelMedium();
    ~ChannelMedium();

    void setBit(int value);

public slots:
    void timeOut();
    void unsetBit();

signals:
    void done();

private:
    short bitValue;


};

class spBuffer
{
private:
    QList<Frame> list;
    int buf_size;

public:

void listAdd(Frame &frame);

QList<Frame> &getList();
QList<Frame> getList() const;
void setList(const QList<Frame> &value);
};


class Stations
{
private:
    ChannelMedium *bus;
    spBuffer buffer;
    Frame *frame;
    int id;

public:
    Stations(int id);
    bool checkChannel();
    bool attachChannel(const ChannelMedium *channel);

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
};

#endif
