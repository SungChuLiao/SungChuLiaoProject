#pragma once

#include "paddle.h"

class PaddlePlayer : public Paddle
{
public:
	PaddlePlayer(int playerNumber);
	void Update();

private:
	int playerNumber;
};