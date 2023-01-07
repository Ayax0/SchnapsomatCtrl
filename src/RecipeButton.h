#ifndef RecipeButton_h
#define RecipeButton_h

#include <Arduino.h>
#include "Schnapsomat.h"
#include "Recipe.h"

#define STATUS_UNKNOWN -1
#define STATUS_DISABLED 0
#define STATUS_ENABLED 1

class RecipeButton {
    private:
        int status = 0;

        int pin_status;
        int pin_red;
        int pin_green;
        void setStatus(int status);

        Schnapsomat* master;
        Recipe* recipe;
    public:
        RecipeButton(int pin_status, int pin_red, int pin_green);
        void enable();
        void disable();
        void bind(Schnapsomat* master, Recipe* recipe);
        void loop();
        boolean isPressed();
        boolean isEnabled();
};
#endif