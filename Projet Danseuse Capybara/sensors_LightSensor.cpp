#include "sensors_LightSensor.h"

// Constructeur : initialise le pin analogique et le seuil de luminosité
LightSensor::LightSensor(int pinAnalog, int threshold)
  : pin_(pinAnalog), threshold_(threshold) {}

void LightSensor::begin() {
  // Aucune configuration spécifique nécessaire pour un capteur analogique sur Arduino
}

String LightSensor::name() const {
  return "LightSensor";  // Nom du capteur de lumière
}

int LightSensor::value() {
  return analogRead(pin_);  // Lit la valeur analogique brute du capteur de lumière (0-1023)
}

bool LightSensor::isNight() {
  // Détermine s'il fait "nuit" en comparant la valeur lue au seuil
  return value() <= threshold_;
}
