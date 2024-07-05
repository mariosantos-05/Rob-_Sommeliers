#include "LED.h"
#include <Arduino.h>

LED::LED(int r, int g, int b) : redPin(r), greenPin(g), bluePin(b) {
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
    turnOff(); // Garante que o LED esteja desligado ao inicializar
}

void LED::setColor(int red, int green, int blue) {
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);
}

void LED::turnOff() {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
}