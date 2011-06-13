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

	friend class SpatialHash;

	public:
		Object();
		~Object();

		virtual void aggro(Object &target, float ElapsedTime, std::vector<Object*> objects, std::vector<int> possible) {}
		void move(Direction d, float ElapsedTime, std::vector<Object*> &objects, std::vector<int> possible);
		int* collisions(std::vector<Object*> objects, std::vector<int> possible);

		sf::Sprite getSprite();
		Direction getFacing();
		void setFacing(Direction d);
		
	protected:
		sf::Image up[3];
		sf::Image down[3];
		sf::Image left[3];
		sf::Image right[3];
		sf::Sprite avatar;
		int speed;
		int frame;
		int frame_buffer;
		int ignore;

		bool facingRight;
		Direction facing;

};

#endif
  
