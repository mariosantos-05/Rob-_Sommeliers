#ifndef COLORSENSOR_H
#define COLORSENSOR_H


#include <Wire.h>
//#include <Adafruit_TCS34725.h> //mudar para o sensor de fato

class ColorSensor {
private:
    Adafruit_TCS34725 tcs;

public:
    ColorSensor();
    bool begin();
    void readColor(int *red, int *green, int *blue);
};

#endif