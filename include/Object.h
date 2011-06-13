#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Screen.h"

enum Direction 
{
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
		Object(int x, int y, int level);
		~Object();
		Object(Object &other);

		virtual void aggro(Object &target, float ElapsedTime, std::vector<Object*> &objects, std::vector<int> possible) {}
		void move(Direction d, float ElapsedTime, std::vector<Object*> &objects, std::vector<int> possible);
		int* collisions(std::vector<Object*> &objects, std::vector<int> possible);

		void sendDamage(std::vector<Object*> &objects, int position);
		void setDamage(int damage);

		Type getType();
		sf::Sprite getSprite();
		Direction getFacing();
		void setFacing(Direction d);
		virtual bool enemy(Object *subject); 
		
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
		Type type;

		bool facingRight;
		Direction facing;

		int health;
		int attack;
};

#endif
  
