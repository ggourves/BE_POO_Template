/////////////////////CLASSE PERIPHERIQUE////////////////////////////////////

#ifndef _Peripherique_hpp
#define _Peripherique_hpp

class Peripherique {

protected : 
    int broche; 

public : 

//Constructeur sans argument pour I2C 
  Peripherique(); 

//Constructeur avec argument
 Peripherique(int broche); 

//destructeur
  ~Peripherique(); 

};


#endif
