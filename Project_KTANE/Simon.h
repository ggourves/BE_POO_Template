#ifndef Simon_h
#define Simon_h
#include "Bombe.hpp"
#include <Arduino.h>

class Simon: public ModuleBase {

  public:
    int Nb_Button=0;
    char Prev_Led=NULL;
    char Next_Led=NULL;
    int BB_temp=LOW; // 1 si Bouton Bleu appuyé
    int BR_temp=LOW; // 1 si Bouton Bleu appuyé
    int BJ_temp=LOW; // 1 si Bouton Bleu appuyé
    int BV_temp=LOW; // 1 si Bouton Bleu appuyé
    int stage=0;
    int nb_Leds=1;
    unsigned long previousMillis_R=millis();
    unsigned long previousMillis_B=millis();
    unsigned long previousMillis_J=millis();
    unsigned long previousMillis_V=millis();
    unsigned long previousMillis=millis();

    unsigned long currentMillis_R=millis();
    unsigned long currentMillis_B=millis();
    unsigned long currentMillis_J=millis();
    unsigned long currentMillis_V=millis();
    unsigned long currentMillis=millis();

    unsigned long interval=4000;
    int index_led=0;

    char Tab_Stage[5][6] = {
        {'R',' ',' ',' ',' ',' '},
        {'R', 'B', ' ', ' ', ' '}, // Stage 1
        {'R', 'B', 'V', ' ', ' '}, // Stage 2
        {'R', 'B', 'V', 'R', ' '}, // Stage 3
        {'R', 'B', 'V', 'R', 'J'}  // Stage 4
    };

    char Tab_Error0[5][6] = {
        {'B',' ',' ',' ',' ',' '},
        {'B', 'R', ' ', ' ', ' '}, // Stage 1
        {'B', 'R', 'J', ' ', ' '}, // Stage 2
        {'B', 'R', 'J', 'B', ' '}, // Stage 3
        {'B', 'R', 'J', 'B', 'V'}  // Stage 4
    };

    char Tab_Error1[5][6] = {
        {'J',' ',' ',' ',' ',' '},
        {'J', 'V', ' ', ' ', ' '}, // Stage 1
        {'J', 'V', 'B', ' ', ' '}, // Stage 2
        {'J', 'V', 'B', 'J', ' '}, // Stage 3
        {'J', 'V', 'B', 'J', 'R'}  // Stage 4
    };

    char Tab_Error2[5][6] = {
        {'V',' ',' ',' ',' ',' '},
        {'V', 'R', ' ', ' ', ' '}, // Stage 1
        {'V', 'R', 'J', ' ', ' '}, // Stage 2
        {'V', 'R', 'J', 'V', ' '}, // Stage 3
        {'V', 'R', 'J', 'V', 'B'}  // Stage 4
    };


    int pin_button[4]={41,43,45,47}; // pins des bouttons poussoir

    Simon(Bomb *b);
    void Simon_pin_config();
    void LED_ON(char led);
    void LED_OFF(char led);
    void Reset(); // reset toute la classe et ajoute l'erreur à la classe Bombe et
    void FlashLed0(); // Si aucune erreur cette fonction est appelé
    void FlashLed1(); // Si deux erreurs
    void FlashLed2(); // Si deux erreurs
    void Simon_Check();

    ~Simon();
  };

#endif