#ifndef MOTORDC_H
#define MOTORDC_H
#include <Arduino.h>

class MotorDC{
private:
    int pin1, pin2, enablepin;
public:
    MotorDC(int p1, int p2,int en);
    void Backward();
    void Forward();
    void Stop();
};

#endif