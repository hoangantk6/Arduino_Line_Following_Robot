#ifndef Wheels_h
#define Wheels_h
#include "Motor.h"
class Wheels
{
private:

public:
    Motor FR;
    Motor FL;
    Motor BR;
    Motor BL;
    Wheels();
    Wheels(Motor &FR,Motor &FL,Motor &BR,Motor &BL);

    void setFR(int analogPin, int digitalPin);
    void setFL(int analogPin, int digitalPin);
    void setBR(int analogPin, int digitalPin);
    void setBL(int analogPin, int digitalPin);

    void controlFR(int value,bool dir);
    void controlFL(int value,bool dir);
    void controlBR(int value,bool dir);
    void controlBL(int value,bool dir);


    void movingForward(int valueFR, int valueFL, int valueBR, int valueBL);
    void movingBackward(int valueFR, int valueFL, int valueBR, int valueBL);
    void movingLeft(int valueFR, int valueFL, int valueBR, int valueBL);
    void movingRight(int valueFR, int valueFL, int valueBR, int valueBL);
    void turnLeft(int valueFR, int valueFL, int valueBR, int valueBL);
    void turnRight(int valueFR, int valueFL, int valueBR, int valueBL);
    void stop();

    
    void dirForward();
    void dirBackward();
    void dirLeft();
    void dirRight();
    void dirTurnLeft();
    void dirTurnRight();
};

#endif