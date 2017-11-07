#include "Obstacle.h"


Obstacle::Obstacle()
{
	this->Load("Rock.png");
	this->MovementY = 0;
	this->timer = 0;
	this->stopTime = false;
}
void Obstacle::Update()
{
	if (stopTime)
	{
		timer--;
		if (timer <= 0)
		{
			ReUpdate();
		}
	}
	if (this->getPosition().y < 150)
	{
		this->velocity.y *= -1;
	}
	if (this->getPosition().y + this->getGlobalBounds().height > 750)
	{
		this->velocity.y *= -1;
	}
	Object::Update();
}
void Obstacle::Stop()
{
	MovementY = this->velocity.y;
	this->velocity.y = 0;
	timer = 20.0f;
	stopTime = true;
}
void Obstacle::ReUpdate()
{
	stopTime = false;
	this->velocity.y = MovementY;
}
