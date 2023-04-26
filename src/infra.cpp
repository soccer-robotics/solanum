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
    for (int i = 0; i < 24; i++) {
        _xcomp[i] = sin((i+1) * PI / 12);
        _ycomp[i] = cos((i+1) * PI / 12);
    }
}

int Infra::read() {
    Serial.print("infra ");

    // read all 24 sensors
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            int val = 1024-_mcp[i].analogRead(j);
            //val = val * 50 / constants::INFRA_SCL[i*8+j];
            _ir[i*8+j] = val;
        }
    }

    // bandage failed sensors 20, 12, 13
    // _ir[20] = (_ir[19] + _ir[21]) / 2;
    // _ir[12] = (_ir[11] + _ir[14]) / 2;
    // _ir[13] = (_ir[11] + _ir[14]) / 2;

    // vector addition of all 24 sensors
    int x = 0;
    int y = 0;

    for (int i = 0; i < 24; i++) {
        Serial.print(_ir[i]);
        for (int j = 0; j < 5-_len(_ir[i]); j++) {
            Serial.print(" ");
        }
        x += _ir[i] * _xcomp[i];
        y += _ir[i] * _ycomp[i];
    }
    Serial.println();
    
    // return angle of vector
    return atan2(y, x) * 180 / PI;
}

int Infra::_len(int num) {
    int len = 0;
    while (num > 0) {
        num /= 10;
        len++;
    }
    return len;
}