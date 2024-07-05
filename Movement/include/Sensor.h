#ifndef SENSOR_H
#define SENSOR_H

class Sensor{
private:
    int trigPin;
    int echoPin;
public:
    Sensor(int trig, int echo);
    long getDistance();
};

            
#endif