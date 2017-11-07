#pragma once

#include "Paddle.h"
#include"Ball.h"
class PaddleAI : public Paddle
{
public:
	PaddleAI(int playerNumber);
	void SetBall(Ball* ballObject);
	void Update();

private:
	int playerNumber;
	Ball* ballObject;
};