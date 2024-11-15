# BE_POO_ESP8266
# Projet : Système Intégré de Contrôle et d’Alerte pour Pièce de Vie

## Idée du Projet
L’objectif est de créer un système intelligent pour surveiller et interagir avec une pièce de vie. Ce système mesure la luminosité ambiante, la distance d’un obstacle (pour détecter un mouvement), la température et l’humidité, et peut émettre des alertes sonores et visuelles en fonction des paramètres surveillés. De plus, l’utilisateur peut interagir via un bouton et visualiser des informations sur l’écran LCD.

## Fonctionnalités du Système
Surveillance des Paramètres de la Pièce : Mesure en continu de la luminosité, la température et l’humidité, pour afficher les valeurs actuelles et émettre des alertes.
Détection de Mouvement : Utilisation du capteur ultrasonique pour détecter la présence d’une personne ou d’un obstacle dans une certaine zone.
Interaction Utilisateur : Un bouton permet d’afficher des informations supplémentaires ou de réinitialiser les alertes.
Alertes Visuelles et Sonores : Une LED rouge et un buzzer sont activés lorsque des conditions particulières sont détectées (par exemple, faible luminosité ou niveau de son élevé).
Affichage sur Écran LCD : L’écran LCD affiche les valeurs mesurées (température, humidité, luminosité) et les alertes.
Composants Utilisés et Rôles
Potentiomètre : Peut être utilisé pour régler la sensibilité de certains capteurs (comme le niveau de son pour activer une alerte).
Buzzer : Émet un son en cas d’alerte (par exemple, mouvement détecté dans la zone surveillée).
Capteur de lumière Grove (v1.2) : Mesure le niveau de luminosité de la pièce.
Capteur de température et d'humidité : Surveille les conditions ambiantes.
Capteur ultrasonique : Détecte la présence d’un obstacle, utile pour un détecteur de mouvement.
Capteur de son : Utilisé pour surveiller le niveau de bruit ambiant.
Bouton Grove : Permet à l’utilisateur d’interagir avec le système (par exemple, pour désactiver une alerte).
LED Rouge : Sert d’alerte visuelle.
Écran LCD : Affiche les valeurs des capteurs et les notifications du système.
Architecture Orientée Objet en C++
Classe de Base Capteur : Définit les attributs communs pour tous les capteurs (ID, type) et une méthode virtuelle pour effectuer une mesure.

Méthodes : mesurer(), afficherValeur().
Classes Dérivées pour Chaque Capteur

CapteurLuminosite : Hérite de Capteur pour gérer le capteur de lumière.
CapteurTemperatureHumidite : Gère le capteur de température et d’humidité.
CapteurUltrasonique : Gère le capteur de distance, utilisé pour la détection de mouvement.
CapteurSon : Gère le capteur de son pour détecter un niveau de bruit élevé.
Classe Actionneur : Classe de base pour les actionneurs (LED, buzzer).

Méthodes : activer(), desactiver(), avec des méthodes spécifiques pour la LED et le buzzer.
Classe EcranLCD : Gère l'affichage sur l’écran LCD.

Méthodes : afficherTexte() pour afficher les informations sur l’écran.
Classe SystemeControlePiece : Gère le système global.

Attributs : Liste des capteurs et actionneurs, seuils d’alerte, état du système.
Méthodes : surveillerParametres(), alerter(), afficherSurLCD() pour orchestrer les mesures et gérer les alertes.
Extrait de Code Exemple
Voici un exemple de la classe pour le capteur de luminosité (CapteurLuminosite), qui hérite de Capteur.


## Prototype de code
class Capteur {
protected:
    int id;
    String type;

public:
    Capteur(int id, String type) : id(id), type(type) {}
    virtual float mesurer() = 0; // Méthode virtuelle pure pour mesurer
    virtual void afficherValeur() = 0; // Pour afficher la valeur sur l'écran
};

class CapteurLuminosite : public Capteur {
private:
    int pin;
    int valeurLuminosite;

public:
    CapteurLuminosite(int id, int pin) : Capteur(id, "Luminosité"), pin(pin) {}

    float mesurer() override {
        valeurLuminosite = analogRead(pin);
        return valeurLuminosite;
    }

    void afficherValeur() override {
        Serial.print("Luminosité : ");
        Serial.println(valeurLuminosite);
    }
};

## Scénario d’Utilisation
Initialisation : Les capteurs et actionneurs sont configurés.
Mesure et Surveillance : Les capteurs mesurent périodiquement leurs paramètres (luminosité, température, humidité, son, mouvement).
Alerte : Si le niveau sonore est trop élevé, si la luminosité est trop basse, ou si un mouvement est détecté, le système déclenche la LED et le buzzer, et affiche un message sur l’écran LCD.
Interaction Utilisateur : L’utilisateur peut appuyer sur le bouton pour désactiver les alertes.
Affichage sur l’Écran LCD : Les valeurs mesurées sont affichées en continu ou en rotation (ex. température/humidité, puis luminosité, puis niveau sonore).
Rapport et Documentation
Le rapport de ce projet inclura :

Les cas d’utilisation (détection de mouvement, surveillance de la qualité de l’air et de la luminosité).
Schémas de classes et diagramme de séquence : Montrant les relations entre les capteurs, les actionneurs, et le système de contrôle.
Schéma de câblage : Avec les connexions entre les capteurs, actionneurs et l’ESP8266.
Évolution possible : Ajouter un contrôle Wi-Fi pour suivre à distance les paramètres via une application mobile.
Ce projet est polyvalent et interactif, permettant de surveiller en temps réel l’environnement d’une pièce avec des alertes visuelles et sonores, et offre aussi une interaction utilisateur via l’écran LCD et le bouton.
