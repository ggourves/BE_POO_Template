#ifndef _Citrouille_hpp
#define _Citrouille_hpp

# include "legume.hpp"


# define ProbCitrouille 1

class Citrouille: public Legume{

protected:
  
  int diametre; //diamètre de la citrouille
  String nom;   //nom de la citrouille

public:

  //Constructeur
  Citrouille (int d, String n);
  
  //Caractéristiques de la citrouille
  String Caracteristiques();

  //renvoie le temps de pousse d'une citrouille
  int TempsDePousse();

  // Renvoie le nom de la citrouille
  String getname();

  // Renvoie le diametre de la citrouille
  int getdiam();

  //Redéfinition de l'opérateur + pour pouvoir ajouter deux citrouilles et créer un bébé citrouille 
  friend Citrouille& operator+ (Citrouille& c1, Citrouille& c2);

  // Renvoie les PDV de la citrouille
  int GetPointDeVie();

// Renvoie la durée d'arrosage de la citrouille
int GetDureeArrosage();

// Renvoie le seuil d'arrosage de la citrouille
float GetSeuilArrosage();
  
  //Destructeur
  ~Citrouille();


};


#endif
