#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

enum Direction {
  LEFT,
  RIGHT,
  UP,
  DOWN
};

class Object {

 public:
  Object();
  ~Object();
  void move(Direction d, float ElapsedTime);
  sf::Sprite getSprite();
 protected:
  sf::Image pic;
  sf::Sprite avatar;
  int _x;
  int _y;
  int speed;
  int width;
  int height;
  bool facingRight;
};

#endif
  
