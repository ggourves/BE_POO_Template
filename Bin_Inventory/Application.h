/*********************************************************************
 * @file  Apllication.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Hardware/Grid.h"
#include "Manager/itemsManager.h"
#include "Manager/DetectionManager.h"
#include "Hardware/Capteur.h"
#include "Hardware/Led.h"
#include "Hardware/Led.h"
#include "Hardware/Capteur.h"


/**
  * @class Application
  * @brief Classe Application 
*/    
class Application
{
  private:
    Grid4x4 grid;
    itemManager manager;
    DetectionManager detectionManager;

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