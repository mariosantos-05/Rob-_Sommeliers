#include <Arduino.h>
#include "Robot.h"
#include "MotorDC.h"
#include "Sensor.h"
#include "LED.h"
#include "ColorSensor.h"
#include <Servo.h>

// Definindo os pinos no arduino (todos devem ser modificados para o que são de fato)
const int motorLeftPin1 = 2;
const int motorLeftPin2 = 3;
const int motorLeftEn = 4;
const int motorRightPin1 = 5;
const int motorRightPin2 = 6;
const int motorRightEn = 7;
const int clawPin = 8;
const int sensorLeftTrig = 9;
const int sensorLeftEcho = 10;
const int sensorRightTrig = 11;
const int sensorRightEcho = 12;
const int sensorFrontTrig = 13;
const int encoderA = 15;
const int encoderB = 16;
const int sensorFrontEcho = A0;
const int redLEDPin = A1;
const int greenLEDPin = A3;
const int blueLEDPin = A4;
const int S0 = 7;
const int S1 = 6;
const int S2 = 5;
const int S3 = 4;
const int Coutput = 3;

// Criando os objetos referente as partes
MotorDC motorLeft(motorLeftPin1, motorLeftPin2, motorLeftEn, encoderA, encoderB );
MotorDC motorRight(motorRightPin1, motorRightPin2, motorRightEn, encoderA, encoderB);
Sensor sensorLeft(sensorLeftTrig, sensorLeftEcho);
Sensor sensorRight(sensorRightTrig, sensorRightEcho);
Sensor sensorFront(sensorFrontTrig, sensorFrontEcho);
Servo claw, stacker;
ColorSensor colorSensor(S0, S1, S2, S3, Coutput); 
LED led(redLEDPin, greenLEDPin, blueLEDPin);    

// Construtor do robo
Robot robot(motorLeft, motorRight, claw, stacker , sensorLeft, sensorRight, sensorFront, colorSensor, led);

void setup() {
    Serial.begin(9600);
    colorSensor.begin();
    claw.attach(clawPin);
    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);
    pinMode(blueLEDPin, OUTPUT);
    pinMode(sensorLeftTrig, OUTPUT);
    pinMode(sensorLeftEcho, INPUT);
    // Inicializando componentes se necessario
}

// Definindo Macros para navegação
#define MOVE_UNTIL_DISTANCE(robot, tolerance_front) while ((robot).Get_F_Distance() > (tolerance_front)) { (robot).Straight_Run(); }
#define COLOR_READ do { colorSensor.readColor(&r, &g, &b); robot.Update_LED_CS(r, g, b); } while(0)


// Definindo variaveis que devem ser refinadas antes da partida:

float tolerance_front = 0.0;
float tolerance_Align = 0.0;
int openPosition = 0;   
int closedPosition = 90;  
int r, g, b;
int counterA = 0;
int counterDoors = 0;
int counterCubes = 0;

// Estrategia principal de navegação do robô (quase um pseudodigo por enquanto!)

void getCube() { // funcao de pegar cubos
    robot.Open_Claw();
    robot.Straight_Run_cm(6);
    robot.SetLEDColor(colorSensor.readColor()) // le a cor do cubo e liga o LED
    robot.Close_Claw();
    robot.Straight_Back_cm(6);
}

void deliverCube() {
    if (counterCubes > 1 && counterCubes < 5) {
        robot.Go_Up_cm(14);
    } else {
        robot.Go_Up_cm(4);
    } 
    robot.Straight_Run_cm(5);
    robot.Open_Claw();
    robot.Straight_Back_cm(5);
    robot.Close_Claw();
    if (counterCubes > 1 && counterCubes < 5) {
        robot.Go_Down_cm(14);
    } else {
        robot.Go_Down_cm(4);
    } 
}


void We_Dont_have_No_claw(){
    // Entrando no canal
    robot.Straight_Run_cm(10);
    robot.Align(tolerance_Align);
    
    MOVE_UNTIL_DISTANCE(robot, tolerance_front);
    robot.Turn_Left_90();
    robot.Straight_Run_cm(145);

    //  Lendo a cor dos cubos 
    robot.Turn_Left_90();
    COLOR_READ;

    robot.Turn_right_90();
    robot.Straight_Back_cm(5);
    robot.Turn_Left_90();
    COLOR_READ;

    robot.Turn_right_90();
    robot.Straight_Run_cm(10);
    robot.Turn_Left_90();
    robot.Straight_Run_cm(15);
    robot.Turn_right_90();
    COLOR_READ;

    robot.Turn_Left_90();
    robot.Straight_Run_cm(115);
    robot.Turn_right_90();
    COLOR_READ;

    robot.Turn_Left_90();
    robot.Straight_Run_cm(10);
    robot.Turn_right_90();
    COLOR_READ;

    robot.Straight_Back_cm(20);
    robot.Turn_right_90();
    MOVE_UNTIL_DISTANCE(robot,tolerance_front);
    

    robot.Turn_Left_90();
    robot.Straight_Run_cm(40);
    robot.Align(tolerance_Align);
    // Saindo do canal D indo em direção ao canal B
    
    while (robot.Vision() != 'A'){
        robot.Straight_Run();
        if(robot.Get_F_Distance() < 10){
            robot.Turn_Angle(-45);
            robot.Straight_Run_cm(30);
            robot.Turn_Angle(90);
            robot.Straight_Run_cm(30);
            robot.Turn_Angle(-45);
        }

        if(robot.Get_R_Distance() > 30){
            robot.Turn_right_90();
            robot.Straight_Run_cm(10);
            robot.Turn_Angle(180);
            robot.Straight_Run_cm(10);
            robot.Turn_Left_90();
        }
    
    MOVE_UNTIL_DISTANCE(robot,tolerance_front);

    }
}

void twofour(){

}


void We_do_have_a_claw(){
    robot.Straight_Run_cm(10);
    robot.Align(tolerance_Align);
    MOVE_UNTIL_DISTANCE(robot, tolerance_front);
    robot.Turn_Left_90();
    robot.Straight_Run_cm(145);
    //Put here the function in acord to the cube disposition
    
}


void teste_componentes(){
    int distance = sensorLeft.getDistance();
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(100);
    while(1){
    robot.Close_Claw(200);
    }

    robot.SetLEDColor(255, 0, 0);
   /// Serial.println("Red");
    delay(1000);

}

void loop() { // real real mesmo
    while(1) { // procura a entrada do corredor 'C'
        robot.Straight_Run();
        if (robot.Get_F_Distance() < 11) {
            robot.Turn_Left_90();
        } 
        if (robot.Get_R_Distance() > 40) {
            robot.Turn_right_90();
            robot.Vision();
            if(robot.Vision() == 'C') {
                break;
            }
            robot.Turn_Left_90()
        }
    }

    // caminha pelo corredor c ateh a sala de entrega
    robot.Align(tolerance_Align);
    while(robot.Get_F_Distance() > 11) {
        robot.Straight_Run();
    }
    robot.Turn_Left_90();
    robot.Align(tolerance_Align);
    while(robot.Get_F_Distance() > 11) {
        robot.Straight_Run(); // para em frente ah prateleira
    }

    // comeca a pegar os cubos
    robot.Turn_right_90();
    while(robot.Get_F_Distance() > 6) {
        robot.Straight_Run();
    }
    robot.Turn_right_90();
    while(robot.Get_F_Distance() > 6) {
        robot.Straight_Run(); // se posiciona em frente ao cubo 1
    }
    getCube();
    robot.Turn_right_90();
    robot.Straight_Run_cm();
    robot.Turn_right_90();
    while (robot.Get_F_Distance() > 5) {
        robot.Straight_Run(); // se posiciona em frente ah prateleira
    }
    deliverCube(); // entrega o cubo 1 na posição direita 
    counterCubes++;

    // cubo 2
    robot.Turn_right_90();
    robot.Straight_Run_cm();
    robot.Turn_right_90();
    while(robot.Get_F_Distance() > 6) {
        robot.Straight_Run(); // se posiciona em frente ao cubo 2
    }
    getCube();
    robot.Turn_right_90();
    robot.Straight_Run_cm();
    robot.Turn_right_90();
    while (robot.Get_F_Distance() > 5) {
        robot.Straight_Run(); // se posiciona em frente ah prateleira
    }
    deliverCube(); // entrega o cubo 2 na posição d 
    counterCubes++;


    // cubo 3
    robot.Turn_right_90();
    while(robot.Get_F_Distance() > 6) {
        robot.Straight_Run();
    }
    robot.Turn_right_90();
    while(robot.Get_F_Distance() > 6) {
        robot.Straight_Run();
    } // posiciona em frente ao cubo 3
    getCube();
    robot.Turn_right_90();
    robot.Turn_right_90();
    robot.Straight_Run_cm();
    robot.Turn_Left_90();
    robot.Straight_Run_cm();
    robot.Turn_right_90();
    deliverCube();
    counterCubes++;

    // cubo 4
    robot.Turn_right_90();
    robot.Straight_Run_cm();
    robot.Turn_right_90();
    robot.Turn_right_90();
    while(robot.Get_F_Distance() > 6) {
        robot.Straight_Run();
    } // posiciona em frente ao cubo 4
    getCube();
    robot.Turn_right_90();
    robot.Straight_Run_cm();
    robot.Turn_right_90();
    while (robot.Get_F_Distance() > 5) {
        robot.Straight_Run(); // se posiciona em frente ah prateleira
    }
    counterCubes++;

    // cubo 5
    robot.Turn_Left_90();
    while(robot.Get_F_Distance() > 6) {
        robot.Straight_Run();
    }
    robot.Turn_Left_90();
    while(robot.Get_F_Distance() > 6) {
        robot.Straight_Run();
    } // posiciona em frente ao cubo 5
    getCube();
    robot.Turn_Left_90();
    robot.Straight_Run_cm();
    robot.Turn_Left_90();
    while (robot.Get_F_Distance() > 5) {
        robot.Straight_Run(); // se posiciona em frente ah prateleira
    }
    deliverCube();

    // sai da sala
    robot.Turn_Left_90();
    while(robot.Get_F_Distance() > 6) {
        robot.Straight_Run();
    } 
    robot.Turn_Left_90();
    while(robot.Get_R_Distance() < 10) {
        robot.Straight_Run();
    }
    robot.Turn_Left_90();
    robot.Straight_Run_cm(); // para entrar no corredor
    robot.Align(tolerance_Align);
    while(robot.Get_F_Distance() > 6) {
        robot.Straight_Run();
    } 
    robot.Turn_Left_90();
    while(robot.Get_L_Distance() < 40 && robot.Get_R_Distance() < 40) {
        robot.Straight_Run();
    } // chegou na zona central
    }
    

    // Procurar a porta correta:
    /*while(robot.Vision() != 'C'){
        if(robot.Get_F_Distance() < 10){
            robot.Turn_Angle(30);
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
        }
        if(robot.Get_L_Distance() < 10){
            robot.Turn_Angle(30);
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);  
        }
        if(robot.Get_F_Distance() < 30){
            robot.Turn_Angle(-30);
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
        }
        MOVE_UNTIL_DISTANCE(robot, tolerance_front);
        robot.Turn_right_90();
        while (robot.Get_L_Distance() <  40){
            robot.Straight_Run();
        }
        robot.Turn_Left_90();
    }
    // Forward logic TODO: Put here the function to the right case



/*
    // Main robot loop
    char receivedLetter = robot.Vision();
    switch (receivedLetter) {
    case 'A':
        break;
    case 'B':
        break;
    case 'C':
        while (robot.Get_F_Distance() > tolerance_front){
            robot.Align(tolerance_Align);
            robot.Straight_Run();
        }
        robot.Turn_Left_90();
        robot.Straight_Run_cm(110); // Aqui ele já deve estar dentro do caixa 1 / este valor deve ser testado
        robot.Turn_Left_90();
        int cubos = 0;
        while (cubos > 7){
            // pensar melhor sobre como pegar os cubos 
            // Pega o cubo
            while (cubo not in sight){
                robot.Straight_Run();
            }
            robot.Open_Claw(openPosition);
            robot.Straight_Run_cm(5);
            robot.Close_Claw(closedPosition);
            robot.Update_LED_CS(); //liga o led da cor do cubo
            robot.Straight_Back_cm(10); 
            robot.Turn_right_90();
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_right_90();
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_right_90();
            robot.Straight_Run_cm(150/2);
            robot.Turn_Left_90();
            // Entrega o cubo
            cubos++;
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_Left_90();
        }

        MOVE_UNTIL_DISTANCE(robot, tolerance_front);
        robot.Turn_right_90();
        robot.Straight_Run_cm(150/2);
        robot.Turn_Left_90();
        MOVE_UNTIL_DISTANCE(robot, tolerance_front);
        robot.Turn_Left_90();
        robot.Straight_Run_cm(150*2); //vai parar na porta do caso B
        break;


    case 'D':
        while (robot.Get_F_Distance() > tolerance_front){
            robot.Align(tolerance_Align);
            robot.Straight_Run();
        }
        robot.Turn_right_90();
        robot.Straight_Run_cm(110); // Aqui ele já deve estar dentro do caixa 1 / este valor deve ser testado
        robot.Turn_right_90();
        int cubos = 0;
        while (cubos > 7){
            // pensar melhor sobre como pegar os cubos 
            // Pega o cubo
            while (cubo not in sight){
                robot.Straight_Run();
            }
            claw.writeMicroseconds(openPosition);
            robot.Straight_Run_cm(5);
            claw.writeMicroseconds(closedPosition);
            robot.Update_LED_CS(); //liga o led da cor do cubo
            robot.Straight_Back_cm(10); 
            robot.Turn_Left_90();
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_Left_90();
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_Left_90();
            robot.Straight_Run_cm(150/2);
            robot.Turn_right_90();
            // Entrega o cubo
            cubos++;
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_right_90();
        }

        MOVE_UNTIL_DISTANCE(robot, tolerance_front);
        robot.Turn_Left_90();
        robot.Straight_Run_cm(150/2);
        robot.Turn_right_90();
        MOVE_UNTIL_DISTANCE(robot, tolerance_front);
        robot.Turn_right_90();
        robot.Straight_Run_cm(150*2); //vai parar na porta do caso A

        break;
    default:
        //stub
        break;
    }
    */
}   
