#include <line.h>
#include <constants.hpp>
#include <MCP3XXX.h>
#include <utility>
#include <Arduino.h>

Line::Line() {
    for (int i = 0; i < 3; i++) {
        _mcp[i].begin(
            constants::LINE_CS[i],
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

std::pair<int, int> Line::getLine () {
    // read all 24 sensors
    Serial.print("line ");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            int val = _mcp[i].analogRead(j);
            Serial.print(val);
            for (int j = 0; j < 5-_len(val); j++) {
                Serial.print(" ");
            }
            _line[i*8+j] = val;
        }
    }
    Serial.println();

    // get two sensors that are on the line
    int max = 0;
    int max2 = 0;
    int maxIndex = 0;
    int max2Index = 0;
    for (int i = 0; i < 24; i++) {
        if (_line[i] > max) {
            max2 = max;
            max2Index = maxIndex;
            max = _line[i];
            maxIndex = i;
        } else if (_line[i] > max2) {
            max2 = _line[i];
            max2Index = i;
        }
    }

    return std::make_pair(maxIndex, max2Index);
}

std::pair<int, int> Line::getCorrectionVector() {
    return std::make_pair(0, 0); // NOT IMPLEMENTED
}

int Line::_len(int num) {
    int len = 0;
    while (num > 0) {
        num /= 10;
        len++;
    }
    return len;
}