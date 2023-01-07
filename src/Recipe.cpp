#include "Recipe.h"
#include "Schnapsomat.h"

void Recipe::produce(Schnapsomat* master) {
    if(zwetschge > 0) master->dispenseIngredience("zwetschge", zwetschge);
    if(traesch > 0) master->dispenseIngredience("traesch", traesch);
    if(vodka > 0) master->dispenseIngredience("vodka", vodka);
}