namespace constants
{
    // Pin numbers for motor drivers (CHANGE!!)
    const int MOTORPINS[4][2] = {
        {2, 3}, // topleft
        {4, 5}, // topright
        {6, 7}, // bottomright
        {8, 9}  // bottomleft
    };

    // SPI communication
    const int MISO = 12;
    const int MOSI = 11;
    const int SCK = 13; // CHANGE?

    // ADC pins for Infrared
    const int INFRA_CS[3] = {10, 36, 37};
    
    // ADC pins for Line Sensors
    const int LINE_CS[3] = {38, 39, 40}; // CHANGE!!

    // Pin number for solenoid (CHANGE!!)
    const int SOLENOIDPIN = 5;
}