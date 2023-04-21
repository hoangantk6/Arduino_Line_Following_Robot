#include "Encoder.h"
#include "Arduino.h"

Encoder::Encoder() {
    this -> _enPin = -1;

}

Encoder::Encoder(int enPin) {
    this ->_enPin= enPin;
    pinMode(enPin, INPUT_PULLUP);
}



