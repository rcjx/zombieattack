#include <iostream>

#include "Player.h"

const float Player::SHOOT_DELAY = 0.25;

Player::Player() : Entity(10000, 1) {
  
  type = FRIEND;

  int _x = SCREEN_WIDTH/2-avatar.GetSize().x/2;
  int _y = SCREEN_HEIGHT/2-avatar.GetSize().y/2;
  
  avatar.SetPosition(_x, _y);
		     
  speed *= 2;
  frame_buffer = 0;
  facing = DOWN;
  last_shot = 0.0;  

  if (!bullet_pic.LoadFromFile("../resources/sprites/bullet.png")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }
  bullet_sprite.SetImage(bullet_pic);

  if (!bite_wav.LoadFromFile("../resources/sfx/bite.wav")) {
    std::cout << "Error loading sfx" << std::endl; 
    exit(EXIT_SUCCESS);
  }

  if (!gun_wav.LoadFromFile("../resources/sfx/gun.wav")) {
    std::cout << "Error loading sfx" << std::endl; 
    exit(EXIT_SUCCESS);
  }
  kills = 0;
}

Player::~Player() {}

void Player::shoot(float running_time) {

  if ((running_time - last_shot) > SHOOT_DELAY) {

    int _x = this->getSprite().GetPosition().x;
    int _y = this->getSprite().GetPosition().y;
    int _w = avatar.GetSize().x;
    int _h = avatar.GetSize().y;
    // to ignore player
    int sprite_offset = 30;

    if (facing == DOWN) {
      bullet_sprite.Rotate(180);
      bullet_sprite.SetPosition(_x+_w/2, _y+_h + sprite_offset);
      Bullet *tmp = new Bullet(bullet_sprite);
      tmp->setFacing(DOWN);
      bullets.push_back(tmp);
      bullet_sprite.Rotate(180);
    }
    else if (facing == UP) {
      bullet_sprite.SetPosition(_x + _w/2, _y-sprite_offset);
      Bullet *tmp = new Bullet(bullet_sprite);
      tmp->setFacing(UP);
      bullets.push_back(tmp);
    }
    else if (facing == LEFT) {
      bullet_sprite.Rotate(90);
      bullet_sprite.SetPosition(_x-sprite_offset, _y + _h/2);
      Bullet *tmp = new Bullet(bullet_sprite);
      tmp->setFacing(LEFT);
      bullets.push_back(tmp);
      bullet_sprite.Rotate(270);
    }
    else if (facing == RIGHT) {
      bullet_sprite.Rotate(270);
      bullet_sprite.SetPosition(_x + _w + sprite_offset, _y + _h/2);
      Bullet *tmp = new Bullet(bullet_sprite);
      tmp->setFacing(RIGHT);
      bullets.push_back(tmp);
      bullet_sprite.Rotate(90);
    }
    sound.SetBuffer(gun_wav); 
    sound.SetVolume(50.f);
    sound.Play();
    last_shot = running_time;
  }
}


void Player::takeDamage(std::vector<Object*> objects, int me, int damage) {

  if (sound.GetStatus() != sf::Sound::Playing) {
    sound.SetBuffer(bite_wav); 
    sound.SetVolume(200.f);
    sound.Play();
  }
  health -= damage;
}

bool Player::enemy(Object *subject)
{
    return false;
}
