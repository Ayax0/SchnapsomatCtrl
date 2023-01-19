#include "Schnapsomat.h"
#include "Packet.h"

Schnapsomat::Schnapsomat(int  rx, int  tx) {
    SerialPort = new HardwareSerial(1);
    SerialPort->begin(115200, SERIAL_8N1, rx, tx);

    for(int i = 0; i < BUFFER_SIZE; i++) buffer[i] = NULL;
    ready = true;
}
void Schnapsomat::loop() {
    if(SerialPort->available()) {
        StaticJsonDocument<200> packet;
        DeserializationError error = deserializeJson(packet, *SerialPort);

        if(error == DeserializationError::Ok) {
            if(packet["id"] == PACKET_ACK) ack();
            if(packet["id"] == PACKET_OK) ready = true;
            if(packet["id"] == PACKET_NOK) ready = false;
            if(packet["id"] == PACKET_OK && buffer[0] != NULL) buffer[0]->exec(SerialPort);
        } else {
            Serial.print("SerializationError: ");
            Serial.println(error.c_str());

            while(SerialPort->available() > 0) SerialPort->read();
        }
    }
}

void Schnapsomat::send(Packet *packet) {
    for(int i = 0; i < BUFFER_SIZE; i++) {
        if(buffer[i] == NULL) {
            Serial.print("queue at: ");
            Serial.println(i);
            buffer[i] = packet;

            if(i == 0 && ready) packet->exec(SerialPort);
            return;
        }
    }
    Serial.println("buffer is full!");
}

void Schnapsomat::ack() {
    Serial.println("ack");
    for(int i = 1; i < BUFFER_SIZE; i++) {
        if(buffer[i] != NULL) buffer[i - 1] = buffer[i];
        else buffer[i - 1] = NULL;
    }
}

void Schnapsomat::dispenseIngredience(String ingredience, int amount) {
    Packet *packet = new Packet(PACKET_CMD);
    packet->data["action"] = "DISP";
    packet->data["ingredience"] = ingredience;
    packet->data["amount"] = amount;

    send(packet);
}

