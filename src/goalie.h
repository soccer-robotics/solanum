class Goalie {
    public:
        Goalie();
        int getAngle(int angle, int proximity);
    private:
        int _urgency; // proportional control
        int _eagerness; // integral control
        int _restraint; // derivative control
        bool orbitMode;
        int _modeTimer;
};