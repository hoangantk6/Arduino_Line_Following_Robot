#include "Arduino.h"
#include "ObsAvoiding.h"
ObsAvoiding::ObsAvoiding(){
    _position = 0;
    _last_pos = 0;
    _temp = 0;
    _finish = true;
}
ObsAvoiding::ObsAvoiding(DisSensors &myDisSensors){
    this -> _myDisSensors = myDisSensors;
    _position = 0;
    _last_pos = 0;
    _temp = 0;
    _finish = true;
}

bool ObsAvoiding::objAhead() {
    // if object ahead the car return true
    if(_myDisSensors._objFR or _myDisSensors._objFL){
        if(this -> _finish == true)
        {
            this -> _finish = false;
            _last_pos = 10;
        }
        return true;
    } else{
        return false;
    }
}

bool ObsAvoiding::objSide() {
    if(_myDisSensors._objBR or _myDisSensors._objBL){
        return true;
    } else{
        return false;
    }
}


int ObsAvoiding::getPos(bool line_detect) {
    /**
     * getPosition: based on distance of 4 ultrasonic sensor, determine the position of car and object
     * return:
     * -2 -> when all dis infinity, out line detect, used to move left -> move right to comeback line
     * -1 -> when disFR <=10    , disFL infinity -> object before + right side -> move left to avoid object
     * 0  -> when disFR infinity, disFL infinity, disBR or disBL <= 10 -> go forward
     * 1  -> when disFR infinity, disFL <=10     -> object before + left side  -> move right to avoid object
     * 2  -> when all dis infinity, out line detect, used to move right -> move left to comeback line
     * 9  -> finish task
     * */
     
     //set min dis to start avoid obj
     int min_front = 20;

     /**
     if(line_detect and ObsAvoiding::objAhead()){
         //if in line and object ahead
         if(_disFL < min_front){
             _last_pos = 1;
             return 1;
         } else{
             _last_pos = -1;
             return -1;
         }
     }

     if(!line_detect and ObsAvoiding::objAhead() and _last_pos != 0){
         //if object still ahead and out line
         return _last_pos;
     }

     if (!line_detect and _last_pos != 0 and !ObsAvoiding::objAhead() and ObsAvoiding::objSide()){
         //if detected last position + object not ahead +
         return 0;
     }

    if (!line_detect and _last_pos != 0 and !ObsAvoiding::objAhead() and !ObsAvoiding::objSide()){
        return _last_pos*2;
    }

    if (line_detect and _last_pos != 0 and !ObsAvoiding::objAhead() and ! ObsAvoiding::objSide()){
        _finish = true;
        return 0;
    }
    return 0;
      */

     /**
      * Have total 7 steps for robot to overcome object.
      *
      * */

    int check_time = 2;
    _myDisSensors.getAllDis4();
    switch (_position) {
        case 0:
            //first step
            if(line_detect and ObsAvoiding::objAhead()){
                //if in line and object ahead
                // -1: move left, +1: move right
                _temp++;
                if(_temp > check_time){
                    _last_pos = 1;
                    _position = 1;
                    _temp = 0;
                }
                return 1;
            } else {
                _last_pos = 0;
                _finish = true;
                return 9;
            }

        case 1:
            if(ObsAvoiding::objAhead()){
                return _last_pos;
            }else{
                _temp++;
                if(_temp > check_time + 1){
                    _position = 2;
                    _temp = 0;
                    return 0;
                }
                return _last_pos;
            }
        case 2:
            if(!ObsAvoiding::objSide()){
                return 0;
            } else{
                _temp++;
                if(_temp > check_time){
                    _position = 3;
                    _temp = 0;
                }
                return 0;
            }
        case 3:
            if(ObsAvoiding::objSide()){
                return 0;
            } else{
                _temp++;
                if(_temp > check_time){
                    _position = 4;
                    _temp = 0;
                }
                return _last_pos*2;
            }
        case 4:
            if(!line_detect){
                return _last_pos*2;
            } else{
                _position = 0;
                _last_pos = 10;
                _finish = true;         
                return 9;
            }
    }


}

bool ObsAvoiding::obsFinish(bool line_detect) {
    if(line_detect and _finish){
        return true;
    }else return false;
}

void ObsAvoiding::nextAction(long time,Wheels &myWheels,Speed &mySpeedControl, int position, int speed) {
    /**
     * getPosition: based on distance of 4 ultrasonic sensor, determine the position of car and object
     * return:
     * -2 -> when all dis infinity, out line detect, used to move left -> move right to comeback line
     * -1 -> when disFR <=10    , disFL infinity -> object before + right side -> move left to avoid object
     * 0  -> when disFR infinity, disFL infinity, disBR or disBL <= 10 -> go forward
     * 1  -> when disFR infinity, disFL <=10     -> object before + left side  -> move right to avoid object
     * 2  -> when all dis infinity, out line detect, used to move right -> move left to comeback line
     * */

    switch (position) {
        case 9:
            //finish task
            myWheels.stop();
            delay(10);

        case 0:
            // go forward
            
            myWheels.movingForward(speed+30,speed-10,speed+30,speed-10);
            break;
        case 1:
            // move right
            myWheels.movingRight(speed,speed+20,speed,speed+20);
        
            break;
        case 2:
            if (millis() -time >=1200)
                myWheels.movingLeft(speed,speed,speed,speed);
            else if (millis() - time >= 3000)
            myWheels.movingForward(speed+30,speed,speed+30,speed);
            else if (millis() -time >= 4300)
            myWheels.movingRight(speed-20,speed+30,speed-20,speed+30);


            break;
        // case -1:
        //     // move left
        //     myWheels.movingLeft(speed,speed,speed,speed);
        //     break;
        // case -2:
        //     // move right
        //     myWheels.movingRight(speed,speed,speed,speed);
        //     break;

    }
    // mySpeedControl.updateSpeedFL(myWheels,speed,1);
    // mySpeedControl.updateSpeedFR(myWheels,speed,1);
    // mySpeedControl.updateSpeedBL(myWheels,speed,1);
    // mySpeedControl.updateSpeedBR(myWheels,speed,1);
}
