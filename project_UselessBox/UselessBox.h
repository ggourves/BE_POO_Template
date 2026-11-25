/*********************************************************************
 * @file  Apllication.h
 * @author <mettre l'adresse mail ou nom prenom>
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef APPLICATION_H_
#define APPLICATION_H_

/**
  * @class Application
  * @brief Classe Application 
*/    
class Box
{
  public :
    /**
     * @fn Application();
     * @brief Constructeur par defaut
    */    
    //Constructeur
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
  private :
};

class Capteur : public Box{

	
	
}

class Actionneur : public Box {


}

class Humeur : public Box {

	
}

class nbTentatives : public Box {

	
}


#endif
