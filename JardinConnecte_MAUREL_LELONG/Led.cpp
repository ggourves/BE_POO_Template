#include <Arduino.h>
#include "Led.hpp"

Led::Led(int b) : Actionneur(b) {
}

void Led::Activer() {
    etat = true;
    digitalWrite(broche, HIGH);
}

void Led::Desactiver() {
    etat = false;
    digitalWrite(broche, LOW);
}

void Led::Toggle() {
    if (etat) {
        Desactiver();
    } else {
        Activer();
    }
}

Led::~Led() {
    Desactiver();
}
