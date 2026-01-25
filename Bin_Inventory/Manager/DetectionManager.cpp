#include "DetectionManager.h"

// Constructeur
DetectionManager::DetectionManager() :
    changementAjoutDetecte(false),      // Initialisation des drapeaux de détection (état par défaut)
    changementSuppressionDetecte(false),
    lastDetectionTime(0) {  // Initialisation du temps de la dernière détection à 0 (sinon la première détection serait aléatoire en fonction de ce qu'il y a dans la mémoire)

    for (int i = 0; i < TAILLE; i++) {      // Boucle pour initialiser l'état précédent des capteurs à false
        for (int j = 0; j < TAILLE; j++) {
            etatPrecedentCapteurs[i][j] = false;
        }
    }
}

// Méthode pour détecter les changements (non bloquante)
void DetectionManager::detecterChangement(Grid4x4 *grille) {

    // Détection des ajouts (0 à 1)
    if (!changementAjoutDetecte) {
        for (int i = 0; i < TAILLE; i++) {
            for (int j = 0; j < TAILLE; j++) {
                if (grille->cells[i][j].capteur && !etatPrecedentCapteurs[i][j]) {  // Si l'état actuel est 1 et que l'état prcédént est 0 on a détecté un changement
                    changementAjoutDetecte = true;  //On met le drapeau à true
                    lastDetectionTime = millis();   // On enregistre le temps de la détection, pour pouvoir comparer après
                    return; // On sort dès le premier changement détecté
                }
            }
        }
    }

    // Détection des suppressions (1 à 0)
    if (!changementSuppressionDetecte) {
        for (int i = 0; i < TAILLE; i++) {
            for (int j = 0; j < TAILLE; j++) {
                if (!grille->cells[i][j].capteur && etatPrecedentCapteurs[i][j]) {  // Si l'état actuel est 0 et que l'état prcédént est 1 on a détecté un changement
                    changementSuppressionDetecte = true; //On met le drapeau à true
                    lastDetectionTime = millis();   // On enregistre le temps de la détection, pour pouvoir comparer après
                    return; // On sort dès le premier changement détecté
                }
            }
        }
    }
}

// Méthode pour gérer la détection et interagir avec l'utilisateur
void DetectionManager::gererDetection(Grid4x4 *grille, itemManager *manager) {
    // Gestion de l'ajout
    if (changementAjoutDetecte) {
        if (millis() - lastDetectionTime >= DELAI_DETECTION) {  // Délai atteint depuis la dernière détection

            int nb_slots = 0;   // RAZ du nombre de slots affectés côté hardware
            struct coordinates affected_slots[TAILLE * TAILLE]; // Tableau de la taille maximale possible

            // Enregistrer les capteurs passés de 0 à 1
            for (int i = 0; i < TAILLE; i++) {
                for (int j = 0; j < TAILLE; j++) {
                    if (grille->cells[i][j].capteur && !etatPrecedentCapteurs[i][j]) {
                        affected_slots[nb_slots].x = i; // Stocker les coordonnées
                        affected_slots[nb_slots].y = j;
                        nb_slots++; // Grâce au nb_slots on sait combien de slots sont affectés
                    }
                }
            }

            // Demander les infos à l'utilisateur pour l'ajout
            Serial.println("Nouvelle boîte détectée !");
            Serial.print("Nombre de slots affectés : ");
            Serial.println(nb_slots);

            Serial.println("Entrez le nom de l'item :");
            while (Serial.available() == 0) {}
            String nom = Serial.readStringUntil('\n');  // mieux que read niveau robustesse
            nom.trim(); // Enlever les espaces inutiles

            Serial.println("Entrez la valeur de l'item :");
            while (Serial.available() == 0) {}
            String valeur = Serial.readStringUntil('\n');   // pareil
            valeur.trim();

            Serial.println("Entrez la quantité de l'item :");
            while (Serial.available() == 0) {}
            String quantInput = Serial.readStringUntil('\n');   //pareil
            quantInput.trim();
            if (quantInput.length() == 0) {
                Serial.println("Quantité non entrée, annulation.");
                changementAjoutDetecte = false;
                return;
            }
            int quantite = quantInput.toInt();  // Conversion en int

            // Ajouter l'item au gestionnaire
            manager->add(nb_slots, affected_slots, nom, valeur, quantite);

            // Mettre à jour l'état précédent
            for (int i = 0; i < TAILLE; i++) {
                for (int j = 0; j < TAILLE; j++) {
                    etatPrecedentCapteurs[i][j] = grille->cells[i][j].capteur;
                }
            }

            Serial.println("Item ajouté avec succès !");
            changementAjoutDetecte = false; // Retombée du drapeau
        }
    }
    // Gestion de la suppression
    else if (changementSuppressionDetecte) {    
        if (millis() - lastDetectionTime >= DELAI_DETECTION) {  // Délai atteint depuis la dernière détection


            int nb_slots = 0;   // RAZ du nombre de slots affectés côté hardware
            struct coordinates affected_slots[TAILLE * TAILLE]; // Tableau de la taille maximale possible

            // Enregistrer les capteurs passés de 1 à 0
            for (int i = 0; i < TAILLE; i++) {  
                for (int j = 0; j < TAILLE; j++) {  
                    if (!grille->cells[i][j].capteur && etatPrecedentCapteurs[i][j]) {  
                        affected_slots[nb_slots].x = i; // Stocker les coordonnées
                        affected_slots[nb_slots].y = j; 
                        nb_slots++;     // Grâce au nb_slots on sait combien de slots sont affectés
                    }
                }
            }

            // Supprimer les cellules désactivées
            manager->gridRemoveCells(nb_slots, affected_slots);

            // Mettre à jour l'état précédent
            for (int i = 0; i < TAILLE; i++) {
                for (int j = 0; j < TAILLE; j++) {
                    etatPrecedentCapteurs[i][j] = grille->cells[i][j].capteur;
                }
            }

            Serial.println("Cellules supprimées avec succès !");
            changementSuppressionDetecte = false;   // Retombée du drapeau
        }
    }
}

void DetectionManager::setInitialState(Grid4x4 *grille) {   // initialisation de l'état précédent des capteurs (pour éviter d'avoir des valeurs random)
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            etatPrecedentCapteurs[i][j] = grille->cells[i][j].capteur;
        }
    }
}
