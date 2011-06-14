#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <time.h>

#include "Enemy.h"
#include "Player.h"
#include "SpatialHash.h"

int main(int argc, char** argv) 
{
  sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Zombie Attack");

  App.SetFramerateLimit(60);

  sf::Music bgm;    
  if (!bgm.OpenFromFile("../resources/music/cry_of_the_planet.ogg")) 
    {
      std::cout << "Error loading music" << std::endl; 
      exit(EXIT_SUCCESS);
    }

  bgm.Play();

  std::vector<Object*> objects;

  Player *player = new Player; 
  objects.push_back(player);

  objects.push_back(new Enemy(10, 10));

  objects.push_back(new Enemy(SCREEN_WIDTH - 10, 10));
  objects.push_back(new Enemy(10, SCREEN_HEIGHT - 100));
  objects.push_back(new Enemy(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100));
  objects.push_back(new Enemy(100, 100));
  objects.push_back(new Enemy(SCREEN_WIDTH - 100, 100));
  objects.push_back(new Enemy(100, SCREEN_HEIGHT - 100));


  SpatialHash grid;

  sf::Font MyFont;
  //if (!MyFont.LoadFromFile("../resources/fonts/comics.ttf", 50)) {
  //  std::cout << "Fail" << std::endl;
  //  return EXIT_FAILURE;
  //}

  //sf::String Hello;
  
  /*
  Hello.SetFont(MyFont);
  Hello.SetColor(sf::Color(255, 0, 0));
  Hello.SetSize(75.f);
  Hello.SetPosition(SCREEN_WIDTH/2 - Hello.GetSize()/2, 10.f);
  //Hello.SetRotation(15.f);
  */
    
  float running_time = 0.0;
  float last_time = 0.0;

  std::srand(std::time(NULL));

  //Start game loop
  while (App.IsOpened()) {

    if (running_time - last_time > 2.0) {
      objects.push_back(new Enemy(rand() % SCREEN_WIDTH - 10,
				  rand() % SCREEN_HEIGHT - 10));
      last_time = running_time;
    }

      grid.setup(objects);

      //Process events
      sf::Event Event;

      //Window closed
      while (App.GetEvent(Event)) 
	{
	  if(Event.Type == sf::Event::Closed)
	    App.Close();

	  //Escape key pressed
	  if((Event.Type == sf::Event::KeyPressed) &&
	     (Event.Key.Code == sf::Key::Escape))	
	    App.Close();

	  if(Event.Key.Code == sf::Key::F1) 
	    {
	      sf::Image Screen = App.Capture();
	      Screen.SaveToFile("screenshot.jpg");
	    }      
	}

      //Get elapsed time
      float ElapsedTime = App.GetFrameTime();
      running_time += ElapsedTime;

      if(App.GetInput().IsKeyDown(sf::Key::Space))
	player->shoot(running_time);

      //Move the sprite
      if(App.GetInput().IsKeyDown(sf::Key::Left))
	player->move(LEFT, ElapsedTime, objects, grid.getNearby(player));
      if(App.GetInput().IsKeyDown(sf::Key::Right))
	player->move(RIGHT, ElapsedTime, objects, grid.getNearby(player));
      if(App.GetInput().IsKeyDown(sf::Key::Up))
	player->move(UP, ElapsedTime, objects, grid.getNearby(player));
      if(App.GetInput().IsKeyDown(sf::Key::Down))
	player->move(DOWN, ElapsedTime, objects, grid.getNearby(player));

      //Clear the screen (fill it w/white color)
      App.Clear(sf::Color(255, 255, 255));

      std::stringstream s;
      s << (int)running_time;
      std::string time_string;
      s >> time_string;
      
//      Hello.SetText(time_string);
  //    App.Draw(Hello);
      App.Draw(player->getSprite());

      for (unsigned int i = 0; i < objects.size(); ++i) {

	  objects[i]->aggro(*player, ElapsedTime, objects, grid.getNearby(objects[i]), running_time);
	  App.Draw(objects[i]->getSprite());
	}

      for(unsigned int i = 0; i < player->bullets.size(); ++i) {
	  App.Draw(player->bullets[i]->getSprite());
	  player->bullets[i]->move(ElapsedTime, objects, grid.getNearby(player->bullets[i]), player->bullets, i);
	}

      for(unsigned int i = 0; i < objects.size(); ++i)
	objects[i]->alive(objects, i, running_time);

      grid.clear();

      //Diplay window contents on screen
      App.Display();
    }

  return 0;
}
