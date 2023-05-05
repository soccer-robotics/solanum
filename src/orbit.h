class Orbit {
    public:
        Orbit();
        int getOrbit(int angle, int proximity);
    private:
        int _tuneAngle;
        int _tuneScale;
        float _aggressiveness;
        float _multiplier;
        int _distscl;
        // formula: min(aggressiveness * e^(multiplier * angle), 90)
};