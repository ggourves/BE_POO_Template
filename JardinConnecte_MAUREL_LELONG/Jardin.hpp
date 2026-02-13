/////////////////////CLASSE JARDIN////////////////////////////////////

#ifndef JARDIN_HPP
#define JARDIN_HPP

#include "Rose.hpp"
#include "Tulipe.hpp"
#include "poireau.hpp"
#include "citrouille.hpp"
#include "LCD.hpp"
#include "BoutonPoussoir.hpp"
#include "Arrosage.hpp"

class Jardin {
private:
    // Capteurs et actionneurs
    CapteurTemperature temp;  // Lit les valeurs de temperature et humidité 
    LCD lcd;                 // Affiche les différents écrans souhaités (température+ humidité et caractéristiques des plantes)
    Led led;                // led allumée = mode auto / led eteinte = mode manuel 
    CapteurTactile ct;     // capteur tactile qui actionne la led selon le mode d'arrosage souhaité 
    Buzzer buzz;          //buzzer qui simule le temps d'arrosage de chaque plante 
    BoutonPoussoir bp;   // bouton pour navigation menu 

    // Plantes du jardin
    std::vector<Plante*> plantes; 

    // Arrosage 
    Arrosage arroser;

    // Timers pour mettre à jour les points de vie des plantes 
    unsigned long derniereMiseAJourPlantes;
    const unsigned long intervalMiseAJourPlantes = 30000; // 30s

public:

    //Constructeur 
    Jardin();

    //Initialisation du jardin 
    void init();

    //Programme
    void run();

    // Ajouter une plante au jardin
    void AjouterPlante(Plante* plante);
};

#endif