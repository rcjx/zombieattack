#include <iostream>

#include "Enemy.h"

Enemy::Enemy() : Entity(80, 5) {

  if (!pic.LoadFromFile("../resources/sprites/ZombieFront.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_SUCCESS);
  }

  avatar.SetImage(pic);
  avatar.SetColor(sf::Color(0, 0, 0));
  avatar.Resize(200, 200);
  avatar.SetPosition(0, 0); 


  // Get the sprite's dimensions
  width  = avatar.GetSize().x;
  height = avatar.GetSize().y;

  speed *= 0.5;
  facingRight = true;
}

Enemy::Enemy(int x, int y) : Entity(80, 5) {

  if (!pic.LoadFromFile("../resources/sprites/JoeFront.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_SUCCESS);
  }

  pic.CreateMaskFromColor(sf::Color(255, 255, 255));
  avatar.SetImage(pic);
  //sf::IntRect Rect(100, 14, 161, 80);
  //avatar.SetSubRect(Rect);
  avatar.SetColor(sf::Color(255, 255, 255));
  // avatar.Resize(pic.GetWidth(), pic.GetHeight());
  avatar.SetPosition(x, y); 


  // Get the sprite's dimensions
  width  = avatar.GetSize().x;
  height = avatar.GetSize().y;

  speed *= 0.5;
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
  else if (avatar.GetPosition().x > target.getSprite().GetPosition().x) {
    move(LEFT, ElapsedTime, objects);
    if (facingRight) {      
      avatar.FlipX(true);
      facingRight = false;
    }
  }
  if (avatar.GetPosition().y > target.getSprite().GetPosition().y) {
    move(UP, ElapsedTime, objects);
  }
  else if (avatar.GetPosition().y < target.getSprite().GetPosition().y)
    move(DOWN, ElapsedTime, objects);

}

