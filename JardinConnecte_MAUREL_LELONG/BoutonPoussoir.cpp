#include "BoutonPoussoir.hpp"

BoutonPoussoir::BoutonPoussoir(int b):Capteur(b),dernierChangement(0), 
    dernierEtat(LOW),
    etatPrecedent(LOW){
  pinMode(broche, INPUT);
}


bool BoutonPoussoir::LireEtat(){
  
      bool etatActuel = digitalRead(broche);
    
    // Anti-rebond
    if (etatActuel != dernierEtat) {
        dernierChangement = millis();
        dernierEtat = etatActuel;
    }
    
    // Vérifier si le délai d'anti-rebond est passé
    if ((millis() - dernierChangement) > antiRebond) {
        return etatActuel == LOW; // Retourne true si appuyé
    }
    
    return false;
  
}

bool BoutonPoussoir::AppuiDetecte(){

  bool etatActuel = LireEtat();
    
    if (etatActuel && !etatPrecedent) {
        etatPrecedent = etatActuel;
        return true;
    }
    
    etatPrecedent = etatActuel;
    return false;

}

BoutonPoussoir::~BoutonPoussoir(){

}
