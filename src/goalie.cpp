/*
Calculates the goalie movement power based on the angle and proximity of the ball.
*/

#include <goalie.h>
#include <Arduino.h>
#include <constants.hpp>

Goalie::Goalie() {
    _urgency = 5.0;
    _eagerness = 0;
}

int Goalie::getPower(int angle, int proximity) {
    // convert to azimuth
    angle -= 90;
    // normalize to -180 to 180
    angle = (angle + 360) % 360;
    if (angle > 180) {
        angle -= 360;
    }
    // move horizontally
    int res = min(255, max(-255,
        (int)(
            _urgency * angle * min(1.0, 0.02 * exp(4.5 * (float) proximity / 60)) + 
            _eagerness * abs(angle - prevAngle)
            //+ 150 * ((angle > 0) - (angle < 0)) // sign of angle
        )
    )); 
    prevAngle = angle;
    return res;
}