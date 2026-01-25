#ifndef CAPTEUR_H
#define CAPTEUR_H

#include "Grid.h"  // Pour utiliser Grid4x4

/*
    Définition des broches pour les capteurs matriciels
    Broches horizontales (sorties)
    Broches verticales (entrées)

    On utilise une matrice de boutons poussoirs (BP) connectés en grille.
    Chaque intersection entre une broche horizontale et une broche verticale correspond à un BP.
    On a des diodes pour éviter les retours de courant dans d'autres colones lors de la lecture.
    Cela évite les lectures erronées. (si on avait pas ça on pourrait pas lire plusieurs BP en même temps)

    Lecture des BP:
    - On active une broche horizontale à la fois (en la mettant à LOW)  
    - On lit l'état des broches verticales (si une broche verticale est LOW, cela signifie que le BP à cette intersection est pressé)
    - On répète pour chaque broche horizontale

*/



// Initialise les broches des capteurs
void initialiserCapteurs();


// Lit l'état des BP et met à jour la grille
void lireBoutonsPoussoirs(Grid4x4 *grille);

#endif