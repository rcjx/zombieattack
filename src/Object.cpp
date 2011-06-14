#include <iostream>
#include <cstdlib>

#include "Object.h"

Object::Object() {
    
  if (!down[0].LoadFromFile("../resources/sprites/PFront1.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!down[1].LoadFromFile("../resources/sprites/PFront2.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!down[2].LoadFromFile("../resources/sprites/PFront3.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!up[0].LoadFromFile("../resources/sprites/PBack1.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!up[1].LoadFromFile("../resources/sprites/PBack2.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!up[2].LoadFromFile("../resources/sprites/PBack3.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!right[0].LoadFromFile("../resources/sprites/PRight1.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!right[1].LoadFromFile("../resources/sprites/PRight2.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!right[2].LoadFromFile("../resources/sprites/PRight3.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!left[0].LoadFromFile("../resources/sprites/PLeft1.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!left[1].LoadFromFile("../resources/sprites/PLeft2.png")) {
    std::cout << "Error loading image" << std::endl;
  }

  if (!left[2].LoadFromFile("../resources/sprites/PLeft3.png")) {
    std::cout << "Error loading image" << std::endl;
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
      if (_x > 50 && available[LEFT])
	avatar.Move(-velocity, 0);
    }
  else if(d == RIGHT) 
    {    
      avatar.SetImage(right[frame]);
      facing = RIGHT;
      _x += velocity;
      if (_x + _w < GAME_WIDTH && available[RIGHT])
	avatar.Move(velocity, 0);
    }
  else if(d == UP) 
    {
      avatar.SetImage(up[frame]);
      facing = UP;
      _y += -velocity;
      if (_y > 50 && available[UP]) 
	avatar.Move(0, -velocity);    
    }
  else if(d == DOWN) 
    {
      avatar.SetImage(down[frame]);
      facing = DOWN;
      _y += velocity;
      if (_y + _h < GAME_HEIGHT && available[DOWN])
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

int* Object::collisions(std::vector<Object*> objects, std::vector<int> possible)
{
  int *open_sides = new int[4], position;
  for(unsigned int i = 0; i < 4; ++i)
    open_sides[i] = 1; //Declares all sides with no collision

  float _x = avatar.GetPosition().x + (avatar.GetSize().x / 2);
  float _y = avatar.GetPosition().y + (avatar.GetSize().y / 2);

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
		objects[position]->takeDamage(objects, position, getAttack());
				
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
  return false;
}

int Object::getAttack()
{
  return 0;
}

int Object::getHealth()
{
  return 0;
}

bool Object::alive(std::vector<Object*> &objects, int me, float death_time)
{
  return true;
}
