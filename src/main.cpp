#include <Arduino.h>
#include <motion.h>
#include <solenoid.h>
#include <infra.h>
#include <gyro.h>
#include <line.h>
#include <ultra.h>
#include <cam.h>
#include <blue.h>
#include <orbit.h>
#include <goalie.h>
#include <constants.hpp>

void setup() {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);
}

void loop() {
    delay(1000);
}