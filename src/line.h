#include <utility>
#include <MCP3XXX.h>

class Line {
    public:
        Line();
        std::pair<int, int> getLine(); // indices of the two sensors that are on the line
        std::pair<int, int> getCorrectionVector(); // get direction and magnitude of correction motion to avoid line
    private:
        MCP3008 _mcp[3];
        int _xcomp[3][8];
        int _ycomp[3][8];
};