#include "Object.h"
#include <iostream>

class Bullet : public Object {

 public:
  Bullet(sf::Sprite adjusted_sprite);
  ~Bullet();
  Bullet(Bullet &other);

  void move(float ElapsedTime, std::vector<Object*> &objects, std::vector<int> possible, std::vector<Bullet*> &bullets, int me);
  
 protected:
  sf::Image bullet_pic;
};
