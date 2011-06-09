#include <iostream>

#include "Player.h"

Player::Player() : Entity(80, 5) {

  if (!pic.LoadFromFile("../resources/sprites/JoeFront.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_SUCCESS);
  }

  pic.CreateMaskFromColor(sf::Color(255, 255, 255));
  avatar.SetImage(pic);
  //sf::IntRect Rect(126, 0, 142, 35);
  //avatar.SetSubRect(Rect);
  avatar.SetColor(sf::Color(255, 255, 255));
  //avatar.Resize(40, 80);
  avatar.SetPosition(SCREEN_WIDTH/2-avatar.GetSize().x/2, 
		     SCREEN_HEIGHT/2-avatar.GetSize().y/2);

  // Get the sprite's dimensions
  width  = avatar.GetSize().x;
  height = avatar.GetSize().y;

  speed *= 2;
}

Player::~Player() {
  delete this;
}

