
#ifndef CARACTERISTICS_H
#define CARACTERISTICS_H

#include <Arduino.h>

class caracteristics{

protected:
    String name;
    String value;
    unsigned int quantity=0;

public:

    caracteristics(String name, String value, int quantity);   
    // Constructeur qui créé une caractéristique avec un nom, une valeur et une quantité


    ~caracteristics();

    // Getters et setters
    String getName();
    String getValue();

    unsigned int getQuantity();     //finalement utilisé à la place des opérateurs surchargés car ceux-ci ne fonctionnaient pas correctement
    void setQuantity(unsigned int q);

    

    // Opérateur += pour ajouter une quantité
    void operator+=(const int addedQuantity) {
        quantity += addedQuantity;
    }

    // Opérateur -= pour soustraire une quantité
    void operator-=(const int removedQuantity) {
        quantity -= removedQuantity;
    }

    // Opérateur = pour affecter une quantité
    void operator=(const int newQuantity) {
        quantity = newQuantity;
    }


};


#endif