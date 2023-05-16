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
        _xcomp[i] = cos((i+1) * PI / 12);
        _ycomp[i] = sin((i+1) * PI / 12);
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

    // bandage failed sensor 14
    // _ir[13] = (_ir[15] + _ir[11]) / 2;
    // _ir[12] = (_ir[11] + _ir[14]) / 2;
    // _ir[13] = (_ir[11] + _ir[14]) / 2;

    // simulate values for every other sensor (since not soldered yet)
    /*_ir[0] = (_ir[1] + _ir[23]) / 2;
    for (int i=2; i<24; i+=2) {
        _ir[i] = (_ir[i+1] + _ir[i-1]) / 2;
    }*/

    // auto-detect failed sensors and set them to average of neighbors
    for (int i=0; i<24; i++) {
        if (_ir[i] == 1024 || _ir[i] == 1023) {
            _ir[i] = (_ir[(i + 1) % 24] + _ir[(i + 23) % 24]) / 2;
        }
    }

    // bandage #22
    _ir[22] = (_ir[21] + _ir[23]) / 2;

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

int Infra::distance() {
    // rough estimate of distance to ball by averaging all sensors
    int sum = 0;
    for (int i=0; i<24; i++) {
        sum += _ir[i];
    }
    Serial.print("dist ");
    Serial.println(sum / 24);
    return sum / 24;
}

int Infra::_len(int num) {
    // internal function to get number of digits in num (for pretty printing)
    int len = 0;
    while (num > 0) {
        num /= 10;
        len++;
    }
    return len;
}