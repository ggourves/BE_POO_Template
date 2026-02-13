#include <Arduino.h>
#include "Actionneur.hpp"

Actionneur::Actionneur(int b) : Peripherique(b) {
    etat = false;
    pinMode(broche, OUTPUT);
    digitalWrite(broche, LOW);
}

bool Actionneur::GetEtat(){ 
    return etat; 
}

Actionneur::~Actionneur() {
}