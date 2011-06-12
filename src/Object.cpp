#include <iostream>
#include <cstdlib>

#include "Object.h"

Object::Object() {
    
  if (!down[0].LoadFromFile("../resources/sprites/JoeDown.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!down[1].LoadFromFile("../resources/sprites/JoeDownWalk1.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!down[2].LoadFromFile("../resources/sprites/JoeDownWalk2.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!up[0].LoadFromFile("../resources/sprites/JoeUp.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!up[1].LoadFromFile("../resources/sprites/JoeUpWalk1.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!up[2].LoadFromFile("../resources/sprites/JoeUpWalk2.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!right[0].LoadFromFile("../resources/sprites/JoeRight.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!right[1].LoadFromFile("../resources/sprites/JoeRightWalk1.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!right[2].LoadFromFile("../resources/sprites/JoeRightWalk2.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!left[0].LoadFromFile("../resources/sprites/JoeLeft.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!left[1].LoadFromFile("../resources/sprites/JoeLeftWalk1.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!left[2].LoadFromFile("../resources/sprites/JoeLeftWalk2.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  down[0].CreateMaskFromColor(sf::Color(255, 255, 255));
  avatar.SetImage(down[0]);
  avatar.SetColor(sf::Color(255, 255, 255, 255));
  avatar.SetPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + std::rand()%100);

  // Resize the sprite
  // avatar.Resize(72, 70);

  // Flip the sprite on X and Y axis
  // avatar.FlipX(true);
  // Sprite.FlipY(true);
  speed = 75;
  frame = 0;
  frame_buffer = 0;
}

Object::~Object() {
	std::cout << "O destructed" << std::endl;
}

void Object::move(Direction d, float ElapsedTime,
		  std::vector<Object*> objects) {

  int _x = this->getSprite().GetPosition().x;
  int _y = this->getSprite().GetPosition().y;
  int _w  = avatar.GetSize().x;
  int _h = avatar.GetSize().y;

  
  float velocity = speed * ElapsedTime;

  frame_buffer++;
  // std::cout << frame_buffer << ", " << frame << std::endl;
  if (frame_buffer%10 == 0) {
    frame++;
    //std::cout << frame_buffer << ", " << frame << std::endl;
    frame_buffer = 0;
  }

  if (frame == 3)
    frame = 0;      

  if (d == LEFT) {
    avatar.SetImage(left[frame]);
    facing = LEFT;
    _x += -velocity;
    if (_x > 0 && !collisionDetected(objects)) {
    avatar.Move(-velocity, 0);
    }
  }
  else if (d == RIGHT) {    
    avatar.SetImage(right[frame]);
    facing = RIGHT;
    _x += velocity;
    if (_x + _w < SCREEN_WIDTH && !collisionDetected(objects)) {
    avatar.Move(velocity, 0);
    }
  }
  else if (d == UP) {
    avatar.SetImage(up[frame]);
    facing = UP;
    _y += -velocity;
    if (_y > 0 && !collisionDetected(objects)) {
    avatar.Move(0, -velocity);    
    }
  }
  else if (d == DOWN) {
    avatar.SetImage(down[frame]);
    facing = DOWN;
    _y += velocity;
    if (_y + _h < SCREEN_HEIGHT && !collisionDetected(objects)) {
    avatar.Move(0, velocity);
    }
  }  
}

sf::Sprite Object::getSprite() {
  return avatar;
}

Direction Object::getFacing() {
  return facing;
}

void Object::setFacing(Direction d) {
  facing = d;
}

bool Object::collisionDetected(std::vector<Object*> objects) {

  int left, subject_left;
  int right, subject_right;
  int top, subject_top;
  int bottom, subject_bottom;

  left = avatar.GetPosition().x;
  right = left + this->getSprite().GetSize().x;
  top = avatar.GetPosition().y;
  bottom = top + this->getSprite().GetSize().y;

  for (unsigned int i = 0; i < objects.size(); i++) {
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
