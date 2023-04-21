#ifndef ROBOT_SPEED_H
#define ROBOT_SPEED_H
#include "Encoder.h"
#include "Wheels.h"
#include "Arduino.h"

class Speed{
private:
    int _pulseFL, _pulseFR, _pulseBL, _pulseBR;
    static unsigned long _previousMicros[4]; //FL FR BL BR

    static unsigned long _newMicros[4];

    double deltaList[4];
    double speedList[4];
    double eIntegral[4];

    static void countPulseFR();
    static void countPulseFL();
    static void countPulseBR();
    static void countPulseBL();

    void updateDeltaSpeed();

public:
    Encoder _enFL;
    Encoder _enFR;
    Encoder _enBL;
    Encoder _enBR;
    Speed();

    void setFL(int enPin);
    void setFR(int enPin);
    void setBL(int enPin);
    void setBR(int enPin);
    
    void activateMotor(bool a, bool b, bool c,bool d);
    void updateSpeedFR(Wheels &myWheels,double set_speed, double alpha);
    void updateSpeedFL(Wheels &myWheels,double set_speed, double alpha);
    void updateSpeedBR(Wheels &myWheels,double set_speed, double alpha);
    void updateSpeedBL(Wheels &myWheels,double set_speed, double alpha);


};

#endif
