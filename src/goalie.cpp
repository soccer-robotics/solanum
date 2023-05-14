#include <goalie.h>
#include <Arduino.h>
#include <constants.hpp>

Goalie::Goalie() {
    _urgency = 3.0;
    _eagerness = 0;
    _restraint = 0;
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
    return min(255, max(-255,
        (int)(
            _urgency * angle
            + 200 * ((angle > 0) - (angle < 0)) // sign of angle
        )
    )); // simple for now
}