#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Bullet.h"

class Player : public Entity {

 public:
  Player();
  ~Player();
  void shoot(float ElapsedTime);
  std::vector<Bullet*> getBullets();  
  std::vector<Bullet*> bullets;

 private:
  int inventory;
  sf::Image bullet_pic;
  sf::Sprite bullet_sprite;
  float last_shot;
  static const float SHOOT_DELAY;
  //std::vector<Bullet*> bullets;  
};

#endif
  
