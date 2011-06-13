#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "Object.h"

class Entity : public Object {

 public:
  Entity(int hp, int atk);
  ~Entity();
  virtual void aggro(Object &target, float ElapsedTime, std::vector<Object*> objects) {}

 private:
  int health;
  int attack;
};

#endif
  
