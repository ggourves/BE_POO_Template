#include "itemsManager.h"

itemManager::itemManager(){
    // Constructeur vide car la liste chaînée gère elle-même la mémoire
}

itemManager::~itemManager(){
    // Destructeur vide car la liste chaînée gère elle-même la mémoire
}

void itemManager::add(int nb_slots, struct coordinates *affected_slots, String name, String value, int quantity){
    ListeItems.ajouterCellule(new item(nb_slots, affected_slots, name, value, quantity));
}   // Ajout d'un nouvel item à la liste

void itemManager::remove(int Id){   // Suppression d'un item de la liste via son identifiant
    if(Id < 0 || Id >= ListeItems.nombreCellules()){    // Vérification de la validité de l'identifiant
        return;
    }
    ListeItems.supprimerCelluleN(Id);   //Si l'identifiant est valide, suppression de l'item
}

void itemManager::dell(){   // Suppression du dernier item de la liste, non utilisé pour l'instant
    ListeItems.supprimerDerniereCellule();  
}

void itemManager::gridRemoveCells(int nb_slots, struct coordinates *affected_slots){    // Suppression des items dont au moins un slot est dans affecté 
    // Parcourir la liste chaînée de la fin au début pour éviter les problèmes d'indices lors de la suppression, normalement pas nécessaire mais plus sûr
    for(int i = ListeItems.nombreCellules() - 1; i >= 0; i--){
        item* current = ListeItems.lireCelluleN(i); // Récupérer l'item courant
        bool toRemove = false;      // Par défaut, on ne supprime pas l'item
        
        // Vérifier si au moins un slot de l'item est dans affected_slots
        for(int j = 0; j < current->getNbAffectedSlots(); j++){ // Parcourir le tableau des slots de l'item
            coordinates slot = current->getAffectedSlots()[j];
            for(int k = 0; k < nb_slots; k++){  // Parcourir les slots qui doivent être supprimés
                if(slot.x == affected_slots[k].x && slot.y == affected_slots[k].y){ // Les comparer
                    toRemove = true;    // Si une correspondance est trouvée, marquer l'item pour suppression
                    break;  //sortir du for
                }
            }
            if(toRemove) break; // Si l'item est marqué pour suppression, sortir du for
        }
        
        // Si l'item doit être supprimé, le supprimer
        if(toRemove){
            ListeItems.supprimerCelluleN(i);
        }
    }   // On répète pour chaque item de la liste chainee
}

void itemManager::displayItems(){
    // Affichage des items dans la console série sous forme de tableau avec des en-têtes :
    Serial.print("Id");
    Serial.print("\t | \t");
    Serial.print("Name");
    Serial.print("\t | \t");
    Serial.print("Value");
    Serial.print("\t | \t");
    Serial.println("Quantity");

    // Affichage de chaque item avec son Id, son nom, sa valeur et sa quantité
    for(int i = 0; i < ListeItems.nombreCellules(); i++){   // Parcourir toute la liste des items
        item* temp = ListeItems.lireCelluleN(i);    // Récupérer l'item à l'indice i
        Serial.print(i);
        Serial.print("\t | \t");
        Serial.print(temp->getName());
        Serial.print("\t | \t");
        Serial.print(temp->getValue());
        Serial.print("\t | \t");
        Serial.println(temp->getQuantity());
    }
}

void itemManager::modifyQuantity(){     // Modification de la quantité d'un item (procédure séquentielle via la console série)
    Serial.println("Choose the item you want to modify the quantity from this list:");
    displayItems(); // Afficher la liste complète des items

    Serial.println("Enter the ID of the item you want to modify:");
    while (Serial.available() == 0) {   // Attendre que l'utilisateur entre une valeur (bloquant)
    }
    String idInput = Serial.readStringUntil('\n');      // Lire l'entrée jusqu'à la nouvelle ligne
    idInput.trim();     // Supprimer les espaces blancs avant et après l'entrée (plus robuste qu'une simple parseInt, avant on avait des problèmes avec)
    if (idInput.length() == 0) {    // Si après le trim, la longueur est 0, c'est que rien n'a été entré / ou pas des chiffres
        Serial.println("No ID entered! Please try again.");
        return;     // Erreur, on sort de la fonction
    }
    int itemId = idInput.toInt();   // Convertir la chaine de caractères en entier
    Serial.print("You selected item ID: ");
    Serial.println(itemId);

    if (itemId < 0 || itemId >= ListeItems.nombreCellules()) {  // Vérifier si l'ID existe dans la liste (nb de cellules)
        Serial.println("Invalid ID! Please try again.");    // Si c'est pas le cas, message d'erreur
        return;
    }

    Serial.println("Enter '=' to set a new quantity, '+' to add, or '-' to subtract:"); // Choix de l'opération
    while (Serial.available() == 0) {   // Attendre l'entrée de l'utilisateur (bloquant)
    }
    String operationInput = Serial.readStringUntil('\n');   // pareil, plus fiable que le parseInt
    operationInput.trim();
    if (operationInput.length() == 0) {
        Serial.println("No operation entered! Please try again.");
        return;
    }
    char operation = operationInput[0]; // Récupérer uniquement le premier caractère
    Serial.print("You selected: ");
    Serial.println(operation);  // Retour de sélection

    Serial.println("Enter the value:"); // Valeur à ajouter/soustraire/affecter
    while (Serial.available() == 0) {
    }
    String valInput = Serial.readStringUntil('\n'); // pareil qu'avant pour récupérer
    valInput.trim();
    if (valInput.length() == 0) {
        Serial.println("No value entered! Please try again.");
        return;
    }
    int newValue = valInput.toInt();    
    Serial.print("You entered: ");
    Serial.println(newValue);   // Retour valeur lue

    item* selectedItem = ListeItems.lireCelluleN(itemId);

    switch (operation) {
        case '=':
            selectedItem->setQuantity(newValue);    // Affecter la nouvelle quantité, on voulait utiliser les opérateurs surchargés mais ça posait des problèmes et ça ne fonctionnait pas
            Serial.println("Quantity updated!");
            break;
        case '+':
            selectedItem->setQuantity(selectedItem->getQuantity() + newValue);  // Pareil on voulait uiliser les opérateurs
            Serial.println("Quantity increased!");
            break;
        case '-':
            selectedItem->setQuantity(selectedItem->getQuantity() - newValue);  // Pareil on voulait uiliser les opérateurs
            Serial.println("Quantity decreased!");
            break;
        default:
            Serial.println("Invalid operation! Please try again."); // Cas par défaut où l'opération n'est pas reconnue
    }
}

void itemManager::enlightItem(Grid4x4* grid){   // Allumer les LEDs des slots où se trouve la bin sélectionnée
    Serial.println("Choose the item you want to enlighten from this list:");    
    displayItems(); // Afficher la liste complète des items

    Serial.println("Enter the ID of the item you want to enlighten:");
    while (Serial.available() == 0) {   // Attendre que l'utilisateur entre une valeur (bloquant)
    }
    String idInput = Serial.readStringUntil('\n'); // méthode plus robuste qu'un simple parseInt
    idInput.trim();     
    if (idInput.length() == 0) {
        Serial.println("No ID entered! Please try again.");
        return;
    }
    int itemId = idInput.toInt();
    Serial.print("You selected item ID: ");
    Serial.println(itemId);

    if (itemId < 0 || itemId >= ListeItems.nombreCellules()) {
        Serial.println("Invalid ID! Please try again.");
        return;
    }

    item* selectedItem = ListeItems.lireCelluleN(itemId);   // Si l'ID est ok, copier l'item correspondant de la liste chainee

    int nbSlots = selectedItem->getNbAffectedSlots();       // Récupérer les slots et leur nombre
    coordinates* affectedSlots = selectedItem->getAffectedSlots();
    
    Serial.print("Number of affected slots: ");
    Serial.println(nbSlots);    // Nombre de slots qu'on va allumer
    

    for (int i = 0; i < nbSlots; i++) {
        int x = affectedSlots[i].x;
        int y = affectedSlots[i].y;
        grid->cells[x][y].led = CRGB::Red;
    }

    /* Mettre à jour les LEDs immediatement dans la ce code alors qu'on devrait le faire dans le main loop, 
    mais si c'est le cas il faut modifier cette méthode et celle des leds pour qu'elles prennent en compte le délai de 5 secondes 
    mais avec des comparaisons avec millis() et le temps précedent, ce qui complique pas mal le code */
    for (int i = 0; i < nbSlots; i++) {
        int x = affectedSlots[i].x;
        int y = affectedSlots[i].y;
        int numLed = grid->cells[x][y].numeroleds;
        leds[numLed] = grid->cells[x][y].led;
    }
    FastLED.show();
    
    Serial.println("LEDs updated for the selected item.");
    
    // Garder le(s) LED(s) allumée(s) pendant 5 secondes
    delay(5000);
    
    // Éteindre le(s) LED(s) après le délai
    for (int i = 0; i < nbSlots; i++) {
        int x = affectedSlots[i].x;
        int y = affectedSlots[i].y;
        grid->cells[x][y].led = CRGB::Black;
    }
}

void itemManager::actionChoice(Grid4x4* grid){
    Serial.println("Press q to modify a quantity or e to enlight an item of the inventory");

    while (!(Serial.available() > 0)) {}
    int incomingByte = Serial.read();
    // Vider le buffer série pour éviter des problèmes avec des entrées supplémentaires précédentes qui seraient restées dans le buffer
    while (Serial.available() > 0) Serial.read();
    Serial.print("Received: ");
    Serial.println((char)incomingByte);
    
    switch (incomingByte) {     // Choix du type d'action
        case 'q':
            modifyQuantity();
            break;
        case 'e':
            enlightItem(grid);
            break;
        default:
            Serial.print("You entered an incorrect keystroke! ");   // Pas d'action correspondate
    }
}


