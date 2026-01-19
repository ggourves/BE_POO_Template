#ifndef WIFI_SERVICE_H
#define WIFI_SERVICE_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Classe WifiService : gère la connexion Wi-Fi et un serveur web sur l'ESP8266 pour contrôler l'application à distance.
// Permet de configurer le Wi-Fi (SSID, mot de passe) et expose des routes HTTP pour interagir avec la Bailarina.
// Des fonctions de callback (pointeurs de fonction) peuvent être enregistrées pour réagir aux requêtes (changer la chanson, mute, texte LCD, etc.).

class WifiService {
public:
  WifiService(const char* ssid, const char* pass);

  void begin();   // Connecte au Wi-Fi et démarre le serveur web
  void loop();    // À appeler régulièrement dans la boucle principale pour gérer les clients web

  void setStatusJson(const String& json);  // Définit le texte JSON à renvoyer pour la route /status

  // Enregistrement de fonctions de rappel pour contrôler l'application via HTTP
  void onSetSong(void (*fn)(int));
  void onSetMute(void (*fn)(bool));
  void onSetLine1(void (*fn)(const String&));
  void onSetLine2(void (*fn)(const String&));

private:
  const char* ssid_;   // SSID du réseau Wi-Fi
  const char* pass_;   // Mot de passe du réseau Wi-Fi
  ESP8266WebServer server_{80}; // Serveur web HTTP écoutant sur le port 80

  String statusJson_ = "{}";    // Chaîne JSON représentant l'état courant, renvoyée sur /status

  // Pointeurs de fonction (callbacks) vers les fonctions de BailarinaApp correspondantes
  void (*setSong_)(int) = nullptr;
  void (*setMute_)(bool) = nullptr;
  void (*setL1_)(const String&) = nullptr;
  void (*setL2_)(const String&) = nullptr;

  void routes();  // Configure les différentes routes (endpoints) du serveur web
};

#endif
