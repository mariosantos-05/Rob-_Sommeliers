#ifndef MOTORDC_H
#define MOTORDC_H
#include <Arduino.h>

class MotorDC {
private:
    int pin1, pin2, enablepin;
    int encoderPinA, encoderPinB;
    volatile long encoderPosition;
    long targetPosition;
    static MotorDC* instance;

    void updateEncoder();

public:
    MotorDC(int p1, int p2, int en, int encA, int encB);
    void Backward();
    void Forward();
    void Stop();
    void Turn(float angle); // Angle in degrees
    void updatePosition();
    static void updateEncoderA();
    static void updateEncoderB();
};

#endif
