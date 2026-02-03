/*********************************************************************
 * @file  Apllication.h
 * @author <MELADE Ulrich -- LELE Bernys>
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "Bombe.hpp"
#include "Password.hpp"
#include "Thread.h"
#include "Timer.hpp"
#include "Simon.h"
/**
  * @class Application
  * @brief Classe Application 
*/    
class Application
{
  private:
    Bomb bomb;  // On déclare la bombe en premier car utilisée par tous les autres
    Thread ThreadModule;
    Timer Timer_;
    Simon SimonModule;
    Password PasswordModule;

  public :
    /**
     * @fn Application();
     * @brief Constructeur par defaut
    */    
    Application();
    /**
     * @fn Application();
     * @brief Destructeur
    */    
    ~Application();    
    /**
     * @fn void init(void)
     * @brief Fonction d'initialisation de l'application
    */
    void init(void);
    /**
     * @fn void run(void)
     * @brief Fonction de lancement de l'application
    */
    void run(void);
};
#endif