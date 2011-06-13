#include <iostream>
#include <cstdlib>

#include "Entity.h"

Entity::Entity(int hp, int atk) : Object() {

  health = hp;
  attack = atk;
  
}

Entity::~Entity() {
}

void Entity::takeDamage(int dmg, std::vector<Object*> &objects, int me) {
  health -= dmg;
  if (health <= 0) {
    //std::cout << objects.size() << std::endl;
    delete objects[me];
    //objects.erase(objects.begin() + me);
    std::cout << objects.size() << std::endl;
  }
}
