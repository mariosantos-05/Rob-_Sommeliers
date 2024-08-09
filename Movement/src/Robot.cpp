#include "Robot.h"


Robot::Robot(MotorDC& M_Left, MotorDC& M_Right, Servo& claw,Servo& Stacker, Sensor& S_Left, Sensor& S_Right, Sensor& Front,ColorSensor S_Color, LED& leds)
    : motor_left(M_Left), motor_right(M_Right), claw(claw), stacker(Stacker), S_Left(S_Left), S_Right(S_Right), S_front(Front),S_Color(S_Color), Led(leds) {}


void Robot::Align(float tolerance){
    float diference = abs(S_Left.getDistance() - S_Right.getDistance());
    while (diference > tolerance){
        if(S_Left.getDistance() > S_Right.getDistance()){
            motor_right.Forward();
        }
        motor_left.Forward();
    }
    
}

void Robot::Close_Claw(int position){
    claw.write(position);
}

void Robot::Open_Claw(int position){
    claw.write(position);
}


void Robot::Turn_Left_90(){
    motor_left.Stop();
    motor_right.Forward();
}

void Robot::Turn_right_90(){
    motor_left.Forward();
    motor_right.Stop();
}

void Robot::Turn_Angle(float angle){
    motor_left.Turn(angle);
    motor_right.Turn(angle);
}

void Robot::TurnOFFLED() {
    Led.turnOff();
}

void Robot::Update_LED_CS(int r, int g, int b){
    int value = min(r ,min(g, b));
    if(value ==  r) SetLEDColor(255, 0, 0);
    if(value == g) SetLEDColor(0, 255, 0);
    else SetLEDColor(0, 0, 255);
}

void Robot::SetLEDColor(int red, int green, int blue) {
    Led.setColor(red, green, blue);
}

void Robot::Straight_Run() {
    motor_left.Forward();
    motor_right.Forward();
}

void Robot::Straight_Run_cm(float cm) {
    float time = cm / 10.0; // definir essa velocidade na mão!
    unsigned long timeMs = time * 1000; // converte para milissegundos
    Straight_Run();
    delay(timeMs); 
}

void Robot::Straight_Back() {
    motor_left.Backward();
    motor_right.Backward();
}

void Robot::Straight_Back_cm(float cm) {
    float time = cm / 10.0; // definir essa velocidade na mão!
    unsigned long timeMs = time * 1000; // converte para milissegundos
    Straight_Back();
    delay(timeMs); 
}

void Robot::Stop() {
    motor_left.Stop();
    motor_right.Stop();
}

void Robot::Go_Up_cm(float cm){
    stacker.writeMicroseconds(-cm);
}

void Robot::Go_Down_cm(float cm){
    stacker.writeMicroseconds(cm);
}

char Robot::Vision() {
    if (Serial.available() > 0) {
        String receivedLetter = Serial.readStringUntil('\n'); // Lê a letra recebida pelo raspberry pi
        char letra = receivedLetter[0];
        return letra;
    }
    return 'i';
}

long Robot::Get_L_Distance() {
    return S_Left.getDistance();
}

long Robot::Get_R_Distance() {
    return S_Right.getDistance();
}


long Robot::Get_F_Distance() {
    return S_front.getDistance();
}

