#include <Adafruit_BNO055.h>
#include <Arduino.h>

class Gyro {
    public:
        Gyro();
        void calibrate();
        int getHeading();
        void setRefHeading();
        int getCorrection();
    private:
        Adafruit_BNO055 _bno;
        int refHeading;
        int _getRawHeading();
        int _integral;

        float P = 1.5;
        float I = 0.0;
};