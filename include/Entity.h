#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include "Object.h"

class Entity : public Object {

 public:
  Entity(int hp = 0, int atk = 0);
  ~Entity();

  virtual void aggro(Object &target, float ElapsedTime, std::vector<Object*> objects, std::vector<int> possible) {}
  virtual bool enemy(Object *subject);
	
    bool alive(std::vector<Object*> &objects, int me);
    void takeDamage(std::vector<Object*> objects, int me, int damage);
    int getAttack();
    int getHealth();

protected:
    int health;
    int attack;
};

#endif
  
