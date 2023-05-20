/*
Program constants (pin numbers, thresholds, etc.)
*/

namespace constants
{
    // Pin numbers for motor drivers
    const int MOTORPINS[4][2] = { // [dir, pwm]
        {6, 23}, // topleft
        {9, 2}, // topright
        {3, 24}, // bottomright
        {4, 29}  // bottomleft
    };

    // SPI communication
    const int MISO = 12;
    const int MOSI = 11;
    const int SCK = 13;

    // ADC pins for Infrared
    const int INFRA_CS[3] = {37, 36, 10}; //{10, 36, 37};
    
    // ADC pins for Line Sensors
    const int LINE_CS[3] = {26, 28, 27};

    // Threshold for line sensors
    const int LINE_THRESHOLD = 500;

    // Safety angle for line (how much angular offset when clamping)
    const int LINE_SAFETY = 20;

    // Trigger and echo pins for ultrasonic
    const int ULTRA_TRIG[4] = {14, 15, 16, 17};
    const int ULTRA_ECHO = 20;

    // Pin number for solenoid
    const int SOLENOIDPIN = 5;

    // Light gate pin
    const int LIGHTGATE = 22;

    // Software switch
    const int SWITCHPIN = 32;

    // Field dimensions
    const int FIELD_WIDTH = 182;
    const int FIELD_HEIGHT = 243;
}