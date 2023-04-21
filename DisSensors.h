#ifndef DisSensors_h
#define DisSensors_h

#include "Arduino.h"
#include "Ultrasonic.h"

class DisSensors{
private:
    int trigPin;
    int echoPin_FR, echoPin_FL, echoPin_BR, echoPin_BL;
    int _temp;
    int _start;


public:
    Ultrasonic _ulFR;
    Ultrasonic _ulFL;
    Ultrasonic _ulBR;
    Ultrasonic _ulBL;

    int _disFL, _disFR, _disBL, _disBR;
    bool _objFL, _objFR, _objBL, _objBR;

    DisSensors();
    int setFR(int trigPin, int echoPin);
    int setFL(int trigPin, int echoPin);
    int setBR(int trigPin, int echoPin);
    int setBL(int trigPin, int echoPin);

    void getAllDis();
    void getAllDis4();
    bool detect_cond(int distance);
    void detect_obj();
    void printDis();
    void printDis4();
};

#endif
