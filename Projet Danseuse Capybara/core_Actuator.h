#ifndef ACTUATOR_H
#define ACTUATOR_H

// Classe de base abstraite pour tous les actuateurs (actionneurs).
// Utilisation de l'héritage : les classes concrètes (BuzzerActuator, ServoActuator, LedActuator, etc.)
// hériteront de Actuator. Cette classe définit une interface commune avec :
// - `begin()` comme méthode d'initialisation pure virtuelle que chaque actuateur implémentera.
// Le destructeur virtuel par défaut (~Actuator) assure une destruction correcte des objets dérivés.

class Actuator {
public:
  virtual ~Actuator() = default;  // Destructeur virtuel (important pour une classe de base polymorphique)
  virtual void begin() = 0;       // Méthode virtuelle pure : chaque classe dérivée doit définir son propre begin()
};

#endif
