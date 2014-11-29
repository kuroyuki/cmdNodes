#include "dojosynapse.h"
#include "math.h"
#include "dojonode.h"

dojoSynapse::dojoSynapse(){

}
/*
 *Sensor synapses - use only for input from outside
 */
dojoSensorSynapse::dojoSensorSynapse(float *source, dojoNode *target){
    Target = target;
    Source = source;
}
float dojoSensorSynapse::getVoltage(){
    return *Source;
}
void dojoSensorSynapse::ap(dojoNode *node){

}
dojoNode* dojoSensorSynapse::getTarget(){
    return Target;
}

/*
 *Motor synapses - used only for output to external float variable
 */
dojoMotorSynapse::dojoMotorSynapse(dojoNode* source, float* target){
    Source = source;
    Target = target;
    Terminals = 0;
}

float dojoMotorSynapse::getVoltage(){
    return *Target;
}

void dojoMotorSynapse::ap(dojoNode* node){
    if(node == Source){
        //eject Mediator
         *Target += 100;
    }
}

dojoNode* dojoMotorSynapse::getTarget(){
    return Source;
}

/*
 *Normal Chemical synapses - common for node interconnection in the network
 */
dojoChemicalSynapse::dojoChemicalSynapse(dojoNode* source, dojoNode* target)
{
    Source = source;
    Target = target;

    Terminals = 100;
    Cleft = 0;
    Permability = 5;

    calcLength();
 }

float dojoChemicalSynapse::getVoltage(){

    float voltage = 0;
    //calc what is volatge injected by this synapse multiplied in ms
    if(Cleft>0){
        //synpase voltage will affect trigger area according to distance
        voltage = Cleft*Permability*exp(-Length/LENGHT_CONST);
    }
    //remove all transmitter from cleft
    Cleft = 0;

    return voltage;
}

void dojoChemicalSynapse::ap(dojoNode* node){
    //if it is Presynapse
    if(node == Source){
        //eject Mediator
        Cleft = Terminals;        
    }
    //if it is Postsynapse
    else if (node == Target){

    }
}
dojoNode* dojoChemicalSynapse::getTarget(){
    return Target;
}
void dojoChemicalSynapse::calcLength(){
    QVector3D start = Source->getCoords();
    QVector3D end = Target->getCoords();

    //Calc length
    QVector3D diff = end-start;

    Length = diff.length();
}
