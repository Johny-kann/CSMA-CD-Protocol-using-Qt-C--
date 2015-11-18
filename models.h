#ifndef MODELS_H
#define MODELS_H

#include <QApplication>
//enum bitValue {Postive, Negative};

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



#endif // MODELS_H
