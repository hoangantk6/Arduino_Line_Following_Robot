#include "Arduino.h"
#include "LineFollow.h"
#include "Wheels.h"
#include "math.h"

LineFollow::LineFollow() {
    IR1 = -1;
    IR2 = -1;
    IR3 = -1;
    IR4 = -1;
    IR5 = -1;
}

LineFollow::LineFollow(int IR1, int IR2, int IR3, int IR4, int IR5) {
    this -> IR1 = IR1;
    this -> IR2 = IR2;
    this -> IR3 = IR3;
    this -> IR4 = IR4;
    this -> IR5 = IR5;

    _s1 = digitalRead(IR1);  //Left Most Sensor
    _s2 = digitalRead(IR2);  //Left Sensor
    _s3 = digitalRead(IR3);  //Middle Sensor
    _s4 = digitalRead(IR4);  //Right Sensor
    _s5 = digitalRead(IR5);  //Right Most Sensor

    error = linePos();
    previousError = linePos();
    I = 0;
}

double LineFollow::linePos() {
    _s1 = digitalRead(IR1);  //Left Most Sensor
    _s2 = digitalRead(IR2);  //Left Sensor
    _s3 = digitalRead(IR3);  //Middle Sensor
    _s4 = digitalRead(IR4);  //Right Sensor
    _s5 = digitalRead(IR5);  //Right Most Sensor

    if ((_s1 == 1) & (_s2 == 1) & (_s3 == 1) & (_s4 == 1) & (_s5 == 1)){
        return 10;
    }


    else if ((_s1 == 0) & (_s2 == 0) & (_s3 == 0) & (_s4 == 0) & (_s5 == 0)){
        return 9;
    }


    else if ((_s1 == 1)& (_s2 == 0) & (_s3 == 0) & (_s5 == 0)) {
        return 4;
    }
    else if ((_s1 == 1) & (_s2 == 1) & (_s3 == 0) & (_s5 == 0)){
        return 3;
    }
    else if ((_s1 == 0) & (_s2 == 1) & (_s3 == 0) & (_s5 == 0)){
        return 2;
    }
    else if ( (_s2 == 1) & (_s3 == 1) & (_s5 == 0)){
        return 1;
    }
    else if ((_s1 == 0) & (_s2 == 1) & (_s3 == 1) & (_s4 == 1) & (_s5 == 0)){
        return 0;
    }
    else if ((_s1 == 0) & ((_s2 == 1) &_s3 == 1) & (_s4 == 1)){
        return -1;
    }
    else if ((_s1 == 0) & (_s2 == 0) & (_s3 == 0) & (_s4 == 1)&(_s5 == 0)){
        return -2;
    }
    else if ((_s1 == 0) & (_s2 == 0) & (_s3 == 0) & (_s4 == 1)&(_s5 == 1)){
        return -3;
    }
    else if ((_s1 == 0 )& (_s2 == 0) & (_s3 == 0) & (_s4 == 0)&(_s5 == 1)){
        return -4;
    }
    

}

double LineFollow::linePID(int kp,double ki, int kd) {
    float P = error;
    I = (error == 9)?I:I + error;
    int D = previousError-error;
    if (I>20) I=20;
    if (I<-20) I=-20;
    Serial.print("P: ");
    Serial.println(P);
    Serial.print("I: ");
    Serial.println(I);
    Serial.print("D: ");
    Serial.println(D);
    return (kp * P) + (ki * I) + (kd * D);
}


void LineFollow::follow(Wheels &myWheels) {
    // int PID = linePID(kp,ki,kd);
    // previousError = error;
    // error = linePos();
    // Serial.print("PID: ");
    // Serial.println(PID);

    // int speed_l = speed - PID;
    // int speed_r = speed + PID;


    // if (speed_r>220) speed_r = 220;
    // else if (0>speed_r ) speed_r = 0;
    // if (speed_l>220) speed_l =220;
    // else if (0>speed_l ) speed_l = 0;
    // if (error == 10){
    //     myWheels.stop();
    // }
    // else if (error == 9){
    //     myWheels.stop();
    //     // if (previousError > 0) myWheels.movingForward(160,160,160,160);
    //     // else myWheels.turnRight(160,160,160,160);
    // }
    // else {
    //     Serial.print("SpeedL: ");
    //     Serial.println(speed_l);
    //     Serial.print("SpeedR: ");
    //     Serial.println(speed_r);
    //     if (speed_r > 0){
    //         myWheels.controlFR(speed_r,true);
    //         myWheels.controlBR(speed_r,true);
    //     }
    //     else{
    //         myWheels.controlFR(-speed_r,false);
    //         myWheels.controlBR(-speed_r,false);
    //     }
    //     if (speed_l > 0){
    //         myWheels.controlFL(speed_l,true);
    //         myWheels.controlBL(speed_l,true);
    //     }
    //     else{
    //         myWheels.controlFL(-speed_l,false);
    //         myWheels.controlBL(-speed_l,false);
    //     }
    // }
    error = linePos();
    if(error == 0){
        myWheels.movingForward(170, 170, 170, 170);
    }else if (error == 4){
        myWheels.movingForward(250, 0, 250, 0);
    }else if (error == 3){
        myWheels.movingForward(220, 120, 220, 120);
    }else if (error == 2){
        myWheels.movingForward(170, 150, 170, 150);
    }else if (error == 1){
        myWheels.movingForward(170, 160, 170, 160);
    }else if (error == -1){
        myWheels.movingForward(150, 160, 150, 160);
    }else if (error == -2){
        myWheels.movingForward(150, 190, 150, 190);
    }else if (error == -3){
        myWheels.movingForward(100, 230, 100, 230);
    }else if (error == -4){
        myWheels.movingForward(0, 250, 0, 250);


    }
}
bool LineFollow::endLine(){
    return error == 10;
}
bool LineFollow::inLine() {
    Serial.print("Error: ");
    Serial.println(error); 
    return _s1 || _s2 || _s3 || _s5;
}
