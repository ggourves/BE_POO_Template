// Carte Node MCU 1.0

//#include "Application.h"
#include <ESP8266WiFi.h> // Inclure la bibliothèque ESP8266WiFi

//Application myApplication;

const int brocheLED = LED_BUILTIN_AUX; //D4;   // Broche du LED intégré de l'ESP8266 (D4 ou GPIO 2)
const int brocheBOUTON = D7;

// Réseau Wi-Fi
//const char* ssid = "Wifizinho";       // Nom du réseau Wi-Fi
//const char* password = "Senha123";    // Mot de passe du réseau Wi-Fi

void setup() 
{
  // Configurer la broche du LED comme sortie
  pinMode(brocheLED, OUTPUT);
  pinMode(brocheBOUTON, INPUT);

  Serial.begin(115200); // Initialiser la communication série pour le débogage
  delay(10);

  // Connexion au Wi-Fi
  Serial.println();
  Serial.print("Connexion au reseau Wi-Fi");
  Serial.println(ssid);

  // Démarrer la connexion Wi-Fi
  WiFi.begin(ssid, password);

  // Attendre la connexion au Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Afficher l'adresse IP attribuée une fois connecté
  Serial.println();
  Serial.println("Connecté au Wi-Fi !");
  Serial.print("Adresse IP : ");
  Serial.println(WiFi.localIP());


  // put your setup code here, to run once:
  //myApplication.init();
}

void loop() 
{  
  if(digitalRead(brocheBOUTON) == HIGH){
    digitalWrite(brocheLED, HIGH);
  }  else{
    digitalWrite(brocheLED, LOW);
  }
  // put your main code here, to run repeatedly:
  //myApplication.run();
}
