#include "plante.hpp"

Plante::Plante(){

  Compteur++;
  point_de_vie=5;
}

Plante::~Plante(){

}


int Plante::Compteur=0;
 

int Plante::GetCompteur(){

  return Compteur;

}

void Plante::ModifPointDeVie(CapteurTemperature &capteurhum) {
    int seuil = GetSeuilArrosage(); 
    
    if (capteurhum.LireValeurhum() < seuil) {
        point_de_vie -= 1;
        if (point_de_vie < 0) {
          point_de_vie = 0;
          }}
    else if (capteurhum.LireValeurhum() > seuil+5){
        point_de_vie += 1;
         if (point_de_vie > 10) {
          point_de_vie = 10;
          }
    }

}
    
