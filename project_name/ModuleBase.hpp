//
// Created by ulric on 12/12/2025.
//

#ifndef BE_POO_KTANE_MODULEBASE_HPP
#define BE_POO_KTANE_MODULEBASE_HPP

class Bomb;

class ModuleBase {
    protected:
    int led=0;
    Bomb * bombp; // Pointeur vers la bombe
    public:

     ModuleBase(Bomb* bomb);

    void Made_Error();

    int get_led();

    
};
#endif //BE_POO_KTANE_MODULEBASE_HPP