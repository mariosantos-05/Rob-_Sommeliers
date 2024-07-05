#ifndef LED_H
#define LED_H


class LED{
private:
    int redPin;
    int greenPin;
    int bluePin;
public:
    LED(int r, int g, int b);
    void setColor(int red, int green, int blue);
    void turnOff();
};



#endif