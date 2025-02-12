#include <motion.h>
#include <constants.hpp>
#include <Arduino.h>

Motion::Motion() {
    // lookup table for sin() values (0-90 degrees)
    for (int i = 0; i < 91; i++) {
        _sin[i] = sin(i * PI / 180) * 255;
    }
    for (int i=0; i<4; i++) {
        for (int j=0; j<2; j++) {
            _pins[i][j] = constants::MOTORPINS[i][j];
        }
    }
}

float Motion::fast_sin(int angle) {
    // normalize angle to 0-360 degrees
    angle = ((angle % 360) + 360) % 360;

    // return sin value
    if (angle < 90)
        return _sin[angle];
    else if (angle < 180)
        return _sin[180 - angle];
    else if (angle < 270)
        return -_sin[angle - 180];
    else
        return -_sin[360 - angle];
}

float Motion::fast_cos(int angle) {
    return fast_sin(angle + 90);
}

void Motion::move(int angle, double speed, int rot) {
    // tilt reference frame so top left is 0 degrees
    int y = fast_cos(angle - 40) * speed;
    int x = fast_cos(angle + 40) * speed;

    // normalize
    int max = abs(x + rot);
    if (abs(y+rot) > max) {
        max = abs(y + rot);
    }
    x = x * speed / max;
    y = y * speed / max;

    // set topleft
    digitalWrite(_pins[0][0], (y + rot) > 0);
    analogWrite(_pins[0][1], min(255, abs(y + rot)));

    // set topright
    digitalWrite(_pins[1][0], (x + rot) > 0);
    analogWrite(_pins[1][1], min(255, abs(x + rot)));

    // set bottomright
    digitalWrite(_pins[2][0], (-y + rot) > 0);
    analogWrite(_pins[2][1], min(255, abs(-y + rot)));

    // set bottomleft
    digitalWrite(_pins[3][0], (-x + rot) > 0);
    analogWrite(_pins[3][1], min(255, abs(-x + rot)));
}

void Motion::panic() {
    for (int i=0; i<4; i++) {
        digitalWrite(_pins[i][0], 0);
        analogWrite(_pins[i][1], 0);
    }
}