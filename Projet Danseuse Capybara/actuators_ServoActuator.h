#ifndef SERVO_ACTUATOR_H
#define SERVO_ACTUATOR_H

#include <Arduino.h>
#include <Servo.h>
#include "core_Actuator.h"

// Classe ServoActuator : actuateur pour contrôler un servo-moteur.
// Hérite de Actuator (héritage) pour suivre l'interface commune.
// Contrôle un servo qui oscille entre un angle minimum et maximum, avec un certain pas d'incrément à chaque mouvement.

class ServoActuator : public Actuator { // Héritage : ServoActuator est une classe dérivée de Actuator
public:
  ServoActuator(int pin, int minAngle, int maxAngle, int stepAngle);
  void begin() override;

  void home();  // Ramène le servo à l'angle minimum (position de départ)
  void step();  // Effectue un "pas" de mouvement (fait bouger le servo d'un incrément prédéfini)

private:
  int pin_;                 // Broche à laquelle le servo est connecté
  int minAngle_, maxAngle_; // Angles minimum et maximum entre lesquels le servo peut osciller
  int stepAngle_;           // Incrément en degrés pour chaque mouvement de step()
  int angle_;               // Angle actuel du servo
  int direction_;           // Direction de mouvement: 1 (aller vers max) ou -1 (revenir vers min)
  Servo servo_;             // Objet Servo (librairie Arduino) qui pilote le servo-moteur
};

#endif
