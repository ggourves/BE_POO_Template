/////////////////////CLASSE ACTIONNEUR////////////////////////////////////

#ifndef ACTIONNEUR_HPP
#define ACTIONNEUR_HPP

#include "Peripherique.hpp"

class Actionneur : public Peripherique {
protected:
    bool etat; //Etat true si activé ou false si non activé 
    
public:

    //Constructeur 
    Actionneur(int b);
    
    //fonction qui active l'actionneur (true, HIGH)
    virtual void Activer() = 0;

    //fonction qui desactive l'actionneur (false, LOW)
    virtual void Desactiver() = 0;

    //fonction qui retourne l'état de l'actionneur
    bool GetEtat(); 

    //Destructeur 
    ~Actionneur();
};

#endif