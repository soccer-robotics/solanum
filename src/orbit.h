class Orbit {
    public:
        Orbit();
        int getOrbit(int angle);
    private:
        int _tuneAngle;
        int _tuneScale;
        float _aggressiveness;
        float _multiplier;
        // formula: min(aggressiveness * e^(multiplier * angle), 90)
};