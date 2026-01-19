#ifndef LED_ACTUATOR_H
#define LED_ACTUATOR_H

#include <Arduino.h>
#include "core_Actuator.h"

// Classe LedActuator : représente un actuateur LED (diode électroluminescente).
// Hérite de Actuator (héritage) pour fournir l'interface commune d'initialisation.
// Permet de contrôler une LED : l'allumer, l'éteindre ou définir son état.

class LedActuator : public Actuator { // Héritage : LedActuator est une classe dérivée de Actuator
public:
  explicit LedActuator(int pin);
  void begin() override;

  void on();             // Allume la LED
  void off();            // Éteint la LED
  void set(bool state);  // Allume ou éteint en fonction de `state` (true = on)

private:
  int pin_;  // Broche à laquelle la LED est connectée
};

#endif
