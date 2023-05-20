/*
Interface with BNO055 gyro and implement angle correction PID calculations
*/

#include <Adafruit_BNO055.h>
#include <Arduino.h>

class Gyro {
    public:
        Gyro();
        void calibrate();
        int getHeading();
        void setRefHeading();
        int getCorrection();
        int getCorrection(int offset);
    private:
        Adafruit_BNO055 _bno;
        int refHeading;
        int _getRawHeading();
        int _integral;

        float P = 1.9;
        float I = 0.01;
};