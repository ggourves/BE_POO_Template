#include "music_Song.h"

Song& Song::operator<<(const Note& n) {
  // Ajoute la note à la fin de la liste de notes de la chanson
  notes_.push_back(n);
  return *this;  // Retourne la chanson elle-même pour pouvoir chaîner les ajouts (operator<< surchargé)
}

const Note& Song::operator[](size_t i) const {
  if (notes_.empty()) {
    static Note dummy{0, 4};
    return dummy; 
    // Si la chanson est vide, on renvoie une note factice (fréquence 0) pour éviter tout accès invalide.
  }
  if (i >= notes_.size()) {
    // Si l'index est hors bornes, on renvoie la première note par défaut (fallback).
    // Remarque : on ne lance pas d'exception ici pour les indices invalides, 
    // car l'utilisation d'exceptions est généralement désactivée sur ESP8266.
    return notes_[0];
  }
  return notes_[i];  // Renvoie une référence vers la note demandée (accès en lecture seule)
}

size_t Song::size() const {
  return notes_.size();  // Renvoie le nombre de notes dans la chanson
}
