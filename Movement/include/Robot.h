#ifndef ROBOT_H
#define ROBOT_H

#include "MotorDC.h"
#include "Sensor.h"
#include "ColorSensor.h"
#include "LED.h"
#include <Servo.h>

class Robot{
private:
    MotorDC motor_left, motor_right;
    Servo claw, stacker;
    Sensor S_Left, S_Right, S_front;
    ColorSensor S_Color;
    LED Led;
public:
    Robot(MotorDC& M_Left, MotorDC& M_Right, Servo& Claw, Servo& Stacker, Sensor& S_Left, Sensor& S_Right, Sensor& S_Front,ColorSensor S_Color, LED& Led);
    void Align(float T);
    void Close_Claw(int position);
    void Open_Claw(int position);
    void Turn_right_90();
    void Turn_Left_90();    
    void Turn_Angle(float angle);
    void TurnOFFLED();
    void SetLEDColor(int r, int g, int b);
    void Update_LED_CS();
    void Straight_Run();
    void Straight_Back();
    void Straight_Back_cm(float cm);
    void Straight_Run_cm(float cm);
    void Stop();
    void Go_Up_cm(float cm );
    void Go_Down_cm(float cm);
    char Vision();
    long Get_L_Distance();
    long Get_R_Distance();
    long Get_F_Distance();


};


#endif
