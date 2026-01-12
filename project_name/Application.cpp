/*********************************************************************
 * @file  Application.cpp
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"
#include "Bombe.hpp"
#include <Arduino.h>
#include <TM1637Display.h>

#include "Simon.h"
#include "Thread.h"
#include "Timer.hpp"

Application::Application() : bombe(), ThreadModule(&bombe), Timer_(&bombe), SimonModule(&bombe)
{
}
  
Application::~Application()
{
}  

void Application::init(void)
{
  ThreadModule.initPin();
  Timer_.begin();  // Affiche le temps de départ
  SimonModule.Simon_pin_config();
  Serial.begin(9600);
}

void Application::run(void)
{
  Timer_.update(&bombe);  // S'occupe du temps du timer avec la fonction milis()
  bombe.Verify();
  if (ThreadModule.get_led()!=1)
//  ThreadModule.stateThread(&bombe);
  if ( SimonModule.get_led()!=1)
    SimonModule.Simon_Check();
  if ( (ThreadModule.get_led() + SimonModule.get_led())==4) {

  }

}


