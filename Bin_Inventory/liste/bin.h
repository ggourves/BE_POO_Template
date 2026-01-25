
#ifndef BIN_H
#define BIN_H

struct coordinates{     // Représente les indices i et j d'une case dans la grille 2D (coté hardware)
    int x;
    int y;
};


class bin{

protected:
    int nb_affected_slots;          // Nombre de slots affectés par la bin/boite (son empreinte)
    struct coordinates *affected_slots; // Tableau dynamique des coordonnées des slots affectés par la bin/boite

public:
    bin(int nb_slots, struct coordinates *affected_slots);
    // Constructeur : on passe le nombre de slots affectés et un tableau dynamique des coordonnées des slots affectés

    int getNbAffectedSlots() { return nb_affected_slots; }
    // Getter du nombre de slots affectés

    coordinates* getAffectedSlots() { return affected_slots; }
    // Getter du tableau des coordonnées des slots affectés

    ~bin(){     // Destructeur qui libère la mémoire allouée pour le tableau des coordonnées
        delete[] affected_slots;
    }



};


#endif