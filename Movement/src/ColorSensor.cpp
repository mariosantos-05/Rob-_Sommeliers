#include "ColorSensor.h"
#include <Arduino.h>

ColorSensor::ColorSensor()
    : tcs(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X) {}

bool ColorSensor::begin() {
    return tcs.begin();
}

void ColorSensor::readColor(int *red, int *green, int *blue) {
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);

    // Normalização das leituras de cor
    *red = r;
    *green = g;
    *blue = b;
}
