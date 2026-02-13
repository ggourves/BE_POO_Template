/////////////////////CLASSE BUZZER////////////////////////////////////

#ifndef BUZZER_HPP
#define BUZZER_HPP

#include "Actionneur.hpp"

#define BROCHE_BUZZER D6

class Buzzer : public Actionneur {
public:

    //Constructeur 
    Buzzer(int b);
    
    //fonction qui active le buzzer
    void Activer() override;

    //fonction qui désactive le buzzer 
    void Desactiver() override;

    // fonction qui active et désactive le buzzer toutes les 100ms
    void Bip(int duree = 100);

    //fonction qui bip selon un nombre précis 
    void Signal(int nbBips, int duree = 100, int pause = 100);

    //Destructeur 
    ~Buzzer();
};

#endif