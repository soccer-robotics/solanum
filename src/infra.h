#include <MCP3XXX.h>

class Infra {
    public:
        Infra();
        int read(); // returns angle of infrared vector
        int _len(int num); // number of digits in num
    private:
        MCP3008 _mcp[3]; // 3 MCP3008 chips
        float _xcomp[24]; // precalculated cosine
        float _ycomp[24]; // precalculated sine
        int _ir[24];
};