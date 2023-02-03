#include "RecipeButton.h"

RecipeButton::RecipeButton(int pin_status, int pin_red, int pin_green) {
    this->pin_status = pin_status;
    this->pin_red = pin_red;
    this->pin_green = pin_green;

    pinMode(pin_status, INPUT_PULLDOWN);
    pinMode(pin_red, OUTPUT);
    pinMode(pin_green, OUTPUT);
    setStatus(STATUS_UNKNOWN);

    for(uint8_t i = 0; i < MAX_INGREDIENCE_AMOUNT; i++) this->recipe[i] = 0;
}

void RecipeButton::setStatus(int status) {
    this->status = status;
    if(status == STATUS_UNKNOWN) {
        digitalWrite(pin_red, LOW);
        digitalWrite(pin_green, LOW);
    } else if(status == STATUS_ENABLED) {
        digitalWrite(pin_red, LOW);
        digitalWrite(pin_green, HIGH);
    } else if(status == STATUS_DISABLED) {
        digitalWrite(pin_red, HIGH);
        digitalWrite(pin_green, LOW);
    }
}

void RecipeButton::enable() {
    setStatus(STATUS_ENABLED);
}

void RecipeButton::disable() {
    setStatus(STATUS_DISABLED);
}

void RecipeButton::listen(void (*listener)()) {
    this->listener = listener;
}

boolean RecipeButton::isPressed() {
    return digitalRead(pin_status) == HIGH;
}

boolean RecipeButton::isEnabled() {
    return status == STATUS_ENABLED;
}

boolean RecipeButton::isUnknown() {
    return status == STATUS_UNKNOWN;
}

void RecipeButton::setIngredience(uint8_t index, uint8_t amount) {
    this->recipe[index] = amount;
    if(this->status == STATUS_UNKNOWN) enable();
}

void RecipeButton::setIngredients(uint8_t amounts[], uint8_t array_size) {
    for(uint8_t i = 0; i < array_size; i++) this->recipe[i] = amounts[i];
    if(this->status == STATUS_UNKNOWN) enable();
}

uint8_t RecipeButton::getIngredienceAmount(uint8_t index) {
    return this->recipe[index];
}