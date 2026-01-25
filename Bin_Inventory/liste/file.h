#ifndef FILE_H
#define FILE_H

#include "cellule.h"

template <typename chose>
class file {
    protected:
        cellule<chose> *pDeb = NULL;    // Pointeur vers la première cellule de la file
        cellule<chose> *pFin = NULL;    // Pointeur vers la dernière cellule de la file
        int nbCellules = 0;            // Nombre de cellules dans la file, au début aucune

    public:
        file(chose contenu);    // Constructeur qui crée une file avec une première cellule contenant le contenu donné
        file();               // Constructeur par défaut qui permet de créer une file vide
        void ajouterCellule(chose contenu); // Ajout d'une cellule à la fin de la file
        void supprimerPremiereCellule();    // Suppression de la première cellule de la file
        void supprimerDerniereCellule();    // Suppression de la dernière cellule de la file
        int nombreCellules();   // Getter retourne le nombre de cellules dans la file
        bool estVide();  // Vérifie si la file est vide
        chose lireDerniereCellule();    // Lit le contenu de la dernière cellule de la file
        chose lirePremiereCellule();    // Lit le contenu de la première cellule de la file
        chose lireCelluleN(int nCell);  // Lit le contenu de la n-ième cellule de la file
        void supprimerCelluleN(int nCell);  // Supprime la n-ième cellule de la file

        class Vide {    // Exception levée lorsqu'on tente de supprimer un élément d'une file vide
            public:
                const char* what() const {
                    return "Impossible de supprimer un élément d'une file vide.";
                }
        };
};

#include "file.cpp"

#endif