 #include "Simon.h"
#include <Arduino.h>
#include "Bombe.hpp" //recup la fonction ajout d'erreur 
#include"ModuleBase.hpp"


Simon:: Simon(Bomb *b) : ModuleBase(b){
} //constructeur

// broche a verifier
#define ButtonRstate digitalRead(41)
#define ButtonBstate digitalRead(43) 
#define ButtonJstate digitalRead(45)
#define ButtonVstate digitalRead(47)

void Simon::Simon_pin_config(){
  previousMillis = millis();
  for (int i = 40; i < 49; i++) {
    if (i%2==0)
      pinMode(i, OUTPUT); // config LEDs
    else
      pinMode(i, INPUT_PULLUP); // config bouton boussoir
  }
}

void Simon:: LED_ON(char led){
  
  if(led=='R'){
    digitalWrite(40,HIGH);
  }
  else if(led=='B'){
    digitalWrite(42,HIGH);
  }
  else if(led=='J'){
    digitalWrite(44,HIGH);
  }
  else if(led=='V'){
    digitalWrite(46,HIGH);
  }
}

void Simon:: LED_OFF(char led){
  
  if(led=='R'){
    digitalWrite(40,LOW);
  }
  else if(led=='B'){
    digitalWrite(42,LOW);
  }
  else if(led=='J'){
    digitalWrite(44,LOW);
  }
  else if(led=='V'){
    digitalWrite(46,LOW);
  }
}

void Simon::Reset(){

  bombp->AddError();

  previousMillis_R=millis();
  previousMillis_B=millis();
  previousMillis_J=millis();
  previousMillis_V=millis();
  currentMillis_R=millis();
  currentMillis_B=millis();
  currentMillis_J=millis();
  currentMillis_V=millis();
  currentMillis=millis();
  interval=4000;

  BB_temp=0;
  BR_temp=0;
  BJ_temp=0;
  BV_temp=0;

  index_led=0;
  Nb_Button=0;
  Prev_Led=NULL;
  Next_Led=NULL;
}

void Simon::FlashLed0() {
  // ici on flash une fois un boutton appuyé
  if(BB_temp){
    //Serial.println(BB_temp);
    currentMillis_B=millis();
    if((currentMillis_B - previousMillis_B)>=500) {
      LED_OFF('B');
      if (BB_temp == 1) {
        
        if (Tab_Error0[stage][Nb_Button] =='B') {
           
          if (Nb_Button== stage ) {     
            stage++;
            index_led=0;
            Nb_Button=0;
          }
          else {
            Nb_Button++;
          }
        }
        else {
          Reset();
         
        }
        BB_temp = 2; //anti rebond
      }
      
    }
      else{
        LED_ON('B');
      }
      if ( ButtonBstate == LOW and BB_temp == 2)
        BB_temp=0;
  }
    if(BR_temp) {
      currentMillis_R=millis();
      if((currentMillis_R - previousMillis_R)>=500) {
        LED_OFF('R');
        if (BR_temp == 1) {
          if (Tab_Error0[stage][Nb_Button] =='R'){
            if (Nb_Button== stage ) {
              stage++;
              index_led=0;
              Nb_Button=0;
            }
            else {
              Nb_Button++;
            }
          }
          else {
            Reset();
          }
          BR_temp = 2;
        }
      }
        else{
          LED_ON('R');
        }
        if ( ButtonRstate == LOW and BR_temp == 2)
          BR_temp=0;
    }
    if(BJ_temp) {
      currentMillis_J=millis();
      if((currentMillis_J - previousMillis_J)>=500) {
        LED_OFF('J');
        if (BJ_temp == 1) {
          if (Tab_Error0[stage][Nb_Button] =='J'){
            if (Nb_Button== stage ) {
              stage++;
              index_led=0;
              Nb_Button=0;
            }
            else {
              Nb_Button++;
            }
          }
          else {
            Reset();
          }
          BJ_temp = 2;
        }
      }
        else{
          LED_ON('J');
        }
        if ( ButtonJstate == LOW and BJ_temp == 2)
          BJ_temp=0;
    }
    if(BV_temp) {
      currentMillis_V=millis();
      if((currentMillis_V - previousMillis_V)>=500) {
        LED_OFF('V');
        if (BV_temp == 1) {
          if (Tab_Error0[stage][Nb_Button] =='V'){
            if (Nb_Button== stage ) {
              stage++;
              index_led=0;
              Nb_Button=0;
            }
            else {
              Nb_Button++;
            }
          }
          else {
            Reset();
          }
          BV_temp = 2;
        }
      }
        else{
          LED_ON('V');
        }
        if ( ButtonVstate == LOW and BV_temp == 2)
          BV_temp=0;
    }
    // Si aucun boutton n'est appuyé
       
    if(BB_temp==0 and BR_temp==0 and BV_temp==0 and BJ_temp==0){
      currentMillis=millis();

      
      if ( currentMillis-previousMillis>=interval){
        previousMillis=currentMillis;
        if (interval==4000 or interval==3000){
          LED_ON(Tab_Stage[stage][index_led]);
          interval=100;
          Prev_Led=Tab_Stage[stage][index_led];
          if((index_led+1)<=stage){
            
            Next_Led=Tab_Stage[stage][index_led+1];
          }
        }
        else if(interval==100){
          LED_OFF(Prev_Led);
          index_led++;
          if(index_led<=stage)
            interval=500;
          else{
            interval=4000;
            index_led=0;
          }
        }
        else if(interval==500){
          //Serial.println(nb_Leds);
          LED_ON(Next_Led);
          //Serial.println((const char*)Prev_Led);
          interval=100;
          Prev_Led=Next_Led;
          //Serial.println(stage-(nb_Leds-1));
          
          if((index_led+1)>0){
            Next_Led=Tab_Stage[stage][index_led+1];
          }
          
        }
      }
    }
  }

void Simon::FlashLed1() {
  // ici on flash une fois un boutton appuyé
  if(BB_temp){
    //Serial.println(BB_temp);
    currentMillis_B=millis();
    if((currentMillis_B - previousMillis_B)>=500) {
      LED_OFF('B');
      if (BB_temp == 1) {

        if (Tab_Error1[stage][Nb_Button] =='B') {

          if (Nb_Button== stage ) {
            stage++;
            index_led=0;
            Nb_Button=0;
          }
          else {
            Nb_Button++;
          }
        }
        else {
          Reset();

        }
        BB_temp = 2; //anti rebond
      }

    }
      else{
        LED_ON('B');
      }
      if ( ButtonBstate == LOW and BB_temp == 2)
        BB_temp=0;
  }
    if(BR_temp) {
      currentMillis_R=millis();
      if((currentMillis_R - previousMillis_R)>=500) {
        LED_OFF('R');
        if (BR_temp == 1) {
          if (Tab_Error1[stage][Nb_Button] =='R'){
            if (Nb_Button== stage ) {
              stage++;
              index_led=0;
              Nb_Button=0;
            }
            else {
              Nb_Button++;
            }
          }
          else {
            Reset();
          }
          BR_temp = 2;
        }
      }
        else{
          LED_ON('R');
        }
        if ( ButtonRstate == LOW and BR_temp == 2)
          BR_temp=0;
    }
    if(BJ_temp) {
      currentMillis_J=millis();
      if((currentMillis_J - previousMillis_J)>=500) {
        LED_OFF('J');
        if (BJ_temp == 1) {
          if (Tab_Error1[stage][Nb_Button] =='J'){
            if (Nb_Button== stage ) {
              stage++;
              index_led=0;
              Nb_Button=0;
            }
            else {
              Nb_Button++;
            }
          }
          else {
            Reset();
          }
          BJ_temp = 2;
        }
      }
        else{
          LED_ON('J');
        }
        if ( ButtonJstate == LOW and BJ_temp == 2)
          BJ_temp=0;
    }
    if(BV_temp) {
      currentMillis_V=millis();
      if((currentMillis_V - previousMillis_V)>=500) {
        LED_OFF('V');
        if (BV_temp == 1) {
          if (Tab_Error1[stage][Nb_Button] =='V'){
            if (Nb_Button== stage ) {
              stage++;
              index_led=0;
              Nb_Button=0;
            }
            else {
              Nb_Button++;
            }
          }
          else {
            Reset();
          }
          BV_temp = 2;
        }
      }
        else{
          LED_ON('V');
        }
        if ( ButtonVstate == LOW and BV_temp == 2)
          BV_temp=0;
    }
    // Si aucun boutton n'est appuyé

    if(BB_temp==0 and BR_temp==0 and BV_temp==0 and BJ_temp==0){
      currentMillis=millis();


      if ( currentMillis-previousMillis>=interval){
        previousMillis=currentMillis;
        if (interval==4000 or interval==3000){
          LED_ON(Tab_Stage[stage][index_led]);
          interval=100;
          Prev_Led=Tab_Stage[stage][index_led];
          if((index_led+1)<=stage){

            Next_Led=Tab_Stage[stage][index_led+1];
          }
        }
        else if(interval==100){
          LED_OFF(Prev_Led);
          index_led++;
          if(index_led<=stage)
            interval=500;
          else{
            interval=4000;
            index_led=0;
          }
        }
        else if(interval==500){
          //Serial.println(nb_Leds);
          LED_ON(Next_Led);
          //Serial.println((const char*)Prev_Led);
          interval=100;
          Prev_Led=Next_Led;
          //Serial.println(stage-(nb_Leds-1));

          if((index_led+1)>0){
            Next_Led=Tab_Stage[stage][index_led+1];
          }

        }
      }
    }
  }

void Simon::FlashLed2() {
  // ici on flash une fois un boutton appuyé
  if(BB_temp){
    //Serial.println(BB_temp);
    currentMillis_B=millis();
    if((currentMillis_B - previousMillis_B)>=500) {
      LED_OFF('B');
      if (BB_temp == 1) {

        if (Tab_Error2[stage][Nb_Button] =='B') {

          if (Nb_Button== stage ) {
            stage++;
            index_led=0;
            Nb_Button=0;
          }
          else {
            Nb_Button++;
          }
        }
        else {
          Reset();

        }
        BB_temp = 2; //anti rebond
      }

    }
      else{
        LED_ON('B');
      }
      if ( ButtonBstate == LOW and BB_temp == 2)
        BB_temp=0;
  }
    if(BR_temp) {
      currentMillis_R=millis();
      if((currentMillis_R - previousMillis_R)>=500) {
        LED_OFF('R');
        if (BR_temp == 1) {
          if (Tab_Error2[stage][Nb_Button] =='R'){
            if (Nb_Button== stage ) {
              stage++;
              index_led=0;
              Nb_Button=0;
            }
            else {
              Nb_Button++;
            }
          }
          else {
            Reset();
          }
          BR_temp = 2;
        }
      }
        else{
          LED_ON('R');
        }
        if ( ButtonRstate == LOW and BR_temp == 2)
          BR_temp=0;
    }
    if(BJ_temp) {
      currentMillis_J=millis();
      if((currentMillis_J - previousMillis_J)>=500) {
        LED_OFF('J');
        if (BJ_temp == 1) {
          if (Tab_Error2[stage][Nb_Button] =='J'){
            if (Nb_Button== stage ) {
              stage++;
              index_led=0;
              Nb_Button=0;
            }
            else {
              Nb_Button++;
            }
          }
          else {
            Reset();
          }
          BJ_temp = 2;
        }
      }
        else{
          LED_ON('J');
        }
        if ( ButtonJstate == LOW and BJ_temp == 2)
          BJ_temp=0;
    }
    if(BV_temp) {
      currentMillis_V=millis();
      if((currentMillis_V - previousMillis_V)>=500) {
        LED_OFF('V');
        if (BV_temp == 1) {
          if (Tab_Error2[stage][Nb_Button] =='V'){
            if (Nb_Button== stage ) {
              stage++;
              index_led=0;
              Nb_Button=0;
            }
            else {
              Nb_Button++;
            }
          }
          else {
            Reset();
          }
          BV_temp = 2;
        }
      }
        else{
          LED_ON('V');
        }
        if ( ButtonVstate == LOW and BV_temp == 2)
          BV_temp=0;
    }
    // Si aucun boutton n'est appuyé

    if(BB_temp==0 and BR_temp==0 and BV_temp==0 and BJ_temp==0){
      currentMillis=millis();


      if ( currentMillis-previousMillis>=interval){
        previousMillis=currentMillis;
        if (interval==4000 or interval==3000){
          LED_ON(Tab_Stage[stage][index_led]);
          interval=100;
          Prev_Led=Tab_Stage[stage][index_led];
          if((index_led+1)<=stage){

            Next_Led=Tab_Stage[stage][index_led+1];
          }
        }
        else if(interval==100){
          LED_OFF(Prev_Led);
          index_led++;
          if(index_led<=stage)
            interval=500;
          else{
            interval=4000;
            index_led=0;
          }
        }
        else if(interval==500){
          //Serial.println(nb_Leds);
          LED_ON(Next_Led);
          //Serial.println((const char*)Prev_Led);
          interval=100;
          Prev_Led=Next_Led;
          //Serial.println(stage-(nb_Leds-1));

          if((index_led+1)>0){
            Next_Led=Tab_Stage[stage][index_led+1];
          }

        }
      }
    }
  }


  void Simon::Simon_Check() {
  if ( stage <5){
    if ( ButtonRstate==HIGH and BR_temp==LOW) {
      if ( BR_temp==LOW) {
        previousMillis_R=millis();
      }
      previousMillis=millis();
      interval=3000;
      BR_temp=HIGH;
    }
    if ( ButtonBstate==HIGH and BB_temp==LOW) {
     
      if ( BB_temp==LOW) {
        previousMillis_B=millis();
      }
      
      previousMillis=millis();
      interval=3000;
      BB_temp=HIGH;
    }
    if ( ButtonJstate==HIGH and BJ_temp==LOW) {
      if ( BJ_temp==LOW) {
        previousMillis_J=millis();
      }
      previousMillis=millis();
      interval=3000;
      BJ_temp=HIGH;
    }
    if ( ButtonVstate==HIGH and BV_temp==LOW) {
      if ( BV_temp==LOW) {
        previousMillis_V=millis();
      }
      previousMillis=millis();
      interval=3000;
      BV_temp=HIGH;
    }
    int err = bombp->getError();
    if (err==0)
      FlashLed0();
    else if (err==1)
       FlashLed1();
     else if (err==2)
       FlashLed2();
  }
  else {
    digitalWrite(48, HIGH);
    if ( led !=1){
      led = 1;
      bombp->AddSuccess();
    }
  }
}

  Simon::~Simon(){

  }