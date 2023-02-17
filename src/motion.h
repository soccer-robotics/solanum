class Motion {
    public:
        Motion(int pins[4][2]);
        void move(int angle, double speed, int rot);
        int fast_sin(int angle);
        int fast_cos(int angle);
    private:
        int _pins[4][2];
        int _sin[91];
};