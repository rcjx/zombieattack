#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Player.h"

class Enemy : public Entity {

 public:
  Enemy();
  Enemy(int x, int y);
  ~Enemy();
  void aggro(Object &target, float ElapsedTime);
 private:
  int inventory;
};

#endif
  
