#include "Life.h"

Life::Life(sf::Font &font, unsigned int size, int health) : sf::Text("Life: ", font, size)
{
	this->myLife = health;
}

void Life::LoseLife()
{
	this->myLife -= 1;
}
void Life::Update()
{
	this->setString("Life: " + std::to_string(this->myLife));
}
