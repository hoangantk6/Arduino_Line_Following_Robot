

#ifndef ROBOT_FINISHLINE_H
#define ROBOT_FINISHLINE_H
#include "Wheels.h"
#include "Speed.h"

class FinishLine
{
private:
    bool status;
public:
    FinishLine();
    FinishLine(Wheels &myWheels, Speed &speedControl);
    void run1(Wheels &myWheels, Speed &speedControl);
    void run2(Wheels &myWheels, Speed &speedControl);
    bool endRun();
};


#endif //ROBOT_FINISHLINE_H
