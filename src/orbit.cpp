#include <orbit.h>
#include <math.h>
#include <constants.hpp>
#include <Arduino.h>

Orbit::Orbit() {
    _aggressiveness = 0.04;
    _multiplier = 0.15;
    _tuneAngle = 0;
    _tuneScale = 0;
}

int Orbit::getOrbit(int angle) {
    angle -= 90;
    // normalize to -180 to 180
    angle = (angle + 360) % 360;
    if (angle > 180) {
        angle -= 360;
    }
    // calculate orbit
    float offset = 0;
    if (angle > 0) {
        offset = min(_aggressiveness * exp(_multiplier * angle), 90.0);
        return (int)(angle + offset + 90) % 360;
    }
    else {
        offset = min(_aggressiveness * exp(-_multiplier * angle), 90.0);
        return (int)(angle - offset + 90) % 360;
    }
}