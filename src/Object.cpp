#include <iostream>
#include <cstdlib>

#include "Object.h"

Object::Object() {
    
  if (!pic.LoadFromFile("../resources/sprites/object.png")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  avatar.SetImage(pic);
  avatar.SetColor(sf::Color(255, 255, 255, 255));
  avatar.SetPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + std::rand()%100);

  // Get the sprite's dimensions
  width  = avatar.GetSize().x;
  height = avatar.GetSize().y;

  // Resize the sprite
  // avatar.Resize(72, 70);

  // Flip the sprite on X and Y axis
  // avatar.FlipX(true);
  // Sprite.FlipY(true);
  speed = 100;
}

Object::~Object() {
  delete this;
}

void Object::move(Direction d, float ElapsedTime,
		  std::vector<Object*> objects) {

  _x = this->getSprite().GetPosition().x;
  _y = this->getSprite().GetPosition().y;
  
  float velocity = speed * ElapsedTime;

  if (d == LEFT) {
    _x += -velocity;
    if (_x > 0 and !collisionDetected(objects)) {
    avatar.Move(-velocity, 0);
    }
    else _x += velocity;
  }
  else if (d == RIGHT) {
    _x += velocity;
    if (_x + width < SCREEN_WIDTH and !collisionDetected(objects)) {
    avatar.Move(velocity, 0);
    }
    else _x += -velocity;
  }
  else if (d == UP) {
    _y += -velocity;
    if (_y > 0 and !collisionDetected(objects)) {
    avatar.Move(0, -velocity);    
    }
    else _y += velocity;
  }
  else if (d == DOWN) {
    _y += velocity;
    if (_y + height < SCREEN_HEIGHT and !collisionDetected(objects)) {
    avatar.Move(0, velocity);
    }
    else _y += -velocity;
  }  
}

sf::Sprite Object::getSprite() {
  return avatar;
}

bool Object::collisionDetected(std::vector<Object*> objects) {

  int left, subject_left;
  int right, subject_right;
  int top, subject_top;
  int bottom, subject_bottom;

  left = _x;
  right = left + this->getSprite().GetSize().x;
  top = _y;
  bottom = top + this->getSprite().GetSize().y;

  for (unsigned int i = 0; i < objects.size(); i++) {
    if (this != objects[i]) {
      subject_left = objects[i]->getSprite().GetPosition().x;
      subject_right = subject_left + objects[i]->getSprite().GetSize().x;
      subject_top = objects[i]->getSprite().GetPosition().y;
      subject_bottom = subject_top + objects[i]->getSprite().GetSize().y;

      if ((bottom <= subject_top) or (top >= subject_bottom) or (right <= subject_left) or (left >= subject_right))
	continue;
      else
	return true;
    }    
  }
  return false;

}
