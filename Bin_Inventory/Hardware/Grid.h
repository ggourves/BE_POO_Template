#ifndef GRID_H
#define GRID_H

#include <FastLED.h>

#define TAILLE 4
#define NUM_LEDS (TAILLE * TAILLE)

struct Cellule {
    bool capteur;   // État du capteur (true = activé, false = désactivé)
    CRGB led;    // Couleur de la LED associée
    int numeroleds; // Numéro de la LED dans la bande
};

struct Grid4x4 {
    Cellule cells[TAILLE][TAILLE];
    void initialiser();  // appel de la fonction initialiser qui me permet d'initialiser les capteurs + LEDs
};

#endif
