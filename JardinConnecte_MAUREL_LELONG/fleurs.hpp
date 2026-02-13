/////////////////////CLASSE FLEURS////////////////////////////////////

#ifndef _fleurs_hpp
#define _fleurs_hpp

#include "plante.hpp"

class Fleurs: public Plante{

protected :

  String nom; //Nom de la fleur 
  String couleur;  //Couleur de la fleur 
 
public :

  //Constructeur 
  Fleurs(String nom, String couleur, int dureeArrosage);

  //fonction qui retourne les caracteriqtiques de la fleur (nom + couleur)
  String Caracteristiques();
 
 //Destructeur 
  ~Fleurs(); 

};


#endif
