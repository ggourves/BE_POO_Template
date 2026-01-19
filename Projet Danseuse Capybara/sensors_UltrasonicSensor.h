#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>
#include "core_Sensor.h"

// Classe UltrasonicSensor : capteur de distance à ultrasons (p. ex. HC-SR04).
// Hérite de Sensor (héritage) pour s'intégrer dans la hiérarchie de capteurs.
// Ce capteur utilise la même broche pour émettre un son ultrasonique et écouter l'écho afin de mesurer une distance.

class UltrasonicSensor : public Sensor { // Héritage : UltrasonicSensor est une classe dérivée de Sensor
public:
  explicit UltrasonicSensor(int pinSig);
  void begin() override;
  String name() const override;
  float distanceCm();  // Mesure la distance en centimètres (renvoie -1.0 si pas d'objet détecté)

private:
  int pin_;  // Broche utilisée pour le signal trigger/echo du capteur ultrason
};

#endif
