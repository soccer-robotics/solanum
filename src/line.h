#include <utility>
#include <MCP3XXX.h>

class Line {
    public:
        Line();
        std::pair<int, int> getLine(); // indices of the two sensors that are on the line
        std::pair<int, int> getCorrectionVector(); // get direction and magnitude of correction motion to avoid line
        int redirect(int angle); // get angle of correction motion to avoid line
    private:
        MCP3008 _mcp[3];
        float _xcomp[24];
        float _ycomp[24];
        int _line[24];
        int _len(int num);
};