#include "Bullet.h"

Bullet::Bullet(sf::Sprite adjusted_sprite) {
  avatar = adjusted_sprite;
  speed *= 10;
  ignore = 1;
}

Bullet::~Bullet() {}

void Bullet::move(float ElapsedTime, std::vector<Object*> &objects, std::vector<int> possible, std::vector<Bullet*> &bullets, int me) 
{
	int _x = this->getSprite().GetPosition().x;
	int _y = this->getSprite().GetPosition().y;
	int _w  = avatar.GetSize().x;
	int _h = avatar.GetSize().y;

	int *available = collisions(objects, possible);

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