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

Infra infra;
Gyro gyro;
Line line;
Motion motion;
Ultra ultra;
Orbit orbit;

bool switchState = 0;

int ballAngle;

void setup() {
    pinMode(constants::SWITCHPIN, INPUT);
    pinMode(13, OUTPUT);
    for (int i=0; i<4; i++) {
        pinMode(constants::MOTORPINS[i][0], OUTPUT);
        pinMode(constants::MOTORPINS[i][1], OUTPUT);
    }
    //gyro.calibrate();
    // flash LED to indicate calibration
    for (int i=0; i<3; i++) {
        digitalWrite(13, HIGH);
        delay(200);
        digitalWrite(13, LOW);
        delay(200);
    }
}

void loop_motorTest() {
    // Test each motor in turn
    for (int i=0; i<4; i++) {
        digitalWrite(constants::MOTORPINS[i][0], 1);
        analogWrite(constants::MOTORPINS[i][1], 200);
        delay(1000);
        analogWrite(constants::MOTORPINS[i][1], 0);
    }
    /*for (int i=0; i<360; i+=45) {
        motion.move(i, 200, 0);
        delay(1000);        
    }*/
}

void loop_motorGyroTest() {
    for (int i=0; i<360; i+=45) {
        for (int j=0; j<100; j++) {
            int ang = gyro.getHeading();
            // simple proportional control
            if (ang > 180) {
                ang -= 360;
            }
            int rot = ang * 1.5;
            motion.move(i, 200, -rot);
            delay(10);
        }
    }
}

void loop_ballTrack() {
    int ang = gyro.getHeading();
    // simple proportional control
    if (ang > 180) {
        ang -= 360;
    }
    int rot = ang * 1.5;

    // track ball
    ballAngle = infra.read();
    motion.move(ballAngle, 255, -rot);
    //Serial.println(ballAngle);
    delay(1);
    //ultra.debug();
}

void loop_orbit() {
    int ang = gyro.getHeading();

    // simple proportional control
    if (ang > 180) {
        ang -= 360;
    }
    int rot = ang * 1.5;

    // track ball
    ballAngle = infra.read();

    // get orbit
    int orbitAngle = orbit.getOrbit(ballAngle);

    // line
    orbitAngle = line.redirect(orbitAngle);

    // move
    motion.move(orbitAngle, 200, -rot);
    delay(1);
}

void loop() {
    // When switch is turned on:
    if (digitalRead(constants::SWITCHPIN) == HIGH && switchState == 0) {
        switchState = 1;
        digitalWrite(13, HIGH);
        // set gyro reference heading
        gyro.setRefHeading();
    }
    // When switch is turned off:
    else if (digitalRead(constants::SWITCHPIN) == LOW && switchState == 1) {
        switchState = 0;
        digitalWrite(13, LOW);
    }
    // When switch is on:
    else if (switchState == 1) {
        line.getLine();
        delay(50);
    }
    // When switch is off:
    else if (switchState == 0) {
        motion.panic();
    }
}