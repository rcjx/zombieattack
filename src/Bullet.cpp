#include "Bullet.h"

Bullet::Bullet(sf::Sprite adjusted_sprite) : Entity(1, 1)
{
  avatar = adjusted_sprite;
  speed *= 10;
  ignore = 1;
  type = FRIEND;
}

Bullet::~Bullet() {}

void Bullet::move(float ElapsedTime, std::vector<Object*> &objects, std::vector<int> possible, std::vector<Bullet*> &bullets, int me) 
{
	int _x = this->getSprite().GetPosition().x;
	int _y = this->getSprite().GetPosition().y;
	int _w  = avatar.GetSize().x;
	int _h = avatar.GetSize().y;

	int *available = collisions(objects, possible);

	for(unsigned int i = 0; i < 4; ++i)
	{
	    if(!available[i])
		{
			delete bullets[me];
			bullets.erase(bullets.begin() + me);
		}
	}

	float velocity = speed * ElapsedTime;

	if(facing == LEFT) 
	{
		_x += -velocity;
		if (_x > 0 && available[LEFT])
			avatar.Move(-velocity, 0);
		else 
		{
			delete bullets[me];
			bullets.erase(bullets.begin() + me);
		}
	}
	else if(facing == RIGHT) 
	{    
		_x += velocity;
		if (_x + _w < SCREEN_WIDTH && available[RIGHT])
			avatar.Move(velocity, 0);
		else 
		{
			delete bullets[me];
			bullets.erase(bullets.begin() + me);
		}
	}
	else if(facing == UP) 
	{
		_y += -velocity;
		if (_y > 0 && available[UP]) 
			avatar.Move(0, -velocity);   
		else 
		{
			delete bullets[me];
			bullets.erase(bullets.begin() + me);
		}
	}
	else if(facing == DOWN) 
	{
		_y += velocity;
		if (_y + _h < SCREEN_HEIGHT && available[DOWN])
		    avatar.Move(0, velocity);
		else 
		{
			delete bullets[me];
			bullets.erase(bullets.begin() + me);
		}
	}  
}

int* Bullet::collisions(std::vector<Object*> objects, std::vector<int> possible)
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
				{
				    objects[position]->takeDamage(objects, position, getAttack());
					return open_sides;
				}
			}	
		}
	}	
    return open_sides;
}