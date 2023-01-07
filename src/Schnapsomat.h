#ifndef Schnapsomat_h
#define Schnapsomat_h

#include <Arduino.h>

class Schnapsomat {
    private:
        HardwareSerial* SerialPort;
        void send(String command);
    public:
        Schnapsomat();
        void begin(int  rx, int  tx);
        void dispenseIngredience(String ingredience, int amount);
};
#endif