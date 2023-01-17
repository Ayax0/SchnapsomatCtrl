#include "Packet.h"

Packet::Packet(int id) {
    this->packet["id"] = id;
    this->data = packet.createNestedObject("data");
    this->timestamp = millis();
}

void Packet::queue(Packet* next) {
    if(this->next_packet == nullptr) this->next_packet = next;
    else this->next_packet->queue(next);
}

void Packet::exec(HardwareSerial* SerialPort) {
    serializeJson(packet, *SerialPort);
}

Packet* Packet::next() {
    return next_packet;
}