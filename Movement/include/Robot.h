#ifndef ROBOT_H
#define ROBOT_H

#include "MotorDC.h"
#include "Sensor.h"
#include "ColorSensor.h"
#include "LED.h"
#include "Claw.h"

class Robot{
private:
    MotorDC motor_left, motor_right;
    Claw claw;
    Sensor S_Left, S_Right, S_front;
    ColorSensor S_Color;
    LED Led;
public:
    Robot(MotorDC& M_Left, MotorDC& M_Right, Claw& Claw, Sensor& S_Left, Sensor& S_Right, Sensor& S_Front,ColorSensor S_Color, LED& Led);
    void Turn_right();
    void Turn_Left();
    void TurnOFFLED();
    void SetLEDColor(int r, int g, int b);
    void Update_LED_CS();
    void Straight_Run();
    void Straight_Back();
    void Straight_Run_cm(float cm);
    void Stop();
    void Vision();
    long Get_L_Distance();
    long Get_R_Distance();
    long Get_F_Distance();


};


#endif
