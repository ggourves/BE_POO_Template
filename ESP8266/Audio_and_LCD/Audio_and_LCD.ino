#include <Arduino.h>
#include <LittleFS.h>                 // Bibliothèque LittleFS faire sortir la musique
#include "AudioFileSourceLittleFS.h"  // Source Audio LittleFS pour lire la musique
#include "AudioGeneratorMP3.h"        // Pour convertir la source en musique
#include "AudioOutputI2S.h"           // Pour envoyer la musique
#include <SoftwareSerial.h>           // Ajouter un port TX/RX pour l'ESP8266
#include <Wire.h>
#include "rgb_lcd.h"
#include <ESP8266WiFi.h>
// --- CONFIGURATION ---
SoftwareSerial Mega(14, 12);  // Tx en 14 et Rx en 12 correspondant à D6 et D5.

// Generation des adresses du Fichier Audio

AudioGeneratorMP3 *mp3;
AudioFileSourceLittleFS *file;
AudioOutputI2S *out;
rgb_lcd lcd;
char codeDisplay[5] = { 'A', 'A', 'A', 'A', 'A' };  // Les lettres actuelles
int selectedPos = 0;                                // Quelle lettre clignote ? (0 à 4)
bool blinkState = true;                             // Pour l'effet clignotant
unsigned long lastBlinkTime = 0;                    // Pour gérer le clignotement

void setup() {
  WiFi.mode(WIFI_OFF); 
  WiFi.forceSleepBegin();
  delay(1);

  Mega.begin(9600);

  lcd.begin(16, 2);
  lcd.setRGB(0, 0, 200);

  if (!LittleFS.begin()) {
    lcd.setRGB(255, 0, 0);
    lcd.print("Err: LittleFS");
    while(1); // On bloque si ça ne marche pas
  }

  out = new AudioOutputI2S();
  out->SetGain(0.4);  // Volume 40%
  mp3 = new AudioGeneratorMP3();

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Mot de passe :");
  Update_Letter(true);  // Force l'affichage
}

void playFile(String filename) {
  // Arrêt propre si déjà en lecture
  if (mp3->isRunning()) {
    mp3->stop();
  }

  // --- GESTION DU NOM DE FICHIER ---
  // Ajouter .mp3 si manquant
  if (!filename.endsWith(".mp3")) filename += ".mp3";
  // Ajouter le / au début si manquant pour LittleFS
  if (!filename.startsWith("/")) filename = "/" + filename;

  if (LittleFS.exists(filename)) {  // Regarde si le fichier existe ou non
    // 4. NETTOYAGE MÉMOIRE CRITIQUE
    // Si 'file' a déjà été utilisé, on le supprime pour libérer la RAM
    if (file != nullptr) {
      delete file;
      file = nullptr;
    }
    // Lecture avec LittleFS
    file = new AudioFileSourceLittleFS(filename.c_str());
    mp3->begin(file, out);
  }
}

void Update_Letter(bool ForceOn) {  // ForceOn sert au moment ou on ne veut plujs clignoter
  int positions[5] = { 2, 5, 8, 11, 14 };
  for (int i = 0; i < 5; i++) {
    lcd.setCursor(positions[i], 1);

    if (i == selectedPos) {
      if (blinkState or ForceOn) {
        lcd.print(codeDisplay[i]);
      } else {
        lcd.print(" ");
      }
    }
    else
      lcd.print(codeDisplay[i]);
  }
}

void loop() {
  // 1. Moteur Audio
  if (mp3->isRunning()) {
    if (!mp3->loop()) {
      mp3->stop();
    }
  }

  if (millis() - lastBlinkTime > 500) {
    lastBlinkTime = millis();
    blinkState = !blinkState;
    Update_Letter(false);
  }

  // 2. Ecoute du Mega
  if (Mega.available()) {
    String command = Mega.readStringUntil('\n');
    command.trim();
    if (command.startsWith("SEL:")) {
      selectedPos = command.substring(4).toInt();
      blinkState = true;
      Update_Letter(true);
    } else if (command.startsWith("SET:")) {
      int pos = command.charAt(4) - '0';  // On récupère le chiffre à la position 4

      char letter = command.charAt(6);  // On récupère la lettre à la position 6

      codeDisplay[pos] = letter;
      Update_Letter(true);
    } else if (command.startsWith("PLAY:")) {
      String soundName = command.substring(5);
      playFile(soundName);
    }
  }
}
