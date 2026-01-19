#include <Arduino.h>
#include "app_BailarinaApp.h"

// Broches utilisées (NodeMCU ESP8266)
const int pinServo  = D4;
const int pinBuzzer = D7;
const int pinUS     = D5;
const int pinTouch  = D6;
const int pinLedRed = D0;
const int pinLight  = A0;

BailarinaApp app(
  pinServo, pinBuzzer, pinUS, pinTouch, pinLedRed, pinLight,
  350,                // Seuil de luminosité pour considérer qu'il fait nuit (0-1023)
  "Roberto & Kevin",  // Texte de la première ligne du LCD (par exemple, noms des auteurs)
  "Bailarina"         // Texte de la deuxième ligne du LCD (titre ou message initial)
);

void setup() {
  Serial.begin(115200);  // Initialisation de la communication série (pour debug)
  app.begin();           // Initialisation de l'application Bailarina (capteurs, actuateurs, Wi-Fi, etc.)
}

void loop() {
  app.update();          // Mise à jour en continu de la logique de l'application (appelée à chaque itération)
}
