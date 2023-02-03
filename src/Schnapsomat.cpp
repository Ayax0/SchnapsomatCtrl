#include "Schnapsomat.h"

Schnapsomat::Schnapsomat(int  rx, int  tx) {
    SerialPort = new HardwareSerial(1);
    SerialPort->begin(9600, SERIAL_8N1, rx, tx);
}

void Schnapsomat::loop() {
    while(SerialPort->available()) {
        char inChar = (char)SerialPort->read();
        charReceiver(inChar);
    }

    // RecipeButton Handling
    for(uint8_t button_index = 0; button_index < MAX_BUTTON_AMOUNT; button_index++) {
        if(button_registry[button_index] != NULL) {
            RecipeButton *button = button_registry[button_index];
            if(button->isEnabled() && button->isPressed()) {
                disabled = millis() + BUTTON_TIMEOUT;

                for(uint8_t ingredience_index = 0; ingredience_index < MAX_INGREDIENCE_AMOUNT; ingredience_index++) {
                    if(button->getIngredienceAmount(ingredience_index) > 0)
                        dispenseIngredience(ingredience_index, button->getIngredienceAmount(ingredience_index));
                }

                for(uint8_t i = 0; i < MAX_BUTTON_AMOUNT; i++) {
                    if(button_registry[i] != NULL && !button_registry[i]->isUnknown()) button_registry[i]->disable();
                }
            }
        }
    }

    // RecipeButton Timeout Handling
    if(disabled > 0 && millis() > disabled) {
        disabled = 0;
        for(uint8_t i = 0; i < MAX_BUTTON_AMOUNT; i++) {
            if(button_registry[i] != NULL && !button_registry[i]->isUnknown()) button_registry[i]->enable();
        }
    }
}

void Schnapsomat::dispenseIngredience(uint8_t type, uint8_t amount) {
    Buffer buffer(4);
    buffer.writeUInt8(0x01, 0);
    buffer.writeUInt8(0x00, 1);
    buffer.writeUInt8(type, 2);
    buffer.writeUInt8(amount, 3);
    sendBuffer(buffer);
}

void Schnapsomat::registerButton(uint8_t index, RecipeButton *button) {
    this->button_registry[index] = button;
}

// HDLC
void Schnapsomat::receiveBuffer(Buffer buffer) {
    digitalWrite(10, HIGH);
    delay(200);
    digitalWrite(10, LOW);
    delay(200);
}

void Schnapsomat::charReceiver(uint8_t data) {
    if(data == FRAME_BOUNDARY_OCTET) {
        if(this->escape_character == true) this->escape_character = false;
        else if((this->frame_position >= 2) && (this->frame_checksum == ((this->receive_frame_buffer[this->frame_position-1] << 8 ) | (this->receive_frame_buffer[this->frame_position-2] & 0xff)))) {
            (receiveBuffer)(Buffer(receive_frame_buffer));
        }
        this->frame_position = 0;
        this->frame_checksum = CRC16_CCITT_INIT_VAL;
        return;
    }

    if(this->escape_character) {
        this->escape_character = false;
        data ^= INVERT_OCTET;
    }
    else if(data == CONTROL_ESCAPE_OCTET) {
        this->escape_character = true;
        return;
    }

    receive_frame_buffer[this->frame_position] = data;

    if(this->frame_position-2 >= 0) {
        this->frame_checksum = _crc_ccitt_update(this->frame_checksum, receive_frame_buffer[this->frame_position-2]);
    }

    this->frame_position++;

    if(this->frame_position == this->max_frame_length) {
        this->frame_position = 0;
        this->frame_checksum = CRC16_CCITT_INIT_VAL;
    }
}

void Schnapsomat::charSender(uint8_t data) {
    SerialPort->print((char) data);
}

void Schnapsomat::sendBuffer(Buffer buffer) {
    uint8_t *framebuffer = buffer.toArray();
    uint8_t frame_length = buffer.size();
    uint8_t data;
    uint16_t fcs = CRC16_CCITT_INIT_VAL;

    this->charSender((uint8_t)FRAME_BOUNDARY_OCTET);

    while(frame_length) {
        data = *framebuffer++;
        fcs = _crc_ccitt_update(fcs, data);
        if((data == CONTROL_ESCAPE_OCTET) || (data == FRAME_BOUNDARY_OCTET)) {
            this->charSender((uint8_t)CONTROL_ESCAPE_OCTET);
            data ^= INVERT_OCTET;
        }
        this->charSender((uint8_t)data);
        frame_length--;
    }
    data = low(fcs);
    if((data == CONTROL_ESCAPE_OCTET) || (data == FRAME_BOUNDARY_OCTET)) {
        this->charSender((uint8_t)CONTROL_ESCAPE_OCTET);
        data ^= (uint8_t)INVERT_OCTET;
    }
    this->charSender(data);
    data = high(fcs);
    if((data == CONTROL_ESCAPE_OCTET) || (data == FRAME_BOUNDARY_OCTET)) {
        this->charSender(CONTROL_ESCAPE_OCTET);
        data ^= INVERT_OCTET;
    }
    this->charSender(data);
    this->charSender(FRAME_BOUNDARY_OCTET);
}