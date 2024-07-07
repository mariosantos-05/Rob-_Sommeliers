#include "MotorDC.h"


MotorDC::MotorDC(int p1, int p2, int en): pin1(p1), pin2(p2), enablepin(en){
    pinMode(pin1,OUTPUT);
    pinMode(pin2,OUTPUT);
    pinMode(enablepin,INPUT);
}


void MotorDC::Backward(){
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, HIGH);
    analogWrite(enablepin, 255); 
}


void MotorDC::Forward(){
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    analogWrite(enablepin, 255); 
}

void MotorDC::Stop(){
    analogWrite(enablepin, 0);
}