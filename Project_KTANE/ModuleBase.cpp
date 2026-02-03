//
// Created by ulric on 12/12/2025.
//

#include "ModuleBase.hpp"
#include "Bombe.hpp"

ModuleBase::ModuleBase(Bomb * bomb) {
    this->bombp = bomb; // On donne l'adresse de la bombe
}

void ModuleBase::Made_Error() {
    bombp->AddError();
}

int ModuleBase::get_led(){
    return led;
}