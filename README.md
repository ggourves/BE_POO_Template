# BE_POO_Bin_Inventory

Projet d'inventaire électronique en C++ utilisant la programmation orientée objet (POO).


## Description

Ce projet vise à créer une application d'inventaire électronique en C++ en utilisant les principes de la programmation orientée objet. 
L'application permettra de gérer un inventaire de d'items : 

Lorsqu'on pose une bin/boite sur la matrice de capteurs, l'application détecte la présence de la bin et demande à l'utilisateur son contenu pour l'enregistrer dans une base de données (ici une liste chainée).

Lorsqu'on retire une bin/boite de la matrice de capteurs, l'application détecte son absence et supprime l'item correspondant dans la base de données.

Via le moniteur série, l'utilisateur peut afficher l'inventaire actuel.
Il a deux actions possibles :
- Modifier la quantité d'un item
- Faire resortir un item visuellement (allumage LED)


## Fonctionnalités 

- Détection de la présence/absence de bins sur une matrice de capteurs
- Enregistrement des items dans une base de données (liste chainée)
- Affichage de l'inventaire actuel via le moniteur série
- Modification de la quantité d'un item
- Allumage LED pour faire ressortir un item visuellement


## Technologies Utilisées

- C++
- Programmation Orientée Objet (POO)
- Liste chainée pour la gestion de la base de données
- Matrice de capteurs pour la détection des bins
- Moniteur série pour l'interaction utilisateur
- LED adressables pour l'indication visuelle des items
- Héritage multiple et polymorphisme pour la gestion des items
- Utilisation de la STL (Standard Template Library) 
- Gestion des exceptions pour la robustesse de l'application


## Améliorations Futures

- Intégration d'une interface utilisateur graphique (GUI), esp8266, on peut faire une apllication web pour gérer l'inventaire à distance.
- Ajout de fonctionnalités de recherche et de filtrage des items dans l'inventaire.
- Ajout de la persistance des données. (utilisation de fichiers (ex:json) ou base de données(ex:SQL))
(actuellement les données sont perdues à l'arrêt du programme)
- Ajout de tests unitaires pour assurer la qualité du code.
- Ajout d'un lecteur RFID pour une identification de chaque bin. 
    - A chaque bin est associée à une puce RFID, ce qui permet une identification unique et rapide. 
    - On peut d'abord lire la puce RFID pour identifier la bin, puis on demande à l'utilisateur le contenu de la bin pour l'enregistrer dans la base de données. Il peut ensuite la poser sur la matrice de capteurs.
    - Lorsqu'on retire une bin de la matrice, on peut lire la puce RFID pour identifier la bin à retirer de la base de données.
    - Et bien plus encore...
- Ajout de fonctionnalités de modification avancée des items, comme le changement de catégorie ou l'ajout de tags (trier par type d'item ex de tag : module, microcontrolleur, composant passif, IC...).


## Conclusion

Ce projet d'inventaire électronique est une idée innovante qui met en œuvre la programmation orientée objet en C++ tout en offrant un cas concret d'utilisation.


## Auteurs

- CZUBEK Valentin
- https://github.com/ValentinCZUBEK

- MUELAS Mathieu
- https://github.com/mathieuMuelas

