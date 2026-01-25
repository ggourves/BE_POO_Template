#ifndef DETECTION_MANAGER_H
#define DETECTION_MANAGER_H

#include <Arduino.h>
#include "../Hardware/Grid.h"
#include "itemsManager.h"

class DetectionManager {
private:
    bool etatPrecedentCapteurs[TAILLE][TAILLE]; // État précédent des capteurs pour détection des changements
    bool changementAjoutDetecte;    // Drapeau si un ajout a été détecté
    bool changementSuppressionDetecte;  // Drapeau si une suppression a été détectée
    unsigned long lastDetectionTime;    // Temps de la dernière détection, qu'on utilisera pour trouver le temps écoulé
    static const unsigned long DELAI_DETECTION = 500;   // Délai "anti-rebond" en millisecondes

public:
    DetectionManager(); 

    void detecterChangement(Grid4x4 *grille);   
    // Détecte les changements dans l'état des capteurs en lisant la grille

    void gererDetection(Grid4x4 *grille, itemManager *manager); 
    // Gère les actions à effectuer en fonction des changements détectés (ajout ou suppression, dans le cas de l'ajout on demande les infos via la console série)

    void setInitialState(Grid4x4 *grille);
    // Initialise l'état précédent des capteurs avec l'état actuel de la grille (pour éviter les fausses détections au démarrage avec des valeurs aléatoires)
};

#endif
