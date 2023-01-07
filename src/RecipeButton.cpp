#include "RecipeButton.h"
#include <Arduino.h>

RecipeButton::RecipeButton(int pin_status, int pin_red, int pin_green) {
    this->pin_status = pin_status;
    this->pin_red = pin_red;
    this->pin_green = pin_green;

    pinMode(pin_status, INPUT_PULLDOWN);
    pinMode(pin_red, OUTPUT);
    pinMode(pin_green, OUTPUT);
    setStatus(STATUS_UNKNOWN);
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

void RecipeButton::bind(Schnapsomat* master, Recipe* recipe) {
    this->master = master;
    this->recipe = recipe;
}

void RecipeButton::loop() {
    if(isPressed() && isEnabled()) {
        disable();
        if(master != NULL && recipe != NULL) {
            recipe->produce(master);
        }
    }
}

boolean RecipeButton::isPressed() {
    return digitalRead(pin_status) == HIGH;
}

boolean RecipeButton::isEnabled() {
    return status == STATUS_ENABLED;
}