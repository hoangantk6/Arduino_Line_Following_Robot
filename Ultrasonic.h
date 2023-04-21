#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Arduino.h"


class Ultrasonic
{
  public:
    Ultrasonic();
    Ultrasonic(int trigPin, int echoPin);
    int getStartTime();
    void setStartTime(int start);
    int distance(int now);
    int distance_delay();
    int average_dis();
    bool detect_obj();
    void print_distance();

    int _echoPin, _trigPin, _average_dis;
  private:
    int  _start, _distance;
    

};

#endif
