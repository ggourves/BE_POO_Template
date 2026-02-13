/////////////////////CLASSE LED////////////////////////////////////

#ifndef LED_HPP
#define LED_HPP

#include "Actionneur.hpp"

#define BROCHE_LED D5

class Led : public Actionneur {
public:

    //Constructeur
    Led(int b);
    
    //fonction qui allume la led 
    void Activer() override;

    //fonction qui éteint la led 
    void Desactiver() override;

    //fonction qui fait clignoter la led 
    void Toggle();

    //Destructeur
    ~Led();
};

#endif

