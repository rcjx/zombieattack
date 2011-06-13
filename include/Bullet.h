#include "Object.h"
#include <iostream>

class Bullet : public Object {

 public:
  Bullet(sf::Sprite adjusted_sprite);
  ~Bullet();
  void move(float ElapsedTime, std::vector<Object*> &objects, std::vector<Bullet*> &bullets, int me);
  bool collisionDetected(std::vector<Object*> objects);
  
 protected:
  sf::Image bullet_pic;
};
