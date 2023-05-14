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
    for (int i = 0; i < 24; i++) {
        _xcomp[i] = sin(i * PI / 12);
        _ycomp[i] = cos(i * PI / 12);
    }
}

std::pair<int, int> Line::getLine () {
    // read all 24 sensors
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            int val = _mcp[i].analogRead(j);
            _line[i*8+j] = val;
        }
    }

    // remove broken sensors 22/23
    _line[22] = (_line[21] + _line[0]) / 2;    
    _line[23] = (_line[21] + _line[0]) / 2;

    // print values
    Serial.print("line ");
    for (int i = 0; i < 24; i++) {
        Serial.print(_line[i]);
        for (int j = 0; j < 5-_len(_line[i]); j++) {
            Serial.print(" ");
        }
    }
    Serial.println();

    // get two sensors on the line that are furthest apart
    int a = -1;
    int b = -1;
    int opt = 0;
    for (int i=0; i<24; i++) {
        if (_line[i] < constants::LINE_THRESHOLD) {
            continue;
        }
        for (int j=i+1; j<24; j++) {
            if (_line[j] < constants::LINE_THRESHOLD) {
                continue;
            }
            int dist = min(abs(i-j), 24-abs(i-j));
            if (dist > opt) {
                opt = dist;
                a = i;
                b = j;
            }
        }
    }
    //Serial.println("l_est " + String(a) + " " + String(b));
    return std::make_pair(a, b);
}

std::pair<int, int> Line::getCorrectionVector() {
    return std::make_pair(0, 0); // NOT IMPLEMENTED
}

int Line::redirect(int angle) {
    // get line sensor data
    std::pair<int, int> line = getLine();
    if (line.first == -1 || line.second == -1) {
        _prev = -1;
        return angle;
    }

    // calculate line angle
    int diff = ( (line.first * 15 - line.second * 15 + 180 + 360 ) % 360 ) - 180;
    int l_angle = (360 + line.second * 15 + ( diff / 2 ) ) % 360;

    // if the line angle has flipped, we are crossing the line: initiate panic return
    int line_vector_change = (_prev - l_angle + 180) % 360 - 180;
    line_vector_change = line_vector_change < -180 ? line_vector_change + 360 : line_vector_change;
    line_vector_change = abs(line_vector_change);

    if (_prev != -1 &&
        line_vector_change > 160
    ) {
        return _prev;
    }
    else {
        _prev = l_angle;
    }
    
    // get two angles perpendicular (ish) to line
    int a1 = (l_angle + 90 + constants::LINE_SAFETY) % 360;
    int a2 = (l_angle - 90 - constants::LINE_SAFETY + 360) % 360;

    // is angle against the line?
    // angle is between a1 and l_angle, or between l_angle and a2 means it's towards the line
    int a_diff = ( (l_angle - angle + 180 + 360 ) % 360 ) - 180;
    if (a_diff <= 90 && a_diff >= -90) {
        // am I closer to a1 or a2?
        int a1_diff = min(abs(a1 - angle), 360 - abs(a1 - angle));
        int a2_diff = min(abs(a2 - angle), 360 - abs(a2 - angle));
        if (a1_diff < a2_diff) {
            return a1;
        }
        else {
            return a2;
        }
    }
    return angle;
}

int Line::_len(int num) {
    int len = 0;
    while (num > 0) {
        num /= 10;
        len++;
    }
    return len;
}