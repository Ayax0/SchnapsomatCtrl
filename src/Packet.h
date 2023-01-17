#ifndef Packet_h
#define Packet_h

#define PACKET_ACK 0x00
#define PACKET_NACK 0x01
#define PACKET_OK 0x10
#define PACKET_NOK 0x11
#define PACKET_CMD 0x20
#define PACKET_DATA 0x21

#include <Arduino.h>
#include <ArduinoJson.h>

class Packet {
    private:
        StaticJsonDocument<200> packet;
        Packet* next_packet;
    public:
        JsonObject data;
        int timestamp;

        Packet(int id);
        void queue(Packet* next);
        void exec(HardwareSerial* SerialPort);
        Packet* next();
};

#endif