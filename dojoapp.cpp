#include "dojoapp.h"
#include "math.h"
#include "utils/gephi.h"

dojoApp::dojoApp(QObject *parent) :
    QObject(parent)
{
    network = new dojoNetwork(10, QVector3D(30,10,1));
    server = new wsServer(1234);

    inputCurrent = 0;
    output = 0;

    time = 0;
    maxCurrent = 100;
    frequency = 1;
    shift = 100;

    connect(network, SIGNAL(dojoMessage(QJsonObject)), &log, SLOT(logMessage(QJsonObject)));
    connect(network, SIGNAL(dojoMessage(QJsonObject)), server, SLOT(clientMessage(QJsonObject)));
    connect(&timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));

    network->start();
}
void dojoApp::configDojo(){
    //network.setNodeCoords(network.createNode(), QVector3D(0,0,0));
    /*
    for(int z=0;z<1;z++){
        for(int y=0;y<5;y++){
            for(int x=0;x<5;x++){
                network.setNodeCoords(network.createNode(), QVector3D(x,y,z));
            }
        }
    }
    quint64 node = network.createNode();
    network.setNodeCoords(node, QVector3D(-1,0,0));
    network.getNeighbours(node, 1);

    network.createSynapse(node, node1);
    network.bindInput(&inputCurrent, node);
    network.bindOutput(node1, &output);

    timer.start(1000);
    */
}
void dojoApp::slotTimeout(){
    time += 0.01;

    inputCurrent = maxCurrent*sin(2*PI*frequency*time) + shift;
    /*
    QString str = QString::number(inputCurrent);
    log.logMessage(str);
    */
}
