#pragma once
#include <SFML/Graphics.hpp>

class Life : public sf::Text
{
public:
	Life(sf::Font &font, unsigned int size, int Health);
	void LoseLife();
	void Update();

	int myLife;
private:
	//int myScore;
};
