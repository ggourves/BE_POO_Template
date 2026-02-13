/////////////////////CLASSE LCD////////////////////////////////////

#ifndef LCD_HPP
#define LCD_HPP

#include <Arduino.h>
#include <Wire.h>
#include "rgb_lcd.h" 
#include "BoutonPoussoir.hpp"
#include "CapteurTemperature.hpp"
#include "plante.hpp"

class LCD {

protected:
    rgb_lcd lcd; // objet LCD
    const int colorR = 204; 
    const int colorG = 0; 
    const int colorB = 77; 

public:
   
   //Constructeur
    LCD();

    // fonction qui nitialise le lcd 
    void Init();

    // fonction qui affiche un message 
    void AfficherMessage(const String& message);

    // fonction qui affiche la température
    void AfficherTemperature(float temperature);

    // fonction qui affiche l'humidité
    void AfficherHumidite(float humidite);

    //fonction qui gère l'affichage cyclique sur le LCD 
    void GererMenuLCD(BoutonPoussoir& bp, CapteurTemperature& Temp, std::vector<Plante*>& plantes);

    // Efface l'écran
    void Effacer();

    //Destructeur
    ~LCD(); 

};

#endif
