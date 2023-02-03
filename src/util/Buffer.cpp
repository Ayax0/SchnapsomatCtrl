#include "Buffer.h"

Buffer::Buffer(int size) {
    this->data = (uint8_t *)malloc(size);
}

Buffer::Buffer(uint8_t* data) {
    this->data = data;
}

void Buffer::writeUInt8(uint8_t data, int pos) {
    this->data[pos] = data;
}

void Buffer::writeUInt16(uint16_t data, int pos) {
    this->data[pos] = static_cast<uint8_t>((data & 0x0FF00) >> 8);
    this->data[pos + 1] = static_cast<uint8_t>((data & 0x00FF));
}

uint8_t Buffer::readUInt8(int pos) {
    return this->data[pos];
}

uint16_t Buffer::readUInt16(int pos) {
    return ((uint16_t) this->data[pos] << 8) | this->data[pos + 1];
}

int Buffer::size() {
    return sizeof(this->data);
}

uint8_t* Buffer::toArray() {
    return this->data;
}