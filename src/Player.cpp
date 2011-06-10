#include <iostream>

#include "Player.h"

Player::Player() : Entity(80, 5) {

  _x = SCREEN_WIDTH/2-avatar.GetSize().x/2;
  _y = SCREEN_HEIGHT/2-avatar.GetSize().y/2;
  avatar.SetPosition(_x, _y);
		     

  // Get the sprite's dimensions
  width  = avatar.GetSize().x;
  height = avatar.GetSize().y;

  speed *= 2;
  frame_buffer = 0;
  facing = DOWN;

  if (!bullet_pic.LoadFromFile("../resources/sprites/bullet.png")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }
  bullet_sprite.SetImage(bullet_pic);

}

Player::~Player() {
  delete this;
}

void Player::shoot() {

  if (facing == DOWN) {
    bullet_sprite.Rotate(180);
    bullet_sprite.SetPosition(_x+width/2, _y+height);
    Bullet *tmp = new Bullet(bullet_sprite);
    tmp->setFacing(DOWN);
    bullets.push_back(tmp);
    bullet_sprite.Rotate(180);
  }
  else if (facing == UP) {
    bullet_sprite.SetPosition(_x + width/2, _y);
    Bullet *tmp = new Bullet(bullet_sprite);
    tmp->setFacing(UP);
    bullets.push_back(tmp);
  }
  else if (facing == LEFT) {
    bullet_sprite.Rotate(90);
    bullet_sprite.SetPosition(_x, _y + height/2);
    Bullet *tmp = new Bullet(bullet_sprite);
    tmp->setFacing(LEFT);
    bullets.push_back(tmp);
    bullet_sprite.Rotate(270);
  }
  else if (facing == RIGHT) {
    bullet_sprite.Rotate(270);
    bullet_sprite.SetPosition(_x + width, _y + height/2);
    Bullet *tmp = new Bullet(bullet_sprite);
    tmp->setFacing(RIGHT);
    bullets.push_back(tmp);
    bullet_sprite.Rotate(90);

  }
  //std::cout << bullets.size() << std::endl;
  

}
  
std::vector<Bullet*> Player::getBullets() {
  return bullets;
}
