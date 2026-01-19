#include "sensors_UltrasonicSensor.h"

// Constructeur : enregistre simplement la broche du capteur ultrason
UltrasonicSensor::UltrasonicSensor(int pinSig) : pin_(pinSig) {}

void UltrasonicSensor::begin() {
  // Pas de configuration spéciale requise au démarrage pour le capteur ultrason
}

String UltrasonicSensor::name() const {
  return "UltrasonicSensor";  // Nom du capteur (utilisé à des fins d'identification)
}

float UltrasonicSensor::distanceCm() {
  // Envoi d'une impulsion ultrasonore
  pinMode(pin_, OUTPUT);
  digitalWrite(pin_, LOW);
  delayMicroseconds(2);    // Impulsion basse de 2 µs pour stabiliser le capteur
  digitalWrite(pin_, HIGH);
  delayMicroseconds(10);   // Impulsion haute de 10 µs pour déclencher le "ping" ultrasonore
  digitalWrite(pin_, LOW);

  // Réception de l'écho ultrasonore
  pinMode(pin_, INPUT);
  long duration = pulseIn(pin_, HIGH, 50000); // Mesure la durée de l'état HIGH (écho) sur la broche (timeout 50ms)
  if (duration <= 0) return -1.0f;            // Si aucune réponse (pas d'objet détecté), on renvoie -1.0
  return duration / 58.0f;                   // Convertit la durée en distance (approx. 58 µs par cm)
}
