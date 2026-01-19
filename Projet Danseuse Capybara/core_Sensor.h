#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

// Classe de base abstraite pour tous les capteurs.
// Utilisation de l'héritage : les capteurs concrets (TouchButton, LightSensor, UltrasonicSensor, etc.)
// hériteront de Sensor. Cette classe fournit une interface commune avec :
// - `begin()` (méthode pure virtuelle pour initialiser le capteur).
// - `name()` (méthode pure virtuelle pour obtenir un nom/identifiant du capteur).
// Le destructeur virtuel par défaut permet la destruction correcte via un pointeur de base.

class Sensor {
public:
  virtual ~Sensor() = default;           // Destructeur virtuel par défaut
  virtual void begin() = 0;              // Méthode virtuelle pure d'initialisation
  virtual String name() const = 0;       // Méthode virtuelle pure pour obtenir le nom du capteur
};

#endif
