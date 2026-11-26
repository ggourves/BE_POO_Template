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
  
  Capteur mutton("PingMeButton", PIN_BOUTON);
  cout << mutton.getNom() << endl;
  

  return 0;
}

