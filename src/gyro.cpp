/*
Interface with BNO055 gyro and implement angle correction PID calculations
*/

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

int Gyro::getCorrection() {
    int h = getHeading();
    if (h > 180) {
        h -= 360;
    }
    int correction = P * h + I * _integral;
    _integral += h;
    Serial.println("gyro_correction " + String(correction));
    return correction;
}

int Gyro::getCorrection(int offset) {
    int h = getHeading();
    if (h > 180) {
        h -= 360;
    }
    int correction = 3 * P * (h - offset);
    Serial.println("gyro_correction " + String(correction));
    return correction;
}