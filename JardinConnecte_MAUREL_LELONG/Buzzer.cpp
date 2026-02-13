#include <Arduino.h>
#include "Buzzer.hpp"

Buzzer::Buzzer(int b) : Actionneur(b) {
}

void Buzzer::Activer() {
    etat = true;
    digitalWrite(broche, HIGH);
}

void Buzzer::Desactiver() {
    etat = false;
    digitalWrite(broche, LOW);
}

void Buzzer::Bip(int duree) {
    Activer();
    delay(duree);
    Desactiver();
}

void Buzzer::Signal(int nbBips, int duree, int pause) {
    for(int i = 0; i < nbBips; i++) {
        Activer();
        delay(duree);
        Desactiver();
        if(i < nbBips - 1) {
            delay(pause);
        }
    }
}

Buzzer::~Buzzer() {
    Desactiver();
}