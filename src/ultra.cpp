#include <ultra.h>
#include <Arduino.h>
#include <constants.hpp>

Ultra::Ultra() {
    for (int i=0; i<4; i++) {
        pinMode(constants::ULTRA_TRIG[i], OUTPUT);
    }
    pinMode(constants::ULTRA_ECHO, INPUT);
}

int Ultra::read(int idx) {
    // fire trigger pulse
    digitalWrite(constants::ULTRA_TRIG[idx], LOW);
    delayMicroseconds(2);
    digitalWrite(constants::ULTRA_TRIG[idx], HIGH);
    delayMicroseconds(10);
    digitalWrite(constants::ULTRA_TRIG[idx], LOW);
    
    // read echo
    int duration = pulseIn(constants::ULTRA_ECHO, HIGH);//, 15550);
    int distance = (duration/2) / 29.1;
    if (distance >= 250 || distance <= 0){
        return -1; // out of range or error
    }
    else {
        return distance;
    }
}

void Ultra::debug() {
    Serial.print("Ultra ");
    for (int i=0; i<4; i++) {
        Serial.print(read(i));
        Serial.print(" ");
        //Serial.print(" -1 ");
        delay(50);
    }
    Serial.println();
}