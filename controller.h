

#ifndef CONTROLLER
#define CONTROLLER

#include <QCoreApplication>
#include "models.h"

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
    int num_collisions;

public:
    void test();
    Controller(QObject *parent = 0);
    ~Controller();
    bool startTimer();
    bool stopTimer();
    bool resetTimer();
    void executeOperations();

    void addStations(int num);
    Stations &getStationAt(int num);

    void addPinStrength();

    void collisionChangeMode();

public slots:
    void run();
    void exit();
    void update();

signals:
    void finished();
};

}
#endif // CONTROLLER

