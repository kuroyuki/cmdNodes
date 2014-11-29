#ifndef DOJOAPP_H
#define DOJOAPP_H

#include <QObject>
#include <QTimer>
#include "utils/logger.h"
#include "dojo/dojonetwork.h"
#include "utils/wsserver.h"

#define PI 3.14159265

class dojoApp : public QObject
{
    Q_OBJECT
public:
    explicit dojoApp(QObject *parent = 0);
    void configDojo();
signals:

public slots:
    void slotTimeout();
private:
    dojoNetwork* network;
    wsServer* server;
    QTimer timer;
    logger log;

    float inputCurrent, output;
    float maxCurrent, frequency, time, shift;
};

#endif // DOJOAPP_H
