#include "actuators_LedActuator.h"

// Constructeur : stocke la broche de la LED
LedActuator::LedActuator(int pin) : pin_(pin) {}

void LedActuator::begin() {
  pinMode(pin_, OUTPUT);  // Configure la broche en sortie pour contrôler la LED
  off();                  // Éteint la LED par défaut au démarrage
}

void LedActuator::on()  { digitalWrite(pin_, HIGH); }  // Allume la LED (niveau HIGH sur la broche)
void LedActuator::off() { digitalWrite(pin_, LOW);  }  // Éteint la LED (niveau LOW sur la broche)
void LedActuator::set(bool state) { state ? on() : off(); } // Fixe l'état de la LED en fonction du booléen
