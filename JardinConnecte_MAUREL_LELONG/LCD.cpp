#include "LCD.hpp"


LCD::LCD(){
}

void LCD::Init() { 
    lcd.begin(16, 2);         // LCD 16x2
    lcd.setRGB(colorR,colorG,colorB);
}

void LCD::AfficherMessage(const String& message) {
    lcd.setCursor(0, 0);
    lcd.print(message);
}

void LCD::AfficherTemperature(float temperature) {
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print((char)223); 
    lcd.print("C   ");
}

void LCD::AfficherHumidite(float humidite) {
    lcd.setCursor(0, 0);
    lcd.print("Hum: ");
    lcd.print(humidite);
    lcd.print("%   "); 
    
}

void LCD::GererMenuLCD(BoutonPoussoir& bp, CapteurTemperature& Temp, std::vector<Plante*>& plantes) {
 static int ecranCourant = 0;
    static bool affichageEffectue = false;
     static unsigned long dernierRafraichissement = 0;
    const unsigned long intervalRafraichissement = 2000; 

    if (bp.AppuiDetecte()) {  
        ecranCourant++;
        if (ecranCourant > plantes.size()) {
            ecranCourant = 0;
        }
        lcd.clear();
        affichageEffectue = false;
        dernierRafraichissement = millis();
    }

   bool doitRafraichir = !affichageEffectue || 
                          (millis() - dernierRafraichissement >= intervalRafraichissement);

    if (doitRafraichir) {
        if (ecranCourant == 0) {
            AfficherTemperature(Temp.LireValeurtemp());
            AfficherHumidite(Temp.LireValeurhum());
        } else {
            int idx = ecranCourant - 1;
            if (!plantes.empty() && idx < plantes.size() && plantes[idx] != nullptr) {
                Plante* p = plantes[idx];
                lcd.setCursor(0, 0);
                lcd.print(p->Caracteristiques());
                lcd.print("   ");
                lcd.setCursor(0, 1);
                lcd.print("PV: ");
                lcd.print(p->GetPointDeVie());
                if (p->GetPointDeVie()==0){
                    lcd.print("      Morte");
                }
                lcd.print("   ");
            }
        }
        affichageEffectue = true;
        dernierRafraichissement = millis();
    }
}



void LCD::Effacer() {
    lcd.clear();
}

LCD::~LCD(){};
