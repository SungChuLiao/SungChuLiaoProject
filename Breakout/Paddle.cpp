#include "Paddle.h"

Paddle::Paddle(float newSpeed)
{
	this->ExSpeed = newSpeed;
	this->Load("Paddle.png");
}
void Paddle::Update()
{
	this->velocity.x = (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) * 1.8f - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) * 1.8f) * ExSpeed;
	/*if (event.type == sf::Event::MouseMoved)
	{
		this->setPosition(event.mouseMove.x, this->getPosition().y);
	}*/
	Object::Update();
	if (this->getPosition().x < 0)
	{
		this->setPosition(0, this->getPosition().y);
	}
	if (this->getPosition().x + this->getGlobalBounds().width > 1200)
	{
		this->setPosition(1200 - this->getGlobalBounds().width, this->getPosition().y);
	}
}