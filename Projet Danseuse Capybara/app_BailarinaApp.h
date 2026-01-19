#ifndef BAILARINA_APP_H
#define BAILARINA_APP_H

#include <Arduino.h>
#include <vector>
#include <Wire.h>
#include "rgb_lcd.h"

#include "wifi_WifiService.h"
#include "core_Sensor.h"
#include "core_Actuator.h"
#include "music_Song.h"
#include "sensors_UltrasonicSensor.h"
#include "sensors_LightSensor.h"
#include "sensors_TouchButton.h"
#include "actuators_BuzzerActuator.h"
#include "actuators_ServoActuator.h"
#include "actuators_LedActuator.h"

// Classe principale BailarinaApp : gère l'ensemble de l'application de la "bailarina" (danseuse robotisée).
// Cette classe orchestre les capteurs, les actuateurs, la logique de danse, la musique, l'afficheur LCD et la communication Wi-Fi.
// Elle contient les instances de tous les capteurs et actuateurs, les chansons pré-définies, et les méthodes pour initialiser et mettre à jour le système.

class BailarinaApp {
public:
  BailarinaApp(
    int pinServo, int pinBuzzer, int pinUS, int pinTouch, int pinLedRed, int pinLight,
    int lightThreshold,
    const char* line1, const char* line2
  );

  void begin();   // Initialise l'application (doit être appelé dans setup())
  void update();  // Met à jour l'état de l'application (à appeler régulièrement dans loop())

  // Méthodes de contrôle depuis le Wi-Fi (appels distants)
  void setSong(int i);              // Sélectionne la chanson n°i (0,1,2)
  void setMute(bool m);             // Active (m=true) ou désactive (m=false) le mode silencieux (mute)
  void setLine1(const String& s);   // Change le texte de la première ligne du LCD
  void setLine2(const String& s);   // Change le texte de la deuxième ligne du LCD

private:
  // Écran LCD
  rgb_lcd lcd_;         // Écran LCD RGB 16x2 pour afficher des informations
  const char* line1_;   // Texte fixe de la ligne 1 (par exemple, nom du projet ou des auteurs)
  const char* line2_;   // Texte fixe de la ligne 2 (non utilisé directement, on utilise lcdLine1_ et lcdLine2_)
  String lcdLine1_;     // Buffer modifiable pour la ligne 1 du LCD
  String lcdLine2_;     // Buffer modifiable pour la ligne 2 du LCD

  void updateLcdText(); // Met à jour le texte affiché sur le LCD (selon lcdLine1_ et lcdLine2_)

  // Capteurs (Sensors)
  UltrasonicSensor us_;     // Capteur ultrason (distance)
  LightSensor light_;       // Capteur de luminosité
  TouchButton touch_;       // Bouton tactile
  std::vector<Sensor*> sensors_;   // Utilisation de la STL : vecteur de pointeurs vers des capteurs (pour itérer facilement sur tous les capteurs)

  // Actuateurs (Actuators)
  BuzzerActuator buzzer_;   // Buzzer pour la musique
  ServoActuator servo_;     // Servo-moteur pour la danse
  LedActuator led_;         // LED indicatrice
  std::vector<Actuator*> actuators_; // Vecteur de pointeurs vers des actuateurs (pour les initialiser/contrôler de manière polymorphique)

  // Chansons (mélodies)
  Song song0_, song1_, song2_; // Trois chansons préprogrammées
  int currentSong_ = 0;        // Index de la chanson courante (0, 1 ou 2)

  // Constantes de fréquences des notes (Hz)
  static constexpr int NOTE_C4 = 262;
  static constexpr int NOTE_D4 = 294;
  static constexpr int NOTE_E4 = 330;
  static constexpr int NOTE_F4 = 349;
  static constexpr int NOTE_G4 = 392;
  static constexpr int NOTE_A4 = 440;
  static constexpr int NOTE_B4 = 494;
  static constexpr int NOTE_C5 = 523;

  void buildSongs();                // Construit les chansons (ajoute les notes aux Song correspondantes)
  const Song& currentSong() const;  // Renvoie un accès constant à la chanson courante

  bool mute_ = false;       // Indicateur muet (true si le son est coupé)
  WifiService wifi_;        // Service Wi-Fi pour la communication (serveur web intégré)
};

#endif
