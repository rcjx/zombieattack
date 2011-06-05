#include <iostream>
#include <cstdlib>

#include "Entity.h"

Entity::Entity(int hp, int atk) : Object() {

  health = hp;
  attack = atk;
  
}

Entity::~Entity() {
  delete this;
}
