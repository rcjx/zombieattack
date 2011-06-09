#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Player : public Entity {

 public:
  Player();
  ~Player();
 private:
  int inventory;
};

#endif
  
