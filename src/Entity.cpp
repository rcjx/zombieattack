#include <iostream>
#include <cstdlib>

#include "Entity.h"

Entity::Entity()
{}

Entity::~Entity()
{}

Entity::Entity(int x, int y, int level) : Object(x, y, level)
{}

Entity::Entity(Entity &other)
{
	frame = other.frame;
	frame_buffer = other.frame_buffer;
	ignore = other.ignore;
	type = other.type;
	facingRight = other.facingRight;
	facing = other.facing;
	health = other.health;
	attack = other.attack;
}