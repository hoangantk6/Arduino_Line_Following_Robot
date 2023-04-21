#include "Wheels.h"

class LineFollow{
private:
    int IR1, IR2, IR3, IR4, IR5;
    int _s1, _s2, _s3, _s4, _s5;
    int error;
    int previousError;
    int I;

public:
    LineFollow();
    LineFollow(int IR1, int IR2, int IR3, int IR4, int IR5);

    double linePos();
    double linePID(int kp,double ki, int kd);
    void follow(Wheels &myWheels);
    bool inLine();
    bool endLine();
};