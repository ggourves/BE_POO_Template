#include "bin.h"

bin::bin(int nb_slots, struct coordinates *affected_slots): nb_affected_slots(nb_slots) {
    // Allouer de la mémoire pour stocker une copie des slots
    this->affected_slots = new coordinates[nb_slots];
    // Copier les données
    for(int i = 0; i < nb_slots; i++) {
        this->affected_slots[i] = affected_slots[i];
    }
}

