#include <Adafruit_BNO055.h>
#include <Arduino.h>

class Gyro {
    public:
        Gyro();
        void calibrate();
        int getHeading();
        void setRefHeading();
    private:
        Adafruit_BNO055 _bno;
        int refHeading;
        int _getRawHeading();
};