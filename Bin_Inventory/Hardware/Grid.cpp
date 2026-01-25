#include "Grid.h"

void Grid4x4::initialiser() {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            cells[i][j].capteur = false;  // Capteur inactif
            cells[i][j].led = CRGB::Black;  // LED éteinte
            
            // Numérotation en serpentin inversé (zigzag, car nos LEDs sont câblées ainsi)
            if (i % 2 == 0) {
                // Lignes paires: droite à gauche
                cells[i][j].numeroleds = i * TAILLE + (TAILLE - 1 - j);
            } else {
                // Lignes impaires: gauche à droite
                cells[i][j].numeroleds = i * TAILLE + j;
            }
        }
    }
}
