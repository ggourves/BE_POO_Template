/////////////////////CLASSE BOUTON POUSSOIR////////////////////////////////////

#ifndef _BoutonPoussoir_hpp
#define _BoutonPoussoir_hpp
#include <Arduino.h>
#include "Capteur.hpp"

#define BROCHE_BP1 D8

class BoutonPoussoir : public Capteur {

  protected : 

    unsigned long dernierChangement;
    bool dernierEtat;
    const unsigned long antiRebond = 50; 
    bool etatPrecedent;


  public : 

  //Constructeur 
    BoutonPoussoir(int b ); 

  //fonction qui lit l'état du bp (appuyé ou non)
    bool LireEtat(); 

  //fonction qui détecte si le bouton est appuyé 
    bool AppuiDetecte();

   //Destructeur 
  ~BoutonPoussoir(); 

};


#endif