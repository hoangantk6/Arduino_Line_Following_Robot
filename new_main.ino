#include "Arduino.h"
#include "Wheels.h"
#include "Motor.h"
#include "Ultrasonic.h"
#include "DisSensors.h"
#include "ObsAvoiding.h"
#include "Speed.h"
#include "LineFollow.h"
#include "FinishLine.h"

int IN1_A = 7;
int IN2_A = 6;
int IN3_A = 5;
int IN4_A = 4;

int IN1_B = 8;
int IN2_B = 9;
int IN3_B = 10;
int IN4_B = 11;

int IR1 = 25;
int IR2 = 27;
int IR3 = 29;
int IR4 = 31;
int IR5 = 33;

int EN1 = 18;
int EN2 = 19;
int EN3 = 20;
int EN4 = 21;


int encoder1 = 2;
bool state1 = true;
int en_value1 = 0;
int triPin = 12;
int echoFL = A0, echoFR = A1, echoBL = A2, echoBR = A3;
int s1;
bool inLine;
int obsPosition;
int taskID;
long time;

Wheels myWheels;
DisSensors myDisSensors;
ObsAvoiding myObsAvoiding;
LineFollow myLineFollow;
Speed mySpeedControl;
FinishLine myFinishLine;


void setup() {
  Serial.begin(9600);
  pinMode(IN2_A, OUTPUT); // digital right front
  pinMode(IN4_A, OUTPUT); // analog left front
  pinMode(IN2_B, OUTPUT); // digital left back
  pinMode(IN4_B, OUTPUT); // analog right back

  pinMode(IN1_A, OUTPUT); // analog right front
  pinMode(IN3_A, OUTPUT); // digital left front
  pinMode(IN1_B, OUTPUT); // analog left back
  pinMode(IN3_B, OUTPUT); // digital right back

  pinMode(IR1, INPUT); //line detect
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);
  pinMode(IR4, INPUT);
  pinMode(IR5, INPUT);

  myWheels = Wheels();
  myWheels.setFR(IN2_A,IN1_A);
  myWheels.setFL(IN4_A,IN3_A);
  myWheels.setBL(IN2_B,IN1_B);
  myWheels.setBR(IN4_B,IN3_B);


  myDisSensors = DisSensors();
  myDisSensors.setFR(triPin,echoFR);
  myDisSensors.setFL(triPin,echoFL);
  myDisSensors.setBR(triPin,echoBR);
  myDisSensors.setBL(triPin,echoBL);

  myLineFollow = LineFollow(IR1, IR2, IR3, IR4, IR5);

  mySpeedControl = Speed();
  mySpeedControl.setFL(EN1);
  mySpeedControl.setFR(EN2);
  mySpeedControl.setBL(EN3);
  mySpeedControl.setBR(EN4);

  myObsAvoiding = ObsAvoiding(myDisSensors);

  myFinishLine = FinishLine();

  taskID = 0;

}


void loop() {
    //myWheels.movingForward(70,70,70,70);
    //Serial.print("abc");
    //mySpeedControl.updateMotorSpeed(myWheels, 150, 0.5);
    // // myWheels.movingForward(150,150,150,150);

    inLine = myLineFollow.inLine();
    // //myLineFollow.follow(myWheels);
    obsPosition = myObsAvoiding.getPos(inLine);

    if (taskID == 0){
      myLineFollow.follow(myWheels);
      if (myObsAvoiding.objAhead()){
        taskID = 1;
        time = millis();
        }
      if (myLineFollow.endLine()){
        time = millis();
        taskID = 2;
      }
    }
    else if (taskID == 1){
      myObsAvoiding.nextAction(time,myWheels,mySpeedControl,obsPosition,120);
      if(myObsAvoiding.obsFinish(inLine)){
        taskID = 0;
      }
    }
    else if(taskID == 2){
      
        myFinishLine.run2(myWheels,mySpeedControl);
        if (millis()-time >= 6800){
          myWheels.movingForward(100,100,100,100);
          if (millis()-time >= 7500){
            myWheels.stop();
          }
        }
    }
    

    

    
    
    // Serial.print("Obj Position: ");
    // Serial.println(obsPosition);
    
    // Serial.print("Position Case: ");
    // Serial.println(myObsAvoiding._position);
    
    // Serial.print("last pos: ");
    // Serial.println(myObsAvoiding._last_pos);
    // Serial.println();
    

    // mySpeedControl.updateSpeedBR(myWheels,40.0,1);
    // Serial.print("pmw: ");
    // Serial.println(myWheels.BR.getSpeed());

    //Serial.println(myDisSensors._ulFR.distance_delay());
    // myDisSensors.detect_obj();
    

    


}
