//
// Created by ulric on 1/9/2026.
//

#ifndef BE_POO_KTANE_PASSWORD_HPP
#define BE_POO_KTANE_PASSWORD_HPP
#include "ModuleBase.hpp"
#include <Arduino.h>


class Password : public ModuleBase {
    char PSWD [6]= { 'D','I','V','I','N'};
    int cursor=0;
    int Cursor0 = 0;
    int Cursor1 = 0;
    int Cursor2 = 0;
    int Cursor3 = 0;
    int Cursor4 = 0;

    const int TelePin = 6;

    unsigned long prev = millis();
    unsigned long now = millis();

    char UserCode[5][6] = {                                         // Tableau des lettres accessibles
        {'E','A','P','L','D','K'}, // Lettre 0
        {'R', 'A', 'I', 'M', 'N','B'}, // Lettre 1
        {'M', 'T', 'A', 'B', 'V','E'}, // Lettre 2
        {'V', 'E', 'L', 'M', 'R','I'}, // Lettre 3
        {'A', 'N', 'J', 'O', 'R','C'}  // Lettre 4
    };

    public:
    Password(Bomb *bomb);

    void init_Password();

    void Navigate(unsigned long code); // Convertit les donnéees de la télécommande en instruction

    void Put_letter(int cursor); // Envoie l'instruction à l'ESP

    void Check_Password();

    Password & operator <<(unsigned long code); // Surcharge d'opérateur avec << pour envoyer le code à l'ESP

    void Telecommand_check(); // Vérifie si la télécommande a envoyé des données ou non

    ~Password();
};

#endif //BE_POO_KTANE_PASSWORD_HPP