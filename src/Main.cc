#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Enemy.h"
#include "Player.h"

int main(int argc, char** argv)
{

  sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Zombie Attack");

  /* ROL */ App.SetFramerateLimit(60);

  sf::Music bgm;    
  if (!bgm.OpenFromFile("../resources/music/cry_of_the_planet.ogg")) {
    std::cout << "Error loading music" << std::endl; 
    exit(EXIT_SUCCESS);
  }
  
  bgm.Play();

  // sf::Shape Rect = sf::Shape::Rectangle(50, 50, SCREEN_WIDTH - 50,
  // 					SCREEN_HEIGHT - 50,
  // 					sf::Color(255, 255, 255, 0), 3,
  // 					sf::Color(0, 0, 0));

  Player *player = new Player; 
  //Object *thing = new Object;
  std::vector<Object*> objects;
  objects.push_back(player);
  //objects.push_back(thing);
  //objects.push_back(new Enemy(SCREEN_WIDTH - 10, SCREEN_HEIGHT - 10));
  objects.push_back(new Enemy(10, 10));
  //objects.push_back(new Enemy(SCREEN_WIDTH - 10, 10));
  // objects.push_back(new Enemy(10, SCREEN_HEIGHT - 10));
  // objects.push_back(new Enemy(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 10));
  // objects.push_back(new Enemy(100, 10));
  // objects.push_back(new Enemy(SCREEN_WIDTH - 100, 10));
  // objects.push_back(new Enemy(100, SCREEN_HEIGHT - 10));


  // Start game loop
  while (App.IsOpened()) {    
	
    // Process events
    sf::Event Event;

    // Window closed
    while (App.GetEvent(Event)) {
      if (Event.Type == sf::Event::Closed)
	App.Close();

      // Escape key pressed
      if ((Event.Type == sf::Event::KeyPressed) &&
	  (Event.Key.Code == sf::Key::Escape))	
	App.Close();

      if (Event.Key.Code == sf::Key::F1) {
	sf::Image Screen = App.Capture();
	Screen.SaveToFile("screenshot.jpg");
      }      
    }

    // Get elapsed time
    float ElapsedTime = App.GetFrameTime();

    // Move the sprite
    if (App.GetInput().IsKeyDown(sf::Key::Left))
      player->move(LEFT, ElapsedTime, objects);
    if (App.GetInput().IsKeyDown(sf::Key::Right))
      player->move(RIGHT, ElapsedTime, objects);
    if (App.GetInput().IsKeyDown(sf::Key::Up))
      player->move(UP, ElapsedTime, objects);
    if (App.GetInput().IsKeyDown(sf::Key::Down))
      player->move(DOWN, ElapsedTime, objects);

    if (App.GetInput().IsKeyDown(sf::Key::Space))
      player->shoot();

    //thing->move(LEFT, ElapsedTime, objects);   
      
    // Clear the screen (fill it w/white color)
    App.Clear(sf::Color(255, 255, 255));
    // App.Draw(Rect);
    App.Draw(player->getSprite());
    for (unsigned int i = 0; i < objects.size(); ++i)  {
      objects[i]->aggro(*player, ElapsedTime, objects);
      App.Draw(objects[i]->getSprite());
    }

	for(unsigned int i = 0; i < player->bullets.size(); ++i)
	{
		App.Draw(player->bullets[i]->getSprite());
		player->bullets[i]->move(ElapsedTime, objects);

		if(player->bullets[i]->collisionDetected(objects))
		{
		    std::cout << i << " size: " << player->bullets.size() << std::endl;
			
			delete player->bullets[i];

			//delete player->bullets[i];
			//player->bullets[i] = NULL;
			player->bullets.erase(player->bullets.begin() + i);
		}
	}

	/*
    for (unsigned int i = 0; i < player->getBullets().size(); ++i) {
      App.Draw(player->getBullets()[i]->getSprite());      
      player->getBullets()[i]->move(ElapsedTime, objects);
      if (player->getBullets()[i]->collisionDetected(objects)) {
		  std::cout << i << " size: " << player->getBullets().size() << std::endl;

	    //delete player->getBullets()[i];
		  player->getBullets().pop_back();

	//delete player->getBullets()[i];
	//player->getBullets()[i] = NULL;
	//player->getBullets().erase(player->getBullets().begin() + i);
//player->getBullets().erase(player->getBullets().begin());

      }
	 
    }
  */
    // if (player->tmp)
    //   App.Draw(player->tmp->getSprite());
    // Diplay window contents on screen   
    App.Display();

  }
  
  return 0;
}
