#include "Jardin.hpp"

Jardin::Jardin()
    : led(BROCHE_LED),
      ct(BROCHE_CT),
      buzz(BROCHE_BUZZER),
      bp(BROCHE_BP1),
      arroser(led, ct, buzz, temp, plantes),
      derniereMiseAJourPlantes(0)
{
     try{
    // Création des plantes de base
    Rose* rose1 = new Rose("rouge");
    Tulipe* tulipe1 = new Tulipe("bleue");
    Rose* rose2 = new Rose("blanche");
    Poireau* poireau1 = new Poireau(15, "Berthe");
    
    Citrouille* citrouille = new Citrouille(20,"Pascale");
    Poireau* poireau2 = new Poireau(10, "Denys");
    Poireau* poireau3 = new Poireau(*poireau1 + *poireau2);

    // Ajouter plantes au jardin
    AjouterPlante(rose1);
    AjouterPlante(tulipe1);
    AjouterPlante(rose2);
    AjouterPlante(poireau1);
    AjouterPlante(citrouille);
    AjouterPlante(poireau2);
    AjouterPlante(poireau3); 
    
    Citrouille* citrouille2 = new Citrouille(201,"Ginette");
    AjouterPlante(citrouille2);
    }

    catch (int a){
        if (a==ProbCitrouille){
            Serial.println("Le jardin s'est fait écrasé par une citrouille !!! Oh non");
        }
    }
}

void Jardin::init() {
    lcd.Init();
    temp.Init();
}

void Jardin::run() {
    unsigned long now = millis();

    // Mise à jour PV des plantes
    if (now - derniereMiseAJourPlantes >= intervalMiseAJourPlantes) {
        for (auto& p : plantes) {
            p->ModifPointDeVie(temp);
        }
        derniereMiseAJourPlantes = now;
    }

    // Arrosage
    arroser.ChangerModeArrosage();
    arroser.ArroserPlante();

    // LCD
    lcd.GererMenuLCD(bp, temp, plantes);

}

  void Jardin::AjouterPlante(Plante* plante) {
        plantes.push_back(plante);
    }
