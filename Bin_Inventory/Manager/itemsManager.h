
#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include "../liste/file.h"
#include "../liste/item.h"
#include "../Hardware/Grid.h"
#include <string.h>
#include "Arduino.h"

class itemManager{

    private:
    file<item*> ListeItems;

    public:

    itemManager();
    ~itemManager();

    void add(int nb_slots, struct coordinates *affected_slots, String name, String value, int quantity);
    // Ajout d'un item à la liste en lui passant les caractéristiques et spécifications de la bin
    
    void remove(int Id);
    // Suppression d'un item de la liste via son identifiant

    void dell();
    // Suppression du dernier item de la liste

    void gridRemoveCells(int nb_slots, struct coordinates *affected_slots);
    // Suppression des items dont au moins un slot est affecté et doit être supprimé

    void displayItems();
    // Affichage de tous les items dans la console série

    void modifyQuantity();
    // Modification de la quantité d'un item via la console série

    void enlightItem(Grid4x4* grid);   
    // Allumer les LEDs des slots où se trouve la bin sélectionnée (item)

    void actionChoice(Grid4x4* grid);
    // Choix de l'action à effectuer via la console série (modifier quantité ou allumer LEDs)
};

#endif