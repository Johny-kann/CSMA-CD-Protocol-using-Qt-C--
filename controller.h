#include <QCoreApplication>

#ifndef CONTROLLER
#define CONTROLLER

#include "models.h"

namespace control
{

class Controller : public QObject
{
    Q_OBJECT
    ChannelMedium med;
public:
    void test();
    Controller(QObject *parent = 0);
public slots:
    void run();
    void exit();

signals:
    void finished();
};

}
#endif // CONTROLLER

