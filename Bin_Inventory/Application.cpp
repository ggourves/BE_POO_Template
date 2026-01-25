/*********************************************************************
 * @file  Apllication.cpp
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"

#include "Arduino.h"


Application::Application()
{
  // Code
  ; 
}
  
Application::~Application()
{
  // Code
  ;
}  

void Application::init(void)
{
  // Code
  Serial.begin(115200);
  grid.initialiser();
  initialiserCapteurs();
  initialiserLEDs();
  lireBoutonsPoussoirs(&grid);
  detectionManager.setInitialState(&grid);
  // Autres initialisations si nécessaires
}


void Application::run(void)
{
  // Code
  lireBoutonsPoussoirs(&grid);
  mettreAJourLEDs(&grid);
  // Détecter les changements sur la grille
  detectionManager.detecterChangement(&grid);
  
  // Gérer les détections (ajout/suppression d'items)
  detectionManager.gererDetection(&grid, &manager);
  
  // Gérer les interactions utilisateur via Serial
  if(Serial.available()>0){
  manager.actionChoice(&grid);
  }
}
