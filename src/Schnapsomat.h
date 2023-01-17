#ifndef Schnapsomat_h
#define Schnapsomat_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include "Packet.h"

class Schnapsomat {
    public:
        static const int BUFFER_SIZE = 64;
    private:
        HardwareSerial* SerialPort;
        Packet *buffer[BUFFER_SIZE];
        void send(Packet *packet);
        void ack();
    public:
        Schnapsomat();
        void begin(int  rx, int  tx);
        void loop();
        void dispenseIngredience(String ingredience, int amount);
};
#endif