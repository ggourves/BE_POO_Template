
#ifndef ITEM_H
#define ITEM_H

#include <Arduino.h>
#include "bin.h"
#include "caracteristics.h"

class item: public bin, public caracteristics{

protected:

public:

    item(int nb_slots, struct coordinates *affected_slots, String name, String value, int quantity);
    // Constructeur qui initialise un item avec les caractéristiques et les spécifications de la bin/boite

    ~item(){
    }

};


#endif