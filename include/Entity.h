#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "Object.h"

class Entity : public Object {

 public:
  Entity(int hp, int atk);
  ~Entity();
 private:
  int health;
  int attack;
};

#endif
  
