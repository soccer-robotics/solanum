class Motion {
    public:
        Motion(int pins[4][2]);
        void move(int angle, int speed);
    private:
        int _pins[4][2];
};