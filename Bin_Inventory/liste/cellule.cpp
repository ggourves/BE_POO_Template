#ifndef CELLULE_CPP
#define CELLULE_CPP

#include "cellule.h"

template <typename truc>    // Pour accepter le type qu'on souhaite, dans notre cas ce sera un objet item héritant de la classe caracteristics et bin
cellule<truc>::cellule(truc cont) : contenu(cont) { // Constructeur qui enregistre le contenu
}

// Assesseur/setter du contenu
template <typename truc>
truc cellule<truc>::obtenirContenu() {
    return contenu;
}

// Getter de la cellule suivante
template <typename truc>
cellule<truc>* cellule<truc>::obtenirPostCellule() {
    return pCellule;
}

// Associer la cellule suivante
template <typename truc>
void cellule<truc>::associerPostCellule(cellule<truc>* p_cell) {
    pCellule = p_cell;
}

// Destructeur
template <typename truc>
cellule<truc>::~cellule() {
    contenu = NULL; // Libérer le contenu, il est donc déréférencé et sera détruit par le garbage collector
}

#endif