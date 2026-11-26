#ifndef CAPTEUR_CPP_
#define CAPTEUR_CPP_
#include "UselessBox.h"



class CapteurBouton : public Capteur () {
    public:
    //constructeur
        CapteurBouton(int _signal) : m_signal(_signal) {};
    
    //fonctions
        int getSignal() {
            return _signal;
        }
    //destructeur
        virtual ~CapteurBouton() =default;

};


class CapteurDistance : public Capteur () {
    public:
    //constructeur
        CapteurDistance(int _signal) : m_signal(_signal) {};
    
    //fonctions
        int getSignal() {
            return _signal;
        }
    //destructeur
        virtual ~CapteurDistance() =default;
};


class CapteurLuminosite : public Capteur () {
    public:
    //constructeur
        CapteurLuminosite(int _signal) : m_signal(_signal) {};
    
    //fonctions
        int getSignal() {
            return _signal;
        }
    //destructeur
        virtual ~CapteurLuminosite() =default;
};

#endif