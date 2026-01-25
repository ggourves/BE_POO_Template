#include "Capteur.h"
#include <Arduino.h>  // inclu digitalRead/digitalWrite

// Broches horizontale (sorties)
const int lignes[TAILLE] = {16, 5, 4, 0}; //adapté pour notre carte, on utilise les GPIO 0,4,5,16
// Broches verticale (entrées)
const int colonnes[TAILLE] = {14, 12, 13, 15};  //adapté pour notre carte, on utilise les GPIO 12,13,14,15



void initialiserCapteurs() {
    // Initialise les broches des lignes en sortie
    for (int i = 0; i < TAILLE; i++) {
        pinMode(lignes[i], OUTPUT);
        digitalWrite(lignes[i], HIGH);  // Désactive les lignes au début (Nous sommes en logique inversée car on utilise les pullup en interne du microcontroleur)
    }

    // Initialise les broches des colonnes en entrée avec pull-up
    for (int i = 0; i < TAILLE; i++) {
        pinMode(colonnes[i], INPUT_PULLUP);
    }
}




void lireBoutonsPoussoirs(Grid4x4 *grille) {    // Lit l'état des capteurs et met à jour la grille
    // Activation de chaque ligne (une par une)
    for (int i = 0; i < TAILLE; i++) {
        digitalWrite(lignes[i], LOW);  // Active l'axe horizontal i

        // Vérification de chaque axe vertical 
        for (int j = 0; j < TAILLE; j++) {
            // Met à jour l'état du capteur dans la grille
            grille->cells[i][j].capteur = (digitalRead(colonnes[j]) == LOW);    // En logique inversée, LOW signifie que le capteur est activé car on tire à la masse
        }

        digitalWrite(lignes[i], HIGH);  // Désactive l'axe horizontal i
    }
}