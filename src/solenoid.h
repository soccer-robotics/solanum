class solenoid {
    public:
        solenoid(int pin);
        void fire();
    private:
        int _pin;
        int _lastFire;
};