
#ifndef CELLULE_H
#define CELLULE_H

template <typename truc>
class cellule {
    protected:
        cellule<truc> *pCellule = NULL; // Pointeur vers la cellule suivante
        truc contenu;               // Contenu de la cellule
    
    public:

        cellule(truc cont);  // Constructeur qui enregistre le contenu

        truc obtenirContenu();      // Getter du contenu

        cellule<truc> *obtenirPostCellule();    // Getter de la cellule suivante

        void associerPostCellule(cellule<truc> *p_cell);    // Associer la cellule suivante (setter)

        ~cellule(); // Destructeur de la cellule
};

#include "cellule.cpp"

#endif
