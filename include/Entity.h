#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "Object.h"

class Entity : public Object {

 public:
  Entity(int hp, int atk);
  ~Entity();
  virtual void aggro(Object &target, float ElapsedTime,
		     std::vector<Object*> objects)
		     {  }
  void takeDamage(int dmg, std::vector<Object*> &objects, int me);
  
 protected:
  int health;
  int attack;
};

#endif
  
