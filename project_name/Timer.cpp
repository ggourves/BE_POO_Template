//
// Created by ulric on 12/21/2025.
//

#include "Timer.hpp"
#include "Bombe.hpp"
#include "TM1637Display.h"
#include "Arduino.h"

/////// Port Timer ////
#define CLK 2 // Port PWM 2
#define DIO 3 // Port PWM 3
//////////////////////////

extern TM1637Display display;


Timer::Timer(Bomb * b) {
    MaxTime = b->getTimer();
    display.setBrightness(0x0f);
}

void Timer::begin() {
    lastUpdate = millis();  // Initialise le temps de référence
    int seconde = MaxTime % 60;
    int minute = MaxTime / 60;
    int displayTime = minute * 100 + seconde;  // Format MMSS (ex: 5:30 -> 530)
    display.clear();
    display.showNumberDecEx(displayTime, 0x40, false);  // Affiche le temps de départ au format M:SS
}

void Timer::update(Bomb * b) {
    if ( b->getError()<2) {
        unsigned long now = millis();
        if (now - lastUpdate >= 1000) {  // 1 seconde écoulée
            lastUpdate = now;
            if (MaxTime > 0) {
                MaxTime--;
                int seconde = MaxTime % 60;
                int minute = MaxTime / 60;
                int displayTime = minute * 100 + seconde;
                display.showNumberDecEx(displayTime, 0x40, false);  // Affiche le temps restant au format M:SS
            }
        }
    }
}

Timer Timer::operator-( int a) {
    MaxTime -= a;
    return *this;
}

Timer Timer::operator--() {
    MaxTime--;
    return *this;
}

Timer Timer::operator+( int a) {
    MaxTime += a;
    return *this;
}

Timer Timer::operator++() {
    MaxTime++;
    return *this;
}
