#include "Led.h"


//Définition pour utilisation de fast_leds
#define DATA_PIN 2
#define INTERVALE_RAFRAICHISSEMENT 200

extern CRGB leds[NUM_LEDS];  // Les Leds physiques sont déclarées dans projet_name.ino
static unsigned long dernierRafraichissement = 0;  // Dernier moment de rafraîchissement
static CRGB etatPrecedentLEDs[NUM_LEDS];  // État précédent des LEDs pour comparaison



// Je commence en initialisant les LEDs physiques
void initialiserLEDs() {
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    FastLED.clear();
    for (int i=0 ; i < NUM_LEDS ; i++) {
        leds[i] = CRGB :: Red;  //Allume toutes les leds en rouge au démarrage pour vérification visuelle que les leds fonctionnent et voir que le système est bien démarré
    }
    FastLED.show(); // Affiche les changements

    //initialise l'état précédent des leds 
    for (int i=0 ; i < NUM_LEDS ; i++) {
        etatPrecedentLEDs[i] = CRGB :: Black;
    }

}

// Vérification et mise à jour des LEDs en physiques, en fonction de l'état de la grille
void mettreAJourLEDs(Grid4x4 *grille) {
    unsigned long maintenant = millis();
    //Rafraichissement toute les 200ms 
    if (maintenant - dernierRafraichissement >= INTERVALE_RAFRAICHISSEMENT){    // Temps écoulé depuis le dernier rafraîchissement
        dernierRafraichissement = maintenant ;  // Met à jour le temps du dernier rafraîchissement pour le prochain cycle
        //Je m'occupe maintenant de la mise a jour de la LED en fonction de notre grid.
        for (int i = 0; i < TAILLE; i++) {      // Parcours des lignes
            for (int j = 0; j < TAILLE; j++) {      // Parcours des colonnes
                int numLed = grille->cells[i][j].numeroleds;  // Utilise le numéro de LED stocké
                leds[numLed] = grille->cells[i][j].led;  // Applique la couleur
            }
        }
        FastLED.show();  // Met à jour les LEDs
    }
}
