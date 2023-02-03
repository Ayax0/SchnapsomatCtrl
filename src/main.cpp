#include <Arduino.h>
#include "Schnapsomat.h"
#include "recipe/RecipeButton.h"

#define INGREDIENCE_AMOUNT 6

Schnapsomat Schnapsomat_Master(GPIO_NUM_41, GPIO_NUM_42);

RecipeButton Button1(GPIO_NUM_17, GPIO_NUM_10, GPIO_NUM_11);
RecipeButton Button2(GPIO_NUM_16, GPIO_NUM_8, GPIO_NUM_9);
RecipeButton Button3(GPIO_NUM_15, GPIO_NUM_6, GPIO_NUM_7);
RecipeButton Button4(GPIO_NUM_14, GPIO_NUM_4, GPIO_NUM_5);
RecipeButton Button5(GPIO_NUM_13, GPIO_NUM_2, GPIO_NUM_3);

void setup() {
  uint8_t LuusbuebeTee[INGREDIENCE_AMOUNT] = {2, 1, 3, 5, 2, 4};

  Button1.setIngredients(LuusbuebeTee, INGREDIENCE_AMOUNT);
  Button2.setIngredients(LuusbuebeTee, INGREDIENCE_AMOUNT);
  Button3.setIngredients(LuusbuebeTee, INGREDIENCE_AMOUNT);

  Schnapsomat_Master.registerButton(0, &Button1);
  Schnapsomat_Master.registerButton(1, &Button2);
  Schnapsomat_Master.registerButton(2, &Button3);
  Schnapsomat_Master.registerButton(3, &Button4);
  Schnapsomat_Master.registerButton(4, &Button5);
}

void loop() {
  Schnapsomat_Master.loop();
}