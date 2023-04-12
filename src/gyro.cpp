#include <gyro.h>
#include <Arduino.h>

Gyro::Gyro() {
    _bno = Adafruit_BNO055(55);
    if(!_bno.begin())
    {
        Serial.println("ERROR No BNO055 detected!");
    }
    _bno.setExtCrystalUse(true);
}

void Gyro::calibrate() {
    uint8_t system, gyro, accel, mag;
    while (system != 3) {
        Serial.println("gyro_calibration " + String(system) + " " + String(gyro) + " " + String(accel) + " " + String(mag));
        _bno.getCalibration(&system, &gyro, &accel, &mag);
        delay(500);
    }
}

int Gyro::_getRawHeading() {
    sensors_event_t event;
    _bno.getEvent(&event);
    return event.orientation.roll;
}

void Gyro::setRefHeading() {
    refHeading = _getRawHeading();
}

int Gyro::getHeading() {
    int h = (_getRawHeading() - refHeading + 360) % 360;
    Serial.println("gyro " + String(h));
    return h;
}