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
        bool ready = false;
        void send(Packet *packet);
        void ack();
        void nack();
    public:
        Schnapsomat(int  rx, int  tx);
        void loop();
        void dispenseIngredience(String ingredience, int amount);
};
#endif