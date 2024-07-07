#include "Robot.h"




Robot::Robot(MotorDC& M_Left, MotorDC& M_Right, Servo& claw, Sensor& S_Left, Sensor& S_Right, Sensor& Front,ColorSensor S_Color, LED& leds)
    : motor_left(M_Left), motor_right(M_Right), claw(claw), S_Left(S_Left), S_Right(S_Right), S_front(Front),S_Color(S_Color), Led(leds) {}


void Robot::Align(float tolerance){
    float diference = abs(S_Left.getDistance() - S_Right.getDistance());
    while (diference > tolerance){
        if(S_Left.getDistance() > S_Right.getDistance()){
            motor_right.Forward();
        }
        motor_left.Forward();
    }
    
}

void Robot::Turn_Left(){
    motor_left.Stop();
    motor_right.Forward();
}

void Robot::Turn_right(){
    motor_left.Forward();
    motor_right.Stop();
}

void Robot::TurnOFFLED() {
    Led.turnOff();
}

void Robot::Update_LED_CS(){
    int red, green, blue;
    S_Color.readColor(&red, &green, &blue);
    SetLEDColor(red, green, blue);
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

void Robot::Stop() {
    motor_left.Stop();
    motor_right.Stop();
}

char Robot::Vision() {
    if (Serial.available() > 0) {
        char receivedLetter = Serial.read(); // Lê a letra recebida pelo raspberry pi
        return receivedLetter;

        // print testes
        Serial.print("Letra recebida: ");
        Serial.println(receivedLetter);
    }
    return 'H';
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

