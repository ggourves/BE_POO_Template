#ifndef LED_H
#define LED_H

#include <FastLED.h>
#include "Grid.h"

// Initialise les LEDs physiques
void initialiserLEDs();

// Met à jour les LEDs physiques en fonction de l'état de la grille
void mettreAJourLEDs(Grid4x4 *grille);

#endif
