#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "Object.h"

class Entity : public Object {

 public:
  Entity();
  ~Entity();

  virtual void aggro(Object &target, float ElapsedTime, std::vector<Object*> objects, std::vector<int> possible) {}

protected:
  int health;
  int attack;
};

#endif
  
