#include "PaddlePlayer.h"


PaddlePlayer::PaddlePlayer (int playerNumber)
{
	this->playerNumber = playerNumber;
	switch (this->playerNumber)
	{
	case 0:
		this->Load("myPaddle1.png");
		break;
	default:
		this->Load("myPaddle2.png");
		break;
	}
}
void PaddlePlayer::Update()
{
	switch (this->playerNumber)
	{
	case 0:
		this->velocity.y = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) * 1.8f - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) * 1.8f;
		break;
	default:
		this->velocity.y = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) * 1.8f - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) * 1.8f;
		break;
	}
	Object::Update();
	if (this->getPosition().y < 0)
	{
		this->setPosition(this->getPosition().x, 0);
	}
	if (this->getPosition().y + this->getGlobalBounds().height > 900)
	{
		this->setPosition(this->getPosition().x, 900 - this->getGlobalBounds().height);
	}
}
