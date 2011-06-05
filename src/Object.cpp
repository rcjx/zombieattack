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
  avatar.SetPosition(640, 
		     480/2 + std::rand()%100);

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

void Object::move(Direction d, float ElapsedTime) {

  if (d == LEFT)
    avatar.Move(-speed * ElapsedTime, 0);
  else if (d == RIGHT)
    avatar.Move(speed * ElapsedTime, 0);
  else if (d == UP)
    avatar.Move(0, -speed * ElapsedTime);
  else if (d == DOWN)
    avatar.Move(0, speed * ElapsedTime);

}

sf::Sprite Object::getSprite() {
  return avatar;
}
