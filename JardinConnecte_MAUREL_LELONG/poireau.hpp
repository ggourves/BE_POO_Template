#ifndef _Poireau_hpp
#define _Poireau_hpp

# include "legume.hpp"



class Poireau: public Legume{

protected:
  
  int longueur; //longueur du poireau
  String nom;  // nom du poireau 

public:

  //Constructeur
  Poireau(int l, String n);
  
  // Renvoie caractéristiques du poireau 
  String Caracteristiques();

  //Renvoie le temps de pousse du poireau 
  int TempsDePousse();

  //Renvoie le nom du poireau 
  String getname();

  //Renvoie la longueur du poireau 
  int getlenght();

  // Redefinition opérateur + 
  friend Poireau& operator+ (Poireau& p1, Poireau& p2);

  // Renvoie les points de vie du poireau 
  int GetPointDeVie();

  // Renvoie la durée d'arrosage du poireau 
int GetDureeArrosage();

//Renvoie le seuil d'arrosage du poireau 
float GetSeuilArrosage();

  //Destructeur 
  ~Poireau();


};

#endif



