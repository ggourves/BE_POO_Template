#ifndef SONG_H
#define SONG_H

#include <Arduino.h>
#include <vector>

// Structure Note : représente une note de musique avec sa fréquence et sa durée (division rythmique).
struct Note {
  int freq;  // Fréquence de la note en Hertz (ex: 440 pour la note La4)
  int div;   // Division de la note (ex: 4 pour une noire, 8 pour une croche, etc.)
};

class Song {
public:
  // Surcharge de l'opérateur << pour ajouter une note à la chanson.
  Song& operator<<(const Note& n);
  // Surcharge de l'opérateur [] pour accéder à une note de la chanson par son index.
  const Note& operator[](size_t i) const;
  // Renvoie le nombre de notes dans la chanson.
  size_t size() const;

private:
  std::vector<Note> notes_;  // Utilisation de la STL : vecteur dynamique contenant les notes de la chanson
};

#endif
