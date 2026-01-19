## BE POO – Projet Bailarina

Ce dépôt correspond au projet **Danseuse Capybara**, réalisé dans le cadre du **Bureau d’Études de C++** à l’**INSA Toulouse**.

Le projet implémente un système embarqué interactif basé sur un **ESP8266**, intégrant plusieurs capteurs et actionneurs, et piloté selon une architecture **orientée objet en C++**.  
Il met en œuvre les principes fondamentaux de la POO (abstraction, héritage, composition et polymorphisme) ainsi qu’une communication **WiFi via HTTP**.

### Fonctionnalités principales
- Détection de présence par capteur ultrason
- Détection de luminosité (mode nuit)
- Interaction utilisateur via bouton tactile
- Commande et supervision à distance via serveur HTTP embarqué
- Animation mécanique (servo), sonore (buzzer) et visuelle (LED)
- Affichage de l’état du système sur écran LCD RGB

### Architecture logicielle
Le projet est structuré de manière modulaire autour de :
- interfaces abstraites pour les capteurs et actionneurs,
- classes concrètes spécialisées,
- une classe applicative centrale assurant l’orchestration du système,
- un fichier `.ino` volontairement minimal servant de point d’entrée.

Cette organisation vise à garantir la lisibilité, l’extensibilité et la maintenabilité du code.

### Travail collaboratif
Le développement est réalisé de manière collaborative à l’aide de **GitHub**, en utilisant des branches de développement et des intégrations via *pull requests*.

### Auteurs
- **Roberto Ibanez Mingarro**
- **Kevin Felipe Visbal Pinzón**
---

Dépôt initialisé à partir du template fourni pour le BE POO.

### Diagrammes UML

#### Diagramme de classes
![Diagramme de classes UML](uml_diagrams/UML_Clase_Diagram.png)

#### Diagramme de cas d’utilisation
![Diagramme de cas d’utilisation UML](uml_diagrams/UML_UseCase.png)
