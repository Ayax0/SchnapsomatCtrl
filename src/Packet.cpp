#include "Packet.h"

Packet::Packet() {
    this->data = packet.createNestedObject("data");
    this->timestamp = millis();
}

Packet::Packet(int id) {
    this->packet["id"] = id;
    this->data = packet.createNestedObject("data");
    this->timestamp = millis();
}

void Packet::init(int id) {
    this->packet["id"] = id;
}

void Packet::queue(Packet* next) {
    if(this->next == nullptr) this->next = next;
    else this->next->queue(next);
}

void Packet::exec(HardwareSerial* SerialPort) {
    serializeJson(packet, *SerialPort);
}