#ifndef FILE_CPP
#define FILE_CPP

#include "file.h"

// On utilise des template partout pour mettre le type qu'on souhaite dans la file
template <typename chose>
file<chose>::file(chose contenu) {
    cellule<chose>* cell = new cellule<chose>(contenu); // Allocation de mémoire pour que l'adresse reste valide après la fin du constructeur
    pDeb = cell;    // La première et la dernière cellule pointent sur la même cellule lorsqu'on créé la file avec un seul élément
    pFin = cell;
    nbCellules++;   // Incrémentation du nombre de cellules
}

template <typename chose>
file<chose>::file() {
    // Constructeur par défaut qui permet d'initialiser une file vide
}

template <typename chose>
void file<chose>::ajouterCellule(chose contenu) {   // Ajout d'une cellule à la fin de la file
    cellule<chose>* cell = new cellule<chose>(contenu); // Allocation de mémoire pour que l'adresse reste valide après la fin du constructeur
    if (pDeb == NULL) { // Si la file est vide, la nouvelle cellule devient la première et la dernière
        pDeb = cell;
        pFin = cell;
    } else {
        pFin->associerPostCellule(cell);    // Sinon, on ajoute la cellule à la fin
        pFin = cell;
    }
    nbCellules++;   // Incrémentation du nombre de cellules
}

template <typename chose>
void file<chose>::supprimerPremiereCellule() {  // Suppression de la première cellule de la file
    if (estVide()) {    // Si la file est vide, on ne fait rien
        return;
    } else {
        cellule<chose>* nouveau_pDeb = pDeb->obtenirPostCellule();  // On récupère la cellule suivante
        delete pDeb;  // On supprime la première cellule en la déréférençant
        pDeb = nouveau_pDeb;    // On met à jour le pointeur vers la nouvelle première cellule (qui sera la suivante de l'ancienne ou NULL si la file ne contenait qu'une cellule)
        nbCellules--;   // Décrémentation du nombre de cellules
    }
}

template <typename chose>
void file<chose>::supprimerDerniereCellule() {  // Suppression de la dernière cellule de la file
    if (estVide()) {    // Si la file est vide, on ne fait rien
        return;
    } else {
        cellule<chose>* pTemp = pDeb;   // Pointeur temporaire pour parcourir la file
        cellule<chose>* pTempMoinsUn = pDeb;    // Pointeur temporaire pour garder l'avant dernière cellule

        while (pTemp->obtenirPostCellule() != NULL) {   // On parcourt la file jusqu'à la dernière cellule (qui n'a donc pas de cellule suivante)
            pTempMoinsUn = pTemp;
            pTemp = pTemp->obtenirPostCellule();
        }
        delete pFin;  // On supprime la dernière cellule
        pFin = pTempMoinsUn;    // On met à jour le pointeur vers la nouvelle dernière cellule
        if (pFin != NULL) { // Si la file n'est pas vide après suppression
            pFin->associerPostCellule(NULL);
        } else {
            pDeb = NULL;  // Si la file n'avait qu'une cellule, on met aussi le début à NULL
        }
        nbCellules--;   // Décrémentation du nombre de cellules
    }
}

template <typename chose>
int file<chose>::nombreCellules() { // Getter retourne le nombre de cellules dans la file
    return nbCellules;
}

template <typename chose>
bool file<chose>::estVide() {   // Vérifie si la file est vide
    return nbCellules == 0;
}

template <typename chose>
chose file<chose>::lireDerniereCellule() {  // Lit le contenu de la dernière cellule de la file
    if (estVide()) {
        return NULL;    // Si la file est vide, on retourne NULL car il n'y a pas de contenu à lire
    }
    return pFin->obtenirContenu();  // Retourne le contenu de la dernière cellule
}

template <typename chose>
chose file<chose>::lirePremiereCellule() {  // Lit le contenu de la première cellule de la file
    if (estVide()) {
        return NULL;    // Si la file est vide, on retourne NULL car il n'y a pas de contenu à lire
    }
    return pDeb->obtenirContenu();  // Retourne le contenu de la première cellule
}

template <typename chose>
chose file<chose>::lireCelluleN(int nCell) {    // Lit le contenu de la n-ième cellule de la file
    if (estVide() || nCell < 0 || nCell >= nbCellules) {    // Vérifie si la file est vide ou si l'index est hors limites
        return NULL;    // Si c'est le cas, on retourne NULL
    }
    cellule<chose>* pTemp = pDeb;   // Pointeur temporaire pour parcourir la file
    for (int i = 0; i < nCell; i++) {   // On parcourt la file jusqu'à la n-ième cellule
        pTemp = pTemp->obtenirPostCellule(); 
    }
    return pTemp->obtenirContenu(); // Retourne le contenu de la n-ième cellule
}

template <typename chose>
void file<chose>::supprimerCelluleN(int nCell) {    // Supprime la n-ième cellule de la file
    if (estVide() || nCell < 0 || nCell >= nbCellules) {    // Vérifie si la file est vide ou si l'index est hors limites
        return;
    }
    if (nCell == 0) {   // Si c'est la première cellule, on utilise la fonction dédiée
        supprimerPremiereCellule();
        return;
    }
    cellule<chose>* pTempD = pDeb;  // Pointeur temporaire pour parcourir la file jusqu'à l'avant-dernière cellule demandée
    for (int i = 0; i < nCell - 1; i++) {
        pTempD = pTempD->obtenirPostCellule();
    }
    cellule<chose>* toDelete = pTempD->obtenirPostCellule();    // Pointeur vers la cellule à supprimer
    cellule<chose>* next = toDelete->obtenirPostCellule();  // Pointeur vers la cellule suivante à celle à supprimer
    pTempD->associerPostCellule(next);  // On fait pointer l'avant-dernière cellule vers la cellule suivant celle à supprimer, cela déréférence la cellule entre les deux à supprimer
    if (toDelete == pFin) {
        pFin = pTempD;  // Si on supprime la dernière cellule, on met à jour le pointeur de fin
    }
    delete toDelete;    // On supprime la cellule déréférencée
    nbCellules--;   // Décrémentation du nombre de cellules
}

#endif