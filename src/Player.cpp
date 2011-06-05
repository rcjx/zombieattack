#include <iostream>

#include "Player.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

Player::Player() : Entity(80, 5) {

  if (!pic.LoadFromFile("../resources/sprites/player.png")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_SUCCESS);
  }

  avatar.SetImage(pic);
  avatar.SetColor(sf::Color(255, 255, 255, 255));
  // avatar.Resize(pic.GetWidth(), pic.GetHeight());
  avatar.SetPosition(SCREEN_WIDTH/2-avatar.GetSize().x/2, 
		     SCREEN_HEIGHT/2);

  // Get the sprite's dimensions
  width  = avatar.GetSize().x;
  height = avatar.GetSize().y;

  speed *= 2;
}

Player::~Player() {
  delete this;
}

