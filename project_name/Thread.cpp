#include "Thread.h"
#include <Arduino.h>
#include "Bombe.hpp" //recup la fonction ajout d'erreur (#include)
#include "ModuleBase.hpp"

Thread::Thread(Bomb *bomb) : ModuleBase(bomb) {
  }

void Thread::initPin() {
  for (int i = 31; i < 40; i++) {
    if ( i%2==1)
      pinMode(i, INPUT_PULLUP);
  }
      pinMode(26, OUTPUT);
}


void Thread:: stateThread(Bomb *bomb){
  if (bomb->getError()<1){
      int state;
      for (int i=31;i<40; i++){
        if (i%2==1){
          state=digitalRead(i); 
          if(state==HIGH){
              if (i!=31){
                bombp->AddError();
                bombp->AddError();
                bombp->AddError();
                led=0;
                digitalWrite(26, LOW);
              }
              else{
                led=1;
                digitalWrite(26, HIGH);
              }
            }
          }
      }
    }
}
