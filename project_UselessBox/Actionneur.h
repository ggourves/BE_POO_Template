#ifndef ACTIONNEUR_H_
#define ACTIONNEUR_H_

#include "UselessBox.h"
#include <Arduino.h>
#include <servo.h>
#include <Wire.h>
#include <rgb_lcd.h>


//visage heureux
byte heureuxYeuxGauche[] = {0x00,0x00,0x03,0x0F,0x1C,0x10,0x00,0x00};//nr4,10
byte heureuxYeuxDroite[] = {0x00,0x00,0x18,0x1E,0x07,0x01,0x00,0x00};//nr5,11
byte heureuxBoucheGauche[] = {0x00,0x00,0x18,0x1C,0x0F,0x03,0x00,0x00};//nr7
byte heureuxBoucheDroite[] = {0x00,0x00,0x03,0x07,0x1E,0x18,0x00,0x00};//nr8



class LED : public Actionneur{
    //constructeur
    public:
        LED(const string& nom, int pin) : Actionneur(nom, pin) {};
    
        //fonctions
        void initLED() {
            pinMode(pin, OUTPUT);
        }

        void allumerLED() {
            digitalWrite(pin, HIGH);
        }

        void eteindreLED() {
            digitalWrite(pin, LOW);
        }
        //destructeur
        virtual ~LED() =default;

};

class Ecran : public Actionneur {
    private:
        rgb_lcd ecran;

    //constructeur
    public:
        Ecran(const string& nom, int pin) : Actionneur(nom, pin) {};
    
        //fonctions
        void heureux()   {  
            lcd.clear();
            
            //dessiner yeux
            
            lcd.createChar(0, heureuxYeuxGauche);
            lcd.createChar(1, heureuxYeuxDroite);

            lcd.setCursor(4, 0);
            lcd.write(byte(0));
            lcd.setCursor(5, 0);
            lcd.write(byte(1));
            lcd.setCursor(10, 0);
            lcd.write(byte(0));
            lcd.setCursor(11, 0);
            lcd.write(byte(1));

            //dessiner bouche
            lcd.createChar(3, heureuxBoucheGauche);
            lcd.createChar(4, heureuxBoucheDroite);

            lcd.setCursor(7, 1);
            lcd.write(byte(3));
            lcd.setCursor(8, 1);
            lcd.write(byte(4));
        }

        void neutre() { 

        }   

        void ruse() { 
        }

        void irrite() { 
        }

        void furieux() { 
        } 

        //destructeur
        virtual ~Ecran() =default;

};

class Servo : public Actionneur {
    
    private:
        ::Servo moteur;
    //constructeur
    public:
        Servo(const string& nom, int pin) : Actionneur(nom, pin) {};
    
        void initServo() {
            moteur.attach(pin);
        }

        //fonctions pour ouvrir
        void ouvrirBoxVite() {
            moteur.write(45);
        }
        
        void ouvrirBoxLent() {
            for (int i=0; i<45; i++){
                moteur.write(i);
                delay(10);
            }
        }

        void ouvrirBoxAMoitieVite() {
            moteur.write(22);
        }

        void ouvrirBoxAMoitieLent() {
            for (int i=0; i<22; i++){
                moteur.write(i);
                delay(10);
            }
        }

        //fonctions pour fermer
        void fermerBoxVite() {
            moteur.write(0);
        }

        void fermerBoxLent() { //BARE OM 45 FRA FØR AV
            for (int i=45; i>0; i--){
                moteur.write(i);
                delay(10);
            }
        }

        void fermerBoxAMoitieLent() { //BARE OM 22 FRA FØR AV
            for (int i=22; i>0; i--){
                moteur.write(i);
                delay(10);
            }
        }
        
        //fonctions pour pousser le bouton
        void pousserBoutonVite() {
            moteur.write(180);
        }

        void pousserBoutonLent() {
            for (int i=0; i<180; i++){
                moteur.write(i);
                delay(10);
            }
        }

        void pousserBoutonAMoitieVite() {
            moteur.write(130);
        }

        void pousserBoutonAMoitieLent() {
            for (int i=0; i<130; i++){
                moteur.write(i);
                delay(10);
            }
        }

        void pousserBoutonRester() {
            moteur.write(170);
        }

        void relaherBoutonVite() {
            moteur.write(0);
        }

        void relacherBoutonLent() { //BARE OM 180 FRA FØR AV
            for (int i=180; i>0; i--){
                moteur.write(i);
                delay(10);
            }
        }
        
        //destructeur
        virtual ~Servo() =default;

};

class Buzzer : public Actionneur {
    //constructeur
    public:
        Buzzer(const string& nom, int pin) : Actionneur(nom, pin) {};
    
        //fonctions
        void initBuzzer() {
            pinMode(pin, OUTPUT);
        }
        
        void bipHeureux() {
            digitalWrite(pin, HIGH);
            delay(10);
            digitalWrite(pin, LOW);
            delay(10);
            digitalWrite(pin, HIGH);
            delay(10);
            digitalWrite(pin, LOW);
            delay(2070);
        }

        void bipNeutre() {
        }

        void bipRuse() {
        }

        void bipIrrite() {
        }

        void bipFurieux() {
        }

        //destructeur
        virtual ~Buzzer() =default;

};


#endif
