#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include <Arduino.h>
#include "core_Sensor.h"

// Classe LightSensor : capteur de luminosité (par exemple une photoresistance).
// Hérite de Sensor (utilisation de l'héritage) pour fournir une interface commune.
// Ce capteur lit une valeur analogique et détermine si l'environnement est sombre ou éclairé en comparant à un seuil.

class LightSensor : public Sensor { // Héritage : LightSensor est une classe dérivée de Sensor
public:
  LightSensor(int pinAnalog, int threshold);
  void begin() override;
  String name() const override;

  int value();    // Renvoie la valeur lue (analogique) du capteur de lumière
  bool isNight(); // Indique si la luminosité est inférieure au seuil (true = il fait "nuit")

private:
  int pin_;        // Broche analogique du capteur de lumière
  int threshold_;  // Seuil en dessous duquel on considère qu'il fait nuit
};

#endif
