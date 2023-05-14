#include <Arduino.h>

void setup_k() {
    pinMode(13, OUTPUT);
    pinMode(5, OUTPUT);
}

void loop_k() {
    digitalWrite(13, HIGH);
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    delay(1000);
    digitalWrite(13, LOW);
    delay(2000);
}