

#ifndef CONTROLLER
#define CONTROLLER

#include <QCoreApplication>
#include "models.h"
//#include "status.h"


class ChannelMedium;
class Stations;

namespace control
{

class Controller : public QObject
{
    Q_OBJECT

private:
    ChannelMedium med;
    QList<Stations> stations;
    QTimer *mainTimer;
    long int Total_Cycles;
    int num_collisions;

public:
    void test();
    Controller(QObject *parent = 0);
    ~Controller();
    bool startTimer();
    bool stopTimer();
    bool resetTimer();
    void executeOperations();

    void gettingInput();

    void displayingOutput();

    void addStations(int num);
    void generateFrames();

    Stations &getStationAt(int num);

    void addPinStrength();

    void collisionChangeMode();

    void statusPrinter();

    long getTotal_Cycles() const;
    void setTotal_Cycles(long value);

public slots:
    void run();
    void exit();
    void update();

signals:
    void finished();
};

}
#endif // CONTROLLER

