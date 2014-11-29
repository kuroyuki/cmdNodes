#ifndef DOJONODE_H
#define DOJONODE_H

#define VOLTAGE_THRESHOLD 100
#define VOLTAGE_DEFAULT 0
#define TIME_CONST 30 //100 ms The time constants of different neurons typically range from 20 to 50 ms.
#define PUMP_CONST 1//1 mV per per 1 ms

class dojoNode;

#include "dojosynapse.h"
#include <QList>
#include <QVector3D>

class dojoNode
{
public:
    dojoNode();
    void process();
    void synapseGrowing();
    void addTarget(dojoSynapse* synapse);
    void addSource(dojoSynapse* synapse);
    void setCoords(QVector3D newCoords);
    QVector3D getCoords(){return coords;}
    float getSize(){return size;}
        
    //debug function
    void addVoltage(float addedVoltage);

private:
    QVector3D coords;
    float voltage;
    float remainVoltage;
    int sign;

    float size;
    QVector3D* cone;

    QList <dojoSynapse*> sources;
    QList <dojoSynapse*> targets;
};

#endif // DOJONODE_H
