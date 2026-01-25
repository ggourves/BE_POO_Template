#include "Application.h"
#include "Hardware/Grid.cpp"
#include "Hardware/Capteur.cpp"
#include "Hardware/Led.cpp"
#include "liste/bin.cpp"
#include "liste/caracteristics.cpp"
#include "liste/cellule.cpp"
#include "liste/file.cpp"
#include "liste/item.cpp"
#include "Manager/DetectionManager.cpp"
#include "Manager/itemsManager.cpp"

// Déclaration de l'array des LEDs physiques
CRGB leds[NUM_LEDS];

Application myApplication;

void setup() 
{
  // put your setup code here, to run once:
  myApplication.init();
}

void loop() 
{
  // put your main code here, to run repeatedly:
  myApplication.run();
}
