#include "Speed.h"
#include "Encoder.h"
#include "Arduino.h"
#include "Wheels.h"

Speed::Speed(){
    _enFR = Encoder();
    _enFL = Encoder();
    _enBR = Encoder();
    _enBL = Encoder();
    eIntegral[0] = 0;
    eIntegral[1] = 0;
    eIntegral[2] = 0;
    eIntegral[3] = 0;
}
unsigned long Speed::_previousMicros[4];
unsigned long Speed::_newMicros[4];
void Speed::setFL(int enPin) {
    _enFL = Encoder(enPin);

    attachInterrupt(digitalPinToInterrupt(enPin), Speed::countPulseFL, RISING);
}

void Speed::setFR(int enPin) {
    _enFR = Encoder(enPin);
    attachInterrupt(digitalPinToInterrupt(enPin), Speed::countPulseFR, RISING);
}

void Speed::setBL(int enPin) {
    _enBL = Encoder(enPin);
    attachInterrupt(digitalPinToInterrupt(enPin), Speed::countPulseBL, RISING);
}

void Speed::setBR(int enPin) {
    _enBR = Encoder(enPin);
    attachInterrupt(digitalPinToInterrupt(enPin), Speed::countPulseBR, RISING);
}

void Speed ::activateMotor(bool a, bool b, bool c,bool d){
    
}

void Speed::countPulseFL(){
    _previousMicros[0] = _newMicros[0];
    _newMicros[0] = micros();
}
void Speed::countPulseFR(){
    _previousMicros[1] = _newMicros[1];
    _newMicros[1] = micros();
}
void Speed::countPulseBL(){
    _previousMicros[2] = _newMicros[2];
    _newMicros[2] = micros();
}
void Speed::countPulseBR(){
    _previousMicros[3] = _newMicros[3];
    _newMicros[3] = micros();
}

void Speed::updateSpeedFL(Wheels &myWheels,double set_speed, double alpha){
    deltaList[0] = (_newMicros[0] - _previousMicros[0])*1.0e6;
    speedList[0] = 1/deltaList[0];
    double e = set_speed - speedList[0];
    eIntegral[0] = eIntegral[0] + e*deltaList[0];
    myWheels.FL.updateSpeed(e*10+eIntegral[0]*5);
}
void Speed::updateSpeedFR(Wheels &myWheels,double set_speed, double alpha){
    deltaList[1] = (_newMicros[1] - _previousMicros[1])*1.0e6;
    speedList[1] = 1/deltaList[1];
    double e = set_speed - speedList[1];
    eIntegral[1] = eIntegral[1] + e*deltaList[1];
    myWheels.FR.updateSpeed(e*10+eIntegral[1]*5);
    
}
void Speed::updateSpeedBL(Wheels &myWheels,double set_speed, double alpha){
    deltaList[2] = (_newMicros[2] - _previousMicros[2])*1.0e6;
    speedList[2] = 1/deltaList[2];
    double e = set_speed - speedList[2];
    eIntegral[2] = eIntegral[2] + e*deltaList[2];
    myWheels.BL.updateSpeed(e*10+eIntegral[2]*5);

}
void Speed::updateSpeedBR(Wheels &myWheels,double set_speed, double alpha){
    deltaList[3] = (_newMicros[3] - _previousMicros[3])/1.e6;
    Serial.print("previous:");
    Serial.println(_previousMicros[3]);
    Serial.print("now:");
    Serial.println(_newMicros[3]);
    Serial.print("delta:");
    Serial.println(deltaList[3]);
    speedList[3] = 1/deltaList[3];
    double e = set_speed - speedList[3];
    Serial.print("real speed:");
    Serial.println(speedList[3]);
    eIntegral[3] = eIntegral[3] + e*deltaList[3];
    double temp = (e*0.5+eIntegral[3]*0);
    myWheels.BR.updateSpeed(temp);
    Serial.print("change:");
    Serial.println((int)&myWheels.BR);
}
