#include <SoftwareSerial.h>
#include <Arduino.h>

class Bluetooth {
    public:
        Bluetooth(int rx, int tx);
        void send(String data);
        String receive();
    private:
        int _rx;
        int _tx;
        SoftwareSerial* _bluetooth;
};