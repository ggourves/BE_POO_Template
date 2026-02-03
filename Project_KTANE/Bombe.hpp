//
// Created by ulric on 12/18/2025.
//

#ifndef BE_POO_KTANE_BOMBE_HPP
#define BE_POO_KTANE_BOMBE_HPP
#include "ModuleBase.hpp"


class Bomb {
    protected:
    int Timer;
    int Error=0;
    int Success=0;
    friend class Timer;
    public:
    int Update=0;

    Bomb();

    void AddError(); // Ajoute une erreur à la bombe et une update, elle fait aussi jouer un son d'erreur

    void AddSuccess(); // Ajoute 1 à Success et fait jouer un son de réussite

    void Verify();  // Vérifie s'il y a eu une update des erreurs ou si la bombe est désactivé.Fait exploser la bombe ou retentir la musique de réussite

    void Switch_Error_LED(); // Allume les leds selon les erreurs

    void Print_Error(int err); // Affiche Err1 ou Err2 sur le timer

    int getError(); // retourne Error;

    int getTimer();
};

#endif //BE_POO_KTANE_BOMBE_HPP