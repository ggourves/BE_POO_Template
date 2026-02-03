#include "Thread.h"
#include <Arduino.h>
#include "Bombe.hpp" //recup la fonction ajout d'erreur (#include)
#include "ModuleBase.hpp"

Thread::Thread(Bomb *bomb) : ModuleBase(bomb) {
  }

void Thread::initPin() {
  for (int i = 9; i < 14; i++) {
      pinMode(i, INPUT_PULLUP);
  }
      pinMode(26, OUTPUT);
}


void Thread:: stateThread(){
  if (bombp->getError()<1){
      int state;
      for (int i=9;i<14; i++){
          state=digitalRead(i); 
          if(state==HIGH){  // On regarde que si l'état du fil est coupé
              if (i!=13){  // Si le 1er fil n'est pas celui coupé on fait exploser la bombe
                bombp->AddError();
                bombp->AddError();
                bombp->AddError();
                led=0;
                digitalWrite(8, LOW);
              }
              else{         // Sinon on active la led de validation
                if ( led !=1){
                  led=1;
                  digitalWrite(8, HIGH);
                  bombp->AddSuccess();
                }
              }
            }
      }
    }
}
