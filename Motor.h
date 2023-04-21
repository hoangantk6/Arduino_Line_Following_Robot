#ifndef Motor_h
#define Motor_h
#define MAX_SPEED 255
/**
 * Class Motor is in charge of Motor function
 * 
 * 
*/
class Motor
{
private:
    int _forwardPin;
    int _backwardPin;
    int _speed;
    int _dir;

public:
    /**
     * Constructor:
     * @param forwardPin: the forward pin of arduino connecting to the driver
     * @param backwardPin: the backward pin of arduino connecting to the driver
    */
    Motor(int forwardPin, int backwardPin);
    Motor();
    void setPin(int forwardPin, int backwardPin);

    /**
     * The function to demmand the rotation of the motor
     * @param value: the analog value represent the speed. In the range 0-255
     * @param dir: the direction of the motor
    */
    void control(int value,bool dir);

    /**
     * Edit speed to balance between motors.
     * @param alpha: learning step speed = speed +/- alpha
     */
    void updateSpeed(int alpha);
    void updateDir(bool dir);
    int getSpeed();
};

#endif
