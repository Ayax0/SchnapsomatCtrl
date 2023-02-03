#ifndef Buffer_h
#define Buffer_h

#include <Arduino.h>

class Buffer {
    private:
        uint8_t *data;
    public:
        Buffer(int size);
        Buffer(uint8_t* data);
        void writeUInt8(uint8_t data, int pos = 0);
        void writeUInt16(uint16_t data, int pos = 0);
        uint8_t readUInt8(int pos = 0);
        uint16_t readUInt16(int pos = 0);

        int size();
        uint8_t* toArray();
};
#endif