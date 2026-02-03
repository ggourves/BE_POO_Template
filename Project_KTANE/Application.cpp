/*********************************************************************
 * @file  Application.cpp
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier source de l'application
 *********************************************************************/
#include "Application.h"
#include "Bombe.hpp"
#include <Arduino.h>
#include <TM1637Display.h>

#include "Password.hpp"
#include "Simon.h"
#include "Thread.h"
#include "Timer.hpp"
#include "Speaker.hpp"


Application::Application() : bomb(), ThreadModule(&bomb), Timer_(&bomb), SimonModule(&bomb), PasswordModule(&bomb)
{
}
  
Application::~Application()
{
}  

void Application::init(void)
{ 
  Serial.begin(9600);
  Serial1.begin(9600);

  ThreadModule.initPin();
  PasswordModule.init_Password();
  init_Speaker();
  Play_Music("welcome");
  //delay(8000);
  Timer_.begin();  // Affiche le temps de départ
  SimonModule.Simon_pin_config();
}

void Application::run(void)
{
  Timer_.update(&bomb);  // S'occupe du temps du timer avec la fonction milis()
  bomb.Verify();
  ThreadModule.stateThread();
  if ( SimonModule.get_led()!=1)
    SimonModule.Simon_Check();
  PasswordModule.Telecommand_check();
}


