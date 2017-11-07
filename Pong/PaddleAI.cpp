#include "PaddleAI.h"


PaddleAI::PaddleAI(int playerNumber)
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
void PaddleAI::Update()
{
	if (ballObject->velocity.y > 0)
	{
		this->velocity.y = 0.7f;
	}
	if (ballObject->velocity.y < 0)
	{
		this->velocity.y = -0.7f;
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
void PaddleAI::SetBall(Ball* ballObject)
{
	this->ballObject = ballObject;
}