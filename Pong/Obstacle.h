#pragma once
#include"Object.h"

class Obstacle : public Object
{
public:
	Obstacle();
	void Update();
	void Stop();
	void ReUpdate();
private:
	float MovementY;
	float timer;
	bool stopTime;
};