class Goalie {
    public:
        Goalie();
        int getPower(int angle, int proximity);
    private:
        float _urgency; // proportional control
        float _eagerness; // integral control
        float _restraint; // derivative control
        bool orbitMode;
        int _modeTimer;
};