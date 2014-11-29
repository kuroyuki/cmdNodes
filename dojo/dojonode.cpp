#include "dojonode.h"
#include <QDateTime>
#include <QTextStream>

dojoNode::dojoNode()
{
    voltage = VOLTAGE_DEFAULT;
    size = 1;
    cone = new QVector3D(0,0,1);
}
void dojoNode::process(){
    //get all synaptic currents
    float synapseVoltage = 0;
    for (int i = 0; i < sources.size(); ++i) {
        synapseVoltage += sources.at(i)->getVoltage();
    }

    voltage += synapseVoltage;
    //check is above threshold
    if(voltage > VOLTAGE_THRESHOLD){
        //generate spike to all targets
        voltage = VOLTAGE_DEFAULT;
        for (int i = 0; i < targets.size(); ++i) {
            targets.at(i)->ap(this);
        }        
    }
    else{

    }
}
void dojoNode::synapseGrowing(){   
    //get node growing cone length
    //get neighbours of growing cone vector end
    //check is there unconnected nodes
    //unconnected nodes found - select one
    //connect nodes
}

void dojoNode::addTarget(dojoSynapse* synapse){
    targets<<synapse;
}
void dojoNode::addSource(dojoSynapse* synapse){
    sources<<synapse;
}
void dojoNode::addVoltage(float addedVoltage){
    voltage += addedVoltage;
}
void dojoNode::setCoords(QVector3D newCoords){
    coords = newCoords;
}

