/*
Get infrared sensor readings and calculate ball heading/distance
*/

#include <MCP3XXX.h>

class Infra {
    public:
        Infra();
        int read(); // returns angle of infrared vector
        int _len(int num); // number of digits in num
        int distance(); // estimated distance to ball
        int getReading(int num); // get reading of sensor num
    private:
        MCP3008 _mcp[3]; // 3 MCP3008 chips
        float _xcomp[24]; // precalculated cosine
        float _ycomp[24]; // precalculated sine
        int _ir[24];
};