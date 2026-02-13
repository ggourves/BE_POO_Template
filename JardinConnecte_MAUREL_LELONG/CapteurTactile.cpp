#include "CapteurTactile.hpp"

CapteurTactile::CapteurTactile(int b):Capteur(b){
}

bool CapteurTactile::LireEtat(){

        return digitalRead(BROCHE_CT)==HIGH;
}


CapteurTactile::~CapteurTactile(){

}

