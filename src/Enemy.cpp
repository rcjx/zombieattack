#include <iostream>

#include "Enemy.h"

const float Enemy::SFX_DELAY = 10.0;
const float Enemy::DEATH_DELAY = 0.6;

Enemy::Enemy(int x, int y, int level) : Entity(level, level)
{
  if (!down[0].LoadFromFile("../resources/sprites/MFront1.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!down[1].LoadFromFile("../resources/sprites/MFront2.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!down[2].LoadFromFile("../resources/sprites/MFront3.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!up[0].LoadFromFile("../resources/sprites/MBack1.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!up[1].LoadFromFile("../resources/sprites/MBack2.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!up[2].LoadFromFile("../resources/sprites/MBack3.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!right[0].LoadFromFile("../resources/sprites/MRight1.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!right[1].LoadFromFile("../resources/sprites/MRight2.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!right[2].LoadFromFile("../resources/sprites/MRight3.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!left[0].LoadFromFile("../resources/sprites/MLeft1.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!left[1].LoadFromFile("../resources/sprites/MLeft2.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!left[2].LoadFromFile("../resources/sprites/MLeft3.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  for(unsigned int i = 0; i < 3; ++i)
    down[i].CreateMaskFromColor(sf::Color(255, 255, 255));
  for(unsigned int i = 0; i < 3; ++i)
    up[i].CreateMaskFromColor(sf::Color(255, 255, 255));
  for(unsigned int i = 0; i < 3; ++i)
    left[i].CreateMaskFromColor(sf::Color(255, 255, 255));
  for(unsigned int i = 0; i < 3; ++i)
    right[i].CreateMaskFromColor(sf::Color(255, 255, 255));


  avatar.SetImage(down[0]);
  avatar.SetPosition(x, y); 
  speed *= 1;
  facingRight = true;
  type = FOE;

  if (!zombie_wav.LoadFromFile("../resources/sfx/zombie.wav")) {
    std::cout << "Error loading sfx" << std::endl; 
    exit(EXIT_SUCCESS);
  }

  if (!zombie_attacked_wav.LoadFromFile("../resources/sfx/zombie_attacked.wav")) {
    std::cout << "Error loading sfx" << std::endl; 
    exit(EXIT_SUCCESS);
  }

  last_time = 0.0;
  death_time = 0.0;
}

Enemy::~Enemy() {}

void Enemy::aggro(Object &target, float ElapsedTime, std::vector<Object*> objects, std::vector<int> possible, float running_time) {

  if ((running_time - last_time) > SFX_DELAY) {
    sound.SetBuffer(zombie_wav); 
    sound.SetPitch(1.5f);
    sound.SetVolume(10.f);
    sound.Play();
    last_time = running_time;
  }
    
  if (avatar.GetPosition().x < target.getSprite().GetPosition().x) {
    move(RIGHT, ElapsedTime, objects, possible);
    if (!facingRight) {
      avatar.FlipX(false);
      facingRight = true;
    }
  }
  if (avatar.GetPosition().x > target.getSprite().GetPosition().x) {
    move(LEFT, ElapsedTime, objects, possible);
    if (facingRight) {      
      avatar.FlipX(true);
      facingRight = false;
    }
  }
  if (avatar.GetPosition().y > target.getSprite().GetPosition().y) {
    move(UP, ElapsedTime, objects, possible);
  }
  if (avatar.GetPosition().y < target.getSprite().GetPosition().y)
    move(DOWN, ElapsedTime, objects, possible);

}

void Enemy::takeDamage(std::vector<Object*> objects, int me, int damage) {

  sound.SetBuffer(zombie_attacked_wav); 
  sound.SetPitch(1.5f);
  sound.SetVolume(75.f);
  sound.Play();
  std::cout << health << " " << damage << std::endl;
  health -= damage;
}

bool Enemy::alive(std::vector<Object*> &objects, int me, float running_time)
{

  if(health <= 0) {
    if (running_time - death_time > DEATH_DELAY && death_time != 0.0) {
      delete objects[me];
      objects.erase(objects.begin() + me);
      return false;
    }
    else if (death_time == 0.0) {
      sound.SetBuffer(zombie_attacked_wav); 
      sound.SetPitch(1.5f);
      sound.SetVolume(75.f);
      sound.Play();
      death_time = running_time;
    }
    else
      speed /= 2.;
  }
  return true;
}



