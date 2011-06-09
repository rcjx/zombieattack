#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Screen.h"

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
  void move(Direction d, float ElapsedTime, std::vector<Object*> objects);
  sf::Sprite getSprite();
  virtual void aggro(Object &target, float ElapsedTime, std::vector<Object*> objects)
		     { 	std::cout << "object" << std::endl; }
 
  protected:
  sf::Image pic;
  sf::Sprite avatar;
  int _x;
  int _y;
  int speed;
  int width;
  int height;
  bool facingRight;
		     bool collisionDetected(std::vector<Object*> objects);
};

#endif
  
