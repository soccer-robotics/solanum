#include <infra.h>
#include <constants.hpp>
#include <MCP3XXX.h>
#include <Arduino.h>

Infra::Infra() {
    for (int i = 0; i < 3; i++) {
        _mcp[i].begin(
            constants::INFRA_CS[i],
            constants::MOSI,
            constants::MISO,
            constants::SCK
        );
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            _xcomp[i][j] = sin((i * 8 + j) * PI / 12);
            _ycomp[i][j] = cos((i * 8 + j) * PI / 12);
        }
    }
}

int Infra::read() {
    // vector addition of all 24 sensors
    int x = 0;
    int y = 0;

    Serial.print("infra ");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            int val = 1024-_mcp[i].analogRead(j);
            Serial.print(val);
            Serial.print(" ");
            x += val * _xcomp[i][j];
            y += val * _ycomp[i][j];
        }
    }
    Serial.println();
    // return angle of vector
    return atan2(y, x) * 180 / PI;
}