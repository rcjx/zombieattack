#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

#include "Entity.h"

class Enemy : public Entity {

 public:
  Enemy(int x = 0, int y = 0, int level = 1);
  ~Enemy();  

  void aggro(Object &target, float ElapsedTime, std::vector<Object*> objects, std::vector<int> possible);

 private:
  int inventory;
};

#endif
  
