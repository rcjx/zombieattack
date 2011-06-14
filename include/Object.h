#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Screen.h"

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum Type
{
    FRIEND,
	FOE
};

class Object {

  friend class SpatialHash;

 public:
  Object();
  ~Object();

  virtual void aggro(Object &target, float ElapsedTime, std::vector<Object*> objects, std::vector<int> possible, float running_time) {}
  virtual void takeDamage(std::vector<Object*> objects, int me, int damage) {}
  virtual bool alive(std::vector<Object*> &objects, int me, float running_time);
  virtual bool enemy(Object *subject);
  virtual int getAttack();
  virtual int getHealth();
		
		void move(Direction d, float ElapsedTime, std::vector<Object*> &objects, std::vector<int> possible);
		int* collisions(std::vector<Object*> objects, std::vector<int> possible);

		Type getType();
		sf::Sprite getSprite();
		Direction getFacing();
		void setFacing(Direction d);
		
	protected:
		sf::Image up[3];
		sf::Image down[3];
		sf::Image left[3];
		sf::Image right[3];
		sf::Sprite avatar;
		float speed;
		int frame;
		int frame_buffer;
		int ignore;

		Type type;

		bool facingRight;
		Direction facing;
		sf::Sound sound;
};

#endif
  
