#include "Arduino.h"
#include "DisSensors.h"

DisSensors::DisSensors() {
    _objFL = false;
    _objFR = false;
    _objBL = false;
    _objBR = false;
    _disFL = 0.0;
    _disFR = 0.0;
    _disBL = 0.0;
    _disBR = 0.0;
    _start = micros();
    _temp = 1;
}



int DisSensors::setFL(int trigPin, int echoPin) {
    echoPin_FL = echoPin;
    _ulFL = Ultrasonic(trigPin, echoPin);
}

int DisSensors::setFR(int trigPin, int echoPin) {
    echoPin_FR = echoPin;
    _ulFR = Ultrasonic(trigPin, echoPin);
}

int DisSensors::setBL(int trigPin, int echoPin) {
    echoPin_BL = echoPin;
    _ulBL = Ultrasonic(trigPin, echoPin);
}

int DisSensors::setBR(int trigPin, int echoPin) {
    echoPin_BR = echoPin;
    _ulBR = Ultrasonic(trigPin, echoPin);
}

void DisSensors::getAllDis4() {
    int timer = 2;
    Serial.println(_temp);
    switch (_temp){
        // front left
        case 1:
            digitalWrite(_ulFL._trigPin, HIGH);
            _temp=2;
            break;
        case 2:

            if (micros()-_start >= timer){
                digitalWrite(_ulFL._trigPin, LOW);
                _start = micros();
                _disFL = pulseInLong(_ulFL._echoPin, HIGH) /2 /29.423;
                _objFL = detect_cond(_disFL);
                Serial.print(_objFL);
                _temp = 3;
            }
            break;

        // front right
        case 3:
            digitalWrite(_ulFR._trigPin, HIGH);
            _temp=4;
            break;
        case 4:
            if (micros()-_start >= timer){
                digitalWrite(_ulFR._trigPin, LOW);
                _start = micros();
                _disFR = pulseInLong(_ulFR._echoPin, HIGH) /2 /29.423;
                _objFR = detect_cond(_disFR);
                _temp = 5;
            }
            break;

        // back left
        case 5:
            digitalWrite(_ulBL._trigPin, HIGH);
            _temp=6;
            break;
        case 6:
            if (micros()-_start >= timer){
                digitalWrite(_ulBL._trigPin, LOW);
                _start = millis();
                _disBL = pulseInLong(_ulBL._echoPin, HIGH) /2 /29.423;
                _objBL = detect_cond(_disBL);
                _temp = 7;
            }
            break;

        // back right
        case 7:
            digitalWrite(_ulBR._trigPin, HIGH);
            _temp = 8;
            break;
        case 8:
            if (micros()-_start >= timer){
                digitalWrite(_ulBR._trigPin, LOW);
                _start = millis();
                _disBR = pulseInLong(_ulBR._echoPin, HIGH) /2 /29.423;
                _objBR = detect_cond(_disBR);
                _temp = 1;
            }
            break;
    }
    DisSensors::printDis4();
}

bool DisSensors::detect_cond(int distance) {
    if(distance < 33 and distance > 3){
        return true;
    } else{
        return false;
    }
}

void DisSensors::detect_obj() {
    _objFL = _ulFL.detect_obj();
    _disFL = _ulFL._average_dis;

    _objFR = _ulFR.detect_obj();
    _disFR = _ulFR._average_dis;

    _objBL = _ulBL.detect_obj();
    _disBL = _ulBL._average_dis;

    _objBR = _ulBR.detect_obj();
    _disBR = _ulBR._average_dis;

    
    //DisSensors::printDis();
}

void DisSensors::printDis(){
    Serial.print("FL: ");
    Serial.println(_ulFL._average_dis);
    Serial.print("FR: ");
    Serial.println(_ulFR._average_dis);
    Serial.print("BL: ");
    Serial.println(_ulBL._average_dis);
    Serial.print("BR: ");
    Serial.println(_ulBR._average_dis);
}

void DisSensors::printDis4(){
    Serial.print("FL: ");
    Serial.println(_disFL);
    Serial.print("FR: ");
    Serial.println(_disFR);
    Serial.print("BL: ");
    Serial.println(_disBL);
    Serial.print("BR: ");
    Serial.println(_disBR);
}
