//
// Created by ulric on 12/18/2025.
//

#include "Bombe.hpp"
#include <Arduino.h>
#include <TM1637Display.h>

/////// Port Timer ////
#define CLK 2 // Port PWM 2
#define DIO 3 // Port PWM 3
//////////////////////////

/////// Port Diode ////
#define LED_err_1 22 // Port Digit 22
#define LED_err_2 24 // Port Digit 24
//////////////////////////

extern TM1637Display display;  // Défini dans project_name.ino

Bomb::Bomb(){
    SerialNumber=1234;
    Port = 'a';
    NumberOfBatteries = 4;
    Timer=300;

    // initialize the LED pin as an output:
    
    pinMode(LED_err_1, OUTPUT);
    pinMode(LED_err_2, OUTPUT);
}

void Bomb::AddError(){
    Error++;
    Update++;
}

void Bomb::Verify() {
    if ( Update == 1 || Update == 2 || Update == 3) {
        Print_Error( Error); // On affiche Err 1 ou Err 2
        Allume_LED_Error();
        if ( Error >2){
            const uint8_t LOSE[] = {
                SEG_D | SEG_E | SEG_F ,                          // L
                SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
                SEG_A | SEG_D | SEG_F | SEG_G | SEG_C,           // S
                SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
                };

            display.setSegments(LOSE);
        }
        Update--;
    }
}


void Bomb::Print_Error(int e) {

    if (e==1 || Update == 3){
        const uint8_t SEG_Err[] = {
            SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,           // E
            SEG_E | SEG_G,                                   // r
            SEG_E | SEG_G,                                   // r
            SEG_C | SEG_B                                    // 1
        };
        display.setSegments(SEG_Err);
    }
    if (e==2 or Update==2){
        const uint8_t SEG_Err[] = {
             SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,           // E
             SEG_E | SEG_G,                                   // r
             SEG_E | SEG_G,                                   // r
             SEG_A | SEG_B | SEG_D | SEG_E | SEG_G            // 2
	    };
        display.setSegments(SEG_Err);
    }
    
}

void Bomb::Allume_LED_Error(){
    if (digitalRead(LED_err_1)==HIGH)    // Si la LED 1 est allume on allume la deuxieme
        digitalWrite(LED_err_2, HIGH);
    if(digitalRead(LED_err_1)==LOW)      // Si la LED 1 est eteinte on l'allume
        digitalWrite(LED_err_1, HIGH);
}

int Bomb::getError(){
    return Error;
}

int Bomb::getTimer(){
    return Timer;
}
