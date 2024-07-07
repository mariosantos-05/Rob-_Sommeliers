#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <Arduino.h>

class ColorSensor {
private:
    uint8_t redPin;
    uint8_t greenPin;
    uint8_t bluePin;
    uint8_t s0Pin;
    uint8_t s1Pin;
    uint8_t s2Pin;
    uint8_t s3Pin;
    
    void setFrequency(uint8_t freq);

public:
    ColorSensor(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t red, uint8_t green, uint8_t blue);
    void begin();
    void readColor(int *red, int *green, int *blue);
};

#endif
