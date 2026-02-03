# Rapport du BE C++ : Projet  KTANE 

Basé sur le jeu vidéo de coopération "Keep Talking And Nobody Explodes"

Le code de la Mega se trouve dans le dossier Projet_KTANE tandis que le code de l'ESP8266 se trouve dans le dossier ESP8266
## La bombe et sa composition

La bombe correspond à une classe ( Bomb ) comportant la durée du jeu et le nombre d'erreurs.
Pour éviter certains problèmes, nous avons ajouté un entier Update se mettant à jour pour chaque erreur.

Les modules de la bombe seront constitués d'un module de base servant à tous, puis par héritage chaque module sera défini.


### Module Timer et Gestion des erreurs

Ce module vise à définir la gestion du temps et des erreurs.

Il utilise les pins 38 et 53 pour les LEDs des erreurs et les pins 2 et  3 ( Digital PWM ) pour l'affichage ( Timer et Erreur ).
Les modules appellent la fonction AddError() pour ajouter une erreur sur la bombe. 
Le Timer se met à jour avec l'aide de la fonction millis() pour avoir de la précision.
Quand le Timer arrive à zéro la bombe fait un son d'explosion.

Les erreurs sont gérées dans la classe Bomb, où a chaque boucle on vérifie s'il y a eu une update, à ce moment, on allume une LED supplémentaire selon le nombre d'erreurs précédentes et on affiche Err 1 ou Err 2 pendant 1s.
Au bout de 3 erreurs la bombe se déclenche et affiche "LOSE" ( sauf pour les fils où la bombe marque "LOSE" si le fil coupé n'est pas bon ( explosion instantanée )).
Si la bombe a trois succès alors le timer affiche "YEAH" et une musique retentit.

### Module de base

Chaque module sera un héritage de cette classe, elle ne contient que l'état de la led de validation et l'adresse de la bombe.

### Premier Module
Voici le module "Thread":

Il s'agit de la première configuration (de 5 fils) dont le vrai fil à couper est le 4ième fil s'il y a deux fils jaunes et un seul fil rouge.
Pour cela, j'ai fait une classe "Thread" qui aura principalement une fonction permettant de configurer en mode Input les 5 pins (9, 10, 11, 12 et 13) que l'on utilisera pour les fils et une fonction qui permettra de détecter, en fonction de l'état des ports d'entrée de la carte (si une des broches n'est plus alimentée) permettra de savoir si un fil est déconnecté de la broche.
Si le fil coupé n'est pas situé sur la broche 13, la bombe se déclenche sinon la LED s'allume.


La LED de validation est situé sur la pin 26.

### Deuxième Module
Module "Simon":

Broches utilisées → - 41, 43, 45, 47 pour les boutons poussoir
                    - 40 (rouge), 42 (bleu), 44 (jaune), 46 (vert) pour les 4 LEDs du module
                    - 48 pour la LED de validation
Le but de ce module est d'apppuyer sur les boutons qui flashent dans un ordre qui est prédéfini dans notre programme (tableaux des erreurs). Nous avons choisi la configuration correspondant à un nnuméro de série qui contient au moins une voyelle dans le jeu originel.

Le module se comporte de 3 façons différentes en fonction du nombre d'erreurs fait. Au début de la partie, ce sera toujours la LED rouge qui flashera toutes les 4 secondes. À chaque erreur (2 maximum) il y a un ordre de couleurs différentes. Nous avons défini l'ordre des couleurs dans des matrices différentes: Tab_Error0, Tab_Error1 et Tab_Error2. Si un joueur se trompe, il reprendra à partir de la couleur à laquelle il a échoué mais la suite ne sera pas la même que dans les autres cas.
Au bout de 3 erreurs, la bombe se déclenche.

### Troisième Module

Module "Password" :

Utilisation des broches 6 pour la communication avec la télécommande et 7 pour la LED de validation.

Le module se sert de la communication entre la Mega 2560 et l'ESP8266 en USART.
La Mega récupère les touches de la télécommande à travers le module IR et 
convertit ensuite avec la fonction Navigate() en instructions pour l'ESP.
Cela se fait au travers de l'USART 1 ( broche 18 ) de la MEGA ( en Tx ) et en D5 ( Rx SoftWare) pour l'ESP. 
L'envoi de l'instruction se fait à travers une surcharge d'opérateur (>>) pour simplifier la lisibité du code de Telecommmand_Check().

Concernant le code de l'ESP, la Mega fournit les instructions à travers la fonction Navigate() et Put_Letter() et l'ESP récupère les instructions, compare le premier mot d'instruction et agit, pour la télécommande cela correspond à l'instruction "SET:".
Cela nous a permis d'ajouter un module Speaker dépendant de la classe Password en ajoutant l'instruction "PLAY:".


Les instructions de la télécommande sont décomposés en 3 parties : le nom de la commande, l'emplacement de la lettre à changer et la lettre à mettre.
Ainsi, sur l'écran LCD, on peut voir les lettres envoyées apparaitre, et celles-ci sont changés si l'on appuie sur la touche Up ou Down. 
On peut contrôler l'emplacement de la lettre avec les touches fast forward et fast backward. La validation du mot de passe s'effectue avec la touche EQ.


## Problèmes rencontrés

### Pour la Bombe

Sur le plan fonctionnel, nous avons voulu gérer les erreurs et le déclenchement de la bombe par exceptions. Cependant, nous nous sommes rendu compte qu'il nous était impossible de le faire car la carte que nous avons utilisé en plus pour notre projet (Arduino MEGA) ne contient pas le runtime d’exceptions AVR qui permet de linker avec try et catch. On a du donc abandonné l'idée.

### Pour le timer

Compliqué à mettre en place, nous avions d'abord prévu de le faire par interruption, mais cela rendait le code très compliqué et il aurait fallu faire les autres fonctions par interruption. 
On a donc changé pour la fonction millis() plus simple d'utilisation. Cela permet au Timer de ne jamais se bloquer. 

L'affichage n'était pas simple, nous voulions à la base utilisée la surcharge d'opérateur pour décompter le timer mais cela ne menait qu'à davantage de difficulté inutile.
Alors, nous avons juste utilisé un int permettant de décompter.

### Pour les Fils

Difficulté de réalisation, les fils utilisent la fonction output pullup des gpios mais nous voulions faire l'inverse ( si l'état est bas alors le fil est coupé )
mais cela créait des broches flottantes qui n'étaient pas détectées.

### Pour le Simon

Difficulté de compréhension, nous avons dû revoir tout notre code sur un tableau ( toute une après-midi ) pour être sûr de ce qu'on faisait et que nous soyons clairs sur la démarche du module.
La gestion de clignotement des leds étaient aussi compliqués dans la logique de gestion ( selon si on appuie sur un bouton ou non ) faisant appel de nombreuses fois à la fonction millis.

### Pour le Password

Difficulté de syntaxe, première utilisation du module IRreceiver ayant une syntaxe particulière puis affichage sur le LCD avec la carte ESP8266.
Nous avons aussi voulu utilisé la STL dans le code pour avoir l'algorithme d'égalité de deux tableaux sauf que la MEGA ne supporte pas ArduinoSTL, nous avons donc décidé de ne pas l'utiliser.

### Pour la sortie audio

Nous voulions absolument une sortie audio pour la bombe, premier essai sans amplificateur audio ( seulement un transistor NPN ) et en wifi. Le résultat est un son très faible avec plus de grésillements que de signal voulu. 
Avec l'utilisation de l'amplificateur audio le son n'était que plus fort et nous avons du oublié l'utilisation du wifi pour l'audio.

Après ces échecs, nous avons essayé de mettre la partie audio sur la Mega mais celle-ci n'a pas assez de mémoire flash donc deuxième abandon.

Nous avons donc repris l'ESP8266 et avons découvert la librairie LittleFS pas trop complexe d'utilisation et qui permet d'envoyer un fichier directement dans la mémoire de l'ESP.

# Partie Conception

La bombe a été créé à partir de casier de rangement imprimé en 3D par nos soins avec l'utilisation du modèle STL " Interlocking Drawer " trouvé sur Thingiverse : https://www.thingiverse.com/thing:2539830.
Nous avons apporté des modifications au fichier de base ( notamment l'ouverture interne de la carte ).

La conception de l'intérieur a été faite sur-mesure en fonction des composants de chaque module, toujours imprimé en 3D permettant de faire des essais/erreurs.
La conception nous a permis de nous faire continuer d'apprendre la modélisation 3D.

Tous les fichiers STL et 3mf ( dont les erreurs )sont dans le dossier 3D File.

Les boutons ont ensuite été soudé avec les câbles et nous avons torsadé les câbles autour des lEDS ( LED + résistance ).


## Difficultés rencontrées

La gestion interne de la bombe a été compliqué, il a fallu concevoir une architecture solide mais permettant une modularité si l'on veut changer les modules( d'où l'utilisation de casier encastré ) même si cette idée a été un peu abandonnée par manque de temps.

Il a fallu ensuite prendre les mesures de chaque composant et faire des tests lors de la création interne modules pour être sûr que le composant pouvait rester en place.

L'écran LCD a posé des problèmes car il est plus grand que le casier, nous avons donc dû modifier davantage le fichier STL pour créer une encoche sur le dessus et adapter l'intérieur du casier pour pouvoir ajouter la LED et le module IR.

Le plus gros problème a été l'assemblage final et cela venait de l'utilisation des casiers modulables car pour assembler les casiers il faut les encaster par le haut ou le bas.
Ce que nous n'avions pas pris en compte a été le nombre total de fils. Il fallait que tous les fils restent connectés mais nous avons majoritairement utilisés des fils Dupont mâle-mâle ou mâle-femelle ce qui n'aidaient pas au maintien.
Nous avons donc commencé par le Simon ( le plus cablé et moins accessible ), facile à faire mais il a ensuite fallu connecter le timer et placer la Mega à l'intérieur. 
Ici vient deux problèmes : les câbles du Simon se détachent et la carte passe à peine dans son encadrement prévu ( entre les 4 modules ). Nous avons donc dû à de nombreuses reprises rebrancher les fils à la pincette puis percé un trou pour la Mega.
Nous avons ensuite eu des difficultés à placer les deux derniers casiers car il fallait lever la carte pour faire passer les casiers par le haut et le tout sans débrancher les câbles déjà placés, parce qu'ils ne seront plus accessibles.






