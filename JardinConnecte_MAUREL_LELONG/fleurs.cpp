#include "fleurs.hpp"



Fleurs::Fleurs(String n, String c, int dureeArrosage):Plante(){

  nom = n;
  couleur = c; 

}

String Fleurs::Caracteristiques(){

  String s= nom + " " + couleur ; 
  return s;

  
}

Fleurs::~Fleurs(){

}
 
