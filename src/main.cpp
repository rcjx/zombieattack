#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#define SCREEN_WIDTH 680
#define SCREEN_HEIGHT 480

int main(int argc, char** argv)
{
  bool Running = true;
  sf::RenderWindow App(sf::VideoMode(SCREEN_WIDTH, SCREEN_WIDTH, 32), "Zombie Attack");

  sf::Music bgm;    
  if (!bgm.OpenFromFile("../resources/music/cry_of_the_planet.ogg")) {
    std::cout << "Error loading music" << std::endl; 
    exit(EXIT_SUCCESS);
  }
  sf::Image Image;     
    
  if (!Image.LoadFromFile("../resources/sprites/player.png")) {
    std::cout << "Error loading image" << std::endl;
    exit(EXIT_SUCCESS);
  }
  
  Image.CreateMaskFromColor (sf::Color(255, 255, 255), 0);
    
  sf::Sprite Sprite;

  Sprite.SetImage(Image);
  Sprite.SetColor(sf::Color(255, 255, 255, 255));
  Sprite.SetPosition(SCREEN_WIDTH/2-Sprite.GetSize().x/2,
		     SCREEN_HEIGHT/2);

  // Get the sprite's dimensions
  float Width  = Sprite.GetSize().x;
  float Height = Sprite.GetSize().y;

  // Resize the sprite
  // Sprite.Resize(60, 100);

  // Flip the sprite on X and Y axis
  // Sprite.FlipX(true);
  // Sprite.FlipY(true);

  // Get the color of a given pixel inside the sprite
  sf::Color Pixel = Sprite.GetPixel(10, 5);

  bgm.Play();

  sf::Shape Rect = sf::Shape::Rectangle(50, 50, SCREEN_WIDTH - 50,
					SCREEN_WIDTH - 50,
					sf::Color(255, 255, 255, 0), 3, sf::Color(0, 0, 255));
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
      Sprite.Move(-100 * ElapsedTime, 0);
    if (App.GetInput().IsKeyDown(sf::Key::Right))
      Sprite.Move( 100 * ElapsedTime, 0);
    if (App.GetInput().IsKeyDown(sf::Key::Up))
      Sprite.Move(0, -100 * ElapsedTime);
    if (App.GetInput().IsKeyDown(sf::Key::Down))
      Sprite.Move(0,  100 * ElapsedTime);

    // Rotate the sprite
    if (App.GetInput().IsKeyDown(sf::Key::Add))
      Sprite.Rotate(-100 * ElapsedTime);
    if (App.GetInput().IsKeyDown(sf::Key::Subtract))
      Sprite.Rotate( 100 * ElapsedTime);
    
    // Clear the screen (fill it w/red color)
    App.Clear(sf::Color(255, 255, 255));
    App.Draw(Rect);
    App.Draw(Sprite);
    // Diplay window contents on screen
    App.Display();
  }
  
  return 0;
}
