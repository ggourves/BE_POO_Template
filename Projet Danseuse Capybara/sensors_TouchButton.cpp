#include "sensors_TouchButton.h"

// Constructeur : initialise les attributs et l'état initial (bouton non pressé, stable à LOW)
TouchButton::TouchButton(int pinDigital, unsigned long debounceMs)
  : pin_(pinDigital), debounceMs_(debounceMs),
    lastRead_(LOW), stable_(LOW), lastDebounce_(0) {}

void TouchButton::begin() {
  pinMode(pin_, INPUT);      // Configure la broche du bouton tactile en entrée
  lastRead_ = LOW;           // On considère initialement que le bouton n'était pas appuyé
  stable_ = LOW;             // État stable initial (non appuyé)
  lastDebounce_ = 0;         // Reset du compteur de temps de debounce
}

String TouchButton::name() const {
  return "TouchButton";      // Retourne le nom du capteur (pour identification)
}

bool TouchButton::clicked() {
  int reading = digitalRead(pin_);  // Lecture de l'état actuel du bouton (HIGH ou LOW)

  if (reading != lastRead_) {
    // Si la lecture actuelle diffère de la précédente, c'est qu'un changement vient d'avoir lieu.
    // On enregistre le moment du changement et on met à jour la dernière lecture.
    lastDebounce_ = millis();
    lastRead_ = reading;
  }

  // Si suffisamment de temps s'est écoulé depuis le dernier changement d'état (anti-rebond):
  if ((millis() - lastDebounce_) > debounceMs_) {
    // On considère que l'état du bouton s'est stabilisé.
    if (reading != stable_) {
      // Si l'état stable a changé (après la période de debounce), on le met à jour.
      stable_ = reading;
      if (stable_ == HIGH) return true;  // Si le nouvel état stable est HIGH, cela signifie un appui ("clic")
    }
  }
  return false;  // Par défaut, pas de clic détecté
}
