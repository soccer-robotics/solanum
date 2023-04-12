#include <MCP3XXX.h>

class Infra {
    public:
        Infra();
        int read();
    private:
        MCP3008 _mcp[3];
        int _xcomp[3][8];
        int _ycomp[3][8];
};