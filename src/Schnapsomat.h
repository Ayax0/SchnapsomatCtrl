#ifndef Schnapsomat_h
#define Schnapsomat_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Packet.h"

class Schnapsomat {
    private:
        HardwareSerial* SerialPort;
        Packet* packet_buffer;
        void send(String command);
    public:
        Schnapsomat();
        void begin(int  rx, int  tx);
        void loop();
        void dispenseIngredience(String ingredience, int amount);
};
#endif