#include <iostream>
#include <cstdlib>

#include "Object.h"

Object::Object() {
    

  if (!down[0].LoadFromFile("../resources/sprites/JoeDown.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!down[1].LoadFromFile("../resources/sprites/JoeDownWalk1.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!down[2].LoadFromFile("../resources/sprites/JoeDownWalk2.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!up[0].LoadFromFile("../resources/sprites/JoeUp.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!up[1].LoadFromFile("../resources/sprites/JoeUpWalk1.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!up[2].LoadFromFile("../resources/sprites/JoeUpWalk2.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!right[0].LoadFromFile("../resources/sprites/JoeRight.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!right[1].LoadFromFile("../resources/sprites/JoeRightWalk1.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!right[2].LoadFromFile("../resources/sprites/JoeRightWalk2.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!left[0].LoadFromFile("../resources/sprites/JoeLeft.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!left[1].LoadFromFile("../resources/sprites/JoeLeftWalk1.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (!left[2].LoadFromFile("../resources/sprites/JoeLeftWalk2.jpg")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_FAILURE);
  }

    for(unsigned int i = 0; i < 3; ++i)
	    down[i].CreateMaskFromColor(sf::Color(255, 255, 255));
    for(unsigned int i = 0; i < 3; ++i)
	    up[i].CreateMaskFromColor(sf::Color(255, 255, 255));
    for(unsigned int i = 0; i < 3; ++i)
	    left[i].CreateMaskFromColor(sf::Color(255, 255, 255));
    for(unsigned int i = 0; i < 3; ++i)
	    right[i].CreateMaskFromColor(sf::Color(255, 255, 255));
	
  avatar.SetImage(down[0]);
  avatar.SetColor(sf::Color(255, 255, 255, 255));
  avatar.SetPosition(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + std::rand()%100);

  // Resize the sprite
  // avatar.Resize(72, 70);

  // Flip the sprite on X and Y axis
  // avatar.FlipX(true);
  // Sprite.FlipY(true);
  speed = 75;
  frame = 0;
  frame_buffer = 0;
  ignore = 0;
}

Object::~Object() {}

Object::Object(int x, int y, int level)
{
    health = rand() % 5 + level;
}

Object::Object(Object &other)
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

void Object::move(Direction d, float ElapsedTime, std::vector<Object*> &objects, std::vector<int> possible) 
{
	int _x = this->getSprite().GetPosition().x;
	int _y = this->getSprite().GetPosition().y;
	int _w  = avatar.GetSize().x;
	int _h = avatar.GetSize().y;

	int *available = collisions(objects, possible);

	float velocity = speed * ElapsedTime;

	frame_buffer++;
	if(frame_buffer%10 == 0) 
	{
		frame++;
		frame_buffer = 0;
	}

	if(frame == 3)
	    frame = 0;      

	if(d == LEFT) 
	{
		avatar.SetImage(left[frame]);
		facing = LEFT;
		_x += -velocity;
		if (_x > 0 && available[LEFT])
			avatar.Move(-velocity, 0);
	}
	else if(d == RIGHT) 
	{    
		avatar.SetImage(right[frame]);
		facing = RIGHT;
		_x += velocity;
		if (_x + _w < SCREEN_WIDTH && available[RIGHT])
			avatar.Move(velocity, 0);
	}
	else if(d == UP) 
	{
		avatar.SetImage(up[frame]);
		facing = UP;
		_y += -velocity;
		if (_y > 0 && available[UP]) 
			avatar.Move(0, -velocity);    
	}
	else if(d == DOWN) 
	{
		avatar.SetImage(down[frame]);
		facing = DOWN;
		_y += velocity;
		if (_y + _h < SCREEN_HEIGHT && available[DOWN])
		    avatar.Move(0, velocity);
	}  
}

sf::Sprite Object::getSprite() {
  return avatar;
}

Direction Object::getFacing() {
  return facing;
}

void Object::setFacing(Direction d) {
  facing = d;
}

int* Object::collisions(std::vector<Object*> &objects, std::vector<int> possible)
{
	int *open_sides = new int[4], position;
	for(unsigned int i = 0; i < 4; ++i)
		open_sides[i] = 1; //Declares all sides with no collision

	float _x = avatar.GetPosition().x + (avatar.GetSize().x / 2);
	float _y = avatar.GetPosition().y + (avatar.GetSize().y / 2);

	//if(possible.size() > 0 && possible[0] < ignore)
	//	possible.erase(possible.begin());

	//std::cout << possible.size() << std::endl;
	for(unsigned int i = 0; i < possible.size(); ++i)
	{
		position = possible[i];
		if(this != objects[position])
		{
			float other_x = objects[position]->getSprite().GetPosition().x + (objects[position]->getSprite().GetSize().x / 2);
			float other_y = objects[position]->getSprite().GetPosition().y + (objects[position]->getSprite().GetSize().y / 2);

			float y = abs(_y - other_y);
			y -= (objects[position]->getSprite().GetSize().y / 2) + (avatar.GetSize().y / 2);
			float x = abs(_x - other_x);
			x -= (objects[position]->getSprite().GetSize().x / 2) + (avatar.GetSize().x / 2);

			if(y < 0 && x < 0)
			{
			    if(y >= x)
				    (_y > other_y ? open_sides[UP] = 0 : open_sides[DOWN] = 0);  
				if(x >= y)
					(_x > other_x ? open_sides[LEFT] = 0 : open_sides[RIGHT] = 0);
				if(enemy(objects[position]))
					sendDamage(objects, i);
			}	
		}
	}	
    return open_sides;
}

Type Object::getType()
{
    return type;
}

bool Object::enemy(Object *subject)
{
    if(type != subject->getType())
		return true;
	return false;
}

void Object::sendDamage(std::vector<Object*> &objects, int position)
{
	objects[position]->setDamage(attack);
}

void Object::setDamage(int damage)
{
	std::cout << health << std::endl;
    health -= damage;
}