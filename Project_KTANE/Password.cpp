//
// Created by ulric on 1/9/2026.
//

#include "Password.hpp"
#include "ModuleBase.hpp"
#include <Arduino.h>
#include <IRremote.h>

#include "Bombe.hpp"

Password::Password(Bomb *bomb) : ModuleBase(bomb){
}

void Password::init_Password() {
    IrReceiver.begin(TelePin, ENABLE_LED_FEEDBACK);
    Put_letter(0);
    Put_letter(1);
    Put_letter(2);
    Put_letter(3);
    Put_letter(4);
    pinMode(7,OUTPUT);
}

void Password::Check_Password() {
    bool correct = true;
    for(int i=0; i<5; i++) {
        if ( i == 0) {
            if(UserCode[i][Cursor0] != PSWD[i])
                correct = false;
            }
        if ( i == 1) {
            if(UserCode[i][Cursor1] != PSWD[i])
                correct = false;
        }
        if ( i == 2) {
            if(UserCode[i][Cursor2] != PSWD[i])
                correct = false;
        }
        if ( i == 3) {
            if(UserCode[i][Cursor3] != PSWD[i])
                correct = false;
        }
        if ( i == 4) {
            if(UserCode[i][Cursor4] != PSWD[i])
                correct = false;
        }
    }
    if(correct) {
        if ( led !=1){
            led = 1;
            digitalWrite(7, HIGH); // LED Validation
            bombp->AddSuccess();
        }
    }
    else {
        bombp->AddError();
    }
}

void Password::Navigate(unsigned long code) {
    switch (code) {
        case 0xBB44FF00: // Aller à gauche
            cursor--;
            if(cursor < 0)
                cursor = 4; // On revient à droite
            Serial1.println("SEL:" + String(cursor));
            break;
        case 0xBC43FF00: // Aller à droite
            cursor++;
            if(cursor > 4) cursor = 0; // On revient à gauche
            Serial1.println("SEL:" + String(cursor));
            break;
        case 0xF609FF00:  // Monter
            if ( cursor == 0) {
                Cursor0++;
                if ( Cursor0 == 6) {
                    Cursor0 = 0;
                }
            }
            if ( cursor == 1) {
                Cursor1++;
                if ( Cursor1 == 6) {
                    Cursor1 = 0;
                }
            }
            if ( cursor == 2) {
                Cursor2++;
                if ( Cursor2 ==6) {
                    Cursor2 = 0;
                }
            }
            if ( cursor == 3) {
                Cursor3++;
                if ( Cursor3 == 6) {
                    Cursor3 = 0;
                }
            }
            if ( cursor == 4) {
                Cursor4++;
                if ( Cursor4 == 6) {
                    Cursor4 = 0;
                }
            }
            Put_letter(cursor);
            break;
        case 0xF807FF00: // Descendre
            if ( cursor == 0) {
                Cursor0--;
                if ( Cursor0 == -1) {
                    Cursor0 = 5;
                }
            }
            if ( cursor == 1) {
                Cursor1--;
                if ( Cursor1 == -1) {
                    Cursor1 = 5;
                }
            }
            if ( cursor == 2) {
                Cursor2--;
                if ( Cursor2 == -1) {
                    Cursor2 = 5;
                }
            }
            if ( cursor == 3) {
                Cursor3--;
                if ( Cursor3 == -1) {
                    Cursor3 = 5;
                }
            }
            if ( cursor == 4) {
                Cursor4--;
                if ( Cursor4 == -1) {
                    Cursor4 = 5;
                }
            }
            Put_letter(cursor);
            break;
        case 0xE619FF00:   // Bouton EQ pour vérifier le mot de passe
            Check_Password();
            break;
        default:
            Serial.print("Code inconnu: ");
            Serial.println(code, HEX);
    }
}

void Password::Put_letter(int cursor) { // La fonction crée l'instruction de l'ESP
    String cmd;
    if ( cursor == 0)
        cmd = "SET:" + String(cursor) + ":" + String(UserCode[cursor][Cursor0]); // "SET:" correspond au nom de l'instruction
    if ( cursor == 1)                                                            // String(cursor) correspond à l'emplacement que l'on change
        cmd = "SET:" + String(cursor) + ":" + String(UserCode[cursor][Cursor1]); // String(UserCode[cursor][Cursor1])  correspond à la lettre que l'on place
    if ( cursor == 2)
        cmd = "SET:" + String(cursor) + ":" + String(UserCode[cursor][Cursor2]);
    if ( cursor == 3)
        cmd = "SET:" + String(cursor) + ":" + String(UserCode[cursor][Cursor3]);
    if ( cursor == 4)
        cmd = "SET:" + String(cursor) + ":" + String(UserCode[cursor][Cursor4]);
    Serial1.println(cmd);                                                         // On envoie la données à l'ESP à travers le port TX1
    }


Password& Password::operator<<(unsigned long code) {
    this->Navigate(code);
    return *this;
}


void Password::Telecommand_check() {
    if (IrReceiver.decode()) {      // S'active quand la mega reçoit des données de la télécommande
        unsigned long now = millis(); // On empêche la multiple réception du même bouton avec un petit timer
        if (now - prev > 100) {
            unsigned long code = IrReceiver.decodedIRData.decodedRawData;

            if (code > 0) {
                *this<<code; // On envoie le code directement dans l'esp
                prev=now;
            }
        }
        IrReceiver.resume(); // On reprend l'écoute
    }
}

Password::~Password(){

}