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
Goalie goalie;
//Bluetooth blue(7, 8);

// OPERATION MODES
// 0 = orbit
// 1 = goalie
// 2 = sensor test
// 3 = kicker test
// 4 = goal rotation
int mode = 0;

// do we use ultrasounds?
bool useUltra = 0;

bool switchState = 0;
int ballAngle;

int goalieForwardLineCounter = 0;
int ultraTickCounter = 0;
int orbitUltraOffset = 0;


void setup() {
    pinMode(constants::SWITCHPIN, INPUT);
    pinMode(13, OUTPUT);
    for (int i=0; i<4; i++) {
        pinMode(constants::MOTORPINS[i][0], OUTPUT);
        pinMode(constants::MOTORPINS[i][1], OUTPUT);
    }
    if (mode == 0 || mode == 1 || mode == 4) {
        gyro.calibrate();
    }
    // flash LED to indicate calibration
    for (int i=0; i<3; i++) {
        digitalWrite(13, HIGH);
        delay(200);
        digitalWrite(13, LOW);
        delay(200);
    }
    pinMode(22, INPUT);
    pinMode(5, OUTPUT);
}

void loop_motorTest() {
    // Test each motor in turn
    for (int i=0; i<4; i++) {
        digitalWrite(constants::MOTORPINS[i][0], 1);
        analogWrite(constants::MOTORPINS[i][1], 200);
        delay(1000);
        digitalWrite(constants::MOTORPINS[i][0], 0);
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
    motion.move(line.redirect(ballAngle), 255, -rot);
    //Serial.println(ballAngle);
    delay(1);
    //ultra.debug();
}

void loop_sens() {
    //infra.read();
    gyro.getHeading();
    line.getLine();
    Serial.println("gate " + String(analogRead(constants::LIGHTGATE)));
    delay(100);
}

void loop_goalRotate() {
    if (analogRead(constants::LIGHTGATE) > 200) {
        return;
    }

    // get four ultrasound readings
    int r = ultra.read(0);
    delay(50);
    int l = ultra.read(2);
    delay(50);
    int f = ultra.read(1);
    delay(50);
    int b = ultra.read(3);

    // calculate expected position
    int x_l = l;
    int x_r = constants::FIELD_WIDTH - r;
    int y_f = f;
    int y_b = constants::FIELD_HEIGHT - b;

    int x = (x_l + x_r) / 2;
    int y = (y_f + y_b) / 2;

    // calculate angle to goal
    // goal is at (FIELD_WIDTH/2, 0)
    // two cases: x < FIELD_WIDTH/2 and x > FIELD_WIDTH/2
    int ang;
    if (x < constants::FIELD_WIDTH/2) {
        ang = atan2(y, constants::FIELD_WIDTH/2 - x) * 180 / PI;
    }
    else {
        ang = 180 - atan2(y, x - constants::FIELD_WIDTH/2) * 180 / PI;
    }

    // calculate rotation
    int offset = 90 - ang;

    // rotate and move
    for (int i=0; i<150; i++) {
        int rot = gyro.getCorrection(1.5 * offset);
        motion.move(line.redirect(90), 255, -rot);

        std::pair<int, int> l = line.getLine();
        int diff = ( (l.first * 15 - l.second * 15 + 180 + 360 ) % 360 ) - 180;
        int l_angle = (360 + l.second * 15 + ( diff / 2 ) ) % 360;

        if (l_angle > 60 && l_angle < 120) {
            motion.move(270, 255, 0);
            digitalWrite(5, HIGH);
            delay(50);
            digitalWrite(5, LOW);
            for (int i=0; i<30; i++) {
                int rot = gyro.getCorrection();
                motion.move(270, 255, -rot);
                delay(5);
            }
            return;
        }
        delay(2);
    }

    // kick
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);

    /*
    // move back
    for (int i=0; i<100; i++) {
        int rot = gyro.getCorrection();
        motion.move(line.redirect(270), 255, -rot);
        delay(5);
    }
    motion.panic();
    */
}

void loop_orbit() {
    int rot = gyro.getCorrection();

    // track ball
    ballAngle = infra.read();
    int proximity = infra.distance();

    // get orbit
    int orbitAngle = orbit.getOrbit(ballAngle, proximity);

    if (useUltra) {
        loop_goalRotate();
    }

    orbitAngle = line.redirect(orbitAngle);

    // move
    motion.move(orbitAngle, 255, -rot);

    // kick
    /*if (orbit.readyToKick()) {
        digitalWrite(5, HIGH);
        delay(100);
        digitalWrite(5, LOW);
    }*/
    
    // back off, if line detected in front or back
    std::pair<int, int> l = line.getLine();
    int diff = ( (l.first * 15 - l.second * 15 + 180 + 360 ) % 360 ) - 180;
    int l_angle = (360 + l.second * 15 + ( diff / 2 ) ) % 360;

    if (l_angle > 60 && l_angle < 120) {
        for (int i=0; i<30; i++) {
            int rot = gyro.getCorrection();
            motion.move(270, 255, -rot);
            delay(10);
        }
    }
    else if (l_angle > 240 && l_angle < 300) {
        for (int i=0; i<30; i++) {
            int rot = gyro.getCorrection();
            motion.move(90, 255, -rot);
            delay(10);
        }
    }
    delay(2);
}

void loop_orbit2() {
    int rot = gyro.getCorrection();

    // track ball
    ballAngle = infra.read();
    int proximity = infra.distance();

    // get orbit
    int orbitAngle = orbit.getOrbit(ballAngle, proximity);

    /*
    // ultrasound
    if (analogRead(constants::LIGHTGATE) < 300) {
        if (ultraTickCounter == 0) {
            int r = ultra.read(0);
            delay(20);
            int l = ultra.read(2);
            if (r != -1 && l != -1) {
                if (r < l) {
                    orbitUltraOffset = min(60, (int) (20 * ((float) l) / r)); // offset to left
                }
                else {
                    orbitUltraOffset = - min(60, (int) (20 * ((float) r) / l)); // offset to right
                }
                motion.move(line.redirect(90 + orbitUltraOffset), 255, -rot);
                return;
            }
            else {
                orbitUltraOffset = 0;
            }
        }
        ultraTickCounter = (ultraTickCounter + 1) % 5;
    }
    else {
        orbitUltraOffset = 0;
    }
    */
    // line
    //orbitAngle = line.redirect(
    //    (orbitAngle + orbitUltraOffset + 360) % 360
    //);
    orbitAngle = line.redirect(orbitAngle);

    // move
    motion.move(orbitAngle, 255, -rot);
    
    // back off, if line detected in front or back
    std::pair<int, int> l = line.getLine();
    int diff = ( (l.first * 15 - l.second * 15 + 180 + 360 ) % 360 ) - 180;
    int l_angle = (360 + l.second * 15 + ( diff / 2 ) ) % 360;

    if (l_angle > 60 && l_angle < 120) {
        for (int i=0; i<30; i++) {
            int rot = gyro.getCorrection();
            motion.move(270, 255, -rot);
            delay(10);
        }
    }
    else if (l_angle > 240 && l_angle < 300) {
        for (int i=0; i<30; i++) {
            int rot = gyro.getCorrection();
            motion.move(90, 255, -rot);
            delay(10);
        }
    }
    delay(2);
}

void loop_ultra() {
    if (ultraTickCounter == 0) {
        int r = ultra.read(0);
        delay(50);
        int l = ultra.read(2);
        delay(50);
        int b = ultra.read(3);
        delay(50);
        int dirVal = b > 37 ? 120 : 60; // backwards if too far from wall, else forwards
        if (r != -1 && l != -1) {
            if (r < l) {
                orbitUltraOffset = dirVal; // offset to left
            }
            else {
                orbitUltraOffset = -dirVal; // offset to right
            }
        }
    }
    ultraTickCounter = (ultraTickCounter + 1) % 5;

    int rot = gyro.getCorrection();
    motion.move(90 + orbitUltraOffset, 200, -rot);

    delay(30);
}

void loop_goalie() {
    int rot = gyro.getCorrection();

    // track ball
    ballAngle = infra.read();
    int proximity = infra.distance();

    // get goalie direction/power
    int goaliePwr = goalie.getPower(ballAngle, proximity);
    //Serial.println("goaliePwr: " + String(goaliePwr));

    // correct y-position (set offset)
    int offset = 0;
    std::pair<int, int> l = line.getLine();
    if (l.first == -1) {
        if (goalieForwardLineCounter < 50) {
            goalieForwardLineCounter++;
            offset = -30; // forwards
        }
        else {
            offset = 30; // backwards
        }
        // ultrasound centering
        loop_ultra();
        return;
    }
    else {
        goalieForwardLineCounter = 0;
        int diff = ( (l.first * 15 - l.second * 15 + 180 + 360 ) % 360 ) - 180;
        int l_angle = (360 + l.second * 15 + ( diff / 2 ) ) % 360;
        // convert to azimuth
        int a = (360 + l_angle - 90) % 360;
        if (a > 180) {
            a -= 360;
        }

        /* ---- failed line edge detection ----
        a = -a;
        if (a < -45 && a > -135) {
            for (int i=0; i<30; i++) {
                int rot = gyro.getCorrection();
                motion.move(180, 230, -rot); // left
                delay(2);
            }
            offset = -45;
        }
        else if (a > 45 && a < 135) {
            for (int i=0; i<30; i++) {
                int rot = gyro.getCorrection();
                motion.move(0, 230, -rot); // right
                delay(2);
            }
            offset = -45;
        }
        */

        if (abs(a) < 45) {
            offset = -20; // forwards
        }
        else {
            offset = 20; // backwards
        }

        int b = ultra.read(3);
        if (b < 35) {
            offset = -20; // forwards
        }
        else if (b > 40) {
            offset = 20; // backwards
        }

        /*
            edge algorithm:
            partition line sensor circle into left and right half
            if both sensors on line are in the same half, then move in that direction
            otherwise:
                calculate how far each sensor is from the forward vector
                if the left sensor is much closer than the right sensor, then move left
                if the right sensor is much closer than the left sensor, then move right
        */

        int j = (24 + l.first - 24 / 4) % 24;
        int k = (24 + l.second - 24 / 4) % 24;

        if (j > 12) {
            j -= 24;
        }
        if (k > 12) {
            k -= 24;
        }

        // check sign
        if (j < 0 && k < 0) {
            // both on right
            for (int i=0; i<30; i++) {
                int rot = gyro.getCorrection();
                motion.move(30, 160, -rot); // right
                delay(2);
            }
        }
        else if (j > 0 && k > 0) {
            // both on left
            for (int i=0; i<30; i++) {
                int rot = gyro.getCorrection();
                motion.move(150, 160, -rot); // left
                delay(2);
            }
        }
        else {
            // one on left, one on right
            if (abs(j) > abs(k) + 6) {
                // left closer
                for (int i=0; i<30; i++) {
                    int rot = gyro.getCorrection();
                    motion.move(180, 160, -rot); // left
                    delay(2);
                }
            }
            else if (abs(k) > abs(j) + 6) {
                // right closer
                for (int i=0; i<30; i++) {
                    int rot = gyro.getCorrection();
                    motion.move(0, 160, -rot); // right
                    delay(2);
                }
            }
        }
    }

    // move
    if (goaliePwr > 0) {
        //int a = line.redirect(180 + offset);
        motion.move(180 + offset, goaliePwr, -rot);
    }
    else {
        //int a = line.redirect(0 - offset);
        motion.move(0 - offset, -goaliePwr, -rot);
    }

    delay(10);
    /*if (proximity > 700) {
        loop_orbit();
    }*/
    
    if (analogRead(22) < 300 || infra.getReading(5) > 700) { // lightgate or proximity
        for (int i=0; i<40; i++) {
            int rot = gyro.getCorrection();
            motion.move(90, 255, -rot);
            delay(5);
        }
        
        // kick
        digitalWrite(5, HIGH); // fire kicker
        delay(100);
        digitalWrite(5, LOW);
        delay(200);

        // back off
        while (line.getLine().first == -1) {
            int rot = gyro.getCorrection();
            motion.move(270, 255, -rot);
            delay(5);
        }
        /*
        digitalWrite(5, HIGH); // fire kicker
        delay(100);
        digitalWrite(5, LOW);
        delay(200);*/
        //mode = 0;
        //blue.send("sw");
    }
}

void loop_testDip() {
    Serial.print("dip ");
    Serial.print(digitalRead(34));
    Serial.print(" ");
    Serial.print(digitalRead(35));
    Serial.print(" ");
    Serial.print(digitalRead(30));
    Serial.print(" ");
    Serial.println(digitalRead(31));
    delay(100);
}

void loop_kick() {
    digitalWrite(13, HIGH);
    digitalWrite(5, HIGH);
    delay(200);
    digitalWrite(5, LOW);
    delay(1000);
    digitalWrite(13, LOW);
    delay(4000);
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
        /* == Unused Bluetooth Code ==
        if (mode == 0) {
            loop_orbit();
            String a = blue.receive();
            if (a != "sw") {
                mode = 1;
            }
        }
        else if (mode == 1) {
            loop_goalie();
        }*/
        
        if (mode == 0) {
            loop_orbit();
        }
        else if (mode == 1) {
            loop_goalie();
        }
        else if (mode == 2) {
            loop_sens();
        }
        else if (mode == 3) {
            loop_kick();
        }
        else if (mode == 4) {
            loop_goalRotate();
        }

        //loop_motorTest();
        
        /*infra.read();
        infra.distance();
        delay(10);*/
        //Serial.println(analogRead(22));
        //loop_sens();
        //ultra.debug();
        //loop_testDip();
    }
    // When switch is off:
    else if (switchState == 0) {
        motion.panic();
    }
}