#include "Bullet.h"

Bullet::Bullet(sf::Sprite adjusted_sprite) {
  avatar = adjusted_sprite;
  speed *= 10;
}

Bullet::~Bullet() {
  std::cout << "destructed" << std::endl;
}

void Bullet::move(float ElapsedTime, std::vector<Object*> objects) {

  _x = this->getSprite().GetPosition().x;
  _y = this->getSprite().GetPosition().y;
  
  float velocity = speed * ElapsedTime;

  if (facing == LEFT) {
    _x += -velocity;
    if (_x > 0 && !collisionDetected(objects)) {
      avatar.Move(-velocity, 0);
    }
    else _x += velocity;
  }
  else if (facing == RIGHT) {    
    _x += velocity;
    if (_x + width < SCREEN_WIDTH && !collisionDetected(objects)) {
      avatar.Move(velocity, 0);
    }
    else _x += -velocity;
  }
  else if (facing == UP) {
    _y += -velocity;
    if (_y > 0 && !collisionDetected(objects)) {
      avatar.Move(0, -velocity);    
    }
    else _y += velocity;
  }
  else if (facing == DOWN) {
    _y += velocity;
    if (_y + height < SCREEN_HEIGHT && !collisionDetected(objects)) {
      avatar.Move(0, velocity);
    }
    else _y += -velocity;
  }
}
