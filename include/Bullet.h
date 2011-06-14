#include "Entity.h"
#include <iostream>

class Bullet : public Entity {

 public:
  Bullet(sf::Sprite adjusted_sprite);
  ~Bullet();

  void move(float ElapsedTime, std::vector<Object*> &objects, std::vector<int> possible, std::vector<Bullet*> &bullets, int me);
  int* collisions(std::vector<Object*> objects, std::vector<int> possible);
  
 protected:
  sf::Image bullet_pic;
};
