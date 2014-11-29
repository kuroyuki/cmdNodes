#ifndef DOJONETWORK_H
#define DOJONETWORK_H

#include <QObject>
#include <QHash>
#include <QMap>
#include <QTimer>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include "dojonode.h"
#include "dojodb.h"

class dojoNetwork : public QObject
{
    Q_OBJECT
public:
    explicit dojoNetwork(int interval, QVector3D size, QObject *parent = 0);
    quint64 createNode();
    void start();

    void setNodeCoords(quint64 id, QVector3D newCoords);
    void createSynapse(quint64 source, quint64 target);
    void bindInput(float* value, quint64 target);
    void bindOutput(quint64 source, float* value);

    QList<dojoNode*> getNodeNeighbours(dojoNode* forNode, float atDistance);
    QList<dojoNode*> getPointNeighbours(QVector3D forPoint, float atDistance);

    //debug function
    void addVoltage(quint64 node, float voltage){nodeTable[node]->addVoltage(voltage);}
    QList<dojoNode*> getNeighbours(quint64 forNode, float atDistance);    

signals:    
    void dojoMessage(QJsonObject message);

public slots:
    void proceedNetwork();

private :
    void seedNewNode();
    void synapseGrowing();
    
    QHash <quint64, dojoNode*> nodeTable;
    QTimer timer;
    dojoDb* db;

    quint64 nextNodeID;
    QVector3D networkSize;

    uint timeCounter;

};

#endif // DOJONETWORK_H
