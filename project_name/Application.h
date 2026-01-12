/*********************************************************************
 * @file  Apllication.h
 * @author <MELADE Ulrich -- LELE Bernys>
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "Bombe.hpp"
#include "Thread.h"
#include "Timer.hpp"
#include "Simon.h"
/**
  * @class Application
  * @brief Classe Application 
*/    
class Application
{
  public :
    Bomb bombe;  // DOIT être déclaré en premier car utilisé par les autres classes/objets
    
  private:
    Thread ThreadModule;
    Timer Timer_;
    Simon SimonModule;

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