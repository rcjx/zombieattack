#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Bullet.h"

class Player : public Entity {

 public:
  Player();
  ~Player();
  void shoot();

  std::vector<Bullet*> getBullets();
  
  std::vector<Bullet*> bullets;

 private:
  int inventory;
  sf::Image bullet_pic;
  sf::Sprite bullet_sprite;
  //std::vector<Bullet*> bullets;  
};

#endif
  
