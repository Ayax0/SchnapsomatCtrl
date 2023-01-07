#include <Arduino.h>
#include "Schnapsomat.h"

Schnapsomat::Schnapsomat() {
    SerialPort = new HardwareSerial(1);
}

void Schnapsomat::begin(int  rx, int  tx) {
    SerialPort->begin(9600, SERIAL_8N1, rx, tx);
}

void Schnapsomat::send(String command) {
    SerialPort->print(command);
    SerialPort->print('$');
}

void Schnapsomat::dispenseIngredience(String ingredience, int amount) {
    send("DISP " + ingredience + " " + amount);
}

