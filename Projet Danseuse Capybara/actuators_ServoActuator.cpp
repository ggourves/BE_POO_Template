#include "actuators_ServoActuator.h"

// Constructeur : initialise les angles et la direction par défaut (commence à minAngle, direction vers la hausse)
ServoActuator::ServoActuator(int pin, int minAngle, int maxAngle, int stepAngle)
  : pin_(pin),
    minAngle_(minAngle), maxAngle_(maxAngle), stepAngle_(stepAngle),
    angle_(minAngle), direction_(1) {}

void ServoActuator::begin() {
  servo_.attach(pin_);          // Attache le servo à la broche spécifiée
  servo_.write(minAngle_);      // Positionne le servo à l'angle minimum initial
}

void ServoActuator::home() {
  angle_ = minAngle_;           // Réinitialise l'angle actuel au minimum
  direction_ = 1;               // Réinitialise la direction du mouvement (1 = vers l'avant)
  servo_.write(minAngle_);      // Replace physiquement le servo à l'angle minimum (position "de départ")
}

void ServoActuator::step() {
  servo_.write(angle_);                             // Déplace le servo à l'angle courant
  angle_ += direction_ * stepAngle_;                // Calcule le prochain angle en avançant d'un "pas" dans la direction actuelle
  if (angle_ >= maxAngle_ || angle_ <= minAngle_) {
    direction_ *= -1;                               // Inverse la direction si on a atteint un des angles extrêmes
  }
}
