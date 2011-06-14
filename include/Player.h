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
  std::vector<Bullet*> bullets;
  bool enemy(Object *subject);
  void takeDamage(std::vector<Object*> objects, int me, int damage);
  int kills;

 private:
  int inventory;
  sf::Image bullet_pic;
  sf::Sprite bullet_sprite;
  sf::SoundBuffer bite_wav;
  sf::SoundBuffer gun_wav;
  float last_shot;
  static const float SHOOT_DELAY;
};

#endif
  
