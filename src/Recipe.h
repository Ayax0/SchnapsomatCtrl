#ifndef Recipe_h
#define Recipe_h

#include "Schnapsomat.h"

class Recipe {
    public:
        int zwetschge = 0;
        int traesch = 0;
        int vodka = 0;
        int tee_hagenbutte = 0;
        int tee_pfefferminz = 0;
        int wasser = 0;
        int zucker = 0;
        int kaffee = 0;
        
        void produce(Schnapsomat* master);
};
#endif