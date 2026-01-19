#include "actuators_BuzzerActuator.h"

// Constructeur : stocke la broche du buzzer
BuzzerActuator::BuzzerActuator(int pin) : pin_(pin) {}

void BuzzerActuator::begin() {
  pinMode(pin_, OUTPUT);   // Configure la broche du buzzer en sortie
  noTone(pin_);            // S'assure qu'aucun son n'est joué au départ (désactive le buzzer)
}

void BuzzerActuator::stop() {
  noTone(pin_);            // Arrête le son du buzzer (si une note était en cours)
}

void BuzzerActuator::playNote(const Note& n, bool enabled) {
  if (n.div <= 0) return;  // Si la note a une division non valide (<=0), on ne la joue pas

  int noteDurMs = 1000 / n.div;        // Durée totale de la note en millisecondes (ex: div=4 -> 250 ms si noire)
  int onMs  = (int)(noteDurMs * 0.65); // Durée pendant laquelle le son est émis (65% de la durée totale)
  int offMs = noteDurMs - onMs;        // Durée de silence qui suit (35% de la durée)

  if (enabled) {
    tone(pin_, n.freq);    // Joue un son à la fréquence spécifiée par la note
    delay(onMs);           // Maintient le son pendant la durée "on"
    noTone(pin_);          // Coupe le son
    delay(offMs);          // Attend en silence pendant la durée "off"
  } else {
    // Si le son est désactivé (mute ou nuit), on n'émet pas de son et on attend toute la durée de la note
    delay(noteDurMs);
  }
}
