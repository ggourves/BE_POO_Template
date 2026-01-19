#include "app_BailarinaApp.h"

// Pour connecter les fonctions lambda du serveur web aux méthodes de l'instance BailarinaApp
static BailarinaApp* gApp = nullptr;

// Constructeur : initialise tous les composants de l'application
BailarinaApp::BailarinaApp(
  int pinServo, int pinBuzzer, int pinUS, int pinTouch, int pinLedRed, int pinLight,
  int lightThreshold,
  const char* line1, const char* line2
)
: lcd_(),  // Initialise l'écran LCD (rgb_lcd)
  line1_(line1), line2_(line2), // Stocke les textes initiaux pour le LCD

  // Capteurs (initialisation avec les broches et paramètres)
  us_(pinUS),
  light_(pinLight, lightThreshold),
  touch_(pinTouch, 80),

  // Actuateurs (initialisation avec les broches et paramètres)
  buzzer_(pinBuzzer),
  servo_(pinServo, 10, 170, 5),
  led_(pinLedRed),

  // Service Wi-Fi (mode Station) avec SSID et mot de passe
  wifi_("kvisbal", "99999999")
{
  // Stocke les adresses des capteurs et actuateurs dans les vecteurs pour un accès facile
  sensors_ = { &us_, &light_, &touch_ };
  actuators_ = { &buzzer_, &servo_, &led_ };
}

void BailarinaApp::begin() {
  Wire.begin(D2, D1);  // Initialise le bus I2C (utilisé par l'écran LCD, D2 = SDA, D1 = SCL sur NodeMCU)

  gApp = this;  // Enregistre l'instance actuelle dans le pointeur global (pour que les lambdas Wi-Fi puissent y accéder)

  // Relie les callbacks du WifiService aux méthodes de l'application (via le pointeur global gApp)
  wifi_.onSetSong([](int i){ if (gApp) gApp->setSong(i); });       // Quand le serveur web reçoit une commande de changement de chanson
  wifi_.onSetMute([](bool m){ if (gApp) gApp->setMute(m); });      // Commande pour (dés)activer le mode muet
  wifi_.onSetLine1([](const String& s){ if (gApp) gApp->setLine1(s); }); // Commande pour changer la ligne1 du LCD
  wifi_.onSetLine2([](const String& s){ if (gApp) gApp->setLine2(s); }); // Commande pour changer la ligne2 du LCD

  wifi_.begin();  // Démarre le service Wi-Fi (connexion au réseau et lancement du serveur web)

  // Configuration de l'écran LCD
  lcd_.begin(16, 2);              // Initialise l'écran LCD 16 colonnes x 2 lignes
  lcd_.setRGB(255, 255, 255);     // Fixe la couleur de fond du LCD (blanc)

  // Initialise tous les actuateurs et capteurs en appelant leur méthode begin() respective
  for (auto* a : actuators_) {
    a->begin();
  }
  for (auto* s : sensors_) {
    s->begin();
  }

  // Définit le texte initial à afficher sur le LCD
  lcdLine1_ = line1_;            // Première ligne (texte fixe passé au constructeur, ex: nom)
  lcdLine2_ = "chanson 1";       // Deuxième ligne par défaut : "chanson 1" (on commence avec la première chanson)

  // Construit les chansons et met à jour l'affichage du LCD
  buildSongs();
  updateLcdText();
}

void BailarinaApp::update() {
  // Cette fonction doit être appelée fréquemment (dans la loop Arduino) pour faire fonctionner la logistique de la bailarina.
  
  wifi_.loop();  // Fait tourner le serveur web pour traiter d'éventuelles requêtes HTTP en attente

  // Vérifie le bouton tactile pour passer à la chanson suivante si appuyé
  if (touch_.clicked()) {
    currentSong_ = (currentSong_ + 1) % 3;  // Change l'index de chanson (boucle de 0 à 2)
    updateLcdText();                       // Met à jour l'écran LCD pour afficher la nouvelle chanson
  }

  // Lecture des capteurs
  float dist = us_.distanceCm();       // Distance mesurée par le capteur ultrason (en cm)
  bool nightMode = light_.isNight();   // Détecte s'il fait sombre (mode nuit) via le capteur de lumière
  bool dancing = (dist > 10); // On décide de danser si un objet est détecté à moins de ~10 cm

  // Prépare une chaîne JSON contenant l'état courant (distance, lumière, mode nuit, en train de danser ou non, chanson, mute)
  String json = "{";
  json += "\"dist\":" + String(dist, 1) + ",";               // distance en cm (avec 1 décimale)
  json += "\"light\":" + String(light_.value()) + ",";       // valeur brute du capteur de lumière
  json += "\"night\":" + String(nightMode ? 1 : 0) + ",";    // indicateur mode nuit (1 ou 0)
  json += "\"dancing\":" + String(dancing ? 1 : 0) + ",";    // indicateur si la bailarina est en train de danser
  json += "\"song\":" + String(currentSong_) + ",";          // index de la chanson actuelle
  json += "\"mute\":" + String(mute_ ? 1 : 0);
  json += "}";
  wifi_.setStatusJson(json);  // Met à jour le JSON d'état dans le service Wi-Fi (pour que /status le reflète)

  // Si la condition pour danser n'est pas remplie, on arrête tout mouvement/son
  if (!dancing) {
    buzzer_.stop();    // Stoppe le buzzer (au cas où il jouerait une note)
    servo_.home();     // Remet le servo à sa position de repos (angle minimum)
    led_.off();        // Éteint la LED (pas de danse)
    wifi_.loop();      // Appel supplémentaire pour traiter le réseau
    delay(50);         // Petite pause pour éviter de tourner en boucle trop vite
    return;            // On quitte la fonction car on ne danse pas pour l'instant
  }

  // Si on doit danser:
  led_.on();  // Allume la LED pour indiquer que la danse (et la musique) commencent

  // Récupère la chanson courante à jouer
  const Song& s = currentSong();
  for (size_t i = 0; i < s.size(); i++) {
    // On itère sur chaque note de la chanson

    // On revérifie le bouton tactile pendant la lecture pour permettre de changer de chanson à la volée
    if (touch_.clicked()) {
      currentSong_ = (currentSong_ + 1) % 3;  // Passe à la chanson suivante
      updateLcdText();                       // Met à jour le LCD pour afficher la nouvelle chanson
      break;                                 // Interrompt la lecture de la chanson en cours pour changer
    }

    // Effectue un pas de danse (mouvement du servo pour cette note)
    servo_.step();

    // Prépare l'émission du son pour cette note
    bool soundEnabled = (!mute_) && (!nightMode);
    // soundEnabled sera true uniquement si on n'est pas en mode muet ET qu'il ne fait pas nuit
    buzzer_.playNote(s[i], soundEnabled);  // Joue la note s[i] sur le buzzer (ou reste silencieux si soundEnabled est false)

    // Appelle régulièrement le loop Wi-Fi pour rester réactif aux commandes web pendant qu'on joue la musique
    wifi_.loop();
  }
}

void BailarinaApp::buildSongs() {
  // Construit la première chanson (song0_) en ajoutant successivement des notes grâce à l'opérateur << sur Song
  song0_
    << Note{NOTE_C5,4} << Note{NOTE_G4,4} << Note{NOTE_E4,4} << Note{NOTE_A4,4}
    << Note{NOTE_B4,4} << Note{NOTE_A4,4} << Note{NOTE_E4,4} << Note{NOTE_G4,4}
    << Note{NOTE_C5,4} << Note{NOTE_G4,4} << Note{NOTE_E4,4} << Note{NOTE_F4,4}
    << Note{NOTE_G4,4} << Note{NOTE_E4,4} << Note{NOTE_D4,4} << Note{NOTE_C4,4};

  // Construit la deuxième chanson (song1_)
  song1_
    << Note{NOTE_C4,8} << Note{NOTE_D4,8} << Note{NOTE_E4,8} << Note{NOTE_F4,8}
    << Note{NOTE_G4,8} << Note{NOTE_A4,8} << Note{NOTE_B4,8} << Note{NOTE_C5,4}
    << Note{NOTE_C5,8} << Note{NOTE_B4,8} << Note{NOTE_A4,8} << Note{NOTE_G4,8}
    << Note{NOTE_F4,8} << Note{NOTE_E4,8} << Note{NOTE_D4,8} << Note{NOTE_C4,4};

  // Construit la troisième chanson (song2_)
  song2_
    << Note{NOTE_G4,16} << Note{NOTE_G4,16} << Note{NOTE_G4,8} << Note{NOTE_A4,4} << Note{NOTE_G4,4}
    << Note{NOTE_G4,16} << Note{NOTE_G4,16} << Note{NOTE_G4,8}
    << Note{NOTE_G4,16} << Note{NOTE_G4,16} << Note{NOTE_G4,8} << Note{NOTE_A4,4}
    << Note{NOTE_G4,16} << Note{NOTE_G4,16} << Note{NOTE_G4,8} << Note{NOTE_G4,2};
}

const Song& BailarinaApp::currentSong() const {
  // Renvoie une référence constante vers l'une des chansons en fonction de l'index courant
  if (currentSong_ == 0) return song0_;
  if (currentSong_ == 1) return song1_;
  return song2_;
}

void BailarinaApp::updateLcdText() {
  // Met à jour le texte affiché sur l'écran LCD en fonction de la chanson courante et des lignes définies
  if (currentSong_ == 0) lcdLine2_ = "chanson 1";
  else if (currentSong_ == 1) lcdLine2_ = "chanson 2";
  else lcdLine2_ = "capibara";  // Nom particulier pour la troisième chanson

  lcd_.clear();                    // Efface l'écran
  lcd_.setCursor(0, 0);
  lcd_.print(lcdLine1_.substring(0,16)); // Affiche la première ligne (tronquée à 16 caractères max)
  lcd_.setCursor(0, 1);
  lcd_.print(lcdLine2_.substring(0,16)); // Affiche la deuxième ligne (tronquée à 16 caractères)
}

void BailarinaApp::setSong(int i) {
  if (i < 0) i = 0;               // Si l'indice est négatif, on le remet à 0 (chanson 0 par défaut)
  currentSong_ = i % 3;           // Calcule l'index de chanson valide (0,1,2) même si i est hors bornes
  updateLcdText();                // Met à jour l'afficheur LCD pour refléter la nouvelle chanson sélectionnée
}

void BailarinaApp::setMute(bool m) {
  mute_ = m;              // Met à jour l'état muet
  if (mute_) {
    buzzer_.stop();       // Si on active le mode muet, on arrête immédiatement le buzzer pour couper le son
  }
}

void BailarinaApp::setLine1(const String& s) {
  lcdLine1_ = s;         // Change le texte de la première ligne (on stocke la nouvelle valeur)
  updateLcdText();       // Rafraîchit l'affichage complet du LCD (ligne1 et ligne2)
}

void BailarinaApp::setLine2(const String& s) {
  lcdLine2_ = s;                              // Met à jour le texte de la deuxième ligne
  lcd_.setCursor(0, 1);
  lcd_.print("                ");             // Efface la deuxième ligne en imprimant 16 espaces (pour supprimer l'ancien texte)
  lcd_.setCursor(0, 1);
  lcd_.print(lcdLine2_.substring(0,16));      // Affiche le nouveau texte de la ligne 2 (tronqué à 16 caractères)
}
