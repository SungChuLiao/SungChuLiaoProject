#pragma once

#include "Object.h"

class Paddle : public Object
{
public:
	Paddle(float NewSpeed);
	void Update();
	float ExSpeed;
private:
	sf::Event event;
};