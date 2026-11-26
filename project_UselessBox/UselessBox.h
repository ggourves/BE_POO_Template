/*********************************************************************
 * @file  UselessBox.h
 * @author Saethre Ingrid Strøm Camilla
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef USELESSBOX_H_
#define USELESSBOX_H_
#include <iostream>
#include <string>
#include <cstdint>
using namespace std;
/**
  * @class Application
  * @brief Classe Application 
*/    

//enum class Humeur { CALME, AGACEE, FURIEUSE };

//Pins
static const uint8_t PIN_BOUTON    = 1 ;
static const uint8_t PIN_ULTRASON  = 2;
static const uint8_t PIN_LED       = 3;
static const uint8_t PIN_BUZZER    = 4;
static const uint8_t PIN_SERVOLID  = 5;
static const uint8_t PIN_SERVOARM  = 6;


class Box{
  public :
    //constructeur
    Box(void): nbTentatives(0) {};
    //destructeur
    virtual ~Box(){};    
    
    //fonctions
    void init(void);
    //void run(void);

    //operators
    Box & operator+=(int increment) {
      nbTentatives += increment;
      //humeur = calculerHumeur();
      return *this;
    };


    int getNbTentatives() const { return nbTentatives; }
    //Humeur getHumeur() const { return humeur; } --Enum class
       
      

    protected:
    //Humeur calculerHumeur() const; --Enum class
    int nbTentatives;
};

class Capteur{

	public: 
	  //constructer
	  Capteur(const string& nom, uint8_t pin) : nom(nom), pin(pin) {}
    //destructeur
	  virtual ~Capteur() = default;

    //fonction getter
    string getNom() const { return nom; }
	
	protected:
    string nom;
    uint8_t pin;
		
}; 

class Actionneur{

	public: 
    //constructeur
    Actionneur(const string& nom, uint8_t pin) : nom(nom), pin(pin) {};

    //Getters and Setters;
    string getNom() const { return nom; }

    //destructeur
    virtual ~Actionneur() = default;
	protected:
    string nom;
    uint8_t pin;
		
};


/*
class Humeur : public Box {
  public:
  //constructeur
  Humeur(const string& nom) : nom(nom) {};
	


  protected:
   string nom;
};

class nbTentatives : public Box {

	
}; */


#endif
