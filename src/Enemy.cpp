#include <iostream>

#include "Enemy.h"

Enemy::Enemy() : Entity(80, 5) {

  speed *= 1;
  facingRight = true;
}

Enemy::Enemy(int x, int y) : Entity(80, 5) {

  avatar.SetPosition(x, y); 
  speed *= 1;
  facingRight = true;
}

Enemy::~Enemy() {
  delete this;
}

void Enemy::aggro(Object &target, float ElapsedTime,
		  std::vector<Object*> objects) {

  if (avatar.GetPosition().x < target.getSprite().GetPosition().x) {
    move(RIGHT, ElapsedTime, objects);
    if (!facingRight) {
      avatar.FlipX(false);
      facingRight = true;
    }
  }
  if (avatar.GetPosition().x > target.getSprite().GetPosition().x) {
    move(LEFT, ElapsedTime, objects);
    if (facingRight) {      
      avatar.FlipX(true);
      facingRight = false;
    }
  }
  if (avatar.GetPosition().y > target.getSprite().GetPosition().y) {
    move(UP, ElapsedTime, objects);
  }
  if (avatar.GetPosition().y < target.getSprite().GetPosition().y)
    move(DOWN, ElapsedTime, objects);

}

