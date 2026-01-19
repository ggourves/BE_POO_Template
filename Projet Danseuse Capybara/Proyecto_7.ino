#include <Arduino.h>
#include "app_BailarinaApp.h"

// NodeMCU pins
const int pinServo  = D4;
const int pinBuzzer = D7;
const int pinUS     = D5;
const int pinTouch  = D6;
const int pinLedRed = D0;
const int pinLight  = A0;

BailarinaApp app(
  pinServo, pinBuzzer, pinUS, pinTouch, pinLedRed, pinLight,
  350,
  "Roberto & Kevin",
  "Bailarina"
);

void setup() {
  Serial.begin(115200);
  app.begin();
}

void loop() {
  app.update();
}
