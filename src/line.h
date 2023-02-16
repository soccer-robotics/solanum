#include <utility>

class Line {
    public:
        Line(int pins[3][3]);
        std::pair<int, int> getLine();
    private:
        int _pins[3][3];
};