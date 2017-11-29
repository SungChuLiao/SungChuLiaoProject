#pragma once

#include "StateMachine.h"
#include <SFML/Audio.hpp>

class MainMenu : public MatchState
{
public:
	void Initiallize(sf::RenderWindow *window);
	void Update(sf::RenderWindow *window);
	void Render(sf::RenderWindow *window);
	void Destory(sf::RenderWindow *window);

private:
	sf::Font *font;
	sf::Text *title;
	sf::Text *Play;
	sf::Text *quit;

	sf::SoundBuffer* bf;
	sf::Sound* sound;

	int selected;

	bool upKey;
	bool downKey;
};
