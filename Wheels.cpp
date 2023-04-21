#include "Wheels.h"
#include "Arduino.h"

Wheels::Wheels(){
}
Wheels::Wheels(Motor &FR,Motor &FL,Motor &BR,Motor &BL){
    this -> FR = FR;
    this -> FL = FL;
    this -> BR = BR;
    this -> BL = BL;
}

void Wheels::setFR(int forwardPin, int backwardPin) {
    this -> FR = Motor(forwardPin, backwardPin);
}
void Wheels::setFL(int forwardPin, int backwardPin) {
    FL = Motor(forwardPin, backwardPin);
}
void Wheels::setBR(int forwardPin, int backwardPin) {
    BR = Motor(forwardPin, backwardPin);
}
void Wheels::setBL(int forwardPin, int backwardPin) {
    BL = Motor(forwardPin, backwardPin);
}


void Wheels::controlFR(int value,bool dir){
    FR.control(value, dir);
}
void Wheels::controlFL(int value,bool dir){
    FL.control(value,dir);
}
void Wheels::controlBR(int value,bool dir){
    BR.control(value,dir);
}
void Wheels::controlBL(int value,bool dir){
    BL.control(value,dir);
}


void Wheels::movingForward(int valueFR, int valueFL, int valueBR, int valueBL){
    FR.control(valueFR, true);
    FL.control(valueFL,true);
    BR.control(valueBR,true);
    BL.control(valueBL,true);
}
void Wheels::movingBackward(int valueFR, int valueFL, int valueBR, int valueBL){
    FR.control(valueFR, false);
    FL.control(valueFL,false);
    BR.control(valueBR,false);
    BL.control(valueBL,false);
}
void Wheels::movingLeft(int valueFR, int valueFL, int valueBR, int valueBL){
    FR.control(valueFR, true);
    FL.control(valueFL,false);
    BR.control(valueBR,false);
    BL.control(valueBL,true);
}
void Wheels::movingRight(int valueFR, int valueFL, int valueBR, int valueBL){
    FR.control(valueFR, false);
    FL.control(valueFL,true);
    BR.control(valueBR,true);
    BL.control(valueBL,false);
}
void Wheels::turnLeft(int valueFR, int valueFL, int valueBR, int valueBL){
    FR.control(valueFR, true);
    FL.control(valueFL, false);
    BR.control(valueBR, true);
    BL.control(valueBL,false);
}
void Wheels::turnRight(int valueFR, int valueFL, int valueBR, int valueBL){
    FR.control(valueFR, false);
    FL.control(valueFL, true);
    BR.control(valueBR, false);
    BL.control(valueBL,true);
}

void Wheels::stop(){
    FR.control(0, true);
    FL.control(0, true);
    BR.control(0, true);
    BL.control(0, true);
}

void Wheels::dirForward(){
    FR.updateDir(true);
    FL.updateDir(true);
    BR.updateDir(true);
    BL.updateDir(true);
}
void Wheels::dirBackward(){
    FR.updateDir(false);
    FL.updateDir(false);
    BR.updateDir(false);
    BL.updateDir(false);
}
void Wheels::dirLeft(){
    FR.updateDir(true);
    FL.updateDir(false);
    BR.updateDir(false);
    BL.updateDir(true);
}
void Wheels::dirRight(){
    FR.updateDir(false);
    FL.updateDir(true);
    BR.updateDir(true);
    BL.updateDir(false);
}
void Wheels::dirTurnLeft(){
    FR.updateDir(true);
    FL.updateDir(false);
    BR.updateDir(true);
    BL.updateDir(false);
}
void Wheels::dirTurnRight(){
    FR.updateDir(false);
    FL.updateDir(true);
    BR.updateDir(false);
    BL.updateDir(true);
}