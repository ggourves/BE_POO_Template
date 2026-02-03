#ifndef Thread_h
#define Thread_h

#include <Arduino.h>

#include "ModuleBase.hpp"


class Thread : public ModuleBase {
  public: 
    Thread(Bomb *bomb);
    void initPin();
    void stateThread(); // si le fil coupé est le bon
  };

#endif