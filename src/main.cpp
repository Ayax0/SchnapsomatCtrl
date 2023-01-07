#include <Arduino.h>
#include "Schnapsomat.h"
#include "RecipeButton.h"
#include "Recipe.h"

Schnapsomat master;

Recipe recipe_luusbueb;

RecipeButton luusbueb(GPIO_NUM_16, GPIO_NUM_9, GPIO_NUM_10);
RecipeButton holdrio(GPIO_NUM_12, GPIO_NUM_1, GPIO_NUM_2);
RecipeButton tee_z(GPIO_NUM_13, GPIO_NUM_3, GPIO_NUM_4);
RecipeButton kaffee_z(GPIO_NUM_15, GPIO_NUM_7, GPIO_NUM_8);
RecipeButton kaffee_t(GPIO_NUM_14, GPIO_NUM_5, GPIO_NUM_6);

void setup() {
  master.begin(41, 42);

  luusbueb.enable();
  holdrio.enable();
  tee_z.enable();
  kaffee_z.enable();
  kaffee_t.enable();

  recipe_luusbueb.zwetschge = 3;
  recipe_luusbueb.traesch = 6;
  recipe_luusbueb.vodka = 1;

  luusbueb.bind(&master, &recipe_luusbueb);
  holdrio.bind(&master, &recipe_luusbueb);
  tee_z.bind(&master, &recipe_luusbueb);
  kaffee_z.bind(&master, &recipe_luusbueb);
  kaffee_t.bind(&master, &recipe_luusbueb);
}

void loop() {
  luusbueb.loop();
  holdrio.loop();
  tee_z.loop();
  kaffee_z.loop();
  kaffee_t.loop();
}