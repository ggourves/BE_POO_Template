/////////////////////CLASSE CAPTEUR////////////////////////////////////

#ifndef _Capteur_hpp
#define _Capteur_hpp

#include "Peripherique.hpp"


class Capteur : public Peripherique {

  protected :

    public : 

  // Constructeur sans argument pour I2C 
  Capteur(); 

  // Constructeur avec la broche en argument 
  Capteur(int b); 

   // Destructeur 
  ~Capteur(); 

};


#endif
