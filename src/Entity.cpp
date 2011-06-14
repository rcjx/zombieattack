#include <iostream>
#include <cstdlib>

#include "Entity.h"

Entity::Entity(int hp, int atk) : Object()
{
    health = hp;
    attack = atk;
}

Entity::~Entity()
{}

bool Entity::enemy(Object *subject)
{
    if(type != subject->getType())
		return true;
	return false;
}

void Entity::takeDamage(std::vector<Object*> objects, int me, int damage) {
  
  //std::cout << health << " " << damage << std::endl;
  health -= damage;
}

int Entity::getAttack()
{
	return attack;
}

int Entity::getHealth()
{
	return health;
}

bool Entity::alive(std::vector<Object*> &objects, int me)
{
    if(health <= 0)
	{
	    delete objects[me];
		objects.erase(objects.begin() + me);
	}
	return true;
}
