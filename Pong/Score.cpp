#include "Score.h"

Score::Score(sf::Font &font, unsigned int size) : sf::Text("Score: 0", font, size)
{
	this->myScore = 0;
}

void Score::AddScore()
{
	this->myScore += 1;

}
void Score::Update()
{
	this->setString("Score: " + std::to_string(this->myScore));
}
