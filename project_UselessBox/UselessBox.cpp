/*********************************************************************
 * @file  Application.cpp
 * @author Strom Camilla Saethre Ingrid
 * @brief Fichier source de l'application
 *********************************************************************/
#include "UselessBox.h"
#include <iostream>
#include <cstdint>
#include <string>
using namespace std;


void init(void)
{
    
}

/* void run(void){

} */


//TestingTesting 123
int main (){

  Box bitch;

  cout << "bitch created" << endl;
  cout << bitch.getNbTentatives() << endl;
  bitch += 1;
  cout << "NbTentatives: " << bitch.getNbTentatives() << endl;
  
  Capteur mutton("Ping Me lol", PIN_BOUTON);
  cout << mutton.getNom() << endl;
  
  Actionneur cool("Lys Opp Min Verden", PIN_LED);
  cout << cool.getNom() << endl;

  ReactionTest chill("I'm chill");
  cout << chill.getNom() << endl;
  chill.jouer();
  return 0;
}
