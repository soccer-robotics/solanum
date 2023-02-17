#include <motion.h>
#include <Arduino.h>

Motion::Motion(int pins[4][2]) {
    // lookup table for sin() values (0-90 degrees)
    for (int i = 0; i < 91; i++) {
        _sin[i] = sin(i * PI / 180) * 255;
    }
}

int Motion::fast_sin(int angle) {
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

int Motion::fast_cos(int angle) {
    return fast_sin(angle + 90);
}

void Motion::move(int angle, double speed, int rot) {
    /*
    speed is the magnitude of the vector (0-1);
    this ensures that the "speed" value will
    always be the same, regardless of the angle
    */

    // tilt reference frame so top left is 0 degrees
    int y = fast_sin(angle + 45) * speed;
    int x = fast_cos(angle + 45) * speed;

    // set topleft
    analogWrite(_pins[0][0], y + rot > 0);
    analogWrite(_pins[0][1], abs(y + rot));

    // set topright
    analogWrite(_pins[1][0], x + rot > 0);
    analogWrite(_pins[1][1], abs(x + rot));

    // set bottomright
    analogWrite(_pins[2][0], -y + rot > 0);
    analogWrite(_pins[2][1], abs(-y + rot));

    // set bottomleft
    analogWrite(_pins[3][0], -x + rot > 0);
    analogWrite(_pins[3][1], abs(-x + rot));
}