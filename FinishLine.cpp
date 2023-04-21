#include "FinishLine.h"
FinishLine::FinishLine(){
    status = true;
}
//for the right move
bool FinishLine::endRun(){
    return status;
}
void FinishLine::run1(Wheels &myWheels, Speed &speedControl){
    myWheels.FR.updateDir(true);
    myWheels.BL.updateDir(true);
    myWheels.FL.updateDir(true);
    myWheels.BR.updateDir(true);
    speedControl.updateSpeedFR(myWheels,20,1);
    speedControl.updateSpeedBL(myWheels,80,1);
    speedControl.updateSpeedFL(myWheels,80,1);
    speedControl.updateSpeedBR(myWheels,20,1);
    Serial.print("nhanh: ");
    Serial.println(myWheels.FR.getSpeed());
    Serial.print("cham: ");
    Serial.println(myWheels.BR.getSpeed());
}
// case turn left
void FinishLine::run2(Wheels &myWheels, Speed &speedControl){
    myWheels.FR.updateDir(true);
    myWheels.BL.updateDir(true);
    myWheels.FL.updateDir(true);
    myWheels.BR.updateDir(true);
    speedControl.updateSpeedFL(myWheels,5,1);
    speedControl.updateSpeedBR(myWheels,90,1);
    speedControl.updateSpeedFR(myWheels,90,1);
    speedControl.updateSpeedBL(myWheels,5,1);
    Serial.print("nhanh: ");
    Serial.println(myWheels.FR.getSpeed());
    Serial.print("cham: ");
    Serial.println(myWheels.BR.getSpeed());
}