#include <orbit.h>
#include <math.h>
#include <constants.hpp>
#include <Arduino.h>

Orbit::Orbit() {
    _aggressiveness = 0.04;
    _multiplier = 0.15;
    _distscl = 80;
    _tuneAngle = 0;
    _tuneScale = 0;
    forwardCtr = 0;
}

int Orbit::getOrbit(int angle, int proximity) {
    angle -= 90;
    // normalize to -180 to 180
    angle = (angle + 360) % 360;
    if (angle > 180) {
        angle -= 360;
    }
    // calculate orbit
    //proximity = _distscl;
    float damp = min(1.0, 0.02 * exp(5.5 * proximity));
    float offset = 0;
    int ret;
    if (angle > 0) {
        offset = min(_aggressiveness * exp(_multiplier * angle), 90.0);
        ret = (int)(angle + offset * damp + 90 + 360) % 360;
    }
    else {
        offset = min(_aggressiveness * exp(-_multiplier * angle), 90.0);
        ret = (int)(angle - offset * damp + 90 + 360) % 360;
    }
    // test if angle is forward
    if (abs(ret - 90) < 20) {
        forwardCtr++;
    }
    else {
        forwardCtr = 0;
    }
    return ret;
}

bool Orbit::readyToKick() {
    return forwardCtr > 80;
}