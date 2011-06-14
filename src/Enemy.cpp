#include <iostream>

#include "Enemy.h"

Enemy::Enemy(int x, int y, int level) : Entity(level, level)
{
  avatar.SetPosition(x, y); 
  speed *= 1;
  facingRight = true;
  type = FOE;
}

Enemy::~Enemy() {}

void Enemy::aggro(Object &target, float ElapsedTime, std::vector<Object*> objects, std::vector<int> possible) {

  if (avatar.GetPosition().x < target.getSprite().GetPosition().x) {
    move(RIGHT, ElapsedTime, objects, possible);
    if (!facingRight) {
      avatar.FlipX(false);
      facingRight = true;
    }
  }
  if (avatar.GetPosition().x > target.getSprite().GetPosition().x) {
    move(LEFT, ElapsedTime, objects, possible);
    if (facingRight) {      
      avatar.FlipX(true);
      facingRight = false;
    }
  }
  if (avatar.GetPosition().y > target.getSprite().GetPosition().y) {
    move(UP, ElapsedTime, objects, possible);
  }
  if (avatar.GetPosition().y < target.getSprite().GetPosition().y)
    move(DOWN, ElapsedTime, objects, possible);

}

