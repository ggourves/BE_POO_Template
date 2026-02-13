#include "CapteurTemperature.hpp"

CapteurTemperature::CapteurTemperature() 
    : Temperature(0), Humidite(0) {
}

void CapteurTemperature::Init() {
    Wire.begin(D2, D1);
    if (!sht31.begin(0x44)) { 
        Serial.println("Erreur: SHT31 non détecté !"); // test car le capteur peut être non détecté (souvent)
        while (1);
    }}


float CapteurTemperature::LireValeurtemp() {
    float t = sht31.readTemperature();
    if (!isnan(t)) {
        Temperature = t;
    } else {
        Serial.println("Erreur lecture temperature !");
    }
    return Temperature;
}


void CapteurTemperature::AfficheTemperature(){
      Serial.print("Temperature: ");
      Serial.print(Temperature);
      Serial.println(" °C");
    }

    float CapteurTemperature::LireValeurhum() {
    int h = sht31.readHumidity();
    if (!isnan(h)) {
        Humidite = h;
    } else {
        Serial.println("Erreur lecture humidite !");
    }
    return Humidite;
}


void CapteurTemperature::AfficheHumidite(){
      Serial.print("Humidité: ");
      Serial.print(Humidite);
      Serial.println("% ");
    }

bool CapteurTemperature::NecessiteArrosage(float seuil) {
    return LireValeurhum() < seuil;
}


CapteurTemperature::~CapteurTemperature(){


}

