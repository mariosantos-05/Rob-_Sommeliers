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
const int sensorFrontEcho = A0;
const int redLEDPin = A1;
const int greenLEDPin = A2;
const int blueLEDPin = A3; 

// Criando os objetos referente as partes
MotorDC motorLeft(motorLeftPin1, motorLeftPin2, motorLeftEn);
MotorDC motorRight(motorRightPin1, motorRightPin2, motorRightEn);
Sensor sensorLeft(sensorLeftTrig, sensorLeftEcho);
Sensor sensorRight(sensorRightTrig, sensorRightEcho);
Sensor sensorFront(sensorFrontTrig, sensorFrontEcho);
Servo claw;
ColorSensor colorSensor(0, 1, 2, 3, 2, 3, 4); 
LED led(redLEDPin, greenLEDPin, blueLEDPin);

// Construtor do robo
Robot robot(motorLeft, motorRight, claw, sensorLeft, sensorRight, sensorFront, colorSensor, led);

void setup() {
    claw.attach(clawPin);
    // Inicializando componentes se necessario
}

// Definindo Macros para navegação
#define MOVE_UNTIL_DISTANCE(robot, tolerance_front) while ((robot).Get_F_Distance() > (tolerance_front)) { (robot).Straight_Run(); }

// Definindo variaveis que devem ser refinadas antes da partida:

float tolerance_front = 0.0;
float tolerance_Align = 0.0;
int openPosition = 0;   
int closedPosition = 90;  


// Estrategia principal de navegação do robô (quase um pseudodigo por enquanto!)

void loop() {
    // Main robot loop
    /*char receivedLetter = robot.Vision();
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
        robot.Turn_Left();
        robot.Straight_Run_cm(110); // Aqui ele já deve estar dentro do caixa 1 / este valor deve ser testado
        robot.Turn_Left();
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
            robot.Straight_Back(10); //TODO: FAZER UM METODO RUN BACK EM CM
            robot.Turn_right();
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_right();
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_right();
            robot.Straight_Run_cm(150/2);
            robot.Turn_Left();
            // Entrega o cubo
            cubos++;
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_Left();
        }

        MOVE_UNTIL_DISTANCE(robot, tolerance_front);
        robot.Turn_right();
        robot.Straight_Run_cm(150/2);
        robot.Turn_Left();
        MOVE_UNTIL_DISTANCE(robot, tolerance_front);
        robot.Turn_Left();
        robot.Straight_Run_cm(150*2); //vai parar na porta do caso B
        break;


    case 'D':
        while (robot.Get_F_Distance() > tolerance_front){
            robot.Align(tolerance_Align);
            robot.Straight_Run();
        }
        robot.Turn_right();
        robot.Straight_Run_cm(110); // Aqui ele já deve estar dentro do caixa 1 / este valor deve ser testado
        robot.Turn_right();
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
            robot.Straight_Back(10); //TODO: FAZER UM METODO RUN BACK EM CM
            robot.Turn_Left();
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_Left();
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_Left();
            robot.Straight_Run_cm(150/2);
            robot.Turn_right();
            // Entrega o cubo
            cubos++;
            MOVE_UNTIL_DISTANCE(robot, tolerance_front);
            robot.Turn_right();
        }

        MOVE_UNTIL_DISTANCE(robot, tolerance_front);
        robot.Turn_Left();
        robot.Straight_Run_cm(150/2);
        robot.Turn_right();
        MOVE_UNTIL_DISTANCE(robot, tolerance_front);
        robot.Turn_right();
        robot.Straight_Run_cm(150*2); //vai parar na porta do caso A

        break;
    default:
        //stub
        break;
    }*/
}   
