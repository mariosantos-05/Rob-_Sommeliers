#include "ColorSensor.h"

ColorSensor::ColorSensor(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t red, uint8_t green, uint8_t blue)
    : s0Pin(s0), s1Pin(s1), s2Pin(s2), s3Pin(s3), redPin(red), greenPin(green), bluePin(blue) {}

void ColorSensor::begin() {
    pinMode(s0Pin, OUTPUT);
    pinMode(s1Pin, OUTPUT);
    pinMode(s2Pin, OUTPUT);
    pinMode(s3Pin, OUTPUT);
    pinMode(redPin, INPUT);
    pinMode(greenPin, INPUT);
    pinMode(bluePin, INPUT);
    
    // Set frequency to 20% for high sensitivity (change as needed)
    setFrequency(2);
}

void ColorSensor::setFrequency(uint8_t freq) {
    digitalWrite(s0Pin, freq & 0x01);
    digitalWrite(s1Pin, (freq >> 1) & 0x01);
}

void ColorSensor::readColor(int *red, int *green, int *blue) {
    *red = pulseIn(redPin, LOW);
    *green = pulseIn(greenPin, LOW);
    *blue = pulseIn(bluePin, LOW);
}
