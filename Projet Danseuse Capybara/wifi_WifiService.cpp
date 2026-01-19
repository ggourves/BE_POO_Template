#include "wifi_WifiService.h"

WifiService::WifiService(const char* ssid, const char* pass)
  : ssid_(ssid), pass_(pass) {
  // Constructeur: initialise les identifiants Wi-Fi (SSID et mot de passe)
}

void WifiService::onSetSong(void (*fn)(int))   { setSong_ = fn; }   // Enregistre le callback pour changer de chanson
void WifiService::onSetMute(void (*fn)(bool))  { setMute_ = fn; }   // Enregistre le callback pour activer/désactiver le son
void WifiService::onSetLine1(void (*fn)(const String&)) { setL1_ = fn; } // Enregistre le callback pour changer la ligne1 du LCD
void WifiService::onSetLine2(void (*fn)(const String&)) { setL2_ = fn; } // Enregistre le callback pour changer la ligne2 du LCD

void WifiService::setStatusJson(const String& json) {
  statusJson_ = json;  // Met à jour la chaîne JSON représentant l'état courant (sera renvoyée aux clients HTTP)
}

void WifiService::begin() {
  WiFi.mode(WIFI_STA);            // Configure l'ESP8266 en mode Station (client Wi-Fi)
  WiFi.begin(ssid_, pass_);       // Tente de se connecter au réseau Wi-Fi donné

  // On évite de bloquer indéfiniment en attendant la connexion Wi-Fi (timeout ~8 secondes)
  unsigned long t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t0 < 8000) {
    delay(200);
    yield();  // Laisse le CPU à d'autres tâches (évite le watchdog reset)
  }

  routes();               // Configure les routes HTTP du serveur web (endpoints)
  server_.begin();        // Démarre le serveur web

  // Log sur la console série l'état de la connexion Wi-Fi
  Serial.print("WiFi: ");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("connected, IP=");
    Serial.println(WiFi.localIP());  // Affiche l'adresse IP obtenue
  } else {
    Serial.println("not connected (server still running)");
  }
}

void WifiService::loop() {
  server_.handleClient(); // Gère les requêtes HTTP entrantes (s'il y en a)
  yield();                // Permet au système d'effectuer d'autres tâches (bonne pratique sur ESP)
}

void WifiService::routes() {
  // On définit les différentes routes (endpoints) du serveur web.
  // (On utilise des lambdas capturant l'objet courant [this] pour accéder aux méthodes/callbacks de WifiService)
  server_.on("/", [this]() {
    String html =
      "<html><body>"
      "<h2>Bailarina ESP8266</h2>"
      "<p><a href='/status'>/status</a></p>"  // Lien vers l'état JSON
      "<p>Song: <a href='/song?i=0'>0</a> <a href='/song?i=1'>1</a> <a href='/song?i=2'>2</a></p>"  // Liens pour changer de chanson
      "<p>Mute: <a href='/mute?on=1'>ON</a> <a href='/mute?on=0'>OFF</a></p>"  // Liens pour activer/désactiver le mute
      "</body></html>";
    server_.send(200, "text/html", html);  // Envoie la page HTML au client
  });

  // Route "/status": renvoie l'état courant de l'application au format JSON
  server_.on("/status", [this]() {
    server_.send(200, "application/json", statusJson_);
  });

  // Route "/song": permet de sélectionner une chanson via un paramètre 'i'
  server_.on("/song", [this]() {
    if (!server_.hasArg("i")) {
      server_.send(400, "text/plain", "missing i"); 
      return;
    }
    int i = server_.arg("i").toInt();
    if (setSong_) setSong_(i);                  // Appelle la fonction de rappel enregistrée (BailarinaApp::setSong)
    server_.send(200, "text/plain", "ok");
  });

  // Route "/mute": permet d'activer ou désactiver le son (mute) via un paramètre 'on'
  server_.on("/mute", [this]() {
    if (!server_.hasArg("on")) {
      server_.send(400, "text/plain", "missing on"); 
      return;
    }
    bool on = server_.arg("on").toInt() == 1;
    if (setMute_) setMute_(on);                 // Appelle le callback BailarinaApp::setMute
    server_.send(200, "text/plain", "ok");
  });

  // Route "/lcd": permet de mettre à jour les lignes de texte du LCD via paramètres 'l1' et 'l2'
  server_.on("/lcd", [this]() {
    if (server_.hasArg("l1") && setL1_) setL1_(server_.arg("l1"));
    if (server_.hasArg("l2") && setL2_) setL2_(server_.arg("l2"));
    server_.send(200, "text/plain", "ok");
  });
}
