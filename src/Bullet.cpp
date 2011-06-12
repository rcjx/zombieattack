#include "Bullet.h"

Bullet::Bullet(sf::Sprite adjusted_sprite) {
  avatar = adjusted_sprite;
  speed *= 10;
}

Bullet::~Bullet() {}

void Bullet::move(float ElapsedTime, std::vector<Object*> objects) {

  int _x = this->getSprite().GetPosition().x;
  int _y = this->getSprite().GetPosition().y;
  int _w = avatar.GetSize().x;
  int _h = avatar.GetSize().y;
    
  
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
    if (_x + _w < SCREEN_WIDTH && !collisionDetected(objects)) {
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
    if (_y + _h < SCREEN_HEIGHT && !collisionDetected(objects)) {
      avatar.Move(0, velocity);
    }
    else _y += -velocity;
  }
}


bool Bullet::collisionDetected(std::vector<Object*> objects) {

  int _x = this->getSprite().GetPosition().x;
  int _y = this->getSprite().GetPosition().y;
  int _w = avatar.GetSize().x;
  int _h = avatar.GetSize().y;
  
  int left, subject_left;
  int right, subject_right;
  int top, subject_top;
  int bottom, subject_bottom;

  left = _x;
  right = left + _w;
  top = _y;
  bottom = top + _h;

  for (unsigned int i = 1; i < objects.size(); i++) {
    if (this != objects[i]) {
      subject_left = objects[i]->getSprite().GetPosition().x;
      subject_right = subject_left + objects[i]->getSprite().GetSize().x;
      subject_top = objects[i]->getSprite().GetPosition().y;
      subject_bottom = subject_top + objects[i]->getSprite().GetSize().y;

      if ((bottom < subject_top) || (top >= subject_bottom) || (right < subject_left) || (left >= subject_right))
	continue;
      else
	return true;
    }    
  } 
  return false;

}
