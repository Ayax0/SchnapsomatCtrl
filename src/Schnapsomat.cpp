#include "Schnapsomat.h"
#include "Packet.h"

/*
    Packet IDs
    0x00 = ack
    0x01 = nack
    0x10 = ok
    0x11 = nok
    0x20 = cmd
    0x21 = data
*/

Schnapsomat::Schnapsomat() {
    SerialPort = new HardwareSerial(1);
}

void Schnapsomat::begin(int  rx, int  tx) {
    SerialPort->begin(9600, SERIAL_8N1, rx, tx);
}

void Schnapsomat::loop() {
    if(SerialPort->available()) {
        StaticJsonDocument<200> packet;
        DeserializationError error = deserializeJson(packet, *SerialPort);

        if(error == DeserializationError::Ok) {
            if(packet_buffer == nullptr) return;

            Packet p(PACKET_CMD);
            p.data["ack"] = packet["id"] == PACKET_ACK;
            p.data["ok"] = packet["id"] == PACKET_OK;
            p.data["timestamp"] = packet_buffer->timestamp;
            p.exec(SerialPort);

            if(packet["id"] == PACKET_ACK) packet_buffer = packet_buffer->next();
            if(packet["id"] == PACKET_OK && packet_buffer != nullptr) packet_buffer->exec(SerialPort);
        } else {
            Serial.print("SerializationError: ");
            Serial.println(error.c_str());

            while(SerialPort->available() > 0) SerialPort->read();
        }
    }
}

void Schnapsomat::send(String command) {
    Packet packet(PACKET_CMD);
    packet.data["payload"] = command;
    packet.data["queue"] = packet_buffer != nullptr;

    if(packet_buffer == nullptr) {
        packet_buffer = &packet;
        packet_buffer->exec(SerialPort);
    } else {
        packet_buffer->queue(&packet);
    }
}

void Schnapsomat::dispenseIngredience(String ingredience, int amount) {
    send("DISP " + ingredience + " " + amount);
}

