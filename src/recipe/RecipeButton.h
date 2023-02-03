#ifndef RecipeButton_h
#define RecipeButton_h

#include <Arduino.h>

#define MAX_INGREDIENCE_AMOUNT 32

#define STATUS_UNKNOWN -1
#define STATUS_DISABLED 0
#define STATUS_ENABLED 1

class RecipeButton {
    private:
        int status = 0;

        int pin_status;
        int pin_red;
        int pin_green;
        void (*listener)();
        void setStatus(int status);

        uint8_t recipe[MAX_INGREDIENCE_AMOUNT];
    public:
        RecipeButton(int pin_status, int pin_red, int pin_green);
        void enable();
        void disable();
        void listen(void (*listener)());
        void setIngredience(uint8_t index, uint8_t amount);
        void setIngredients(uint8_t amounts[], uint8_t array_size);
        uint8_t getIngredienceAmount(uint8_t index);
        
        boolean isPressed();
        boolean isEnabled();
        boolean isUnknown();
};
#endif