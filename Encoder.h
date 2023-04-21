#ifndef Encoder_h
#define Encoder_h

class Encoder{
private:
    double _enSpeed;
    int _enPin;
public:
    Encoder();
    Encoder(int enPin);
};

#endif

