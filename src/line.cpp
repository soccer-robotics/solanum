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

}

std::pair<int, int> Line::getCorrectionVector() {
    
}