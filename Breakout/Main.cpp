
#include <windows.h>
#include "StateMachine.h"
#include "MainMenu.h"

GameState CoreState;
bool quitGame = false;
//Paddle paddle;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 900), "BreakOut");

	CoreState.setWindow(&window);
	CoreState.SetState(new MainMenu());

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

