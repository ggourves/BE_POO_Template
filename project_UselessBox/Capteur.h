#ifndef CAPTEUR_H_
#define CAPTEUR_H_

#include "UselessBox.h"
#include "Ultrasonic.h"


//int getSignal() const { return digitalRead(m_pin); }
//if (bouton.getSignal() == HIGH) {//slås på eller av}
//kommer ann på hvordan vi vil bruke det?
class CapteurBouton : public Capteur {
    public:
        //constructeur
        CapteurBouton(const string& nom, uint8_t pin) : Capteur(nom, pin), signal(0) {};
    
        //fonctions
        int getSignal() const{
            return digitalRead(pin); //eller signal?
        }
        //destructeur
        virtual ~CapteurBouton() =default;
    private:
        int signal;
};


//ikke sånn den funker? :/
class CapteurDistance : public Capteur {
    public:
        //constructeur
        CapteurDistance(const string& nom, uint8_t pin) : Capteur(nom, pin), signal(0) {};
    
        //fonctions
        int getDistance() const{
            return signal;
        }
        //destructeur
        virtual ~CapteurDistance() =default;
    private:
        int signal;
};

//class CapteurTemperature : public Capteur {};



#endif