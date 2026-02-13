/////////////////////CLASSE CAPTEUR TACTILE////////////////////////////////////

#ifndef _CapteurTactile_hpp
#define _CapteurTactile_hpp
#include <Arduino.h>
#include "Capteur.hpp"

#define BROCHE_CT D7

class CapteurTactile : public Capteur {

  protected :  
  
  public : 

  //Constructeur 
    CapteurTactile(int b);

  //fonction qui lit l'état du capteur tactile (touché ou non)
    bool LireEtat();

  //Destructeur
  ~CapteurTactile(); 

};


#endif