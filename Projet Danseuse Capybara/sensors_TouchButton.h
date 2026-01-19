#ifndef TOUCH_BUTTON_H
#define TOUCH_BUTTON_H

#include <Arduino.h>
#include "core_Sensor.h"

// Classe TouchButton : représente un capteur de bouton tactile/capacitif.
// Elle hérite de Sensor (utilisation du mécanisme d'héritage) pour s'intégrer dans la collection de capteurs.
// Ce capteur gère un bouton avec un anti-rebond logiciel (debounce) pour détecter les "clics".

class TouchButton : public Sensor { // Héritage : TouchButton est une classe dérivée de Sensor
public:
  TouchButton(int pinDigital, unsigned long debounceMs);
  void begin() override;
  String name() const override;

  bool clicked();  // Renvoie true si le bouton a été pressé (détection avec anti-rebond)

private:
  int pin_;                   // Broche du microcontrôleur à laquelle le bouton est connecté
  unsigned long debounceMs_;  // Durée de debounce (en ms) pour filtrer les fluctuations rapides
  int lastRead_;              // Dernière lecture brute du bouton (HIGH/LOW)
  int stable_;                // Dernier état stable confirmé du bouton
  unsigned long lastDebounce_;// Temps du dernier changement d'état détecté (pour le calcul du debounce)
};

#endif
