/////////////////////CLASSE PLANTE////////////////////////////////////

#ifndef _plante_hpp
#define _plante_hpp

#include <Arduino.h>
#include "CapteurTemperature.hpp"


class Plante {

protected :

  static int Compteur; //Nombre de plantes crées 
  int point_de_vie; //Points de vie de chaque plante 
  int dureeArrosage; // Durée arrosage de chaque plante 
  

  public :

  //Constructeur
  Plante();

  //fonction virtuelle qui affiche les caracteristiques de chaque plantes 
  virtual String Caracteristiques()=0;

  //fonction virtuelle qui retourne le temps de pousse de chaque plante 
  virtual int TempsDePousse()=0;

  //fonction virtuelle qui retourne la durée d'arrosage de chaque plante 
  virtual int GetDureeArrosage()=0;  

  //fonction virtuelle qui retourne le seuil d'arrosage de chaque plante 
  virtual float GetSeuilArrosage()=0; 

  //fonction virtuelle qui retourne les points de vie de chaque plante 
  virtual int GetPointDeVie()=0;

  //fonction qui retourne le nombre de plantes crées 
  int GetCompteur ();

  //fonction qui modifie les points de vie de la plante si elle n'est pas bien arrosée 
  void ModifPointDeVie(CapteurTemperature &capteur);

  //Destructeur
    ~Plante();
};




#endif
