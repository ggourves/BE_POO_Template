/////////////////////CLASSE CAPTEUR TEMPERATURE ET HUMIDITE////////////////////////////////////

#ifndef _CapteurTemperature_hpp
#define _CapteurTemperature_hpp
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SHT31.h>
#include "Capteur.hpp"

class CapteurTemperature : public Capteur {

  protected : 

  float Temperature; 
  int Humidite; 
  Adafruit_SHT31 sht31; // objet capteur 


  public : 

    // Constructeur sans arguments 
    CapteurTemperature(); 

    // Init capteur I2C 
    void Init();

    // fonction qui lit la valeur de la température 
    float LireValeurtemp();
   
   // fonction qui affiche la valeur de la température 
    void AfficheTemperature();

  // fonction qui lit la valeur de l'humidité 
     float LireValeurhum();
   
   // fonction qui affiche la valeur de l'humidité 
     void AfficheHumidite();

  // fonction qui renvoie true si la plante a besoin d'être arrosée 
    bool NecessiteArrosage(float seuil);
  
  // Destructeur 
  ~CapteurTemperature(); 

};


#endif
