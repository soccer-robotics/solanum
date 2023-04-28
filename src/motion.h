class Motion {
    public:
        Motion();
        void move(int angle, double speed, int rot);
        void panic();
        float fast_sin(int angle);
        float fast_cos(int angle);
    private:
        int _pins[4][2];
        float _sin[91];
};