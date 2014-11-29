#include "dojonetwork.h"
#include "math.h"

dojoNetwork::dojoNetwork(int interval, QVector3D size,  QObject *parent) :
    QObject(parent)
{
    nextNodeID = 0;
    timeCounter = 0;

    networkSize = size;
    timer.setInterval(interval);

    connect(&timer, SIGNAL(timeout()), this, SLOT(proceedNetwork()));
}
void dojoNetwork::proceedNetwork(){
    timeCounter += 10;
    foreach (dojoNode* node, nodeTable)
         node->process();
    if(timeCounter>1000){
        seedNewNode();
        synapseGrowing();

        timeCounter = 0;
    }
}

void dojoNetwork::start(){

    timer.start();
}

quint64 dojoNetwork::createNode(){

    dojoNode* newNode = new dojoNode();
    quint64 index = nextNodeID++;

    if(nextNodeID == 0){
        QJsonObject json;
        json.insert("error", "counter overload");

        emit dojoMessage(json);

        return 0;
    }
    nodeTable[index] = newNode;   

    QJsonObject json;
    json.insert("command", "an");
    json.insert("id", QString::number(index));

    emit dojoMessage(json);
    return index;
}
void dojoNetwork::setNodeCoords(quint64 id, QVector3D newCoords){
   nodeTable[id]->setCoords(newCoords);

   QJsonObject json;
   json.insert("command", "cn");
   json.insert("id", QString::number(id));
   json.insert("x",newCoords.x());
   json.insert("y",newCoords.y());
   json.insert("z",newCoords.z());
   json.insert("size", nodeTable[id]->getSize());

   emit dojoMessage(json);
}
void dojoNetwork::createSynapse(quint64 source, quint64 target){
    dojoNode* sourceNode = nodeTable[source];
    dojoNode* targetNode = nodeTable[target];   

    dojoChemicalSynapse* synapse = new dojoChemicalSynapse(sourceNode, targetNode);

    sourceNode->addTarget(synapse);
    targetNode->addSource(synapse);

    QJsonObject json;
    json.insert("command", "as");
    json.insert("id",  QString::number(source)+"->"+QString::number(target));
    json.insert("source", QString::number(source));
    json.insert("target", QString::number(target));

    emit dojoMessage(json);
}
void dojoNetwork::bindInput(float* value, quint64 target){
    dojoNode* targetNode = nodeTable[target];

    dojoSensorSynapse* synapse = new dojoSensorSynapse(value, targetNode);
    targetNode->addSource(synapse);

    QJsonObject json;
    json.insert("command", "ai");
    json.insert("id", QString::number(target));

    emit dojoMessage(json);
}

void dojoNetwork::bindOutput(quint64 source, float* value){
    dojoNode* sourceNode = nodeTable[source];

    dojoMotorSynapse* synapse = new dojoMotorSynapse(sourceNode, value);
    sourceNode->addTarget(synapse);

    QJsonObject json;
    json.insert("command", "ao");
    json.insert("id", QString::number(source));

    emit dojoMessage(json);
}
QList<dojoNode*> dojoNetwork::getNodeNeighbours(dojoNode* forNode, float atDistance){
    QVector3D startPoint = forNode->getCoords();
    QList<dojoNode*> list;
    QList<dojoNode*> allNodes = nodeTable.values();

    for(int i=0;i<allNodes.size();i++){
        dojoNode* node = allNodes[i];
        if(node != forNode){
            QVector3D diff = node->getCoords() - startPoint;

            if(diff.length() < atDistance+(node->getSize()/2))
                list << node;

        }
    }
    return list;
}

QList<dojoNode*> dojoNetwork::getPointNeighbours(QVector3D forPoint, float atDistance){
    QList<dojoNode*> list;
    QList<dojoNode*> allNodes = nodeTable.values();

    for(int i=0;i<allNodes.size();i++){
        dojoNode* node = allNodes[i];
        QVector3D diff = node->getCoords() - forPoint;
        if(diff.length() < (atDistance+(node->getSize()/2)))
            list << node;

    }
    return list;
}
QList<dojoNode*> dojoNetwork::getNeighbours(quint64 forNode, float atDistance){
    //emit dojoMessage("start neighbours finding");
    return getNodeNeighbours(nodeTable[forNode], atDistance);
}
void dojoNetwork::seedNewNode(){
    //get random point within the network volume
    qreal x = (qrand() % (int)(2*networkSize.x()))-networkSize.x();
    qreal y = (qrand() % (int)(2*networkSize.y()))-networkSize.z();
    qreal z = (qrand() % (int)(2*networkSize.z()))-networkSize.z();

    QList<dojoNode* > list = getPointNeighbours(QVector3D(x,y,z), 1);
    if(!list.length()){
        setNodeCoords(createNode(), QVector3D(x,y,z));
    }
}
void dojoNetwork::synapseGrowing(){
    //get from node possible
    foreach (dojoNode* node, nodeTable){
        node->synapseGrowing();
    }
}
