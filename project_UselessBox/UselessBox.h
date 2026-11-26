/*********************************************************************
 * @file  UselessBox.h
 * @author Saethre Ingrid Strøm Camilla
 * @brief Fichier header de l'application
 *********************************************************************/
#ifndef USELESSBOX_H_
#define USELESSBOX_H_
using namespace std;
/**
  * @class Application
  * @brief Classe Application 
*/    




class Box{
  public :
    //constructeur
    Box(void): nbTentatives(0) {};
    //destructeur
    virtual ~Box(){};    
    
    //fonctions
    void init(void);
    //void run(void);

    //operators
    Box & operator+=(int increment) {
      nbTentatives += increment;
      return *this;
    };


    int getNbTentatives() const { return nbTentatives; }
    
    int nbTentatives;
};



#endif
