//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Main.hpp>

//Create bu SungChuLiao

#include <windows.h>
#include "Game.h"
#include "MainMenu.h"


GameState CoreState;
bool quitGame = false;
//Paddle paddle;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 900), "Pong");

	CoreState.setWindow(&window);
	CoreState.SetState(new MainMenu());

	//////////Just for testing
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	///////

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);

		CoreState.Update();
		CoreState.Render();
		window.display();

		if (quitGame)
		{
			window.close();
		}

		Sleep(1);
	}

	return 0;
}
