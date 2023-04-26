class Motion {
    public:
        Motion();
        void move(int angle, double speed, int rot);
        void panic();
        int fast_sin(int angle);
        int fast_cos(int angle);
    private:
        int _pins[4][2];
        int _sin[91];
};