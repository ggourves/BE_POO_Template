# BE_POO_Template

# La bombe 

La bombe correspond à une classe ( Bomb ) comportant le numéro de série, le nombre de port, le nombre de pile, la durée du jeu et le nombre d'erreurs.
Pour éviter certains problèmes, nous avons ajouté un entier Update se mettant à jour pour chaque erreur afin d'optimiser la durée de la loop() lorsqu'il n'y a pas d'erreurs.

Les modules de la bombe seront constitués d'un module de base servant à tous puis par héritage chaque module sera défini.


# Module Timer et Gestion des erreurs

Ce module vise à définir la gestion du temps et des erreurs.

Il utilise les pins 22 et 24 pour les LEDs des erreurs et les pins 2 et  3 ( Digital PWM ) pour l'affichage ( Timer et Erreur ).
Les modules appellent la fonction AddError() pour ajouter une erreur sur la bombe. Pour l'instant il n'y a pas de son d'explosion.

Le Timer se mets à jour avec l'aide de la fonction millis() pour avoir de la précision.

Les erreurs sont gérées dans la classe Bomb, où a chaque boucle on vérifie s'il y a eu une update, à ce moment, on allume une LED supplémentaire selon le nombre d'erreurs précédentes et on affiche Err 1 ou Err 2 pendant 1s.
Au bout de 3 erreurs la bombe se déclenche et affiche "LOSE" ( sauf pour les fils où la bombe marque "LOSE" si le fil coupé n'est pas bon )

# Premier Module
Voici le module "Thread":

Il s'agit de la première configuration (de 5 fils) dont le vrai fil à couper est le premier (fil vert, bleu ou un autre peu importe) s'il y a deux fils jaunes et un seul fil rouge.
Pour cela, j'ai fais une classe "Thread" qui aura principalement une fonction permettant de configurer en mode Input les 5 pins (31, 33, 35, 37 et 39) que l'on utilisera pour les fils et une fonction qui permettra de détecter, en fonction de l'état des ports d'entrée de la carte (si une des pins n'est plus alimentée) permettra de savoir si un fil est déconnecté de la pin.
Si le fil coupé n'est pas la pin 31, la bombe se déclenche.

La LED de validation est situé sur la pin 26.

# Deuxième Module
Mudule "Simon":
Pins utilisés-> - 41, 43, 45, 47 pour les boutons poussoir
                - 40 (rouge), 42 (bleu), 44 (jaune), 46 (vert) pour les 4 LEDs du module
                - 48 pour la LED de validation
Le module se comporte de 3 façons différentes en fonction du nombre d'erreurs faits. A chaque erreur (2 maximum) il y a une fin différente. Cependant, si les 3 fautes sont atteintes, la bombe se déclenche.
