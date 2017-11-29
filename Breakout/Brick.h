#pragma once

#include "Object.h"
#include "Score.h"
#include "Ball.h"
class Brick : public Object
{
public:
	Brick(int hp, Ball* ball, Score* myScore);
	void Update();
	void Draw(sf::RenderWindow *window);
	void GetHit();
	void MoreHP();
	void speedBall();
	bool isDead;
private:
	sf::SoundBuffer* bf;
	sf::Sound* sound;
	Score* myScore;
	sf::Color OriginalColor;
	Ball* ball;
	int hp;
	int Mode;
};
