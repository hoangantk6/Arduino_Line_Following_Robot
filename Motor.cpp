#include "Arduino.h"
#include "Motor.h" 
Motor::Motor(){}
Motor::Motor(int forwardPin, int backwardPin){
    this -> _forwardPin = forwardPin;
    this -> _backwardPin = backwardPin;
}


void Motor::setPin(int forwardPin, int backwardPin){
    this -> _forwardPin = forwardPin;
    this -> _backwardPin = backwardPin;
}
void Motor::control(int value,bool dir){
    _dir = dir;
    _speed = value;
    analogWrite(_forwardPin,_speed*_dir);
    analogWrite(_backwardPin,_speed*(1-_dir));
}



void Motor::updateSpeed(int alpha) {
    this -> _speed = _speed + alpha;
    Serial.print("rido an va vo cung nhieu:");
    Serial.println(_speed);
    if (_speed < 0) _speed = 0;
    if(_speed >255) _speed = 255;
    analogWrite(_forwardPin,_speed*_dir);
    analogWrite(_backwardPin,_speed*(1-_dir));
}
int Motor::getSpeed(){
    return _speed;
}
void Motor::updateDir(bool dir){
    _dir = dir;
}