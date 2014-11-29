#ifndef DOJOSYNAPSE_H
#define DOJOSYNAPSE_H

#define LENGHT_CONST 1 //0.5 mm Typical values for neuronal length constants range from 0.1 to 1.0 mm.
class dojoNode;

class dojoSynapse
{
public:
    dojoSynapse();
    virtual float getVoltage() = 0;
    virtual void ap(dojoNode* node) = 0;
    virtual dojoNode* getTarget() = 0;
};
//dojo Synapses
class dojoSensorSynapse : public dojoSynapse
{
public :
    dojoSensorSynapse(float* source, dojoNode* target);

    float getVoltage();
    void ap(dojoNode* node);
    dojoNode* getTarget();

private :
    float* Source;
    dojoNode* Target;
};
class dojoMotorSynapse : public dojoSynapse{
public:
    dojoMotorSynapse(dojoNode* source, float* target);

    float getVoltage();
    void ap(dojoNode* node);
    dojoNode* getTarget() ;

private :
    dojoNode* Source;
    float* Target;
    float Terminals;
};

class dojoChemicalSynapse : public dojoSynapse
{
public:
    dojoChemicalSynapse(dojoNode* source, dojoNode* target);

    float getVoltage();
    void ap(dojoNode* node);
    dojoNode* getTarget();

    float getLength(){return Length;}

private :    
    void calcLength();

    dojoNode* Source;
    dojoNode* Target;

    float Terminals;
    float Cleft;

    float Permability;
    float Length;
};
#endif // DOJOSYNAPSE_H
