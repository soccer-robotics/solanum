/*
Communication routines with HC-05 Bluetooth module
*/

#include <SoftwareSerial.h>
#include <Arduino.h>
#include <blue.h>

Bluetooth::Bluetooth(int rx, int tx) {
    _rx = rx;
    _tx = tx;
    _bluetooth = new SoftwareSerial(rx, tx);
    _bluetooth -> begin(38400);
}

String Bluetooth::receive() {
    String data = "";
    while (_bluetooth -> available()) {
        data += (char)_bluetooth -> read();
    }
    return data;
}

void Bluetooth::send(String data) {
    _bluetooth -> print(data);
}