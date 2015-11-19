#include <QCoreApplication>

#ifndef CONTROLLER
#define CONTROLLER

#include "models.h"

namespace control
{

class Controller : public QObject
{
    Q_OBJECT

private:
    ChannelMedium med;
    QList<Stations> stations;
    QTimer *mainTimer;

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

public slots:
    void run();
    void exit();
    void update();

signals:
    void finished();
};

}
#endif // CONTROLLER

