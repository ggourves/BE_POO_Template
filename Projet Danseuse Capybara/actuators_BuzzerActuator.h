#ifndef BUZZER_ACTUATOR_H
#define BUZZER_ACTUATOR_H

#include <Arduino.h>
#include "core_Actuator.h"
#include "music_Song.h"  // pour le type Note

// Classe BuzzerActuator : actuateur pour jouer de la musique via un buzzer piezo.
// Hérite de Actuator (héritage) et permet de jouer des notes musicales.
// Utilise la classe Song/Note pour obtenir les fréquences et durées des notes à jouer.

class BuzzerActuator : public Actuator { // Héritage : BuzzerActuator est une classe dérivée de Actuator
public:
  explicit BuzzerActuator(int pin);
  void begin() override;

  void stop();                            // Arrête tout son sur le buzzer
  void playNote(const Note& n, bool enabled); // Joue une note donnée (si enabled=true) ou attend silencieusement sa durée si disabled

private:
  int pin_;   // Broche du buzzer
};

#endif
